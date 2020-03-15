/* XDCMotorTest.ino
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
 *     This file is test code for DCMotor module.
 *
 * Version: 1.0.0
 */
 

#include <HQRSystem.h>
#include <XDCMotor.h>


#define CASE_USE_INTERFACE_H	1
#define CASE_USE_INTERFACE_P 	0	//In fact it is DP

XDCMotor dcm;

uint8_t ret;

void setup() {
	// put your setup code here, to run once:
	XSystem.setup();
	Serial.begin(9600);
	
#if (CASE_USE_INTERFACE_H == 1)
    ret = dcm.setup("DCM3200", "5");
#elif (CASE_USE_INTERFACE_P == 1)
	ret = dcm.setup("DCM3200", "6");
	//ret = dcm.setup("DCM3200", "7");
#endif
}

void loop() {

	// put your main code here, to run repeatedly:
	dcm.start(100);
	delay(5000);
	dcm.stop();
	delay(2000);
	dcm.start(30);
	delay(5000);
	dcm.stop();
	delay(2000);
	dcm.start(-100);
	delay(5000);
	dcm.stop();
	delay(2000);
	dcm.start(-30);
	delay(5000);
}
