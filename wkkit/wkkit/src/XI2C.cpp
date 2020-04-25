/* XI2C.cpp
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
 *     This file is an implement of X-I2C protocol.
 *
 * History:
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <Wire.h>
#include <XI2C.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

//all XI2C module XI2C_STATUS_xxx must set this value
#define XI2C_STATUS_ADDRESS		(0x3f)
#define XI2C_STATUS_IDLE		(0x55)
#define XI2C_STATUS_BUSY		(0xaa)

#define XI2C_RELEASE			LOW
#define XI2C_REQUEST			HIGH	

#define XI2C_TIMEOUT			(1000)


XNI2C XI2C;

XNI2C::XNI2C() :
	_hasSetup(0),
	_selected(0)
{
}

XNI2C::~XNI2C() 
{
	if (_hasSetup) {
		Wire.end();
	}
}

void XNI2C::setup()
{
	//delay(300);
	Wire.begin();
	_hasSetup = 1;
}

void XNI2C::reset(uint8_t rstPin, uint8_t selPin)
{
	if (!_hasSetup) {
		//setup();
	}

	pinMode(selPin, OUTPUT);
	digitalWrite(selPin, 0);
	
	pinMode(rstPin, OUTPUT);
	digitalWrite(rstPin, 1);  //set high to reset this I2C-interface module
	delayMicroseconds(500);
	digitalWrite(rstPin, 0);
}

int8_t XNI2C::write(uint8_t selPin, uint8_t devAddr, uint8_t regAddr, const uint8_t *data, uint8_t length)
{
	uint8_t stat = 0;
	int8_t ret = 0;
	int32_t waitCount = 0;

	if (!_hasSetup) {
		setup();
	}

	XI2C.select(selPin);

	delayMicroseconds(500);
	ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	while((ret != 0) || (stat != XI2C_STATUS_BUSY)) {
		if(waitCount++ > XI2C_TIMEOUT){
			LOGN("XI2C status wait busy TIMEOUT");
			XI2C.release(selPin);
			return -2;
		}

		delayMicroseconds(200);
		ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	}

	ret = XI2C.writeData(devAddr, regAddr, data, length);
	waitCount = 0;
	while(ret == -1) {
		if(waitCount++ > XI2C_TIMEOUT) {
			XI2C.release(selPin);
			return -2;
		}

		delayMicroseconds(200);
		ret = XI2C.writeData(devAddr, regAddr, data, length);
	}

	delay(2);
	ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	waitCount = 0;
	while((ret != 0) || (stat != XI2C_STATUS_IDLE)) {
		if(waitCount++ > XI2C_TIMEOUT){
			LOGN("XI2C status wait idle TIMEOUT");
			XI2C.release(selPin);
			return -2;  //send cmd over time
		}

		delayMicroseconds(200);
		ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	}

	XI2C.release(selPin);

	return 0;
}


int8_t XNI2C::read(uint8_t selPin, uint8_t devAddr, uint8_t regAddr, uint8_t *buffer, uint8_t size)
{
	int8_t ret = 0;
	int32_t waitCount = 0;
	uint8_t stat = 0;

	if (!_hasSetup) {
		setup();
	}

	XI2C.select(selPin);

	delayMicroseconds(200);
	ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	while((ret != 0) || (stat != XI2C_STATUS_BUSY)) {
		if(waitCount++ > XI2C_TIMEOUT) {
			LOGN("XI2C status wait busy TIMEOUT");
			XI2C.release(selPin);
			return -2;
		}

		delayMicroseconds(200);
		ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	}

	ret = XI2C.readData(devAddr, regAddr, buffer, size);
	waitCount = 0;
	while(ret == -1) {
		if(waitCount++ > XI2C_TIMEOUT){
			XI2C.release(selPin);
			return -2;
		}

		delayMicroseconds(200);
		ret = XI2C.readData(devAddr, regAddr, buffer, size);
	}

	delayMicroseconds(500);
	ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	waitCount = 0;
	while((ret != 0) || (stat != XI2C_STATUS_IDLE)) {
		if(waitCount++ > XI2C_TIMEOUT){
			LOGN("XI2C status wait idle TIMEOUT");
			XI2C.release(selPin);
			return -2;
		}

		delayMicroseconds(200);
		ret = XI2C.readData(devAddr, XI2C_STATUS_ADDRESS, &stat, 1);
	}

	XI2C.release(selPin);

	return 0;
}


void XNI2C::select(uint8_t selPin)
{
	if(_selected == 0) {
		pinMode(selPin, OUTPUT);
		digitalWrite(selPin, XI2C_REQUEST);
		_selected = 1;
	}
}

void XNI2C::release(uint8_t selPin)
{
	if (_selected == 1) {
		pinMode(selPin, OUTPUT);
		digitalWrite(selPin, XI2C_RELEASE);
		_selected = 0;
	}
}

int8_t XNI2C::readData(uint8_t dev, uint8_t start, uint8_t *buffer, uint8_t size)
{
	int16_t i = 0;
	int8_t return_value = 0;

	if (_selected == 0) {
		return -1;
	}

	Wire.beginTransmission(dev);
	return_value = Wire.write(start);
	if (return_value != 1) {
		return -1;
	}
	return_value = Wire.endTransmission(false);
	if (return_value != 0) {
		return -1;
	}

	delayMicroseconds(1);
	/* Third parameter is true: relase I2C-bus after data is read. */
	Wire.requestFrom(dev, size, (uint8_t)true);
	while (Wire.available() && i < size) {
		buffer[i++] = Wire.read();
	}
	delayMicroseconds(1);
	if (i != size) {
		return -1;
	}

	return 0; //return: no error 
}

int8_t XNI2C::writeData(uint8_t dev, uint8_t start, const uint8_t *pData, uint8_t size)
{
	int8_t return_value = 0;

	if (_selected == 0) {
		return -1;
	}

	Wire.beginTransmission(dev);
	return_value = Wire.write(start); 
	if (return_value != 1) {
		return -1;
	}
	Wire.write(pData, size);  
	return_value = Wire.endTransmission(true); 
	if (return_value != 0) {
		return -1;
	}

	return 0; //return: no error
}

