/* IRR3300Impl.cpp
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
 *     This file is an implement of IRR3300 module device control.
 *
 * Version: 1.0.0
 */


#include "IRR3300Impl.h"


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


IRR3300Impl::IRR3300Impl(const char *model)
{
	(void) model;
	_mSoftSerial = NULL;
}

IRR3300Impl::~IRR3300Impl()
{
	if(_mSoftSerial != NULL)
	{
		_mSoftSerial->end();
		delete _mSoftSerial;
		_mSoftSerial = NULL;
	}
}

int IRR3300Impl::setup(uint8_t keyCheckPin, uint8_t rxPin)
{
	_KeyCheckPin = keyCheckPin;
	_RxPin = rxPin;
	if(_mSoftSerial == NULL)
	{
		_mSoftSerial = new SoftwareSerial(_RxPin, _KeyCheckPin);
		if(_mSoftSerial != NULL)
		{
			_mSoftSerial->begin(9600);
			pinMode(_KeyCheckPin, INPUT);
		}
		else
		{
			LOGN("setup() failed");
			return -1;
		}
	}

	return 0;
}

int IRR3300Impl::available()
{
	int val;

	val = _mSoftSerial->available();
	
	return val;
}

int IRR3300Impl::read()
{
	int val;
	val = _mSoftSerial->read();     /* Read serial infrared data */
	val &= 0xff;
	return(val);
}

bool IRR3300Impl::buttonState()
{
	bool val;

	val =  digitalRead(_KeyCheckPin);

	return(!val);
}

uint8_t IRR3300Impl::getCode()
{
	return _irCode;
}

void IRR3300Impl::loop()
{
	if(buttonState() == 1)
	{
		if(_mSoftSerial->available() > 0)
		{
			int r = read();
			if(r<0xff)
			{
				if(r == 0)
				{
					_irCode = _preIrCode;
				}
				else
				{
					_irCode = r;
					_preIrCode = _irCode;
				}
			}
		}
	}
	else
	{
		_irCode = 0;
		_preIrCode = 0;
	}
}

