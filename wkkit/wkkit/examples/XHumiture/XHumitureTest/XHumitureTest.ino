/* XHumitureTest.ino
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
 *     This file is test code for Humiture module.
 *
 * Version: 1.0.0
 */
 

#include <YGRSystem.h>
#include <XHumiture.h>


XHumiture hum;

float h = 0;
float t = 0;
void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	hum.setup("HUM3200", "1");
	//hum.setup("HUM3200", "2");
	//hum.setup("HUM3200", "4");
	//hum.setup("HUM3200", "5");
	//hum.setup("HUM3200", "6");
	//hum.setup("HUM3200", "7");
}

void loop()
{
	h = hum.getHumidity();
	t = hum.getTemperature();
	
	Serial.print("Humidity: ");
	Serial.print(h);
	Serial.println(" %Rh");
	Serial.print("Temperature: ");
	Serial.print(t);
	Serial.println(" *C ");
	
	// Wait a few seconds between measurements.
	delay(1000);
}

