/* XSevenColorLightTest.ino
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
 *     This file is a sample code for Seven color light module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XSevenColorLight.h>

XSevenColorLight scl;

void setup() {
	// put your setup code here, to run once:
	XSystem.setup();
	
	Serial.begin(9600);

	scl.setup("SCL");
}

void loop() {
	//0-黑，1-红，2-绿，4-蓝，3-黄（红+绿），5-品红（红+蓝），6-青（蓝+绿），7-白
	scl.showColor(0, 7);  //白色
	delay(2000);
	scl.showColor(0, 6);  //青（蓝+绿）
	delay(2000);
	scl.showColor(0, 5);  //品红（红+蓝）
	delay(2000);
	scl.showColor(0, 4);  //蓝
	delay(2000);
	scl.showColor(0, 3);  //黄（红+绿）
	delay(2000);
	scl.showColor(0, 2);  //绿
	delay(2000);
	scl.showColor(0, 1);  //红
	delay(2000);
	scl.showColor(0, 0);  //黑
	delay(2000);
	scl.showColor(1, 1);  //红
	delay(2000);
	scl.showColor(2, 2);  //绿
	delay(2000);
	scl.clear(1);
	delay(2000);
	scl.clear(2);
	scl.showColor(0, 7);  //白色
	delay(2000);
	scl.clear(0);
	delay(2000);
}
