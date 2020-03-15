/* XBridgeSample.ino
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
 *     This file is a test code for X-Bridge protocol.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XBluetooth.h>
#include <XBridge.h>


XBluetooth blt;
const XBridgePacket *pkt;


void setup() {
	XSystem.setup();
    blt.setup("BLT4140", "5");
	XBridge.setup(&blt, "hqrover", 0x12345678);
}

void loop() {
	if (XBridge.available()) {
		if (XBridge.messageIsHandshake()) {
			XBridge.handledHandshake();
		}
		else if (XBridge.messageIsConnect()) {
			XBridge.handledConnect();
		}
		else if (XBridge.messageIsConstructBlock()) {
			pkt = XBridge.getMessage();
			// TODO:
			XBridge.handledConstructBlock(NULL, 0);
		}
		else if (XBridge.messageIsConstructServer()) {
			pkt = XBridge.getMessage();
			// TODO:
			XBridge.handledConstructServer(NULL, 0);
		}
		else if (XBridge.messageIsDisconnect()) {
			XBridge.handledDisconnect();
		}
		else {
			XBridge.handledMessage();
		}
	}
}