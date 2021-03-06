/* XPIRSample.ino
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
 *     This file is a sample code for human motion detected module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XPIR.h>


XPIR pir;
uint8_t status;


void setup()
{
	XSystem.setup();
	XSystem.setBaudrate(9600);
	pir.setup("PIR3300", "1");
}

void loop()
{
	status = pir.isHumanMotionDetected();
	XSystem.printInteger(status); 
	delay(200);
}