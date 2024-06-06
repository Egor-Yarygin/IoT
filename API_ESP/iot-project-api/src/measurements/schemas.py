from pydantic import BaseModel
from datetime import datetime

class TemperatureValue(BaseModel):
    value: float
    location: str
    device_id: str
    timestamp: datetime

    class Config:
        orm_mode = True
