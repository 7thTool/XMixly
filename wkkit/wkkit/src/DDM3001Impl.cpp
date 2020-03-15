/* DDM3001Impl.cpp
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
 *     This file is an implement of DDM3001 module device control.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XDualDCMotor.h>
#include <XI2C.h>
#include <DDM3001Impl.h>



#define DDM3001_I2C_ADDRESS 	(0x3a)
#define DDM3300_I2C_ADDRESS 	(0x7a)

#define DDM3001_CMD_ADDRESS  	(0x00)


#if 0
#include "XDebug.h"
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

DDM3001Impl::DDM3001Impl(const char *model) 
{
	if(model == NULL) {
		return;
	}
		
	if(!strcmp(model, "DDM3001")) {
		_i2cAddr = DDM3001_I2C_ADDRESS;
	} else if(!strcmp(model, "DDM3300")) {
		_i2cAddr = DDM3300_I2C_ADDRESS;
	} else {
		//_i2cAddr = 0x00;
	}
}

void DDM3001Impl::setup(uint8_t rstPin, uint8_t selPin)
{
	_resetPin = rstPin;
	_selectPin = selPin;
}

/* buffer byte data protocol:
 * buf[0]: bit7-4: 0x0 means set motor command 
 *		   bit1-0: 
 *				 1) 0x0 both motor1 and motor2 not need update speed,
 *				 2) 0x1 only motor1 need update speed
 *				 3) 0x2 only motor2 need update speed
 *				 4) 0x3 both motor1 and motor2 need update speed
 *		   bit2: motor1 speed dir (1 means speed < 0) 
 *		   bit3: motor2 speed dir (1 means speed < 0)
 * buf[1]: motor1 speed value 
 * buf[2]: motor2 speed value
 */
void DDM3001Impl::setMotorSpeed(uint8_t motor, int8_t speed)
{
	uint8_t data;
	uint8_t buf[3];
	int8_t ret = 0;

	data = constrain(abs(speed), 0, DDM_SPEED_VALUE_MAX);
	data = map(data, 0, DDM_SPEED_VALUE_MAX, 0, 255);

	buf[0] = 0x00;
	//buf[0] &= 0x3f; //bit7-6: set motor command

	if(motor == 1){
		buf[0] |= 0x01; //bit1-0: only motor1 need update speed
		if(speed<0) {
			buf[0] |= (1<<2); //bit2: motor1 dir
		}
		
		buf[1] = data;
	} else {
		buf[0] |= 0x02; //bit1-0: only motor2 need update speed
		if(speed<0) {
			buf[0] |= (1<<3); //bit3: motor2 dir
		}
		
		buf[2] = data;
	}

	LOGN("setMotorSpeed:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);
	
	ret = XI2C.write(_selectPin, _i2cAddr, DDM3001_CMD_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}


void DDM3001Impl::setAllSpeed(int8_t Lspeed, int8_t Rspeed)
{
	uint8_t Ldata, Rdata;
	uint8_t buf[3];
	int8_t ret = 0;
	
	Ldata = constrain(abs(Lspeed), 0, DDM_SPEED_VALUE_MAX);
	Rdata = constrain(abs(Rspeed), 0, DDM_SPEED_VALUE_MAX);
	Ldata = map(Ldata, 0, DDM_SPEED_VALUE_MAX, 0, 255);
	Rdata = map(Rdata, 0, DDM_SPEED_VALUE_MAX, 0, 255);
	LOG("Lspeed=");LOGN(Lspeed);
	LOG("Rspeed=");LOGN(Rspeed);
	LOG("Ldata=");LOGN(Ldata);
	LOG("Rdata=");LOGN(Rdata);

	buf[0] = 0x00;
	//buf[0] &= 0x3f; //bit7-4: set motor command

	buf[0] |= 0x03; //bit1-0: both motor1 and motor2 need update speed

	if(Lspeed<0) {
		buf[0] |= (1<<2); //bit2: motor1 dir
	}
	if(Rspeed<0) {
		buf[0] |= (1<<3); //bit3: motor2 dir
	}


	buf[1] = Ldata;
	buf[2] = Rdata;

	LOGN("setAllSpeed:");
	LOG("buf[0]=");LOGN(buf[0]);
	LOG("buf[1]=");LOGN(buf[1]);
	LOG("buf[2]=");LOGN(buf[2]);

	ret = XI2C.write(_selectPin, _i2cAddr, DDM3001_CMD_ADDRESS, buf, 3);
	if(ret == -2) 
		XI2C.reset(_resetPin, _selectPin);
}


