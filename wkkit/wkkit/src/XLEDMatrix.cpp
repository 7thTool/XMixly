/* XLEDMatrix.cpp
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
 *     This file is a driver for LED Matrix Display module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XLEDMatrix.h>
#include <LMT3000Impl.h>



#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XLEDMatrix::~XLEDMatrix() 
{
	LOGN("XLEDMatrix::~XLEDMatrix()");

	reset();

	if (_impl) {
		delete (LMT3000Impl *)_impl;
		_impl = NULL;
	}

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XLEDMatrix::setup(const char *model, const char *port)
{
	PortMap pmap;
	
	LOG("XLEDMatrix::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_impl = new LMT3000Impl(model);
	if (!_impl) {
		LOGN("new LMT3000Impl failed");
		return -1;
	}
	
	_portId = PortSetup(port, XPORT_FUNC_I2C, &pmap);
	if (_portId >= 0) {
		((LMT3000Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	} else{
		LOGN("PortSetup() failed!");
		free(_impl);
		return -1;
	}

	return 0;
}

int XLEDMatrix::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XLEDMatrix::setup(");LOG(label);LOGN(")");
	
	if(PortOnBoardSetup(label, model, &pmap)) {
		_impl = new LMT3000Impl(model);
		if (!_impl) {
			LOGN("new LMT3000Impl failed");
			return -1;
		}
		((LMT3000Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	return 0;
}

void XLEDMatrix::reset()
{
	clear();
}

void XLEDMatrix::setBrightness(uint8_t brightness)
{
	((LMT3000Impl *)_impl)->setBrightness(brightness);
}

void XLEDMatrix::setColorInverse(uint8_t value)
{
	((LMT3000Impl *)_impl)->setColorInverse(value);
}

void XLEDMatrix::setEffect(uint8_t effect, uint8_t speed)
{
	if(effect > XLEDMatrix_EFFECT_FLICKER) {
		return;
	}

	if (effect == XLEDMatrix_EFFECT_NONE) {
		speed = 100;
	} else if((effect == XLEDMatrix_EFFECT_LEFT_ROLL) 
		|| (effect == XLEDMatrix_EFFECT_RIGHT_ROLL)) {
		if(speed == 0){
			speed = 30;
		} else if(speed == 1){
			speed = 70;
		} else {
			speed = 90;
		}
	} else {  //if (XLEDMatrix_EFFECT_UP_ROLL, XLEDMatrix_EFFECT_DOWN_ROLL, XLEDMatrix_EFFECT_FLICKER)
		if(speed == 0){
			speed = 60;
		} else if(speed == 1){
			speed = 70;
		} else {
			speed = 90;
		}
	}
	((LMT3000Impl *)_impl)->setEffect(effect, speed);
}

void XLEDMatrix::showBitmap(uint8_t *bitmap, uint8_t len)
{
	((LMT3000Impl *)_impl)->showBitmap(bitmap, len);
}

void XLEDMatrix::updateColumn(uint8_t column, uint8_t value)
{
	((LMT3000Impl *)_impl)->updateColumn(column, value);
}

void XLEDMatrix::updatePoint(uint8_t x, uint8_t y, uint8_t value)
{
	((LMT3000Impl *)_impl)->updatePoint(x, y, value);
}

void XLEDMatrix::showNumber(float num)
{
	((LMT3000Impl *)_impl)->showNumber(num);
}

void XLEDMatrix::showNumberHex(uint32_t num)
{
	((LMT3000Impl *)_impl)->showNumberHex(num);
}

void XLEDMatrix::showString(char *str)
{
	((LMT3000Impl *)_impl)->showString(str);
}

void XLEDMatrix::showNumberPair(uint8_t a, uint8_t b)
{
	((LMT3000Impl *)_impl)->showNumberPair(a, b);
}

void XLEDMatrix::showEmoticon(uint8_t emot)
{
	((LMT3000Impl *)_impl)->showEmoticon(emot);
}

void XLEDMatrix::showFlag(uint8_t flag)
{
	((LMT3000Impl *)_impl)->showFlag(flag);
}

void XLEDMatrix::move(int8_t x, int8_t y)
{
	((LMT3000Impl *)_impl)->move(x, y);
}

void XLEDMatrix::clear()
{
	((LMT3000Impl *)_impl)->clear();
}


#ifdef XBRIDGE_SUPPORT
int8_t XLEDMatrix::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XLEDMatrix::onAccess()");
	(void)result; (void)psize;
	*rsize = 0;

	if (api == XLEDMatrix_API_setEffect) {
		uint8_t effect, speed;
		param = fetchU8(param, &effect);
		param = fetchU8(param, &speed);
		setEffect(effect, speed);
    }
	else if (api == XLEDMatrix_API_showNumber) {
		float f;
		param = fetchFloat(param, &f);
		showNumber(f);
	}
	else if (api == XLEDMatrix_API_showNumberPair) {
		uint8_t a, b;
		param = fetchU8(param, &a);
		param = fetchU8(param, &b);
		showNumberPair(a, b);
	}
	else if (api == XLEDMatrix_API_showEmoticon) {
		uint8_t emot;
		param = fetchU8(param, &emot);
		showEmoticon(emot);
	}
	else if (api == XLEDMatrix_API_showFlag) {
		uint8_t flag;
		param = fetchU8(param, &flag);
		showFlag(flag);
	}
	else if (api == XLEDMatrix_API_clear) {
		clear();
    }
    else {
        return -1;
    }

    return 0;
}
#endif // XBRIDGE_SUPPORT