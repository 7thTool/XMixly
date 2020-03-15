/* XShockSensor.cpp
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
 *     This file is a driver for shock sensor module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XShockSensor.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XShockSensor::XShockSensor() :
	XNBlock(),
	_portId(-2)
{
}

XShockSensor::~XShockSensor()
{
	LOGN("XShockSensor::~XShockSensor()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XShockSensor::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XShockSensor::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
	if (_portId >= 0) {
		_pin = pmap.plat.io.D1.pin;
        pinMode(_pin, INPUT);
	} else {
		LOGN("PortSetup() failed");
		_portId = -2;
		return -1;
	}

	reset();
	return 0;
}

int XShockSensor::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XShockSensor::setup(");LOG(label);LOGN(")");

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

void XShockSensor::reset()
{
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_status = 0xFF;
#endif
}


uint8_t XShockSensor::isShocking()
{
	LOGN("XShockSensor::isShocking()");

	if (_portId == -2) {
		LOGN("XShockSensor not setup");
		return 0x00;
	}

	return digitalRead(_pin);
}
#ifdef XBRIDGE_SUPPORT
int8_t XShockSensor::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XShockSensor::onAccess()");
	(void)param; (void)psize;
	
    if (api == XShockSensor_API_isShocking) {
        result = fillU8(result, isShocking());
        *rsize  = 1;
    } else {
        *rsize = 0;
        return -1;
    }
    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XShockSensor::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XShockSensor::onNotifyRegister()");
	(void)param; (void)psize;
	(void)evt;

	//if (evt == XShockSensor_EVT_Change) {
		_evtMask |= XShockSensor_EVT_Change;
		_status = isShocking();
		fillU8(result, _status);
		*rsize = 1;
	//}
	return 0;
}

int8_t XShockSensor::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint8_t status;
	LOGN("XShockSensor::onNotifyCheck()");

	if (_evtMask & XShockSensor_EVT_Change) {
		status = isShocking();
		if (status != _status) {
			_status = status;
			fillU8(result, status);
			*evt = XShockSensor_EVT_Change;
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT
