/* XRGBLedTest.ino
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
 *     This file is test code for RGB Led module.
 *
 * Version: 1.0.0
 */
 

#include <YGRSystem.h>
#include <XRGBLed.h>
 
XRGBLed rgb;

void setup()
{
	XSystem.setup();
	Serial.begin(9600);
	//rgb.setup("RGB");				//for WuKong platform
	rgb.setup("RGB3280", "2");		//for NeZha platform
}

void loop()
{
	Serial.print("rgb number=");Serial.println(rgb.getNumber());
	rgb.setColor(1, 0x00, 0x00, 0xff);
	rgb.show();
	delay(2000);  
	rgb.setColor(2, 0x00, 0xff, 0x00);
	rgb.show();
	delay(2000); 
	rgb.setColor(3, 0xff, 0x00, 0x00);
	rgb.show();
	delay(2000);
	rgb.setColor(4, 0x00, 0xff, 0xff);
	rgb.setColor(5, 0xff, 0x00, 0xff);
	rgb.setColor(6, 0xff, 0xff, 0x00);
	rgb.setColor(7, 0x80, 0x00, 0x80);
	rgb.setColor(8, 0x00, 0x80, 0x80);
	rgb.show();
	delay(2000);

	rgb.showColor(0, 0xff, 0xff, 0xff);
	delay(2000);

	rgb.clear();
	delay(2000);
}