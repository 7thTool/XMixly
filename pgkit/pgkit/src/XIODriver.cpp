/* XIODriver.cpp
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
 *     This file is a driver for IODriver module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XIODriver.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XIODriver::XIODriver() :
	XNBlock(),
	_portId(-2)
{
}

XIODriver::~XIODriver()
{
	LOGN("XIODriver::~XIODriver()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XIODriver::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XIODriver::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
	if (_portId >= 0) {
		_pin1 = pmap.plat.io.D2.pin1;
		_pin2 = pmap.plat.io.D2.pin2;
        pinMode(_pin1, INPUT);
		pinMode(_pin2, INPUT);
	} else {
		_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
		if (_portId >= 0) {
			_pin1 = pmap.plat.io.D1.pin;
			pinMode(_pin1, INPUT);
		} else {
			LOGN("PortSetup() failed");
			_portId = -2;
			return -1;
		}
	}

	reset();
	return 0;
}

int XIODriver::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XIODriver::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap))
	{
		_pin1 = pmap.plat.io.D2.pin1;
		_pin2 = pmap.plat.io.D2.pin2;
        pinMode(_pin1, INPUT);
		pinMode(_pin2, INPUT);
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

void XIODriver::reset()
{
}



uint8_t XIODriver::digitalRead(uint8_t sno)
{
	uint8_t status = 0x00;

	LOGN("XIODriver::digitalRead()");

	if (_portId == -2) {
		LOGN("XIODriver not setup");
		return 0x00;
	}

	if(sno == 1) {
		pinMode(_pin1, INPUT);
		status = ::digitalRead(_pin1);
	} else {
		pinMode(_pin2, INPUT);
		status = ::digitalRead(_pin2);
	}

	return status;

}

void XIODriver::digitalWrite(uint8_t sno, uint8_t value)
{

	LOGN("XIODriver::digitalWrite()");

	if (_portId == -2) {
		LOGN("XIODriver not setup");
		return;
	}

	if(sno == 1) {
		pinMode(_pin1, OUTPUT);
		::digitalWrite(_pin1, value);
	} else {
		pinMode(_pin2, OUTPUT);
		::digitalWrite(_pin2, value);
	}

}

int32_t XIODriver::analogRead(uint8_t sno)
{
	int32_t avalue = 0;

	LOGN("XIODriver::analogRead()");

	if (_portId == -2) {
		LOGN("XIODriver not setup");
		return 0;
	}

	if(sno == 1) {
		pinMode(_pin1, INPUT);
		avalue = ::analogRead(_pin1);
	} else {
		pinMode(_pin2, INPUT);
		avalue = ::analogRead(_pin2);
	}

	return avalue;

}


