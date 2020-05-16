/* WKKLightShow.cpp
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
 *     This file is an implement of wukong-kit Light Show Server.
 *
 * History:
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <WKKLightShow.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define WKKLightShow_MODE_CLEAR				(0x01)
#define WKKLightShow_MODE_SHOW_COLOR		(0x02)
#define WKKLightShow_MODE_SHOW_METEOR		(0x03)
#define WKKLightShow_MODE_SHOW_BREATH		(0x04)


WKKLightShow::WKKLightShow() :
	_rgb(NULL),
	_mode(WKKLightShow_MODE_CLEAR),
	_index(0),
	_speed(0),
	_red(0x00),
	_green(0x00),
	_blue(0x00)
{
}

WKKLightShow::~WKKLightShow()
{
	reset();
}

int WKKLightShow::setup(XRGBLed *rgb)
{
	if (!rgb) {
		return -1;
	}
	_rgb = rgb;

	reset();
	return 0;
}

void WKKLightShow::reset()
{
	clear(0);
}

void WKKLightShow::loop()
{
	if (!_rgb) {
		return;
	}

	if(_mode == WKKLightShow_MODE_SHOW_METEOR) {
		loopMeteor();
	} else if(_mode == WKKLightShow_MODE_SHOW_BREATH) {
		loopBreath();
	}
}

void WKKLightShow::showMeteor(uint8_t speed, uint8_t red, uint8_t green, uint8_t blue, int duration)
{
	if (!_rgb) {
		return;
	}

	if ((_mode != WKKLightShow_MODE_SHOW_METEOR) ||
		(_speed != ((speed > 2) ? 2 : speed)) ||
		(_red != red) || (_green != green) || (_blue != blue)) {
		_speed = (speed > 2) ? 2 : speed;
		_red = red;
		_green = green;
		_blue = blue;
		_index = 0;
		_timestamp = millis();

		_rgb->clear();
		_mode = WKKLightShow_MODE_SHOW_METEOR;
	}

	if (duration == 0) {
		loop();
	} else if (duration < 0) {
		while (true) {
			loop();
		}
	} else {
		unsigned long now = millis();
		do {
			loop();
		} while (millis() < now + (duration * 1000ul));
		clear(0);
	}
}

void WKKLightShow::showMeteor(uint8_t speed, uint32_t value, int duration)
{
	uint8_t r, g, b;

	r = (value>>16) & 0xff;
	g = (value>>8) & 0xff;
	b = value & 0xff;
	
	showMeteor(speed, r, g, b, duration);
}

void WKKLightShow::showBreath(uint8_t index, uint8_t speed, uint8_t red, uint8_t green, uint8_t blue, int duration)
{
	if (!_rgb || (index > 6)) {
		return;
	}

	if ((_mode != WKKLightShow_MODE_SHOW_BREATH) ||
		(_index != index) || (_speed != ((speed > 2) ? 2 : speed)) ||
		(_red != red) || (_green != green) || (_blue != blue)) {
		_speed = (speed > 2) ? 2 : speed;
		_red = red;
		_green = green;
		_blue = blue;
		_index = index;
		_step = 0;
		_timestamp = millis();

		_rgb->clear();
		_mode = WKKLightShow_MODE_SHOW_BREATH;
	}

	if (duration == 0) {
		loop();
	} else if (duration < 0) {
		while (true) {
			loop();
		}
	} else {
		unsigned long now = millis();
		do {
			loop();
		} while (millis() < now + (duration * 1000ul));
		clear(0);
	}
}

void WKKLightShow::showBreath(uint8_t index, uint8_t speed, uint32_t value, int duration)
{
	uint8_t r, g, b;

	r = (value>>16) & 0xff;
	g = (value>>8) & 0xff;
	b = value & 0xff;
	
	showBreath(index, speed, r, g, b, duration);
}


void WKKLightShow::clear(uint8_t index)
{
	if (_rgb) {
		if (index <= 6) {
			_rgb->showColor(index, 0, 0, 0);
		} else {
			return;
		}
		_mode = WKKLightShow_MODE_CLEAR;
	}
}


#define MAP_INDEX(id) ((id-1)%6 + 1)

void WKKLightShow::loopMeteor()
{
	if (millis() >= _timestamp) {
		switch (_speed) {
		case 0:
			_timestamp += 200ul;
			_rgb->setColor(MAP_INDEX(_index), _red, _green, _blue);
			_rgb->setColor(MAP_INDEX(_index+5), _red >> 3, _green >> 3, _blue >> 3);
			_rgb->setColor(MAP_INDEX(_index+4), _red >> 4, _green >> 4, _blue >> 4);
			break;
		case 1:
			_timestamp += 140ul;
			_rgb->setColor(MAP_INDEX(_index), _red, _green, _blue);
			_rgb->setColor(MAP_INDEX(_index+5), _red >> 4, _green >> 4, _blue >> 4);
			_rgb->setColor(MAP_INDEX(_index+4), _red >> 5, _green >> 5, _blue >> 5);
			break;
		case 2:
			_timestamp += 80ul;
			_rgb->setColor(MAP_INDEX(_index), _red, _green, _blue);
			_rgb->setColor(MAP_INDEX(_index+5), _red >> 5, _green >> 5, _blue >> 5);
			_rgb->setColor(MAP_INDEX(_index+4), _red >> 6, _green >> 6, _blue >> 6);
			break;
		default:
			return;
		}

		_rgb->setColor(MAP_INDEX(_index+3), 0, 0, 0);
		_rgb->setColor(MAP_INDEX(_index+2), 0, 0, 0);
		_rgb->setColor(MAP_INDEX(_index+1), 0, 0, 0);
		_rgb->show();
		if (++_index > 6) {
			_index = 1;
		}
	}
}

void WKKLightShow::loopBreath()
{
	if (millis() >= _timestamp) {
		uint8_t r, g, b, stp;

		stp = _step & 0x7F;

		if (_speed == 0) {
			_timestamp = millis() + 50ul;
			r = (uint8_t)((float)_red * stp / 50);
			g = (uint8_t)((float)_green * stp / 50);
			b = (uint8_t)((float)_blue * stp / 50);
			if (_step & 0x80) {
				if (--_step == 0x81) {
					_step = 0x01;
				}
			} else {
				if (++_step == 50) {
					_step = 0x80 | 50;
				}
			}
		} else if (_speed == 1) {
			_timestamp = millis() + 35ul;
			r = (uint8_t)((float)_red * stp / 35);
			g = (uint8_t)((float)_green * stp / 35);
			b = (uint8_t)((float)_blue * stp / 35);
			if (_step & 0x80) {
				if (--_step == 0x81) {
					_step = 0x01;
				}
			} else {
				if (++_step == 35) {
					_step = 0x80 | 35;
				}
			}
		} else { // 2--fast
			_timestamp = millis() + 25ul;
			r = (uint8_t)((float)_red * stp / 25);
			g = (uint8_t)((float)_green * stp / 25);
			b = (uint8_t)((float)_blue * stp / 25);
			if (_step & 0x80) {
				if (--_step == 0x81) {
					_step = 0x01;
				}
			} else {
				if (++_step == 25) {
					_step = 0x80 | 25;
				}
			}
		}

		_rgb->showColor(_index, r, g, b);
	}
}



