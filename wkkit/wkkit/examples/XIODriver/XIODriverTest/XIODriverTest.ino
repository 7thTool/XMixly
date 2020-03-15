/* XIODriverTest.ino
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
 *     This file is test code for IO-Driver module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XIODriver.h>


#define DI_TEST		1
#define DO_TEST		0

XIODriver iod;
uint8_t status;


void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	iod.setup("IOD3300", "1");
}

void loop()
{	
#if (DI_TEST == 1)
	uint8_t l_status;

	l_status = iod.digitalRead(1);
	
	Serial.print("status1: ");Serial.println(l_status);
	
	delay(1000);

	l_status = iod.digitalRead(2);
	
	Serial.print("status2: ");Serial.println(l_status);
	
	delay(1000);
#endif

#if (DO_TEST == 1)
	iod.digitalWrite(1, 0);
	
	delay(1000);

	iod.digitalWrite(1, 1);

	delay(1000);

	iod.digitalWrite(2, 0);

	delay(1000);

	iod.digitalWrite(2, 1);

	delay(1000);
#endif
}