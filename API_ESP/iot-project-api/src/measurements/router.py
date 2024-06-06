from fastapi import APIRouter, Depends, HTTPException
from fastapi.responses import RedirectResponse
from sqlalchemy.orm import Session
from database import SessionLocal, engine
from measurements import models, schemas
from datetime import datetime

models.Base.metadata.create_all(bind=engine)

router = APIRouter()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@router.get("/")
async def redirect_to_docs():
    return RedirectResponse(url="/docs")

@router.get("/temperature")
def get_temperature(location: str, db: Session = Depends(get_db)):
    measurements = db.query(models.Measurement).filter(models.Measurement.location == location).all()
    if not measurements:
        raise HTTPException(status_code=404, detail="No measurements found for this location")
    return {"values": [measurement.value for measurement in measurements], "location": location}

@router.post("/submit_temperature")
def submit_temperature(measurement: schemas.TemperatureValue, db: Session = Depends(get_db)):
    db_measurement = models.Measurement(
        value=measurement.value,
        location=measurement.location,
        device_id=measurement.device_id,
        timestamp=measurement.timestamp
    )
    db.add(db_measurement)
    db.commit()
    db.refresh(db_measurement)
    return {"status": "updated"}
