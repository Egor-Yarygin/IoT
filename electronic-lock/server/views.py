from fastapi import APIRouter, Request, Form, Depends, HTTPException
from fastapi.responses import HTMLResponse, JSONResponse, RedirectResponse
from fastapi.templating import Jinja2Templates
import mysql.connector
from passlib.context import CryptContext

router = APIRouter()
pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

db_config = {
    'host': 'localhost',
    'user': 'root',
    'password': 'Turbobots152361_',
    'database': 'log_db'
}

def get_db_connection():
    try:
        connection = mysql.connector.connect(**db_config)
        return connection
    except mysql.connector.Error as e:
        raise HTTPException(status_code=500, detail=str(e))

templates = Jinja2Templates(directory="templates")

global_uid = None  # Глобальная переменная для хранения UID

@router.get("/")
async def root():
    return RedirectResponse(url="/actions")

@router.get("/data", response_class=HTMLResponse)
async def index(request: Request, db_connection=Depends(get_db_connection)):
    if "user" not in request.session or not request.session.get("user"):
        return RedirectResponse(url="/login")
    
    ueid = request.session.get("ueid")
    if not ueid:
        return RedirectResponse(url="/login")

    cursor = db_connection.cursor()
    cursor.execute("SELECT id, uid, user, permission FROM rfid_keys WHERE ueid=%s", (ueid,))
    data = cursor.fetchall()
    cursor.close()
    db_connection.close()
    
    return templates.TemplateResponse("index.html", {"request": request, "data": data})

@router.get("/uid")
async def get_data(db_connection=Depends(get_db_connection)):
    cursor = db_connection.cursor()
    cursor.execute("SELECT uid FROM rfid_keys WHERE permission = 'YES'")
    data = cursor.fetchall()
    cursor.close()
    db_connection.close()

    return JSONResponse({"uid": [row[0] for row in data]})

@router.post("/api/uid")
async def api_uid(uid: str = Form(...)):
    global global_uid
    global_uid = uid
    return JSONResponse(status_code=200, content={"message": "UID received"})

@router.get("/create", response_class=HTMLResponse)
async def create_form(request: Request):
    if "user" not in request.session or not request.session.get("user"):
        return RedirectResponse(url="/login")
    global global_uid
    uid = global_uid if global_uid else ""
    return templates.TemplateResponse("create.html", {"request": request, "uid": uid})

@router.post("/create")
async def create(request: Request, uid: str = Form(...), user: str = Form(...), permission: str = Form(...), db_connection=Depends(get_db_connection)):
    if not uid or not user or not permission:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Все поля должны быть заполнены.'})
    
    if permission.upper() not in ['YES', 'NO']:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Значение для Permission должно быть либо "YES", либо "NO".'})

    # Получение ueid из сессии
    ueid = request.session.get("ueid")
    if not ueid:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Не удалось получить ueid.'})

    cursor = db_connection.cursor()
    cursor.execute("INSERT INTO rfid_keys (uid, user, permission, ueid) VALUES (%s, %s, %s, %s)", 
                   (uid, user, permission, ueid))
    db_connection.commit()
    cursor.close()
    db_connection.close()
    
    return RedirectResponse(url="/data", status_code=302)

@router.get("/edit/{id}", response_class=HTMLResponse)
async def edit_form(id: int, request: Request, db_connection=Depends(get_db_connection)):
    if "user" not in request.session or not request.session.get("user"):
        return RedirectResponse(url="/login")
    cursor = db_connection.cursor()
    cursor.execute("SELECT id, uid, user, permission FROM rfid_keys WHERE id=%s", (id,))
    user_data = cursor.fetchone()
    cursor.close()
    db_connection.close()
    
    if user_data is None:
        raise HTTPException(status_code=404, detail="Пользователь не найден")
    
    return templates.TemplateResponse("edit.html", {"request": request, "user_data": user_data})

@router.post("/edit/{id}")
async def edit(id: int, uid: str = Form(...), user: str = Form(...), permission: str = Form(...), db_connection=Depends(get_db_connection)):
    if not uid or not user or not permission:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Все поля должны быть заполнены.'})
    
    if permission.upper() not in ['YES', 'NO']:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Значение для Permission должно быть либо "YES", либо "NO".'})
    
    cursor = db_connection.cursor()
    cursor.execute("UPDATE rfid_keys SET uid=%s, user=%s, permission=%s WHERE id=%s", 
                   (uid, user, permission, id))
    db_connection.commit()
    cursor.close()
    db_connection.close()
    
    return RedirectResponse(url="/data", status_code=302)

@router.post("/delete")
async def delete(id: int = Form(...), db_connection=Depends(get_db_connection)):
    cursor = db_connection.cursor()
    cursor.execute("DELETE FROM rfid_keys WHERE id=%s", (id,))
    db_connection.commit()
    cursor.close()
    db_connection.close()
    
    return RedirectResponse(url="/data", status_code=302)

@router.get("/current_uid")
async def current_uid():
    global global_uid
    return JSONResponse({"uid": global_uid})

@router.post("/register")
async def register(username: str = Form(...), ueid: str = Form(...), password: str = Form(...), db_connection=Depends(get_db_connection)):
    # Проверка на пустые поля
    if not username or not ueid or not password:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'All fields must be filled.'})

    # Проверка на уникальность ueid
    cursor = db_connection.cursor()
    cursor.execute("SELECT * FROM admin_device WHERE ueid=%s", (ueid,))
    existing_device = cursor.fetchone()

    if existing_device:
        cursor.close()  # Закрыть курсор
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Device with this UEID already exists.'})

    # Хеширование пароля
    hashed_password = pwd_context.hash(password)

    # Добавление пользователя в базу данных
    cursor.execute("INSERT INTO admin_device (admin_name, ueid, password) VALUES (%s, %s, %s)", (username, ueid, hashed_password))
    db_connection.commit()
    
    cursor.close()  # Закрыть курсор
    db_connection.close()  # Закрыть соединение

    return JSONResponse(status_code=201, content={'success': True, 'message': 'User registered successfully'})

@router.get("/register", response_class=HTMLResponse)
async def register_form(request: Request):
    return templates.TemplateResponse("register.html", {"request": request})

@router.post("/login")
async def login(request: Request, username:  str = Form(...), password: str = Form(...), db_connection=Depends(get_db_connection)):
    # Проверка на пустые поля
    if not username or not password:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'All fields must be filled.'})

    # Поиск пользователя по username
    cursor = db_connection.cursor()
    cursor.execute("SELECT password, ueid FROM admin_device WHERE admin_name=%s", (username,))
    user = cursor.fetchone()
    cursor.close()

    if not user:
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Invalid username or password'})

    # Сравнение введенного пароля с хэшированным паролем
    if not pwd_context.verify(password, user[0]):
        return JSONResponse(status_code=400, content={'success': False, 'message': 'Invalid username or password'})
    
    request.session["user"] = username
    request.session["ueid"] = user[1]
    db_connection.close()

    return RedirectResponse(url="/data", status_code=302)

@router.get("/logout")
async def logout(request: Request):
    request.session.clear()
    return RedirectResponse(url="/login")

@router.get("/login", response_class=HTMLResponse)
async def login_form(request: Request):
    return templates.TemplateResponse("login.html", {"request": request})

@router.get("/actions", response_class=HTMLResponse)
async def actions(request: Request):
    return templates.TemplateResponse("actions.html", {"request": request})