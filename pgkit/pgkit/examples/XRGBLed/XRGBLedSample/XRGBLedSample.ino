/* XRGBLedSample.ino
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
 *     This file is a sample code for RGB Led module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XRGBLed.h>
 
 
XRGBLed rgb;


void setup()
{
	XSystem.setup();
	rgb.setup("RGB");
}

void loop()
{
	rgb.setColor(1, 0x00, 0x00, 0xff);
	rgb.show();
	delay(300);  

	rgb.showColor(0, 0x88, 0x00, 0x88);
	delay(300);

	rgb.clear();
	delay(300);
}