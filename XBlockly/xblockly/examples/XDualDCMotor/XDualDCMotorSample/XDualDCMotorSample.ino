/* XDualDCMotorSample.ino
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
 *     This file is a sample code for DualDCMotor module.
 *
 * Version: 1.0.0
 */


//#include <Wukong.h>
#include <XSystem.h>
#include <XDualDCMotor.h>


XDualDCMotor ddc;


void setup() {
	XSystem.setup();
	ddc.setup("DDM");
}

void loop() {
	ddc.setMotorSpeed(1, 20);
	ddc.setMotorSpeed(2, 50);
	delay(2000);
	ddc.stopMotor(1);
	ddc.stopMotor(2);
	delay(1000);
	
	ddc.setAllSpeed(50, 50);
	delay(2000);
	ddc.stopAllMotor();
	delay(1000);
}