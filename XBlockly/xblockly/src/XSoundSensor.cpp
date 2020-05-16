/* XSoundSensor.cpp
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
 *     This file is a driver for Sound Sensor module.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <xport.h>
#include <XSoundSensor.h>


#define XSOUND_SENSOR_3C_NAME	"SND"


#define SND3000_MODEL_NAME "SND3000"
#define SND3200_MODEL_NAME "SND3200"
#define SND3300_MODEL_NAME "SND3300"


#define SENSOR_RAW_DATA_MIN 30
#define SENSOR_RAW_DATA_MAX 580
#define MODEL_OUTPUT_MIN 0
#define MODEL_OUTPUT_MAX 100
//#define SENSOR_RAW_DATA_LEVEL1 120
//#define MODEL_OUTPUT_LEVEL1 35

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XSoundSensor::XSoundSensor()
{
	_portId = -1;
	_pin = 0xFF;
}

XSoundSensor::~XSoundSensor()
{
	LOGN("XSoundSensor::~XSoundSensor()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XSoundSensor::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XSoundSensor::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_A1, &pmap);
	if (_portId >= 0) {
		_pin = pmap.plat.io.A1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XSoundSensor::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XSoundSensor::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap)) {
		_pin = pmap.plat.io.A1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	reset();
	return 0;
}

int XSoundSensor::setup(const char *model, const uint8_t pinA)
{
	(void)model;
	
	_pin = pinA;

	reset();
	return 0;
}

void XSoundSensor::reset()
{
}

uint8_t XSoundSensor::getVolume()
{
	int value;

	LOGN("XSoundSensor::getVolume()");

	if (_pin == 0xFF) {
		LOGN("XSoundSensor not setup");
		return 0;
	}

	value = analogRead(_pin);
	value = constrain(value, SENSOR_RAW_DATA_MIN, SENSOR_RAW_DATA_MAX);
#if 0
	if(value<SENSOR_RAW_DATA_LEVEL1)
		value = map(value, SENSOR_RAW_DATA_MIN, SENSOR_RAW_DATA_LEVEL1, MODEL_OUTPUT_MIN, MODEL_OUTPUT_LEVEL1);
	else
		value = map(value, SENSOR_RAW_DATA_LEVEL1, SENSOR_RAW_DATA_MAX, MODEL_OUTPUT_LEVEL1, MODEL_OUTPUT_MAX);
#else
	value = map(value, SENSOR_RAW_DATA_MIN, SENSOR_RAW_DATA_MAX, MODEL_OUTPUT_MIN, MODEL_OUTPUT_MAX);
#endif
	return (uint8_t)value;
}
