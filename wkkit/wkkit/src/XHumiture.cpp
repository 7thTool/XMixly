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
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_evtCheck = 0;
	_tempSensitive = 1;
	_humiSensitive = 1;
	_preHumidity = 999;
	_preTemperature = 999;
#endif
}

#ifdef XBRIDGE_SUPPORT
int8_t XHumiture::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XHumiture::onAccess()");
	(void)param; (void)psize;
	
    if (api == XHumiture_API_getHumidity) {
        result = fillFloat(result, getHumidity());
        *rsize = 4;
    }else if (api == XHumiture_API_getTemperature) {
        result = fillFloat(result, getTemperature());
        *rsize = 4;		
    } else {
        *rsize = 0;
        return -1;
    }

    return 0;
}
#endif // XBRIDGE_SUPPORT

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


#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XHumiture::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XHumiture::onNotifyRegister()");
	(void)psize;

	if (evt == XHumiture_EVT_Temperature_Change) {
		_evtMask |= XHumiture_EVT_Temperature_Change;
		fetchFloat(param, &_tempSensitive);
		_preTemperature = getTemperature();
		fillFloat(result, _preTemperature);
		*rsize = 4;
	} else if (evt == XHumiture_EVT_Humidity_Change) {
		_evtMask |= XHumiture_EVT_Humidity_Change;
		fetchFloat(param, &_humiSensitive);
		_preHumidity = getHumidity();
		fillFloat(result, _preHumidity);
		*rsize = 4;
	}
	return 0;
}

int8_t XHumiture::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	float diff;
	LOGN("XHumiture::onNotifyRegister()");

	if (_evtCheck == 0) {
		_evtCheck = _evtMask;
	}

	if (_evtCheck & XHumiture_EVT_Temperature_Change) {
		float temperature = getTemperature();
		diff = (_preTemperature > temperature) ?
				(_preTemperature - temperature) :
				(temperature - _preTemperature);
		if (diff >= _tempSensitive) {
			_preTemperature = temperature;
			fillFloat(result, temperature);
			*evt = XHumiture_EVT_Temperature_Change;
			*rsize = 4;
			_evtCheck &= ~XHumiture_EVT_Temperature_Change;
			return _evtCheck;
		}
	} else if (_evtCheck & XHumiture_EVT_Humidity_Change) {
		float humidity = getHumidity();
		diff = (_preHumidity > humidity) ?
				(_preHumidity - humidity) :
				(humidity - _preHumidity);
		if (diff >= _humiSensitive) {
			_preHumidity = humidity;
			fillFloat(result, humidity);
			*evt = XHumiture_EVT_Humidity_Change;
			*rsize = 4;
			_evtCheck &= ~XHumiture_EVT_Humidity_Change;
			return _evtCheck;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY


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
