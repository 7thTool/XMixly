/* XBluetooth.cpp
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
 *     This file is a driver for Bluetooth module.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <xport.h>
#include <XI2C.h>
#include <XBluetooth.h>


#define BTT_BAUDRATE	115200


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


int XBluetooth::ATCommand(const char *cmd, char *result, uint8_t rlen)
{
	unsigned long timeout = 0;
	
	sendBytes((uint8_t *)cmd, strlen(cmd));
	while (!available()) {
		delay(20);
		timeout += 20;
		if (timeout > 200) {
			return 0;
		}
	}
	
	return recvBytes((uint8_t *)result, rlen);
}

XBluetooth::~XBluetooth()
{
	LOGN("XBluetooth::~XBluetooth()");

	reset();
	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XBluetooth::setup(const char *model, const char *port)
{
    PortMap pmap;

	LOG("XBluetooth::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

    _portId = PortSetup(port, XPORT_FUNC_UART, &pmap);
	if (_portId >= 0) {
#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
        if (pmap.plat.io.UART.nbr == XPORT_UART_SOFTWARE) {
            mSoftSerial = new SoftwareSerial(pmap.plat.io.UART.pin1, pmap.plat.io.UART.pin2);
			if (!mSoftSerial) {
				LOGN("new SoftwareSerial failed");
				_portId = -2;
				return -1;
			}
			mIsSoftSerial = 1;
			mSoftSerial->begin(BTT_BAUDRATE);
        } else {
			Serial.begin(BTT_BAUDRATE);
        }
#else
		Serial.begin(BTT_BAUDRATE);
#endif
    } else {
		LOGN("PortSetup() failed");
		_portId = -2;
		return -1;
	}

	reset();
    return 0;
}

int XBluetooth::setup(const char *label)
{
	LOG("XBluetooth::setup(");LOG(label);LOGN(")");
	(void)label;
	_portId = -2;
	return -1;
}

void XBluetooth::reset()
{
	LOG("XBluetooth::reset()");

	if (_portId != -2) {	
		/*!< FIXME: Only valid in WuKong Board */
		int8_t ret = 0;
		uint8_t cmd = 0x50; // reset XIP45
		ret = XI2C.write(8, 0x3a, 0x00, &cmd, 1);
		if(ret == -2) 
			XI2C.reset(10, 8);
			
//
		// JDY-08 default baudrate is 115200
		char result[8]="Error";
		//ATCommand("AT+RST", result, 8);
		ATCommand("AT+POWR0", result, 8);  // POWR0--4db, POWR1--0db, POWR2---6db, POWR3---23db
		ATCommand("AT+KBYTE3", result, 8); // KBYTE0--1KBytes, KBYTE1--2KBytes, KBYTE3--3KBytes
		//ATCommand("AT+REVERSE0", result, 8);	// P16 low level when BT connected

		flush();
	}
}

void XBluetooth::setBroadcast(const char *adv)
{
	// Check if setup failed.
	if (_portId != -2) {
		char cmd[24], result[8];
		sprintf(cmd, "AT+NAME%s", adv);
		ATCommand(cmd, result, 8);
	}
}

uint8_t XBluetooth::isConnected()
{
	char result[8];

	// Check if setup failed.
	if (_portId == -2) {
		return 0;
	}

	ATCommand("AT+GETSTAT", result, 8);
	if (!strcmp(result, "+STS:01")) { // 未连接状态 + 从机模式
		return 0;
	} else {
		return 1;
	}
}

int XBluetooth::available()
{
	// Check if setup failed.
	if (_portId == -2) {
		return -1;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->available();
    } else {
		return Serial.available();
    }
#else
	return Serial.available();
#endif
}

void XBluetooth::flush()
{
	// Check if setup failed.
	if (_portId == -2) {
		return;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
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

#if 0
void XBluetooth::setTimeout(int ms)
{
	// Check if setup failed.
	if (_portId == -2) {
		return;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->setTimeout(ms);
    } else {
		return Serial.setTimeout(ms);
    }
#else
	return Serial.setTimeout(ms);
#endif
}
#endif

#if 0
int XBluetooth::sendByte(char val)
{
	// Check if setup failed.
	if (_portId == -2) {
		return 0;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->write(val);
    } else {
		return Serial.write(val);
    }
#else
	return Serial.write(val);
#endif
}
#endif

int XBluetooth::sendBytes(uint8_t *buf, int len)
{
	// Check if setup failed.
	if (_portId == -2) {
		return -1;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->write(buf, len);
    } else {
		return Serial.write(buf, len);
    }
#else
	return Serial.write(buf, len);
#endif
}

uint8_t XBluetooth::recvByte()
{
	// Check if setup failed.
	if (_portId == -2) {
		return 0;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->read();
    } else { 	
		return Serial.read();
    }
#else
	return Serial.read();
#endif
}

int XBluetooth::recvBytes(uint8_t *buf, int len)
{
	// Check if setup failed.
	if (_portId == -2) {
		return -1;
	}

#ifdef XBLUE_ENABLE_USE_SOFTWARE_SERIAL
    if (mIsSoftSerial) {
        return mSoftSerial->readBytes(buf, len);
    } else {
		return Serial.readBytes(buf, len);
    }
#else
	return Serial.readBytes(buf, len);
#endif
}