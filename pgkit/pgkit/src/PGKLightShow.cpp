/* PGKLightShow.cpp
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
 *     This file is an implement of pangu-kit Light Show Server.
 *
 * History:
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XBlock.h>
#include <XBridge.h>
#include <PGKLightShow.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define PGKLightShow_MODE_CLEAR				(0x01)
#define PGKLightShow_MODE_SHOW_COLOR		(0x02)


PGKLightShow::PGKLightShow() :
	_rgb(NULL)
{
}

PGKLightShow::~PGKLightShow()
{
	reset();
}

int PGKLightShow::setup(XRGBLed *rgb)
{
	if (!rgb) {
		return -1;
	}
	_rgb = rgb;

	reset();
	return 0;
}

void PGKLightShow::reset()
{
	clear(0);
}

void PGKLightShow::loop()
{
}



void PGKLightShow::showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t clearOthers)
{
	if (_rgb) {
		if (index <= 6) {
			if(clearOthers != 0) {
				_rgb->clear();
			}
			_rgb->showColor(index, red, green, blue);
		} else {
			return;
		}
	}
}

void PGKLightShow::showColor(uint8_t index, uint32_t value, uint8_t clearOthers)
{
	uint8_t r, g, b;

	r = (value>>16) & 0xff;
	g = (value>>8) & 0xff;
	b = value & 0xff;
	
	showColor(index, r, g, b, clearOthers);
}

void PGKLightShow::clear(uint8_t index)
{
	if (_rgb) {
		if (index <= 6) {
			_rgb->showColor(index, 0, 0, 0);
		} else {
			return;
		}
	}
}

