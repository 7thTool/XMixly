/* XDualDCMotor.cpp
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
 *     This file is a driver for DualDCMotor module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XDualDCMotor.h>
#include <DDM3001Impl.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XDualDCMotor::~XDualDCMotor() 
{
	LOGN("XDualDCMotor::~XDualDCMotor()");

	reset();

	if (impl) {
		delete (DDM3001Impl *)impl;
		impl = NULL;
	}

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XDualDCMotor::setup(const char *model, const char *port)
{
	PortMap pmap;
	
	LOG("XDualDCMotor::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	impl = new DDM3001Impl(model);
	if (!impl) {
		LOGN("new DDM3001Impl failed");
		return -1;
	}

	_portId = PortSetup(port, XPORT_FUNC_I2C, &pmap);
	if (_portId >= 0) {
		((DDM3001Impl *)impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	} else{
		LOGN("PortSetup() failed!");
		free(impl);
		return -1;
	}

	_speed1 = 0;
	_speed2 = 0;

	return 0;
}

int XDualDCMotor::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XDualDCMotor::setup(");LOG(label);LOGN(")");
	
	if(PortOnBoardSetup(label, model, &pmap)) {
		impl = new DDM3001Impl(model);
		if (!impl) {
			LOGN("new DDM3001Impl failed");
			return -1;
		}
		((DDM3001Impl *)impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	_speed1 = 0;
	_speed2 = 0;

	return 0;
}

void XDualDCMotor::reset()
{
	stopAllMotor();
}

void XDualDCMotor::setMotorSpeed(uint8_t motor, int8_t speed)
{
	LOG("XDualDCMotor::setMotorSpeed(");LOG(motor);LOG(",");LOG(speed);LOGN(")");

	if (impl) {
		if ((motor != 1) && (motor != 2)) {
			return;
		}
		speed = (speed > 100) ? 100 : ((speed < -100) ? -100 : speed);

		if(((motor == 1) && (_speed1 == speed))
			|| ((motor == 2) && (_speed2 == speed))) 
		{
			return;
		}
#if 1
		if (motor == 1) {
			((DDM3001Impl *)impl)->setAllSpeed(1, 1);
			((DDM3001Impl *)impl)->setAllSpeed(speed, _speed2);
		} else {
			((DDM3001Impl *)impl)->setAllSpeed(1, 1);
			((DDM3001Impl *)impl)->setAllSpeed(_speed1, speed);
		}
#else
		((DDM3001Impl *)impl)->setMotorSpeed(motor, speed);
#endif

		if(motor == 1) {
			_speed1 = speed;
		} else {
			_speed2 = speed;
		}
	}
}

void XDualDCMotor::setAllSpeed(int8_t speed1, int8_t speed2)
{
	LOGN("XDualDCMotor::setAllSpeed(");LOG(speed1);LOG(",");LOG(speed2);LOGN(")");
		
	if (impl) {
		speed1 = (speed1 > 100) ? 100 : ((speed1 < -100) ? -100 : speed1);
		speed2 = (speed2 > 100) ? 100 : ((speed2 < -100) ? -100 : speed2);

		if((_speed1 == speed1) && (_speed2 == speed2))
		{
			return;
		}

		if(_speed1 == speed1)
		{
			setMotorSpeed(2, speed2);
		}
		else if(_speed2 == speed2)
		{
			setMotorSpeed(1, speed1);
		}
		else
		{
			if (!((speed1 == 0) && (speed2 == 0))) { // workaround
				((DDM3001Impl *)impl)->setAllSpeed(1, 1);
			}
			((DDM3001Impl *)impl)->setAllSpeed(speed1, speed2);
			_speed1 = speed1;
			_speed2 = speed2;
		}
	}
}

void XDualDCMotor::stopMotor(uint8_t motor)
{
	LOGN("XDualDCMotor::stopMotor(");LOG(motor);LOGN(")");

	if(((motor == 1)&&(_speed1 == 0))
		|| ((motor == 2)&&(_speed2 == 0)))
	{
		return;
	}

	if (impl) {
		if ((motor != 1) && (motor != 2)) {
			return;
		}
		((DDM3001Impl *)impl)->setMotorSpeed(motor, 0);
		
		if(motor == 1) {
			_speed1 = 0;
		} else {
			_speed2 = 0;
		}
	}
}

void XDualDCMotor::stopAllMotor()
{
	LOGN("XDualDCMotor::stopAllMotor()");

	if((_speed1 == 0) && (_speed2 == 0)) {
		return;
	}

	if (impl) {
		if(_speed1 == 0)
		{
			stopMotor(2);
		}
		else if(_speed2 == 0)
		{
			stopMotor(1);
		}
		else
		{
			((DDM3001Impl *)impl)->setAllSpeed(0, 0);
			_speed1 = 0;
			_speed2 = 0;
		}
	}
}

