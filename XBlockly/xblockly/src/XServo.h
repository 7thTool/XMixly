/* XServo.h
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
 *     This file is a header file for XServo.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XSERVO_H__
#define __XSERVO_H__

#include <Servo.h>



class XServo {
public:
    XServo();
    ~XServo();

	/*
	??:	???“????”
	??:	model, ????
			port, ???????????
	??:	????0,??????
	*/
	int setup(const char *model, const char *port);

	/*
	??:	???“????”
	??:	label, ??????????
	??:	????0,??????
	*/
	int setup(const char *label);

	int setup(const char *model, const uint8_t pinP);

	void reset();

	/*
	??:	??????
	??:	angle, ???,0~359
	??:	?
	*/
	void setAngle(uint16_t angle);

	/*
	??:	??????
	??:	?
	??:	???,0~359
	*/
	uint16_t getAngle();

private:
	int8_t _portId;
    Servo * _servo;
};

#endif //__XSERVO_H__

