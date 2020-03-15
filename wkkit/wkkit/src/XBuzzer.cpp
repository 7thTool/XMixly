/* XBuzzer.cpp
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
 *     This file is a driver for Buzzer module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <avr/wdt.h>
#include <xport.h>
#include <XBuzzer.h>

#define XBUZZER_3C_NAME		"BUZ"


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XBuzzer::~XBuzzer()
{
	LOGN("XBuzzer::~XBuzzer()");
	
	reset();

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XBuzzer::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XBuzzer::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
	if (_portId >= 0) {
		_pin = pmap.plat.io.D1.pin;
		pinMode(_pin, OUTPUT);
	} else{
		LOGN("PortSetup() failed!");
		return -1;
	}

	reset();
	return 0;
}

int XBuzzer::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XBuzzer::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap))
	{
		_pin = pmap.plat.io.D1.pin;
		_portId = -1;
		pinMode(_pin, OUTPUT);
	} else {
		LOGN("PortOnBoardSetup failed!");
		return -1;
	}

	reset();
	return 0;
}

void XBuzzer::reset()
{
	if (_pin != 0xFF) {
		digitalWrite(_pin, LOW);
	}
}

void XBuzzer::playTone(uint16_t frequency, uint32_t duration)
{
	int period = 1000000L / frequency;
	int pulse = period / 2;

	LOGN("XBuzzer::playTone():");
	LOG("frequency = ");LOGN(frequency);
	LOG("duration = ");LOGN(duration);
	LOG("period = ");LOGN(period);

	if (_pin == 0xFF) {
		LOGN("XBuzzer not setup");
		return;
	}

	for (unsigned long i = 0; i < duration * 1000ul; i += period)
	{	
		digitalWrite(_pin, HIGH);
		delayMicroseconds(pulse);
		digitalWrite(_pin, LOW);
		delayMicroseconds(pulse);

		wdt_reset();	/*!< CAUTION: */
	}
}

#ifdef XBRIDGE_SUPPORT
int8_t XBuzzer::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XBuzzer::onAccess()");
	(void)psize; (void)result;
	
    if (api == XBuzzer_API_playTone) {
		uint16_t frequency;
		uint32_t duration;
		param = fetchU16(param, &frequency);
		param = fetchU32(param, &duration);
        playTone(frequency, duration);
        *rsize = 0;
    }
    else {
        *rsize = 0;
        return -1;
    }
    return 0;
}
#endif // XBRIDGE_SUPPORT