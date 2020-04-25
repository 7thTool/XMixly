/* LMT3000Impl.cpp
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
 *     This file is an implement of LMT3000 module device control.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XLedMatrix.h>
#include <XI2C.h>
#include <LMT3000Impl.h>



#define LMT_I2C_ADDRESS 		(0x3a)
#define LMT3300_I2C_ADDRESS 	(0x5a)

#define LMT3000_SET_ADDRESS		(0x0d)	// WO, 0x0d~0x0f
#define LMT3000_BITMAP_ADDRESS	(0x10)	// WO, 0x10~0x1f
#define LMT3000_UPDATE_ADDRESS	(0x20)	// WO, 0x20~0x3e



#if 0
#include "XDebug.h"
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

LMT3000Impl::LMT3000Impl(const char *model) 
{
	if(model == NULL) {
		return;
	}
		
	if(!strcmp(model, "LMT3000")) {
		_i2cAddr = LMT_I2C_ADDRESS;
	} else if(!strcmp(model, "LMT3300")) {
		_i2cAddr = LMT3300_I2C_ADDRESS;
	} else {
		//_i2cAddr = 0x00;
	}
}

void LMT3000Impl::setup(uint8_t rstPin, uint8_t selPin)
{
	_resetPin = rstPin;
	_selectPin = selPin;
}


void LMT3000Impl::setBrightness(uint8_t brightness)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x00;
	buf[1] = brightness;

	LOGN("setBrightness:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_SET_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::setColorInverse(uint8_t value)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x01;
	buf[1] = value;

	LOGN("setColorInverse:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_SET_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::setEffect(uint8_t effect, uint8_t speed)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x02;
	buf[1] = effect;
	buf[2] = speed;

	LOGN("setEffect:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_SET_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::showBitmap(uint8_t *bitmap, uint8_t len)
{
	uint8_t i;
	uint8_t buf[16];
	int8_t ret = 0;

	if(len == 0) return;
	
	if(len>16) {
		len=16;
	}

	memset(buf, 0x00, 16);
	
	for(i=0;i<len;i++)
		buf[i] = bitmap[i];

	LOGN("showBitmap:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_BITMAP_ADDRESS, buf, 16);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::updateColumn(uint8_t column, uint8_t value)
{
	uint8_t buf[3];
	int8_t ret = 0;


	buf[0] = 0x00;
	buf[1] = column;
	buf[2] = value;

	LOGN("updateColumn:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::updatePoint(uint8_t x, uint8_t y, uint8_t value)
{
	uint8_t buf[4];
	int8_t ret = 0;


	buf[0] = 0x01; 
	buf[1] = x;
	buf[2] = y;
	buf[3] = value;

	LOGN("updatePoint:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	LOG("buf[3]=");LOGN(buf[3]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 4);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::showNumber(float num)
{
	uint8_t buf[5];
	int8_t ret = 0;
	//int32_t value = (int32_t)(num*1000);
	uint32_t value = (uint32_t)(num*1000);

	buf[0] = 0x02;
	buf[1] = (uint8_t)(value&0xff);
	buf[2] = (uint8_t)((value>>8)&0xff);
	buf[3] = (uint8_t)((value>>16)&0xff);
	buf[4] = (uint8_t)((value>>24)&0xff);

	LOGN("showNumber:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	LOG("buf[3]=");LOGN(buf[3]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 5);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::showNumberHex(uint32_t num)
{
	uint8_t buf[5];
	int8_t ret = 0;

	buf[0] = 0x09;
	buf[1] = (uint8_t)(num&0xff);
	buf[2] = (uint8_t)((num>>8)&0xff);
	buf[3] = (uint8_t)((num>>16)&0xff);
	buf[4] = (uint8_t)((num>>24)&0xff);

	LOGN("showNumberHex:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	LOG("buf[3]=");LOGN(buf[3]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 5);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);	
}

void LMT3000Impl::showString(char *str)
{
	uint8_t buf[18];
	int8_t ret = 0;
	uint8_t len = strlen(str);

	buf[0] = 0x03;

	if(strlen(str) > 16) {
		len = 16;
		memcpy(buf+1, str, 16);
		buf[17] = '\0';
	}
	else {
		strcpy((char *)(buf+1), str);
	}

	LOGN("showString:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, len+2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void LMT3000Impl::showNumberPair(uint8_t a, uint8_t b)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x04;
	buf[1] = a;
	buf[2] = b;

	LOGN("showNumberPair:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::showEmoticon(uint8_t emot)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x05;
	buf[1] = emot;

	LOGN("showEmoticon:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::showFlag(uint8_t flag)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x06;
	buf[1] = flag;

	LOGN("showFlag:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::move(int8_t x, int8_t y)
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x07;
	buf[1] = (uint8_t)x;
	buf[2] = (uint8_t)y;

	LOGN("move:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void LMT3000Impl::clear()
{
	uint8_t buf[3];
	int8_t ret = 0;

	buf[0] = 0x08;

	LOGN("clear:");
	LOG("buf[0]=");LOGN(buf[0]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, LMT3000_UPDATE_ADDRESS, buf, 1);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

