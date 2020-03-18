/* X24GReceiver.cpp
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
 *     This file is a driver for 2.4G receiver module.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <xport.h>
#include <XI2C.h>
#include <X24GReceiver.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define X24G_BAUDRATE	115200


X24GReceiver::~X24GReceiver()
{
	LOGN("X24GReceiver::~X24GReceiver()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int X24GReceiver::setup(const char *model, const char *port)
{
    PortMap pmap;

	LOG("X24GReceiver::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

    _portId = PortSetup(port, XPORT_FUNC_UART, &pmap);
	if (_portId >= 0) {
#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
        if (pmap.plat.io.UART.nbr == XPORT_UART_SOFTWARE) {
            mSoftSerial = new SoftwareSerial(pmap.plat.io.UART.pin1, pmap.plat.io.UART.pin2);
			if (!mSoftSerial) {
				LOGN("new SoftwareSerial failed");
				_portId = -2;
				return -1;
			}
			mIsSoftSerial = 1;
			mSoftSerial->begin(X24G_BAUDRATE);
        } else {
			Serial.begin(X24G_BAUDRATE);
        }
#else
		Serial.begin(X24G_BAUDRATE);
#endif
    } else {
		LOGN("PortSetup() failed");
		_portId = -2;
		return -1;
	}

	reset();
    return 0;
}

int X24GReceiver::setup(const char *label)
{
	LOG("X24GReceiver::setup(");LOG(label);LOGN(")");
	(void)label;
	_portId = -2;
	return -1;
}

void X24GReceiver::reset()
{
	LOG("X24GReceiver::reset()");

	if (_portId != -2) {	
		/*!< FIXME: Only valid in WuKong Board */
		int8_t ret = 0;
		uint8_t cmd = 0x50; // reset XIP45
		ret = XI2C.write(8, 0x3a, 0x00, &cmd, 1);
		if(ret == -2) {
			XI2C.reset(10, 8);
		}

		flush();
	}
}

uint8_t X24GReceiver::isConnected()
{
	return 0;
}

int X24GReceiver::available()
{
	// Check if setup failed.
	if (_portId == -2) {
		return -1;
	}

#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->available();
    } else {
		return Serial.available();
    }
#else
	return Serial.available();
#endif
}

void X24GReceiver::flush()
{
	// Check if setup failed.
	if (_portId == -2) {
		return;
	}

#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        //return software->flush();
		while (mSoftSerial->read() != -1);
    } else {
		return Serial.flush();
    }
#else
	return Serial.flush();
#endif
}

uint8_t X24GReceiver::recvByte()
{
	// Check if setup failed.
	if (_portId == -2) {
		return 0;
	}

#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->read();
    } else { 	
		return Serial.read();
    }
#else
	return Serial.read();
#endif
}

int X24GReceiver::recvBytes(uint8_t *buf, int len)
{
	// Check if setup failed.
	if (_portId == -2) {
		return -1;
	}

#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->readBytes(buf, len);
    } else {
		return Serial.readBytes(buf, len);
    }
#else
	return Serial.readBytes(buf, len);
#endif
}