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

