from sqlalchemy import Column, Integer, String, Float, DateTime
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class Measurement(Base):
    __tablename__ = "measurements"

    id = Column(Integer, primary_key=True, index=True)
    value = Column(Float, nullable=False)
    location = Column(String, index=True)
    device_id = Column(String, index=True)
    timestamp = Column(DateTime, nullable=False)
