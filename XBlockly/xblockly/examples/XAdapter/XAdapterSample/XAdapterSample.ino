/* XAdapterSample.ino
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
 *     This file is a sample code for Adapter module.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XAdapter.h>


XAdapter adp;
uint16_t analogValue;
uint8_t digtalValue;


void setup()
{
	XSystem.setup();
	XSystem.setBaudrate(9600);
	adp.setup("", "1");
}

void loop()
{
	analogValue = analogRead(ADP_PIN_S1);
	XSystem.printInteger(analogValue);

	digtalValue = digitalRead(ADP_PIN_S1);
	XSystem.printInteger(digtalValue);
	
	digitalWrite(ADP_PIN_S1, 0);
	delay(100);
	digitalWrite(ADP_PIN_S1, 1);
	delay(100);
	digitalWrite(ADP_PIN_S1, 0);
}