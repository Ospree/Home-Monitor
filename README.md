# Home-Monitor

This is my home monitoring and automation hobby project.

The application is distributed on 2 arduino boards. Arduino Nano with ATmega328P is doing the sensor reading and generating the data stream, uart 9600 baud strem. Arduino MEGA 256 with Ethernet shield (mini SD card) is used as datalogger. The MEGA is configured to use 2 serial ports, serial 0 is is configurad at 57600 baud and used as debug port, serial 1 is configured at 9600 baud and connected to the Nano. Sensor connected to Nano are BME-280 to measure temperature, humidity and pressure; BH1750 to measure light intensity. All sensors are supplied via 3.3V and connected via I2C. The nano is powered by the 5V of MEGA. The datalog is called LOGFILE.TXT.
