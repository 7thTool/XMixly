/* XIRReceiverTest.ino
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
 *     This file is test code for IR Receiver module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XIRReceiver.h>

#define CASE_TEST_RECEIVE		1
#define CASE_TEST_LONG_PRESS	0
#define CASE_TEST_WAIT_PICK		0

XIRReceiver irr;

//decode_results myResult;

void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	//irr.setup("IRR");
	irr.setup("IRR3300", "5");
}

void test_receive()
{
	uint8_t key = irr.receive();

	if(key != 0xFF) {
		switch(key) {
		case XIR_KEY_A:
			Serial.println("Key 'A' is pressed.");
			break;
		case XIR_KEY_B:
			Serial.println("Key 'B' is pressed.");
			break;
		case XIR_KEY_C:
			Serial.println("Key 'C' is pressed.");
			break;
		case XIR_KEY_D:
			Serial.println("Key 'D' is pressed.");
			break;
		case XIR_KEY_E:
			Serial.println("Key 'E' is pressed.");
			break; 
		case XIR_KEY_F:
			Serial.println("Key 'F' is pressed.");
			break; 
		case XIR_KEY_0:
			Serial.println("Key '0' is pressed.");
			break;
		case XIR_KEY_1:
			Serial.println("Key '1' is pressed.");
			break;
		case XIR_KEY_2:
			Serial.println("Key '2' is pressed.");
			break;
		case XIR_KEY_3:
			Serial.println("Key '3' is pressed.");
			break;
		case XIR_KEY_4:
			Serial.println("Key '4' is pressed.");
			break; 
		case XIR_KEY_5:
			Serial.println("Key '5' is pressed.");
			break;
		case XIR_KEY_6:
			Serial.println("Key '6' is pressed.");
			break;
		case XIR_KEY_7:
			Serial.println("Key '7' is pressed.");
			break;
		case XIR_KEY_8:
			Serial.println("Key '8' is pressed.");
			break;
		case XIR_KEY_9:
			Serial.println("Key '9' is pressed.");
			break; 
		case XIR_KEY_OK:
			Serial.println("Key 'OK' is pressed.");
			break;
		case XIR_KEY_LEFT:
			Serial.println("Key '<' is pressed.");
			break;
		case XIR_KEY_RIGHT:
			Serial.println("Key '>' is pressed.");
			break; 
		case XIR_KEY_UP:
			Serial.println("Key 'UP' is pressed.");
			break;
		case XIR_KEY_DOWN:
			Serial.println("Key 'DOWN' is pressed.");
			break;
		/*case XIR_KEY_STAR:
			Serial.println("Key '*' is pressed.");
			break;
		case XIR_KEY_POUND:
			Serial.println("Key '#' is pressed.");
			break;*/
		default:
			Serial.println("Error.");
			break;                   
		}
		//Serial.print("Recv 0x");Serial.println(code, HEX);
	}
}

void test_long_press()
{
	irr.enableLongPress(0xff);
	while(1)
	{
		test_receive();
	}
}

void test_wait_pick()
{
	while(1)
	{
		irr.wait();
		Serial.println(irr.pick());
	}
}

void loop()
{
#if (CASE_TEST_RECEIVE == 1)
	test_receive();
#endif
#if (CASE_TEST_LONG_PRESS == 1)
	test_receive();
#endif
#if (CASE_TEST_WAIT_PICK == 1)
	test_wait_pick();
#endif
}
