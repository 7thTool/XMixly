/* XSoundSensorTest.ino
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
 *     This file is test code for Sound Sensor module.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XSoundSensor.h>

XSoundSensor snd;

void setup() {
	XSystem.setup();
	Serial.begin(9600);
	
	snd.setup("SND");				//for WuKong platform
	//snd.setup("SND3200", "1");	//for NeZha platform
}

void loop() {

	delay(100);
	Serial.println(snd.getVolume());
}
