from fastapi import FastAPI
from measurements.router import router as measurements_router

app = FastAPI()

app.include_router(measurements_router)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run("main:app", host="192.168.0.103", port=8005, reload=True)
