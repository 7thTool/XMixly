/* XButton.cpp
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
 *     This file is a driver for Button module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XButton.h>

#define XBUTTON_3C_NAME		"BTN"

#define BTN3000_MODEL_NAME "BTN3000"
#define BTN3300_MODEL_NAME "BTN3300"

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XButton::XButton():
        XNBlock(),
		_portId(-1),
		_pin(0xFF),
		_knocked(0)
{
	LOGN("XButton::XButton()");
}

XButton::~XButton()
{
	LOGN("XButton::~XButton()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XButton::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XButton::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_A1, &pmap);
	if (_portId >= 0) {
		_pin = pmap.plat.io.A1.pin;
		pinMode(_pin, INPUT);
	} else{
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XButton::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XButton::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap)) {
		_pin = pmap.plat.io.A1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

void XButton::reset()
{
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_status = 0xFF;
#endif
}

#define BTN3200_HIGH_THRESHOLD 100

uint8_t XButton::isPressed()
{
	//LOGN("XButton::isPressed()");

	if (_pin == 0xFF) {
		return 0;
	}

	return (analogRead(_pin) > BTN3200_HIGH_THRESHOLD) ? 0 : 1;
}

uint8_t XButton::isKnocked()
{
	int value = 0;

	//LOGN("XButton::isKnocked()");

	if (_pin == 0xFF) {
		return 0;
	}

	value = analogRead(_pin);
	if (_knocked == 0) {
		if (value < BTN3200_HIGH_THRESHOLD) {
			_knocked = 1;
			return 1;
		}
	} else {
		if (value >= BTN3200_HIGH_THRESHOLD) {
			_knocked = 0;
		}
	}
	
	return 0;	
}

#ifdef XBRIDGE_SUPPORT
int8_t XButton::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XButton::onAccess()");
	(void)param; (void)psize;

    if (api == XButton_API_isPressed) {
        result = fillU8(result, isPressed());
        *rsize = 1;
	} else if (api == XButton_API_isKnocked) {
        result = fillU8(result, isKnocked());
        *rsize = 1;
    } else {
        *rsize = 0;
        return -1;
    }

    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XButton::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XButton::onNotifyRegister()");
	(void)param; (void)psize;
	(void)evt;

	//if (evt & XButton_EVT_Change) {
		_evtMask |= XButton_EVT_Change;
		_status = isPressed();
		fillU8(result, _status);
		*rsize = 1;
	//}
	return 0;
}

int8_t XButton::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint8_t status;

	LOGN("XButton::onNotifyCheck()");
	(void)result;

	if (_evtMask & XButton_EVT_Change) {
		status = isPressed();
		if (status != _status) {
			_status = status;
			*evt = XButton_EVT_Change;
			fillU8(result, status);
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT