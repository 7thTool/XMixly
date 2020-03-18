/* XPS2Controllee.cpp
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
 *     This file is an implement of PS2 controllee.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <XPS2Controllee.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


//#define RECV_DETAIL


#define PS2_HEAD1	0xFF
#define PS2_HEAD2	0xAA


#ifdef RECV_DETAIL
#include <XDebug.h>
static unsigned long runtime=0;
#endif


XPS2Controllee::XPS2Controllee()
{
	_24GReceiver = NULL;
}

XPS2Controllee::~XPS2Controllee()
{
}

int XPS2Controllee::setup(X24GReceiver *receiver)
{
	if (!receiver) {
		return -1;
	}

	_24GReceiver = receiver;
	_24GReceiver->flush();

	_lx = _ly = _rx = _ry = 0;
	_btnGroup[0] = _btnGroup[1] = _btnGroup[2] = _btnGroup[3] = 128;

	return 0;
}

int XPS2Controllee::available()
{
#define TIMEOUT		(400ul)	// 400ms
	uint8_t rsize;
	uint8_t head, flag, type, dlen, checkSum;
	unsigned long timeout;

	if (!_24GReceiver) {
		LOGN("XPS2Controllee has not setup");
		return 0;
	}
	
	if (!_24GReceiver->available()) {
#ifdef RECV_DETAIL
		if (runtime++ > 20000) {
			XDebug.print('.');
			runtime = 0;
		}
#endif
		return 0;
	}
#ifdef RECV_DETAIL
	XDebug.println("");
#endif

	rsize = _24GReceiver->available();
	if (rsize < 12) {
#ifdef RECV_DETAIL
		XDebug.println("no data enough to parse");
#endif
		return 0;
	}

	/* Search Head1 */
	do {
		head = _24GReceiver->recvByte();
#ifdef RECV_DETAIL
		XDebug.print(head, HEX); XDebug.print(' ');
#endif
		if (head == PS2_HEAD1) {
			break;
		} else {
			rsize--;
		}
	} while (rsize > 0);
	if (rsize == 0) {
		LOGN("not found HEAD1");
		return 0;
	}

	/* Search Head2 */
	timeout = millis();
	while (head == PS2_HEAD1) {
		if (_24GReceiver->available()) {
			head = _24GReceiver->recvByte();
#ifdef RECV_DETAIL
			XDebug.print(head, HEX); XDebug.print(' ');
#endif
			if (head == PS2_HEAD2) {
				break;
			} else if (head == PS2_HEAD1) {
#ifdef RECV_DETAIL
				XDebug.println("New HEAD1");
#endif
				timeout = millis();
			} else {
				LOGN("received head not HEAD1 neither HEAD2");
				return 0;
			}
		} else {
			if (millis() > timeout + TIMEOUT) {
				LOGN("receive HEAD2 timeout");
				return 0;
			}
		}
	}

	timeout = millis();
	while (true) {
		rsize = _24GReceiver->available();
		if (rsize >= 10) {
			break;
		} else if (millis() > timeout + TIMEOUT) {
			LOGN("receive data timeout");
			return 0;
		}
	}

	flag = _24GReceiver->recvByte();
#ifdef RECV_DETAIL
	XDebug.print(flag, HEX); XDebug.print(' ');
#endif
	type = flag & 0x0F;
	dlen = flag >> 4;
	if ((type != 1/* PS2 */) || (dlen != 8)) {
		LOGN("parse type|dlen failed");
		return 0;
	}
	
	_lx = _24GReceiver->recvByte();
	_btnGroup[0] = _24GReceiver->recvByte();
	_ly = _24GReceiver->recvByte();
	_btnGroup[1] = _24GReceiver->recvByte();
	_rx = _24GReceiver->recvByte();
	_btnGroup[2] = _24GReceiver->recvByte();
	_ry = _24GReceiver->recvByte();
	_btnGroup[3] = _24GReceiver->recvByte();
#ifdef RECV_DETAIL
	XDebug.print(_lx, HEX); XDebug.print(' ');
	XDebug.print(_btnGroup[0], HEX); XDebug.print(' ');
	XDebug.print(_ly, HEX); XDebug.print(' ');
	XDebug.print(_btnGroup[1], HEX); XDebug.print(' ');
	XDebug.print(_rx, HEX); XDebug.print(' ');
	XDebug.print(_btnGroup[2], HEX); XDebug.print(' ');
	XDebug.print(_ry, HEX); XDebug.print(' ');
	XDebug.print(_btnGroup[3], HEX); XDebug.print(' ');
#endif
	if ((_btnGroup[0] & 0x80) || (_btnGroup[1] & 0x80) ||
		(_btnGroup[2] & 0x80) || (_btnGroup[3] & 0x80)) {
		LOGN("parse data failed");
		return 0;
	}

	checkSum = _24GReceiver->recvByte();
#ifdef RECV_DETAIL
	XDebug.println(checkSum, HEX);
#endif
	if (checkSum != PS2_HEAD1 + PS2_HEAD2 + flag +
					_lx + _btnGroup[0] + _ly + _btnGroup[1] +
					_rx + _btnGroup[2] + _ry + _btnGroup[3]) {
		LOGN("checksum failed");
		return 0;
	}
	
	return 1;
}

int8_t XPS2Controllee::checkButtonStatus(uint8_t btn)
{
	int8_t status = 0;
	
	if (!_24GReceiver) {
		return 0;
	}
	
	switch (btn) {
	case XPS2_BTN_LX:
		status = _lx - 128;
		break;
	case XPS2_BTN_LY:
		status = _ly - 128;
		break;
	case XPS2_BTN_RX:
		status = _rx - 128;
		break;
	case XPS2_BTN_RY:
		status = _ry - 128;
		break;
	case XPS2_BTN_L1:	
	case XPS2_BTN_L2:
	case XPS2_BTN_R1:
	case XPS2_BTN_R2:
		status = (_btnGroup[0] & (1 << (btn - 8))) ? 1 : 0;
		break;
	case XPS2_BTN_UP:
	case XPS2_BTN_DOWN:
	case XPS2_BTN_LEFT:
	case XPS2_BTN_RIGHT:
		status = (_btnGroup[0] & (1 << (btn - 16))) ? 1 : 0;
		break;
	case XPS2_BTN_SELECT:
	case XPS2_BTN_MODE:
	case XPS2_BTN_START:
	case XPS2_BTN_TURBO:
		status = (_btnGroup[0] & (1 << (btn - 24))) ? 1 : 0;
		break;
	case XPS2_BTN_TRIANGLE:
	case XPS2_BTN_XSHAPED:
	case XPS2_BTN_SQUARE:
	case XPS2_BTN_ROUND:
	case XPS2_BTN_BUTTON_L:
	case XPS2_BTN_BUTTON_R:
		status = (_btnGroup[0] & (1 << (btn - 32))) ? 1 : 0;
		break;
	default:
		break;
	}
	
	return status;
}