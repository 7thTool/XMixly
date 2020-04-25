/* XHumiture.cpp
 *
 * Copyright (C) 2017-2022 Shanghai Mylecon Electronic Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 * Description: 
 *     This file is a driver for Humidity&Temperature emodule.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XHumiture.h>

#define DHTLIB_ERROR_TIMEOUT 4

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XHumiture::XHumiture() :
	XNBlock(),
	_portId(-1),
	_pin(0xFF)
{
}

XHumiture::~XHumiture()
{
	LOGN("XHumiture::~XHumiture()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XHumiture::setup(const char *model, const char *port)
{
	PortMap pmap;
	unsigned long bootTime;

	LOG("XHumiture::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	bootTime = millis();
	if(bootTime < 1500) 
		delay(1500 - bootTime);

	_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
	if (_portId >= 0) {
		_pin = pmap.plat.io.D1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XHumiture::setup(const char *label)
{
	PortMap pmap;
	char model[8];
	unsigned long bootTime;

	LOG("XHumiture::setup(");LOG(label);LOGN(")");
	
	bootTime = millis();
	if(bootTime < 1500) 
		delay(1500 - bootTime);

	if(PortOnBoardSetup(label, model, &pmap)) {
		_pin = pmap.plat.io.D1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortOnBoardSetup() failed!");
		return -1;
	}

	reset();
	return 0;
}

void XHumiture::reset()
{
	_lastHumidity = 0;
	_lastTemperature = 0;
}

float XHumiture::getHumidity()
{
	update();
	return _lastHumidity;
}

float XHumiture::getTemperature ()
{
	update();
	return _lastTemperature;
}

void XHumiture::update()
{
  uint8_t data[5] = {0};
  unsigned long Time, datatime;

  pinMode(_pin,OUTPUT);
  digitalWrite(_pin,HIGH);
  delay(250);

  digitalWrite(_pin,LOW);
  delay(20);
  
  digitalWrite(_pin,HIGH);
  delayMicroseconds(40);
  digitalWrite(_pin,LOW);

  delayMicroseconds(10);
  Time = millis();
  
  pinMode(_pin,INPUT_PULLUP);
  while(digitalRead(_pin) != HIGH)
  {
    if( ( millis() - Time ) > DHTLIB_ERROR_TIMEOUT)
    {
      _lastHumidity = 0;
      _lastTemperature = 0;
      break;
    }
  }

  Time = millis();
  
  pinMode(_pin,INPUT_PULLUP);
  while(digitalRead(_pin) != LOW)
  {
    if( ( millis() - Time ) > DHTLIB_ERROR_TIMEOUT)
    {
      break;
    }
  }

  for(int16_t i=0;i<40;i++)
  {
  	Time = millis();
    pinMode(_pin,INPUT_PULLUP);
    while(digitalRead(_pin) == LOW)
    {
      if( ( millis() - Time ) > DHTLIB_ERROR_TIMEOUT)
      {
        break;
      }
    }

    datatime = micros();
    Time = millis();

    pinMode(_pin,INPUT_PULLUP);
    while(digitalRead(_pin) == HIGH)
    {
      if( ( millis() - Time ) > DHTLIB_ERROR_TIMEOUT )
      {
        break;
      }
    }

    if ( micros() - datatime > 40 )
    {
      data[i/8] <<= 1;
      data[i/8] |= 0x01;
    }
    else
    {
      data[i/8] <<= 1;
    }
  }
   
  if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
  {
	_lastHumidity = data[0];
	_lastTemperature = data[2];
  }
}
