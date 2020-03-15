/* XDCMotor.cpp
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
 *     This file is a driver for DCMotor module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XDCMotor.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XDCMotor::~XDCMotor() 
{
	LOGN("XDCMotor::~XDCMotor()");

	reset();

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XDCMotor::setup(const char *model, const char *port)
{
	PortMap pmap;
	
	LOG("XDCMotor::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_DP, &pmap); //first use D+P to control, it can update speed value
	if (_portId >= 0) {
		_pwmPin = pmap.plat.io.DP.pinP; //pmap.plat.io.D2.pin1;
		_dirPin = pmap.plat.io.DP.pinD; //pmap.plat.io.D2.pin2;
		pinMode(_pwmPin, OUTPUT);
		pinMode(_dirPin, OUTPUT);
		_portType = 0;
	} else{
		_portId = PortSetup(port, XPORT_FUNC_D2, &pmap); //
		if (_portId >= 0) {
			_pwmPin = pmap.plat.io.D2.pin1;
			_dirPin = pmap.plat.io.D2.pin2;
			//_pwmPin = pmap.plat.io.D2.pin2;
			//_dirPin = pmap.plat.io.D2.pin1;
			pinMode(_pwmPin, OUTPUT);
			pinMode(_dirPin, OUTPUT);
			_portType = 1;
		} else{
			LOGN("PortSetup() failed!");
			return -1;
		}
	}

	return 0;
}

int XDCMotor::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XDCMotor::setup(");LOG(label);LOGN(")");
	
	if(PortOnBoardSetup(label, model, &pmap)) {
		_pwmPin = pmap.plat.io.DP.pinP; //pmap.plat.io.D2.pin1;
		_dirPin = pmap.plat.io.DP.pinD; //pmap.plat.io.D2.pin2;
		pinMode(_pwmPin, OUTPUT);
		pinMode(_dirPin, OUTPUT);
		_portType = 0;
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	return 0;
}

void XDCMotor::reset()
{
	stop();
}

void XDCMotor::start(int8_t speed)
{
	uint8_t data;

	data = constrain(abs(speed), 0, 100);
	data = map(data, 0, 100, 0, 255);
	
	LOG("XDCMotor::start(");LOG(",");LOG(speed);LOGN(")");

	if(speed > 0)
	{
		digitalWrite(_dirPin, HIGH);
		if(1 == _portType)
			digitalWrite(_pwmPin, HIGH);
		else
			analogWrite(_pwmPin, data);
	}
	else if(speed < 0)
	{
		digitalWrite(_dirPin, LOW);
		if(1 == _portType)
			digitalWrite(_pwmPin, HIGH);
		else
			analogWrite(_pwmPin, data);
	}
	else
	{
		stop();
	}
}

void XDCMotor::stop()
{
	LOGN("XDCMotor::stop()");
	digitalWrite(_pwmPin, LOW);
	digitalWrite(_dirPin, LOW);
}

#ifdef XBRIDGE_SUPPORT
#if 1
int8_t XDCMotor::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XDCMotor::onAccess(");LOG(api);LOGN(")");
	(void)psize; (void)result;

    if (api == XDCMotor_API_start) {
		int8_t speed;
		param = fetchU8(param, (uint8_t *)&speed);
		start(speed);
		*rsize = 0;
	}
	else if(api == XDCMotor_API_stop) {
		stop();
		*rsize = 0;
	}
	else {
		*rsize = 0;
		return -1;
	}
	return 0;
}
#endif
#endif // XBRIDGE_SUPPORT