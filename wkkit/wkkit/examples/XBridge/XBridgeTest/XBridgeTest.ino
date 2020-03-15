/* XBridgeTest.ino
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


//#define BLT_USE_SOFTUART
//#define XSegDisplay_USED

#ifdef BLT_USE_SOFTUART
#define LOG(x)    Serial.print(x)
#define LOGN(x)   Serial.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#ifdef XSegDisplay_USED
	#include <XSegDisplay.h>
	XSegDisplay sgd;
#endif

XBluetooth blt;

const XBridgePacket *pkt;


void setup() {
	XSystem.setup();

	// put your setup code here, to run once:
#ifdef BLT_USE_SOFTUART
	Serial.begin(9600);
	blt.setup("BLT4140", "2");
#else
    blt.setup("BLT4140", "5");
#endif
#ifdef XSegDisplay_USED
    sgd.setup("SGD4300", "3");
#endif
	XBridge.setup(&blt, "hqrover", 0x12345678);
}

long cnt = 0;

void loop() {
	// put your main code here, to run repeatedly:
	if ((cnt % 100000) == 0) {
		LOGN(".");
		cnt = 0;
	} else if ((cnt % 1000) == 0){
		LOG(".");
	}
	cnt++;

	if (XBridge.available()) {
		if (XBridge.messageIsHandshake()) {
			LOGN("handshake");
			XBridge.handledHandshake();
		}
		else if (XBridge.messageIsConnect()) {
			LOGN("connect");
			XBridge.handledConnect();
		}
		else if (XBridge.messageIsConstructBlock()) {
			LOGN("construct block");
			pkt = XBridge.getMessage();
			if (pkt->key1() == XBLOCK_TYPE_XSegDisplay) {
#ifdef XSegDisplay_USED
				XBridge.handledConstructBlock(&sgd, 0);
#else
				XBridge.handledConstructBlock(NULL, 0);
#endif
			} else {
				XBridge.handledConstructBlock(NULL, 0);
			}
		}
		else if (XBridge.messageIsConstructServer()) {
			LOGN("construct server");
			XBridge.handledConstructServer(NULL, 0);
		}
		else if (XBridge.messageIsDisconnect()) {
			LOGN("disconnect");
			XBridge.handledDisconnect();
		}
		else {
			LOGN("other message");
			XBridge.handledMessage();
		}
	}
}