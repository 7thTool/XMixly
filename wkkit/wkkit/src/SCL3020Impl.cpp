/* SCL3020Impl.cpp
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
 *     This file is an implement of SCL3020 module device control.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XSevenColorLight.h>
#include <XI2C.h>
#include <SCL3020Impl.h>



#define SCL3020_I2C_ADDRESS 	(0x3a)
#define SCL3020_CMD_ADDRESS  	(0x00)


#if 0
#include "XDebug.h"
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


void SCL3020Impl::setup(uint8_t rstPin, uint8_t selPin)
{
	_resetPin = rstPin;
	_selectPin = selPin;
}

void SCL3020Impl::showColor(uint8_t index, uint8_t color)
{
	uint8_t buf[3];
	int8_t ret = 0;

	/* buffer byte data protocol:
	 * buf[0]: bit7-4: 0x8 means set scl command
	 *				   bit1-0: 
	 *						  1) 0x0 both scl1 and scl2 not need update color,
	 *						  2) 0x1 only scl1 need update color
	 *						  3) 0x2 only scl2 need update color
	 *						  4) 0x3 both scl1 and scl2 need update color
	 *				   buf[1]: scl1 color value 
	 *				   buf[2]: scl2 color value
	 */

	buf[0] = 0x80;
	//buf[0] &= 0x3f; //bit7-6: set scl command

	if(index == 0){
		buf[0] |= 0x03; //bit1-0: both scl1 and scl2 need update color
		buf[1] = color;
		buf[2] = color;
	} else if(index == 1){
		buf[0] |= 0x01; //bit1-0: only scl1 need update color
		buf[1] = color;
	} else if(index == 2){
		buf[0] |= 0x02; //bit1-0: only scl2 need update color
		buf[2] = color;
	} else {
		return;
		//buf[0] |= 0x00; //bit1-0: both scl1 and scl2 not need update color
	}

	LOGN("showColor:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, SCL3020_I2C_ADDRESS, SCL3020_CMD_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}


void SCL3020Impl::clear(uint8_t index)
{
	showColor(index, 0);
}


