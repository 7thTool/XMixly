/* XAdapterTest.ino
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
 *     This file is test code for Adapter module.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XAdapter.h>

#define CASE_TEST_DO	1
#define CASE_TEST_DI	0
#define CASE_TEST_AI	0


XAdapter adp1;
XAdapter adp2;
XAdapter adp3;
XAdapter adp4;

void setup()
{
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps
	
	adp1.setup("Adapter", "1");
	adp2.setup("Adapter", "2");
	adp3.setup("Adapter", "3");
	adp4.setup("Adapter", "4");
}

void test_digitalWrite()
{
	adp1.digitalWrite(ADP_PIN_S1, 0);
	delay(500);
	adp1.digitalWrite(ADP_PIN_S1, 1);
	delay(500);
	adp1.digitalWrite(ADP_PIN_S2, 0);
	delay(500);
	adp1.digitalWrite(ADP_PIN_S2, 1);
	delay(500);

	adp2.digitalWrite(ADP_PIN_S1, 0);
	delay(500);
	adp2.digitalWrite(ADP_PIN_S1, 1);
	delay(500);
	adp2.digitalWrite(ADP_PIN_S2, 0);
	delay(500);
	adp2.digitalWrite(ADP_PIN_S2, 1);
	delay(500);

	adp3.digitalWrite(ADP_PIN_S1, 0);
	delay(500);
	adp3.digitalWrite(ADP_PIN_S1, 1);
	delay(500);
	adp3.digitalWrite(ADP_PIN_S2, 0);
	delay(500);
	adp3.digitalWrite(ADP_PIN_S2, 1);
	delay(500);

	adp4.digitalWrite(ADP_PIN_S1, 0);
	delay(500);
	adp4.digitalWrite(ADP_PIN_S1, 1);
	delay(500);
	adp4.digitalWrite(ADP_PIN_S2, 0);
	delay(500);
	adp4.digitalWrite(ADP_PIN_S2, 1);
	delay(500);
}

void test_digitalRead()
{
	Serial.println(adp1.digitalRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp1.digitalRead(ADP_PIN_S2));
	delay(500);

	Serial.println(adp2.digitalRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp2.digitalRead(ADP_PIN_S2));
	delay(500);
	
	Serial.println(adp3.digitalRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp3.digitalRead(ADP_PIN_S2));
	delay(500);
	
	Serial.println(adp4.digitalRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp4.digitalRead(ADP_PIN_S2));
	delay(500);
}

void test_analogRead()
{
	Serial.println(adp1.analogRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp1.analogRead(ADP_PIN_S2));
	delay(500);

	Serial.println(adp2.analogRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp2.analogRead(ADP_PIN_S2));
	delay(500);
	
	Serial.println(adp3.analogRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp3.analogRead(ADP_PIN_S2));
	delay(500);
	
	Serial.println(adp4.analogRead(ADP_PIN_S1));
	delay(500);
	Serial.println(adp4.analogRead(ADP_PIN_S2));
	delay(500);
}

void loop()
{
#if (CASE_TEST_DO == 1)
	test_digitalWrite();
#endif
#if (CASE_TEST_DI == 1)
	test_digitalRead()
#endif
#if (CASE_TEST_AI == 1)
	test_analogRead();
#endif
}
