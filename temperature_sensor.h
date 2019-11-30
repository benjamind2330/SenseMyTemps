#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>


class ITemperatureSensor {

  public:
    virtual float getTemp() const = 0;
  
};


class Thermometer : public ITemperatureSensor {
  public:

      Thermometer(int pin) :
        oneWire_(pin),
        sensor_(&oneWire_)
      {
        sensor_.begin();
      }

      float getTemp() const {
        sensor_.requestTemperatures();
        return sensor_.getTempCByIndex(sensorAddress_);
      }

  private:

    size_t sensorAddress_ = 0;
    OneWire oneWire_;
    mutable DallasTemperature sensor_; 
};
