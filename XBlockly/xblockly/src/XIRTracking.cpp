/* XIRTracking.cpp
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
 *     This file is a driver for IR Tracking module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XIRTracking.h>
#include <XI2C.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

#define IRT3220_MODEL_NAME "IRT3220"
#define IRT3320_MODEL_NAME "IRT3320"
#define IRT3360_MODEL_NAME "IRT3360"

#define MODEL_CHANNELS_2		1
#define MODEL_CHANNELS_6		2


XIRTracking::XIRTracking() :
	XNBlock(),
	_portId(-2)
{
}

XIRTracking::~XIRTracking()
{
	LOGN("XIRTracking::~XIRTracking()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XIRTracking::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XIRTracking::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	if ((!strcmp(model, IRT3220_MODEL_NAME))
		||(!strcmp(model, IRT3320_MODEL_NAME))) {
		_model = MODEL_CHANNELS_2;
		_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
		if (_portId >= 0) {
			_pin[0] = pmap.plat.io.D2.pin1;
			_pin[1] = pmap.plat.io.D2.pin2;
	        pinMode(_pin[0], INPUT);
	        pinMode(_pin[1], INPUT);
		} else {
			LOGN("PortSetup() failed");
			_portId = -2;
			return -1;
		}
	}
	else if (!strcmp(model, IRT3360_MODEL_NAME)) {
		_portId = PortSetup(port, XPORT_FUNC_I2C, &pmap);
		if (_portId >= 0) {
			_model = MODEL_CHANNELS_6;
			_resetPin = pmap.plat.io.D2.pin1;
			_selectPin = pmap.plat.io.D2.pin2;
			LOG("_resetPin=");LOGN(_resetPin);
			LOG("_selectPin=");LOGN(_selectPin);
		} else{
			LOGN("PortSetup() failed!");
			return -1;
		}
	}
	else {
		LOG("Unknown model of ");LOGN(model);
		return -1;
	}

	reset();
	return 0;
}

int XIRTracking::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XIRTracking::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap))
	{
		_pin[0] = pmap.plat.io.D2.pin1;
		_pin[1] = pmap.plat.io.D2.pin2;
        pinMode(_pin[0], INPUT);
        pinMode(_pin[1], INPUT);
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

void XIRTracking::reset()
{
}

uint8_t XIRTracking::getStatus()
{
	uint8_t status = 0x00;

	LOGN("XIRTracking::getStatus()");

	if (_portId == -2) {
		LOGN("XIRTracking not setup");
		return 0x00;
	}
	
	if(_model == MODEL_CHANNELS_2) {
		if (!digitalRead(_pin[0])) {
			status |= (1<<0);
		}
		if (!digitalRead(_pin[1])) {
			status |= (1<<1);
		}
	}
	else if(_model == MODEL_CHANNELS_6) {
#define IRT_I2C_ADDRESS 			(0x58)
#define IRT_GET_STATUS_ADDRESS		(0x20)
		XI2C.read(_selectPin, IRT_I2C_ADDRESS, IRT_GET_STATUS_ADDRESS,&status,1);
		status = ~status;
		status = status&0x3f;
	}
	return status;
}
