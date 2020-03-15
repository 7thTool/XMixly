/* XSevenColorLight.cpp
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
 *     This file is a driver for Seven Color Light module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XSevenColorLight.h>
#include <SCL3020Impl.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XSevenColorLight::~XSevenColorLight() 
{
	LOGN("XSevenColorLight::~XSevenColorLight()");

	reset();

	if (_impl) {
		delete (SCL3020Impl *)_impl;
		_impl = NULL;
	}

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XSevenColorLight::setup(const char *model, const char *port)
{
	PortMap pmap;
	
	LOG("XSevenColorLight::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_impl = new SCL3020Impl();
	if (!_impl) {
		LOGN("new SCL3020Impl failed");
		return -1;
	}

	_portId = PortSetup(port, XPORT_FUNC_I2C, &pmap);
	if (_portId >= 0) {
		((SCL3020Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	} else{
		LOGN("PortSetup() failed!");
		free(_impl);
		return -1;
	}

	return 0;
}

int XSevenColorLight::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XSevenColorLight::setup(");LOG(label);LOGN(")");
	
	if(PortOnBoardSetup(label, model, &pmap)) {
		_impl = new SCL3020Impl();
		if (!_impl) {
			LOGN("new SCL3020Impl failed");
			return -1;
		}
		((SCL3020Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	return 0;
}

void XSevenColorLight::reset()
{
	clear(0);
}

void XSevenColorLight::showColor(uint8_t index, uint8_t color)
{
	LOGN("XSevenColorLight::showColor(");LOG(index);LOG(",");LOG(color);LOGN(")");
	
	if (_impl) {
		((SCL3020Impl *)_impl)->showColor(index, color);
	}
}

void XSevenColorLight::clear(uint8_t index)
{
	LOGN("XSevenColorLight::clear(");LOG(index);LOGN(")");

	if (_impl) {
		if (index > 2) {
			return;
		}
		((SCL3020Impl *)_impl)->clear(index);
	}
}


#ifdef XBRIDGE_SUPPORT
#if 1
int8_t XSevenColorLight::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XSevenColorLight::onAccess(");LOG(api);LOGN(")");
	(void)psize; (void)result;

    if (api == XSevenColorLight_API_showColor) {
		uint8_t index;
		uint8_t color;
		param = fetchU8(param, &index);
		param = fetchU8(param, &color);
		showColor(index, color);
		*rsize = 0;
	}
	else if(api == XSevenColorLight_API_clear) {
		uint8_t index;
		param = fetchU8(param, &index);
		clear(index);
		*rsize = 0;
	}
	else {
		*rsize = 0;
		return -1;
	}
	return 0;
}
#endif
#endif // XBRIDGE_SUPPORT


