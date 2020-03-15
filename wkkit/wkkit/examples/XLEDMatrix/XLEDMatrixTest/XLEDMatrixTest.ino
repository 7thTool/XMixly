/* XLEDMatrixTest.ino
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
 *     This file is test code for LED Matrix module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XLEDMatrix.h>

#define CASE_TEST_SHOW_NUM1			1
#define	CASE_TEST_SHOW_NUM2			1
#define	CASE_TEST_SHOW_NUM3			1
#define CASE_TEST_SHOW_NUMHEX		1
#define CASE_TEST_SHOW_BITMAP		1
#define CASE_TEST_SHOW_EFFECT		1
#define CASE_TEST_SHOW_FLAG			1


XLEDMatrix lmt;


// 0 --> 9.999 --> 99.99 --> 999.9 --> 9999
void test_show_num1()
{
	float f;

	f = 0;
	while (f < 10) {
		lmt.showNumber(f);
		f += 0.001;
		delay(500);
	}
	lmt.clear();
	delay(200);

	f = 10;
	while (f < 100) {
		lmt.showNumber(f);
		f += 0.03;
		delay(50);
	}
	lmt.clear();
	delay(200);

	f = 100;
	while (f < 1000) {
		lmt.showNumber(f);
		f += 0.3;
		delay(50);
	}
	lmt.clear();
	delay(200);

	f = 1000;
	while (f < 10000) {
		lmt.showNumber(f);
		f += 3;
		delay(50);
	}
	lmt.clear();
	delay(200);
}

// 0 --> -9.99 --> -99.9 --> -999
void test_show_num2()
{
	float f=0;

	while (f > -10) {
		lmt.showNumber(f);
		f -= 0.03;
		delay(50);
	}
	lmt.clear();
	delay(200);

	while (f > -100) {
		lmt.showNumber(f);
		f -= 0.3;
		delay(50);
	}
	lmt.clear();
	delay(200);

	while (f > -1000) {
		lmt.showNumber(f);
		f -= 3;
		delay(50);
	}
	lmt.clear();
	delay(200);
}

// 0, 1.2345, 12.345, 123.45, 12345
// 0, -1.234, -12.34, -123.4, -1234
void test_show_num3()
{
	lmt.showNumber(0);
	delay(500);
	lmt.showNumber(1.2345);
	delay(500);
	lmt.showNumber(12.345);
	delay(500);
	lmt.showNumber(123.45);
	delay(500);
	lmt.showNumber(1234.5);
	delay(500);
	lmt.showNumber(12345);
	delay(500);

	lmt.showNumber(0);
	delay(500);
	lmt.showNumber(-1.234);
	delay(500);
	lmt.showNumber(-12.34);
	delay(500);
	lmt.showNumber(-123.4);
	delay(500);
	lmt.showNumber(-1234);
	delay(500);
}

void test_show_num_hex()
{
	lmt.showNumberHex(0x1230);
	delay(5000);
	lmt.showNumberHex(0x4567);
	delay(5000);
	lmt.showNumberHex(0x89ab);
	delay(5000);
	lmt.showNumberHex(0xcdef);
	delay(5000);
	lmt.showNumberHex(0xf);
	delay(5000);
	lmt.showNumberHex(0xfe);
	delay(5000);
	lmt.showNumberHex(0xfed);
	delay(5000);
	lmt.showNumberHex(0xfedcb);
	delay(5000);
	lmt.showNumberHex(0x0);
	delay(5000);
}

uint8_t bitmap[16] =
{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void test_show_bitmap()
{
	uint8_t i = 0; 
	
    lmt.showBitmap(bitmap, 14);
    delay(3000);
	lmt.showBitmap(bitmap, 16);
	for(i=0;i<8;i++)
	{
		lmt.setBrightness(i);
		delay(3000);
	}
	lmt.move(-1, -1);
    delay(3000);
    lmt.setColorInverse(1);
    delay(3000);
    lmt.setColorInverse(0);
    delay(3000);
    lmt.updateColumn(7, 0x00);
    delay(3000);
	lmt.updatePoint(3, 3, 0x00);
    delay(3000);
	lmt.showNumberPair(4, 3);
	delay(3000);
}

void test_show_effect()
{
	lmt.showString("abcdFGhijklmnopqrstuvwxyz");
	lmt.setEffect(XLEDMatrix_EFFECT_LEFT_ROLL, 0);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_LEFT_ROLL, 1);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_LEFT_ROLL, 2);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_UP_ROLL, 0);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_UP_ROLL, 1);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_UP_ROLL, 2);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_FLICKER, 0);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_FLICKER, 1);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_FLICKER, 2);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_RIGHT_ROLL, 1);
	delay(10000);
	lmt.setEffect(XLEDMatrix_EFFECT_DOWN_ROLL, 1);
	delay(10000);
	lmt.clear();
	delay(2000);
	lmt.showNumber(1234);
	lmt.setEffect(XLEDMatrix_EFFECT_LEFT_ROLL, 1);
	delay(5000);
	lmt.setEffect(XLEDMatrix_EFFECT_RIGHT_ROLL, 1);
	delay(5000);
	lmt.setEffect(XLEDMatrix_EFFECT_UP_ROLL, 1);
	delay(5000);
	lmt.setEffect(XLEDMatrix_EFFECT_DOWN_ROLL, 1);
	delay(5000);
	lmt.setEffect(XLEDMatrix_EFFECT_FLICKER, 1);
	delay(5000);
}

void test_show_flag_emotion()
{
	uint8_t i;
	for(i=0;i<15;i++)
	{
		lmt.showFlag(i);
		delay(2000);
	}
	
	for(i=0;i<9;i++)
	{
		lmt.showEmoticon(i);
		delay(2000);
	}
}


void setup() {
	// put your setup code here, to run once:
	XSystem.setup();
	
	Serial.begin(9600);

	lmt.setup("LMT");
}



void loop() {

	lmt.setBrightness(4);
#if (CASE_TEST_SHOW_NUM1 == 1)
	test_show_num1();
#endif
#if (CASE_TEST_SHOW_NUM2 == 1)
	test_show_num2();
#endif
#if (CASE_TEST_SHOW_NUM3 == 1)
	test_show_num3();
#endif
#if (CASE_TEST_SHOW_NUMHEX == 1)
	test_show_num_hex();
#endif
#if (CASE_TEST_SHOW_BITMAP == 1)
	test_show_bitmap();
#endif
#if (CASE_TEST_SHOW_EFFECT == 1)
	test_show_effect();
#endif
#if (CASE_TEST_SHOW_FLAG == 1)
	test_show_flag_emotion();
#endif

	delay(1000);
}
