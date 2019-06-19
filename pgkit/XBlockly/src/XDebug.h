/* XDebug.h
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
 *     This file is a header file for XDebug.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XDEBUG_H__
#define __XDEBUG_H__

#define TYPE_DEC 10
#define TYPE_HEX 16
#define TYPE_OCT 8
#define TYPE_BIN 2

//#define LOG_USE_SOFTWARE_SERIAL   //Port2: (pin12, pin11)
#ifdef LOG_USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif


class XDebug_ {

public:
	XDebug_();
	void setup(unsigned long baud);
	
    void print(const String &);
    void print(const char[]);
    void print(char);
    void print(unsigned char, int = TYPE_DEC);
    void print(int, int = TYPE_DEC);
    void print(unsigned int, int = TYPE_DEC);
    void print(long, int = TYPE_DEC);
    void print(unsigned long, int = TYPE_DEC);
    void print(double, int = 2);

    void println(const String &s);
    void println(const char[]);
    void println(char);
    void println(unsigned char, int = TYPE_DEC);
    void println(int, int = TYPE_DEC);
    void println(unsigned int, int = TYPE_DEC);
    void println(long, int = TYPE_DEC);
    void println(unsigned long, int = TYPE_DEC);
    void println(double, int = 2);
    void println(void);
};


extern XDebug_ XDebug;



#endif //__XDEBUG_H__

