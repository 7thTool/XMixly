/* XVoiceBroadcast.cpp
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
 *     This file is a driver for Voice broadcast module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XVoiceBroadcast.h>
#include <XI2C.h>



#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define VBC_I2C_ADDRESS 			(0x5C)
#define VBC_CMD_ADDRESS  			(0x00)
#define VBC_CHECK_PLAYING_ADDRESS	(0x20)



XVoiceBroadcast::XVoiceBroadcast()
{
	_portId = -1;
	_resetPin = 0xFF;
	_selectPin = 0xFF;
}

XVoiceBroadcast::~XVoiceBroadcast() 
{
	LOGN("XDualDCMotor::~XDualDCMotor()");

	reset();

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XVoiceBroadcast::setup(const char *model, const char *port)
{
	PortMap pmap;
	
	LOG("XVoiceBroadcast::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");
	(void)model;

	_portId = PortSetup(port, XPORT_FUNC_I2C, &pmap);
	if (_portId >= 0) {
		_resetPin = pmap.plat.io.D2.pin1;
		_selectPin = pmap.plat.io.D2.pin2;
	} else{
		LOGN("PortSetup() failed!");
		return -1;
	}

	return 0;
}

int XVoiceBroadcast::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XVoiceBroadcast::setup(");LOG(label);LOGN(")");
	
	if(PortOnBoardSetup(label, model, &pmap)) {
		_resetPin = pmap.plat.io.D2.pin1;
		_selectPin = pmap.plat.io.D2.pin2;
	}
	else {
		LOGN("PortOnBoardSetup() failed");
		return -1;
	}

	return 0;
}

int XVoiceBroadcast::setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel)
{
	(void)model;

	if ( (PIN_A4 != sda) || (PIN_A5 != scl)) {
		LOGN("Connect to I2C pin failed!");
		return -1;
	}

	_resetPin = rst;
	_selectPin = sel;

	return 0;
}

void XVoiceBroadcast::reset()
{
	stop();
}


void XVoiceBroadcast::reportObject(uint8_t which, float value)
{
	int8_t ret = 0;
    int32_t ival;
    float dval;
    int8_t dvalx100;
	
	if((value > 99999.99) || (value < -99999.99))
	{
		playVoice(32);  //²¥·ÅÒì³£
		return;
	}

	_buf[0] = 0x04;
	_buf[1] = which;
	
    ival = (int32_t)value;
    dval = value - ival;
	
	if (value < 0) {
		_buf[2] = 1;
		ival = 0 - ival;
		dval = 0 - dval;
	} else {
		_buf[2] = 0;
	}
	dvalx100 = dval * 100;
	
	_buf[3] = (uint8_t)(ival & 0xff);
	_buf[4] = (uint8_t)((ival >> 8) & 0xff);
	_buf[5] = (uint8_t)((ival >> 16) & 0xff);
	_buf[6] = (uint8_t)((ival >> 24) & 0xff);
	_buf[7] = dvalx100;

	LOGN("reportObject:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);
	LOG("_buf[2]=");LOGN(_buf[2]);
	LOG("_buf[3]=");LOGN(_buf[3]);
	LOG("_buf[4]=");LOGN(_buf[4]);
	LOG("_buf[5]=");LOGN(_buf[5]);
	LOG("_buf[6]=");LOGN(_buf[6]);
	LOG("_buf[7]=");LOGN(_buf[7]);

	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 8);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}


void XVoiceBroadcast::reportTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	int8_t ret = 0;

	if(hour > 24) hour = 0;
	if(minute > 59) minute = 0;
	if(second > 59) second = 0;

	_buf[0] = 0x05;
	_buf[1] = hour;
	_buf[2] = minute;
	_buf[3] = second;

	LOGN("reportTime:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);
	LOG("_buf[2]=");LOGN(_buf[2]);
	LOG("_buf[3]=");LOGN(_buf[3]);

	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 4);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void XVoiceBroadcast::reportDate(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday)
{
	int8_t ret = 0;

	if(month > 12) month = 12;
	if(day > 31) day = 31;
	if(weekday > 7) weekday = 7;

	_buf[0] = 0x06;
	_buf[1] = (uint8_t)(year&0xff);
	_buf[2] = (uint8_t)((year>>8)&0xff);
	_buf[3] = month;
	_buf[4] = day;
	_buf[5] = weekday;

	LOGN("reportDate:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);
	LOG("_buf[2]=");LOGN(_buf[2]);
	LOG("_buf[3]=");LOGN(_buf[3]);
	LOG("_buf[4]=");LOGN(_buf[4]);
	LOG("_buf[5]=");LOGN(_buf[5]);

	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 6);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void XVoiceBroadcast::reportOperator(uint8_t which)
{
#if 0
	int8_t ret = 0;

	_buf[0] = 0x07;
	_buf[1] = which;
	
	LOGN("reportOperator:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);

	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
#else
	playVoice(which);
#endif
}


void XVoiceBroadcast::reportSound(uint8_t which, uint8_t repeat)
{
	int8_t ret = 0;

	_buf[0] = 0x08;
	_buf[1] = which;
	_buf[2] = repeat;

	LOGN("reportSound:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);
	LOG("_buf[2]=");LOGN(_buf[2]);

	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}

void XVoiceBroadcast::playVoice(uint8_t segment)
{
	int8_t ret = 0;


	_buf[0] = 0x02;
	_buf[1] = segment;
	
	LOGN("playVoice:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	
	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

void XVoiceBroadcast::playVoices(uint8_t * segs, uint8_t length)
{
	int8_t ret = 0;
	uint8_t i;

	if(!segs || !length) {
		return;
	}

	_buf[0] = 0x03;
	_buf[1] = (length > 30) ? 30 : length;
	
	LOGN("playVoices:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	LOG("_buf[1]=");LOGN(_buf[1]);
	for(i=0;i<length;i++)
		_buf[2+i] = segs[i];
	
	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, length+2);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

uint8_t XVoiceBroadcast::isPlaying()
{
	uint8_t _buf = 0;

	XI2C.read(_selectPin,VBC_I2C_ADDRESS,VBC_CHECK_PLAYING_ADDRESS,&_buf,1);

	return _buf;
}

void XVoiceBroadcast::stop()
{
	int8_t ret = 0;

	_buf[0] = 0x1;

	LOGN("stop:");
	LOG("_buf[0]=");LOGN(_buf[0]);
	
	ret = XI2C.write(_selectPin, VBC_I2C_ADDRESS, VBC_CMD_ADDRESS, _buf, 1);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);

}

