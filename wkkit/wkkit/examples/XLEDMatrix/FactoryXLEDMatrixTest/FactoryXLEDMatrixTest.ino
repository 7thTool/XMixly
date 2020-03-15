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


#include <XLEDMatrix.h>

#define USE_MAINBOARD_PANGU
//#define USE_MAINBOARD_WUKONG	
//#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARD_PANGU
#include <PGKSystem.h>
#endif
#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#endif
#ifdef USE_MAINBOARD_NEZHA
#include <YGRSystem.h>
#endif


XLEDMatrix lmt;


uint8_t bitmap[16] =
{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void test_show_bitmap()
{
	lmt.showBitmap(bitmap, 16);
	delay(3000);
	lmt.clear();
	delay(500);
}



void setup() {
	// put your setup code here, to run once:
	XSystem.setup();

	lmt.setup("LMT");
#ifdef USE_MAINBOARD_PANGU
	lmt.setup("LMT3300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	lmt.setup("LMT3300", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	lmt.setup("LMT");
#endif

	lmt.setBrightness(7);
}



void loop() {
	test_show_bitmap();
}
