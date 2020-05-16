/* XServo.cpp
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
 *     This file is a driver for Servo module.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <xport.h>
#include <XServo.h>
#include <Servo.h>

#define XSERVO_3C_NAME "SVO"

#define SVO3000_MODEL_NAME "SVO3000"
#define SVO3210_MODEL_NAME "SVO3210"

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 360
#define SERVO_DEFAULT_ANGLE 0

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XServo::XServo()
{
	_portId = -1;
	_servo = NULL;
}

XServo::~XServo()
{
	LOGN("XServo::~XServo()");
	
	if(_servo){
		_servo->detach();
		delete _servo;
		_servo = NULL;
	}

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XServo::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XServo::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_P1, &pmap);
	if (_portId >= 0) {
		_servo = new Servo;
		if (_servo) {
			LOGN("new Servo failed");
			return -1;
		}
		_servo->attach(pmap.plat.io.P1.pin);
	} else {
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XServo::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XServo::setup(");LOG(label);LOGN(")");

	_portId = PortOnBoardSetup(label, model, &pmap);
	if(_portId > 0)
	{
		_servo = new Servo;
		if (!_servo) {
			LOGN("new Servo failed");
			return -1;
		}
		_servo->attach(pmap.plat.io.P1.pin);
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XServo::setup(const char *model, const uint8_t pinP)
{
	(void)model;

	_servo = new Servo;
	if (_servo) {
		LOGN("new Servo failed");
		return -1;
	}
	_servo->attach(pinP);

	reset();
	return 0;
}

void XServo::reset()
{
	if (_servo) {
		_servo->write(SERVO_DEFAULT_ANGLE);
	}
}

void XServo::setAngle(uint16_t angle)
{
	LOGN("XServo::setAngle():");
	LOG("angle = ");LOGN(angle);

	if (_servo) {
		//angle = constrain((int16_t)angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
		angle = angle % 360;
		_servo->write(angle);
	}
}

uint16_t XServo::getAngle()
{
	LOGN("XServo::getAngle()");

	if (_servo) {
		return _servo->read();
	} else {
		return 0;
	}
}