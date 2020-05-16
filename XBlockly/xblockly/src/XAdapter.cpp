/* XAdapter.cpp
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
 *     This file is a driver for Adapter module.
 *
 * Version: 1.0.0
 */



#include <Arduino.h>
#include <xport.h>
#include <XAdapter.h>


XAdapter::XAdapter()
{
	_portId = -1;
	_pin1 = 0xFF;
	_pin2 = 0xFF;
}

XAdapter::~XAdapter()
{
	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XAdapter::setup(const char *model, const char *port)
{
	PortMap pmap;

	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
	if (_portId >= 0) {
		_pin1 = pmap.plat.io.D2.pin1;
		_pin2 = pmap.plat.io.D2.pin2;
	} else{
		return -1;
	}

	return 0;
}

int XAdapter::setup(const char *model, const uint8_t pin1, const uint8_t pin2)
{
	(void)model;

	_pin1 = pin1;
	_pin2 = pin2;

	return 0;
}

uint16_t XAdapter::analogRead(uint8_t signal)
{
	uint8_t pin;

	if (_portId == -1) {
		return 0;
	}

	if (signal == ADP_PIN_S1) {
		pin = _pin1;
	} else if (signal == ADP_PIN_S2) {
		pin = _pin2;
	} else {
		return 0;
	}

	pinMode(pin, INPUT);

	return ::analogRead(pin);
}

uint8_t XAdapter::digitalRead(uint8_t signal)
{
	uint8_t pin;

	if (_portId == -1) {
		return 0;
	}

	if (signal == ADP_PIN_S1) {
		pin = _pin1;
	} else if (signal == ADP_PIN_S2) {
		pin = _pin2;
	} else {
		return 0;
	}

	pinMode(pin, INPUT);

	return ::digitalRead(pin);
}

void XAdapter::digitalWrite(uint8_t signal, uint8_t level)
{
	uint8_t pin;

	if (_portId == -1) {
		return;
	}

	if (signal == ADP_PIN_S1) {
		pin = _pin1;
	} else if (signal == ADP_PIN_S2) {
		pin = _pin2;
	} else {
		return;
	}

	pinMode(pin, OUTPUT);

	::digitalWrite(pin, level ? HIGH : LOW);
}
