/* XPIR.cpp
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
 *     This file is a driver for human motion detected module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XPIR.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XPIR::XPIR() :
	XNBlock(),
	_portId(-2)
{
}

XPIR::~XPIR()
{
	LOGN("XPIR::~XPIR()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XPIR::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XPIR::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
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

int XPIR::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XPIR::setup(");LOG(label);LOGN(")");

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

void XPIR::reset()
{
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_status = 0xFF;
#endif
}


uint8_t XPIR::isHumanMotionDetected()
{
	LOGN("XPIR::isHumanMotionDetected()");

	if (_portId == -2) {
		LOGN("XPIR not setup");
		return 0x00;
	}

	return digitalRead(_pin);
}

#ifdef XBRIDGE_SUPPORT
int8_t XPIR::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XPIR::onAccess()");
	(void)param; (void)psize;
	
    if (api == XPIR_API_isHumanMotionDetected) {
        result = fillU8(result, isHumanMotionDetected());
        *rsize  = 1;
    } else {
        *rsize = 0;
        return -1;
    }
    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XPIR::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XPIR::onNotifyRegister()");
	(void)param; (void)psize;
	(void)evt;

	//if (evt == XPIR_EVT_Change) {
		_evtMask |= XPIR_EVT_Change;
		_status = isHumanMotionDetected();
		fillU8(result, _status);
		*rsize = 1;
	//}
	return 0;
}

int8_t XPIR::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint8_t status;
	LOGN("XPIR::onNotifyCheck()");

	if (_evtMask & XPIR_EVT_Change) {
		status = isHumanMotionDetected();
		if (status != _status) {
			_status = status;
			fillU8(result, status);
			*evt = XPIR_EVT_Change;
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT
