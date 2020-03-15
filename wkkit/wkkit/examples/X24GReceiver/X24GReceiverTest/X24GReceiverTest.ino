/* X24GReceiverTest.ino
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
 *     This file is test code for 24GReceiver module.
 *
 * Version: 1.0.0
 */

 
#include <YGRSystem.h>
#include <X24GReceiver.h>


X24GReceiver x24r;


void setup() {
	XSystem.setup();

	//x24r.setup("24R4124", "5");	//for WuKong platform
	x24r.setup("24R4124", "3");		//for NeZha platform

	//x24r.setBroadcast("WuKong");
	//x24r.setBroadcast("NeZha");
}


int len=0;
const char c[64];
char sbuf[64];

void loop() {
	if (x24r.available() > 0) {
		len = x24r.recvBytes(sbuf, 64);
		memcpy(c, sbuf, 64);
		Serial.println(sbuf);
	}
}
