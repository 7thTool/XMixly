/* XIRAvoiding.cpp
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
 *     This file is a driver for IR Avoiding module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XIRAvoiding.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

#define IRA3200_MODEL_NAME "IRA3200"
#define IRA3300_MODEL_NAME "IRA3300"
#define IRA3400_MODEL_NAME "IRA3400"


#define MODEL_IRA3200		1
#define MODEL_IRA3300		2  //IRA3400 is the same to IRA3300




XIRAvoiding::XIRAvoiding() :
	XNBlock(),
	_model(0),
	_portId(-2)
{
}

XIRAvoiding::~XIRAvoiding()
{
	LOGN("XIRAvoiding::~XIRAvoiding()");

	if (_portId >= 0) {
		stop();
		PortRelease(_portId);
	}
}

int XIRAvoiding::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XIRAvoiding::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	if (!strcmp(model, IRA3200_MODEL_NAME)) {
		_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
		if (_portId >= 0) {
			_pin = pmap.plat.io.D1.pin;
	        pinMode(_pin, INPUT);
		} else {
			LOGN("PortSetup() failed");
			_portId = -2;
			return -1;
		}
		_model = MODEL_IRA3200;
	} else if ((!strcmp(model, IRA3300_MODEL_NAME)) 
		|| (!strcmp(model, IRA3400_MODEL_NAME))) {
		_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
		if (_portId >= 0) {
			_pin = pmap.plat.io.D2.pin2;
			_enPin = pmap.plat.io.D2.pin1;
	        pinMode(_pin, INPUT);
			pinMode(_enPin, OUTPUT);
			digitalWrite(_enPin, LOW);
		} else {
			LOGN("PortSetup() failed");
			_portId = -2;
			return -1;
		}
		_model = MODEL_IRA3300;

		start(100);
	}

	reset();
	return 0;
}

int XIRAvoiding::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XIRAvoiding::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap))
	{
		_pin = pmap.plat.io.D1.pin;
        pinMode(_pin, INPUT);
		_portId = -1;
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		_portId = -2;
		return -1;
	}

	reset();
	return 0;
}

void XIRAvoiding::reset()
{
}

void XIRAvoiding::start(uint8_t sensitive)
{
	uint8_t hlvl_time;
	LOGN("XIRAvoiding::start()");

	if (_portId == -2) {
		LOGN("XIRAvoiding not setup");
		return;
	}

	if(_model == MODEL_IRA3300)
	{
		if(sensitive > 100)
		{
			sensitive = 100;
		}

		if (sensitive == 0)
		{
			hlvl_time = 2;  // 2 means close detects
		}
		else
		{
			hlvl_time = 100 - sensitive + 6;
		}
		
		digitalWrite(_enPin, HIGH);
		delay(hlvl_time);
		digitalWrite(_enPin, LOW);
		delay(2);                  
	}
}

void XIRAvoiding::stop()
{
	LOGN("XIRAvoiding::stop()");

	if (_portId == -2) {
		LOGN("XIRAvoiding not setup");
		return;
	}

	if(_model == MODEL_IRA3300)
	{
		digitalWrite(_enPin, HIGH);
		delay(2); // 2 means close detects
		digitalWrite(_enPin, LOW);
		delay(2);
	}
}

uint8_t XIRAvoiding::getStatus()
{
	LOGN("XIRAvoiding::getStatus()");

	if (_portId == -2) {
		LOGN("XIRAvoiding not setup");
		return 0x00;
	}

	return digitalRead(_pin) ? 0 : 1;
}

