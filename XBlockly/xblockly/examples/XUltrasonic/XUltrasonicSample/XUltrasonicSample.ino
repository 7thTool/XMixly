/* XUltrasonicSample.ino
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
 *     This file is a sample code for Ultrasonic module.
 *
 * Version: 1.0.0
 */
 

//#include <Wukong.h>
#include <XSystem.h>
#include <XUltrasonic.h>
#include <XSegDisplay.h>


XUltrasonic uls;
long dis;


void setup()
{
	XSystem.setup();
	XSystem.setBaudrate(9600);
	uls.setup("ULS3600", "1");
}

void loop()
{
	dis = uls.getDistance();
	XSystem.printInteger(dis);
	delay(100);
}