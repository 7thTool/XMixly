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


XUltrasonic::XUltrasonic() :
	XNBlock(),
	_portId(-1),
	_echoPin(0xFF),
	_triggerPin(0xFF),
	_lastMeasureTime(0ul),
	_dis(0)
{
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

void XUltrasonic::reset()
{
	_lastMeasureTime = millis();
	_dis = 0;
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_sensitive = 5;
	_preDis = 0xFFFF;
#endif
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

#ifdef XBRIDGE_SUPPORT
int8_t XUltrasonic::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XUltrasonic::onAccess()");
	(void)param; (void)psize;

    if (api == XUltrasonic_API_getDistance) {
       result = fillU16(result, getDistance());
	   *rsize = 2;
    } else {
		*rsize = 0;
        return -1;
    }

    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XUltrasonic::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XUltrasonic::onNotifyRegister()");
	(void)psize;
	(void)evt;

	//if (evt == XUltrasonic_EVT_Change) {
		_evtMask |= XUltrasonic_EVT_Change;
		fetchU16(param, &_sensitive);
		_preDis = getDistance();
		fillU16(result, _preDis);
		*rsize = 2;
	//}
	return 0;
}

int8_t XUltrasonic::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint16_t diff;

	LOGN("XUltrasonic::onNotifyCheck()");

	if (_evtMask & XUltrasonic_EVT_Change) {
		getDistance();
		diff = (_dis > _preDis) ? (_dis - _preDis) : (_preDis - _dis);
		if (diff >= _sensitive) {
			_preDis = _dis;
			*evt = XUltrasonic_EVT_Change;
			fillU16(result, _dis);
			*rsize = 2;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT