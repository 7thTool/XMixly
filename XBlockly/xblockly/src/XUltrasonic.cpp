/* XUltrasonic.cpp
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
 *     This file is a driver for Ultrasonic module.
 *
 * Version: 1.0.0
 */

#include <arduino.h>
#include <xport.h>
#include <XUltrasonic.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XUltrasonic::XUltrasonic()
{
	_portId = -1;
	_echoPin = 0xFF;
	_triggerPin = 0xFF;
	_lastMeasureTime = 0ul;
	_dis = 0;
}

XUltrasonic::~XUltrasonic()
{
	LOGN("XUltrasonic::~XUltrasonic()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XUltrasonic::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XUltrasonic::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

    _portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
    if (_portId >= 0) {
        _triggerPin = pmap.plat.io.D2.pin1;
		_echoPin = pmap.plat.io.D2.pin2;
		pinMode(_triggerPin, OUTPUT);
		pinMode(_echoPin, INPUT);
    } else {
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XUltrasonic::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XUltrasonic::setup(");LOG(label);LOGN(")");
		
	if (PortOnBoardSetup(label, model, &pmap)) {
        _triggerPin = pmap.plat.io.D2.pin1;
		_echoPin = pmap.plat.io.D2.pin2;
		pinMode(_triggerPin, OUTPUT);
		pinMode(_echoPin, INPUT);
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XUltrasonic::setup(const char *model, const uint8_t trigger, const uint8_t echo)
{
	(void)model;

    _triggerPin = trigger;
	_echoPin = echo;
	pinMode(_triggerPin, OUTPUT);
	pinMode(_echoPin, INPUT);

	reset();
	return 0;
}

void XUltrasonic::reset()
{
	_lastMeasureTime = millis();
	_dis = 0;
}

#define PULSE_TIMEOUT 22000L	

uint16_t XUltrasonic::getDistance()
{
	unsigned long t;

	LOGN("XUltrasonic::getDistance()");

	if (_echoPin == 0xFF) {
		LOGN("XUltrasonic not setup");
		return 0;
	}
	if(millis() - _lastMeasureTime > 20ul) {
		digitalWrite(_triggerPin, 0);
		delayMicroseconds(2);

		digitalWrite(_triggerPin, 1);
		delayMicroseconds(10);

		digitalWrite(_triggerPin, 0);
		//delayMicroseconds(2);

		t = pulseIn(_echoPin, HIGH, PULSE_TIMEOUT);
		//_dis = (uint16_t)((t * 1000) / 5882);
		_dis = (uint16_t)((t * 1000) / 5800);
		LOG("dis=");LOGN(dis);

		_lastMeasureTime = millis();
	}

	if ((_dis > XULS_MAX_MEASURE_DIS) || (_dis < 10)) {
		_dis = 9999; //1cm-250cm is valid measure distance
	}
    return _dis;
}
