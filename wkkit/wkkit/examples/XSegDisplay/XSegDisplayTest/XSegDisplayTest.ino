/* XSegDisplayTest.ino
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
 *     This file is test code for 7-Segment Display module.
 *
 * Version: 1.0.0
 */
 

#include <YGRSystem.h>
#include <XSegDisplay.h>

#define CASE_TEST_1		0	//show number test1
#define CASE_TEST_2		0	//show number test2
#define CASE_TEST_3		0	//show number test3
#define CASE_TEST_4		0	//show segment test
#define CASE_TEST_5		0	//show hex/bin test
#define CASE_TEST_6		1	//show character test

XSegDisplay sgd;

void setup() {
	// put your setup code here, to run once:
	XSystem.setup();
	Serial.begin(9600);
	sgd.setup("SGD4200", "2");   //SGD4200 for NeZha platform
	//sgd.setup("SGD4300", "2"); //SGD4300 for WuKong platform
}

// 0 --> 9.999 --> 99.99 --> 999.9 --> 9999
void test_1()
{
	float f;

	f = 0;
	while (f < 10) {
		sgd.showNumber(f);
		f += 0.001;
		delay(500);
	}
	sgd.clear();
	delay(200);

	f = 10;
	while (f < 100) {
		sgd.showNumber(f);
		f += 0.03;
		delay(50);
	}
	sgd.clear();
	delay(200);

	f = 100;
	while (f < 1000) {
		sgd.showNumber(f);
		f += 0.3;
		delay(50);
	}
	sgd.clear();
	delay(200);

	f = 1000;
	while (f < 10000) {
		sgd.showNumber(f);
		f += 3;
		delay(50);
	}
	sgd.clear();
	delay(200);
}

// 0 --> -9.99 --> -99.9 --> -999
void test_2()
{
	float f=0;

	while (f > -10) {
		sgd.showNumber(f);
		f -= 0.03;
		delay(50);
	}
	sgd.clear();
	delay(200);

	while (f > -100) {
		sgd.showNumber(f);
		f -= 0.3;
		delay(50);
	}
	sgd.clear();
	delay(200);

	while (f > -1000) {
		sgd.showNumber(f);
		f -= 3;
		delay(50);
	}
	sgd.clear();
	delay(200);
}

// 0, 1.2345, 12.345, 123.45, 12345
// 0, -1.234, -12.34, -123.4, -1234
void test_3()
{
	sgd.showNumber(0);
	delay(500);
	sgd.showNumber(1.2345);
	delay(500);
	sgd.showNumber(12.345);
	delay(500);
	sgd.showNumber(123.45);
	delay(500);
	sgd.showNumber(1234.5);
	delay(500);
	sgd.showNumber(12345);
	delay(500);

	sgd.showNumber(0);
	delay(500);
	sgd.showNumber(-1.234);
	delay(500);
	sgd.showNumber(-12.34);
	delay(500);
	sgd.showNumber(-123.4);
	delay(500);
	sgd.showNumber(-1234);
	delay(500);
}

void test_4()
{
	sgd.showSegment(0, 'a');
	delay(500);
	sgd.clearSegment(3, 'a');
	delay(500);
	sgd.showSegments(0, 0x3);
	delay(500);
	sgd.clearSegment(3, 'a');
	delay(500);
}

void test_5()
{
	uint32_t i;

	for (i=0; i<=16; i++) {
		sgd.showNumber(i, BIN);
		delay(1000);
	}
		
	for (i=0; i<=65536; i++) {
		sgd.showNumber(i, HEX);
		delay(200);
	}

	sgd.clear();
	delay(500);
}

void test_6()
{
	uint32_t i;

	for (i='0'; i<='9'; i++) {
		sgd.showCharacter(0, i);
		delay(1000);
	}

	for (i='A'; i<='G'; i++) {
		sgd.showCharacter(0, i);
		delay(1000);
	}

	for (i='a'; i<='g'; i++) {
		sgd.showCharacter(0, i);
		delay(1000);
	}
	
	sgd.clear();
	delay(500);
	
	sgd.showCharacter(1, 'd');
	delay(1000);
	sgd.showCharacter(2, 'd');
	delay(1000);
	sgd.showCharacter(3, 'd');
	delay(1000);
	sgd.showCharacter(4, 'd');
	delay(1000);

}


void loop() {
	
#if (CASE_TEST_1 == 1)
	test_1();
#endif
#if (CASE_TEST_2 == 1)
	test_2();
#endif
#if (CASE_TEST_3 == 1)
	test_3();
#endif
#if (CASE_TEST_4 == 1)
	test_4();
#endif
#if (CASE_TEST_5 == 1)
	test_5();
#endif
#if (CASE_TEST_6 == 1)
	test_6();
#endif
}