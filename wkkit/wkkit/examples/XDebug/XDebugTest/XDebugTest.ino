/* XDebugTest.ino
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
 *     This file is a test code for X-Debug log system.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XDebug.h>

#define CASE_TEST_PRINTLN		1
#define CASE_TEST_PRINT			1

void setup()
{
	XSystem.setup();
	XDebug.setup(9600);
}

void loop()
{
	int n1 = -10;
	unsigned int n2 = 11;
	long n3 = -1001;
	unsigned long n4 = 256;
	float f1 = 10.256;
	float f2 = 11.2356;
	char c = 'a';
	char s[8] = "bcd";
	String str = "efgh";

#if (CASE_TEST_PRINTLN == 1)
	XDebug.println("test:");
	XDebug.println();
	XDebug.println(n1);
	XDebug.println(n2);
	XDebug.println(n3);
	XDebug.println(n4, TYPE_HEX);
	XDebug.println(f1);
	XDebug.println(f2, 4);
	XDebug.println(c);
	XDebug.println(s);
	XDebug.println(str);
	XDebug.println("--start");
	XDebug.println("--stop");
#endif
#if (CASE_TEST_PRINT == 1)
	XDebug.print("test:");
	XDebug.print(n1);
	XDebug.print(n2);
	XDebug.print(n3);
	XDebug.print(n4, TYPE_HEX);
	XDebug.print(f1);
	XDebug.print(f2, 4);
	XDebug.print(c);
	XDebug.print(s);
	XDebug.print(str);
	XDebug.print("--start");
	XDebug.print("--stop");
#endif
}

