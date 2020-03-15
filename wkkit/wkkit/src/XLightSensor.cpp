/* XLightSensor.cpp
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
 *     This file is a driver for Light Sensor module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XLightSensor.h>


#define SENSOR_PULL_UP_CONFIG 0
#define MIN_RAW_DATA 0
#define MAX_RAW_DATA 1000
#define OUTPUT_VALUE_MIN 0
#define OUTPUT_VALUE_MAX 100

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XLightSensor::XLightSensor() :
	XNBlock(),
	_portId(-1),
	_pin(0xFF)
{
}

XLightSensor::~XLightSensor()
{
	LOGN("XLightSensor::~XLightSensor()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XLightSensor::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XLightSensor::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
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

int XLightSensor::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XLightSensor::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap)) {
		_pin = pmap.plat.io.A1.pin;
		pinMode(_pin, INPUT);
	} else {
		LOGN("PortOnBoardSetup() failed!");
		return -1;
	}

	reset();
	return 0;
}

void XLightSensor::reset()
{
#ifdef XBRIDGE_SUPPORT_NOTIFY
	_evtMask = 0;
	_sensitive = 4;
	_luminance = 0xFF;
#endif
}

uint8_t XLightSensor::getLuminance()
{
	int16_t value;

	LOGN("XLightSensor::getLuminance()");

	if (_pin == 0xFF) {
		LOGN("XLightSensor not setup");
		return 0;
	}

	value = analogRead(_pin);
	value = constrain(value, MIN_RAW_DATA, MAX_RAW_DATA);

	if(SENSOR_PULL_UP_CONFIG)
		value = map(value, MAX_RAW_DATA, MIN_RAW_DATA, OUTPUT_VALUE_MIN, OUTPUT_VALUE_MAX);
	else
		value = map(value, MIN_RAW_DATA, MAX_RAW_DATA, OUTPUT_VALUE_MIN, OUTPUT_VALUE_MAX);

	return (uint8_t)value;
}

#ifdef XBRIDGE_SUPPORT
int8_t XLightSensor::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XLightSensor::onAccess()");
	(void)param; (void)psize;

    if (api == XLightSensor_API_getLuminance) {
        result = fillU8(result, getLuminance());
        *rsize = 1;
    } else {
        *rsize = 0;
        return -1;
    }

    return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XLightSensor::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XLightSensor::onNotifyRegister()");
	(void)psize;
	(void)evt;

	//if (evt == XLightSensor_EVT_Change) {
		fetchU8(param, &_sensitive);
		_evtMask |= XLightSensor_EVT_Change;
		_luminance = getLuminance();
		fillU8(result, _luminance);
		*rsize = 1;
	//}
	return 0;
}

int8_t XLightSensor::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	uint8_t luminance, diff;
	LOGN("XLightSensor::onNotifyRegister()");

	if (_evtMask & XLightSensor_EVT_Change) {
		luminance = getLuminance();
		diff = (luminance > _luminance) ? (luminance - _luminance) : (_luminance - luminance);
		if (diff >= _sensitive) {
			_luminance = luminance;
			fillU8(result, luminance);
			*evt = XLightSensor_EVT_Change;
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT