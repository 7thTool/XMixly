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


XSoundSensor::XSoundSensor() :
	XNBlock(),
	_portId(-1),
	_pin(0xFF)
{
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

void XSoundSensor::reset()
{
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_sensitive = 4;
	_volume = 0xFF;
#endif
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

#ifdef XBRIDGE_SUPPORT
int8_t XSoundSensor::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XSoundSensor::onAccess()");
	(void)param; (void)psize;

    if (api == XSoundSensor_API_getVolume) {
        result = fillU8(result, getVolume());
        *rsize  = 1;
    }
    else {
        *rsize = 0;
        return -1;
    }

    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XSoundSensor::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XSoundSensor::onNotifyRegister()");
	(void)psize;
	(void)evt;

	//if (evt == XSoundSensor_EVT_Change) {
		fetchU8(param, &_sensitive);
		_evtMask |= XSoundSensor_EVT_Change;
		_volume = getVolume();
		fillU8(result, _volume);
		*rsize = 1;
	//}
	return 0;
}

int8_t XSoundSensor::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint8_t volume, diff;
	LOGN("XSoundSensor::onNotifyCheck()");

	if (_evtMask & XSoundSensor_EVT_Change) {
		volume = getVolume();
		diff = (volume > _volume) ? (volume - _volume) : (_volume - volume);
		if (diff >= _sensitive) {
			_volume = volume;
			fillU8(result, volume);
			*evt = XSoundSensor_EVT_Change;
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT