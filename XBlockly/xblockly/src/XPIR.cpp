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


XPIR::XPIR()
{
	_portId = -1;
	_pin = 0xFF;
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

int XPIR::setup(const char *model, const uint8_t sta)
{
	(void)model;

	_pin = sta;
    pinMode(_pin, INPUT);

	reset();
	return 0;
}

void XPIR::reset()
{
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





