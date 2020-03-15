/* XI2C.h
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
 *     This file is a header file for XI2C.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XI2C_H__
#define __XI2C_H__


class XNI2C {
public:
	XNI2C();
	~XNI2C();
	
	void reset(uint8_t rstPin, uint8_t selPin);
	int8_t write(uint8_t selPin, uint8_t devAddr, uint8_t regAddr, const uint8_t *data, uint8_t length);
	int8_t read(uint8_t selPin, uint8_t devAddr, uint8_t regAddr, uint8_t *buffer, uint8_t size);

private:
	void setup();
	void select(uint8_t selPin);
	void release(uint8_t selPin);
	int8_t readData(uint8_t dev, uint8_t start, uint8_t *buffer, uint8_t size);
	int8_t writeData(uint8_t dev, uint8_t start, const uint8_t *data, uint8_t size);
	uint8_t _hasSetup;
	uint8_t _selected;
};

extern XNI2C XI2C;


#endif //__XI2C_H__
