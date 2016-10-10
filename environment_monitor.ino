/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 
 Connection:
 VCC-3.3v
 GND-GND
 SCL-SCL(analog pin 5)
 SDA-SDA(analog pin 4)
 BH1750 ADD-NC or GND
 BME280 SDO 10k resistor to VCC 3.3V
 
 
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  
  Serial.println(F("BME280 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println(F("BH1750 test"));
  lightMeter.begin();
  
  Serial.println("temperature,light,pressure,humidity,altitude");
  Serial.println(" *C, lux, hPa, %, m above see level");
}

void loop() {
  
    double temperature, pressure, altitude, humidity, light;
    uint16_t lux;
    
    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    humidity = bme.readHumidity();
    
    lux = lightMeter.readLightLevel();
    
    Serial.print(temperature);
    Serial.print(",");
    Serial.print(lux);
    Serial.print(",");
    Serial.print(pressure);
    Serial.print(",");
    Serial.print(humidity);
    Serial.print(",");
    Serial.print(altitude);
    Serial.println(",");
    
    // once every 10 seconds
    delay(5000);
    delay(5000);
}
