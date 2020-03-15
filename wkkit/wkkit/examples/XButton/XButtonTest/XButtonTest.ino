/* XButtonTest.ino
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
 *     This file is test code for Button module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XButton.h>

#define CASE_TEST_PRESSED	1
#define CASE_TEST_KNOCKED	1

XButton btn;

void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	btn.setup("BTN");
}

void loop()
{
#if (CASE_TEST_PRESSED == 1)
	if(btn.isPressed()) {
		Serial.println("#");
	}
	else {
		Serial.print(".");
	}
#endif

#if (CASE_TEST_KNOCKED == 1)
	if (btn.isKnocked()) {
		Serial.println("K");
	}
#endif
}