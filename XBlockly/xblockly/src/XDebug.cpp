/* XDebug.cpp
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
 *     This file is an implement of X-Debug log system.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XDebug.h>


XDebug_ XDebug;

#ifdef LOG_USE_SOFTWARE_SERIAL
SoftwareSerial SoftSerial(12, 11);
//SoftwareSerial SoftSerial(5, PIN_A2);
#endif


XDebug_::XDebug_()
{
}

void XDebug_::setup(unsigned long baud)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.begin(baud);
#else
	Serial.begin(baud);
#endif
}

void XDebug_:: print(const String &s)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(s);
#else
	Serial.print(s);
#endif
}

void XDebug_:: print(const char str[])
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(str);;
#else
	Serial.print(str);
#endif
}

void XDebug_:: print(char c)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(c);
#else
	Serial.print(c);
#endif
}

void XDebug_:: print(unsigned char b, int base)
{
	(void)base;
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(b);
#else
	Serial.print(b);
#endif
}

void XDebug_:: print(int n, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(n, base);
#else
	Serial.print(n, base);
#endif
}

void XDebug_:: print(unsigned int n, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(n, base);
#else
	Serial.print(n, base);
#endif
}

void XDebug_:: print(long n, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(n ,base);
#else
	Serial.print(n ,base);
#endif
}

void XDebug_:: print(unsigned long n, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(n ,base);
#else
	Serial.print(n ,base);
#endif
}

void XDebug_:: print(double n, int digits)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.print(n, digits);
#else
	Serial.print(n, digits);
#endif
}

void XDebug_:: println(const String &s)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(s);
#else
	Serial.println(s);
#endif
}

void XDebug_:: println(const char c[])
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(c);
#else
	Serial.println(c);
#endif
}

void XDebug_:: println(char c)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(c);
#else
	Serial.println(c);
#endif
}

void XDebug_:: println(unsigned char b, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(b, base);
#else
	Serial.println(b, base);
#endif
}

void XDebug_:: println(int num, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(num, base);
#else
	Serial.println(num, base);
#endif
}

void XDebug_:: println(unsigned int num, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(num, base);
#else
	Serial.println(num, base);
#endif
}

void XDebug_:: println(long num, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(num, base);
#else
	Serial.println(num, base);
#endif
}

void XDebug_:: println(unsigned long num, int base)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(num, base);
#else
	Serial.println(num, base);
#endif
}

void XDebug_:: println(double num, int digits)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println(num, digits);
#else
	Serial.println(num, digits);
#endif
}

void XDebug_::println(void)
{
#ifdef LOG_USE_SOFTWARE_SERIAL
	SoftSerial.println();
#else
	Serial.println();
#endif
}

