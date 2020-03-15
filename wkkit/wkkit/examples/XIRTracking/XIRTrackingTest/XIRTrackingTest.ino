/* XIRTrackingTest.ino
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
 *     This file is test code for IR Tracking module.
 *
 * Version: 1.0.0
 */
 

#include <YGRSystem.h>
#include <XIRTracking.h>


XIRTracking irt;
uint8_t status;

void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	irt.setup("IRT3220", "1");  	//IRT3220 for NeZha platform
	//irt.setup("IRT3320", "4"); 	//IRT3320 for WuKong platform
}

void loop()
{
	status = irt.getStatus();
	Serial.print("status: ");Serial.println(status);
	delay(1000);
}
