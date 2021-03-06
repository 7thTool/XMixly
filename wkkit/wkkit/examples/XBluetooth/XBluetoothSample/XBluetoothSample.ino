/* XBluetoothSample.ino
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
 *     This file is a sample code for Bluetooth module.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XBluetooth.h>


XBluetooth blt;
int size=0;
uint8_t sbuf[64];


void setup() {
	XSystem.setup();
	blt.setup("BLT4140", "5");
}

void loop() {
	if (blt.available() > 0) {
		size = blt.recvBytes(sbuf, 64);
		blt.sendBytes(sbuf, size);
	}
}