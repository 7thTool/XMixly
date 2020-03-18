/* XHumitureSample.ino
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
 *     This file is a sample code for Humiture module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XHumiture.h>


XHumiture hum;

float value;


void setup()
{
	XSystem.setup();
	XSystem.setBaudrate(9600);
	hum.setup("HUM3200", "2");
}

void loop()
{
	value = hum.getHumidity();
	XSystem.printFloat(value);
	
	value = hum.getTemperature();
	XSystem.printFloat(value);
	
	delay(1000);
}

