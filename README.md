# BTD - Bedside Table Display

Aim of the project is to create small device with display that is place on bedside table and present time, temperature and air quality info fetched from remote server and more.

## Features

* limited brightness/contrast control of OLED screen using photoresistor
  * SSD1306 has very limited output voltage control so only 2 stages: max and min with threshold on ambient light perceived by myself as dark
* time display with NTP source
* IR control of what's displayed on screen (TBD) 
* local temperature reading (TBD) and upload to InfluxDB (TBD)
* presnetation of data from Lufdaten Air Monitor (TBD)
  * [blog post about this data source](https://blog.dsinf.net/2019/01/budowa-stacji-pogody-z-czujnikiem-smogu-i-prezentacja-danych/)

## Hardware

It's based on aruino style packed ESP8266, a microcontroller with WiFi stack and OLED display. More info like schematics and BOM in [hw directory](https://github.com/danielskowronski/btd/tree/master/hw).

You may be interested in [Altium CircuitMaker project page](https://workspace.circuitmaker.com/Projects/Details/danielskowronski/btd).

## Demo
![](hw/btd.png?raw=true)