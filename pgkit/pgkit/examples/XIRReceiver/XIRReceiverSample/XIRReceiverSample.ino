/* XIRReceiverSample.ino
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
 *     This file is a sample code for IR Receiver module.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XIRReceiver.h>


XIRReceiver irr;


void setup()
{
	XSystem.setup();
	XSystem.setBaudrate(9600);
	irr.setup("IRR");
}

void loop()
{
	uint8_t key = irr.receive();

	if(key != 0xFF) {
		switch(key) {
		case XIR_KEY_A:
			XSystem.printMessage("Key 'A' is pressed.");
			break;
		case XIR_KEY_B:
			XSystem.printMessage("Key 'B' is pressed.");
			break;
		case XIR_KEY_C:
			XSystem.printMessage("Key 'C' is pressed.");
			break;
		case XIR_KEY_D:
			XSystem.printMessage("Key 'D' is pressed.");
			break;
		case XIR_KEY_E:
			XSystem.printMessage("Key 'E' is pressed.");
			break; 
		case XIR_KEY_F:
			XSystem.printMessage("Key 'F' is pressed.");
			break; 
		case XIR_KEY_0:
			XSystem.printMessage("Key '0' is pressed.");
			break;
		case XIR_KEY_1:
			XSystem.printMessage("Key '1' is pressed.");
			break;
		case XIR_KEY_2:
			XSystem.printMessage("Key '2' is pressed.");
			break;
		case XIR_KEY_3:
			XSystem.printMessage("Key '3' is pressed.");
			break;
		case XIR_KEY_4:
			XSystem.printMessage("Key '4' is pressed.");
			break; 
		case XIR_KEY_5:
			XSystem.printMessage("Key '5' is pressed.");
			break;
		case XIR_KEY_6:
			XSystem.printMessage("Key '6' is pressed.");
			break;
		case XIR_KEY_7:
			XSystem.printMessage("Key '7' is pressed.");
			break;
		case XIR_KEY_8:
			XSystem.printMessage("Key '8' is pressed.");
			break;
		case XIR_KEY_9:
			XSystem.printMessage("Key '9' is pressed.");
			break; 
		case XIR_KEY_OK:
			XSystem.printMessage("Key 'OK' is pressed.");
			break;
		case XIR_KEY_LEFT:
			XSystem.printMessage("Key '<' is pressed.");
			break;
		case XIR_KEY_RIGHT:
			XSystem.printMessage("Key '>' is pressed.");
			break; 
		case XIR_KEY_UP:
			XSystem.printMessage("Key 'UP' is pressed.");
			break;
		case XIR_KEY_DOWN:
			XSystem.printMessage("Key 'DOWN' is pressed.");
			break;
		default:
			XSystem.printMessage("Error.");
			break;                   
		}
	}
}
