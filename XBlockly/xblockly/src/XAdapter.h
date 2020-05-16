/* XAdapter.h
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
 *     This file is a header file for XAdapter.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __XADAPTER_H__
#define __XADAPTER_H__


#define ADP_PIN_S1		(1)
#define ADP_PIN_S2		(2)


class XAdapter {
public:
	XAdapter();
	~XAdapter();
	
	int setup(const char *model, const char *port);

	int setup(const char *model, const uint8_t pin1, const uint8_t pin2);
	
	uint16_t analogRead(uint8_t signal);
	//void analogWrite(uint8_t signal, uint16_t value);

	uint8_t digitalRead(uint8_t signal);
	void digitalWrite(uint8_t signal, uint8_t level);

private:
	int8_t	_portId;
	uint8_t _pin1;
	uint8_t _pin2;
};


#endif	// __XADAPTER_H__