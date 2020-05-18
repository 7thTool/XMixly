/* XSystem.cpp
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
 *     This file is an implement of wukong-kit xsystem function.
 *
 * History:
 * Version: 1.0.0
 */



#include <Arduino.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <xport.h>
#include <XSystem.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif



_XSystem::_XSystem()
{
	LOGN("_XSystem::_XSystem()");
}

_XSystem::~_XSystem()
{
	LOGN("_XSystem::~_XSystem()");
}

int _XSystem::setup()
{
	LOGN("_XSystem::setup()");

	return 0;
}

void _XSystem::setBaudrate(uint16_t baudrate)
{
	LOG("_XSystem::setBaudrate("); LOG(baudrate); LOGN(")");

	if ((baudrate == 9600) ||
		(baudrate == 19200) ||
		(baudrate == 38400)) {
		Serial.begin(baudrate);
	}
}

void _XSystem::printMessage(String msg, bool ln)
{
	LOG("_XSystem::printMessage("); LOG(msg); LOG(ln); LOGN(")");

	if (ln) {
		Serial.println(msg);
	} else {
		Serial.print(msg);
	}
}

void _XSystem::printInteger(long num, uint8_t format, bool ln)
{
	LOG("_XSystem::printInteger("); LOG(num); LOG(","); LOG(format); LOG(","); LOG(ln); LOGN(")");

	if ((format != DEC) && (format != HEX) && (format != BIN)) {
		format = DEC;
	}
	
	if (ln) {
		Serial.println(num, format);
	} else {
		Serial.print(num, format);
	}
}

void _XSystem::printFloat(float num, bool ln)
{
	LOG("_XSystem::printFloat("); LOG(num); LOG(","); LOG(ln); LOGN(")");

	if (ln) {
		Serial.println(num);
	} else {
		Serial.print(num);
	}
}

unsigned long _XSystem::runtime()
{
	LOGN("_XSystem::runtime()");
	return millis();
}

void _XSystem::watchdogEnable(uint8_t timeout)
{
	LOGN("_XSystem::watchdogEnable("); LOG(timeout); LOGN(")");

	switch (timeout) {
	case 0:	// 0.5秒
		wdt_enable(WDTO_500MS);
		break;
	case 1:	// 1秒
		wdt_enable(WDTO_1S);
		break;
	case 2:	// 2秒
		wdt_enable(WDTO_2S);
		break;
	case 4:	// 4秒
		wdt_enable(WDTO_4S);
		break;
	case 8:	// 8秒
		wdt_enable(WDTO_8S);
		break;
	default:
		break;
	}
}

void _XSystem::watchdogDisable()
{
	LOGN("_XSystem::watchdogDisable()");
	wdt_disable();
}

void _XSystem::watchdogReset()
{
	LOGN("_XSystem::watchdogReset()");
	wdt_reset();
}

void _XSystem::saveData(uint8_t pos, float value)
{
	LOGN("_XSystem::saveData("); LOG(pos); LOG(","); LOG(value); LOGN(")");

	/*!< 1024 bytes on the ATmega328P */
	EEPROM.put(pos * 4, value);
}

float _XSystem::fetchData(uint8_t pos)
{
	float value;
	LOGN("_XSystem::fetchData("); LOG(pos); LOGN(")");

	/*!< FIXME: 1024 bytes on the ATmega328P */
	EEPROM.get(pos * 4, value);
	return value;
}



