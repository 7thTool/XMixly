/* XServoTest.ino
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
 *     This file is test code for Servo module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XServo.h>

XServo svo;

void setup() {

	XSystem.setup();
	Serial.begin(9600);
	
	svo.setup("SVO"); 
}

int angle = 0;
void loop() {
	/*svo = new XServo();
	if (!svo) {
		Serial.println("new XServo failed");
		while(1);
	}
	if (svo->setup("SVO") != 0) {
		Serial.println("svo->setup failed");
		while(1);
	}*/

	/*angle = 0;
	while (angle <= 180) {
		Serial.println(angle);
		svo->setAngle(angle);
		delay(500);
		angle += 15;
	}*/

	svo.setAngle(30);
	delay(500);
	Serial.print("angle=");Serial.println(svo.getAngle());
	svo.setAngle(75);
	Serial.print("angle=");Serial.println(svo.getAngle());
	delay(500);

	/*delete svo;
	svo = NULL;*/
}


