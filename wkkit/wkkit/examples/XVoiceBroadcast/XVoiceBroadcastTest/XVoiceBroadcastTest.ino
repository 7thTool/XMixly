/* XVoiceBroadcastTest.ino
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
 *     This file is test code for Voice Broadcast module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XVoiceBroadcast.h>


#define CASE_TEST_ISPLAYING					1
#define CASE_TEST_PLAYVOICE					0
#define CASE_TEST_REPORT_OPERATOR			0
#define CASE_TEST_REPORT_SOUND				0
#define CASE_TEST_REPORT_TIME				0
#define CASE_TEST_REPORT_DATE				0
#define CASE_TEST_REPORT_OBJECT				0



XVoiceBroadcast vbc;

uint8_t buf[32];

void test_isPlaying()
{
	vbc.reportDate(2018,11,2,3);
	while(vbc.isPlaying());
	vbc.reportObject(3, 25.2);
	while(vbc.isPlaying());
	vbc.reportSound(122);
	while(1)
	{
		Serial.println(vbc.isPlaying());
	}
}

void test_playVoice()
{
	vbc.playVoice(53);
	delay(1000);
	vbc.playVoice(53);
	vbc.playVoice(23);
	delay(1000);
	vbc.playVoice(121);
    delay(4000);
    vbc.stop();
	
	buf[0] = 38;
	buf[1] = 4;
	buf[2] = 12;
	buf[3] = 9;
	buf[4] = 24;
	vbc.playVoices(buf, 5);
	delay(5000);
}


void test_reportOperator()
{
	vbc.reportOperator(XVoiceBroadcast_Operator_ADD);
	delay(1000);
	vbc.reportOperator(XVoiceBroadcast_Operator_MINUS);
	delay(1000);
	vbc.reportOperator(XVoiceBroadcast_Operator_MULTI);
	delay(1000);
	vbc.reportOperator(XVoiceBroadcast_Operator_DIVIDE);
	delay(1000);
	vbc.reportOperator(XVoiceBroadcast_Operator_EQUAL);
	delay(1000);
}

void test_reportSound()
{
	vbc.reportSound(XVoiceBroadcast_Sound_MUSIC1, 1);
	while(1);
}


void test_reportTime()
{
	vbc.reportTime(23, 8, 5);
	delay(8000);
	vbc.reportTime(8, 18, 21);
	delay(8000);
}

void test_reportDate()
{
	vbc.reportDate(2018, 8, 13, 0);
	delay(5000);
	vbc.reportDate(2018, 10, 5, 5);
	delay(6000);
	vbc.reportDate(2018, 12, 10, 7);
	delay(8000);
	vbc.reportDate(2000, 1, 28, 3);
	delay(8000);
}

void test_reportObject()
{
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 237.56);
	delay(5000);
    vbc.reportObject(XVoiceBroadcast_Object_LIGHT, 0.568);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_SOUND, 1.37);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_TEMPERATURE, 14.5);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_HUMIDITY, 25.89);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_DISTANCE, 1000.56);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_SPEED, 15488.56);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_STATUS, 146688);
	delay(8000);
	
    vbc.reportObject(XVoiceBroadcast_Object_VALUE, 0.99);
    delay(5000);
    vbc.reportObject(XVoiceBroadcast_Object_VALUE, -0.99);
    delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 99999.99);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, -99999.981);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, -30111.5567);
	delay(8000);
	
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 0);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 2);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 20);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 21);
	delay(2000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 100);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 101);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 110);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 111);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1000);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1001);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1010);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1011);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1100);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1101);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1110);
	delay(3000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1111);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10000);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10001);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10010);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10011);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10100);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10101);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10110);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10111);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11000);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11001);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11010);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11011);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11100);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11101);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11110);
	delay(5000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11111);
	delay(8000);
#if 0 //support range [-99999.99, 99999.99]
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 100001);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 100011);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 100111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 101111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 111111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 201111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 211111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1001111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1011111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1101111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1100111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 1111111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10001111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10011111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10101111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10111111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11001111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11011111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11101111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 11111111);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, 10011001);
	delay(8000);
	vbc.reportObject(XVoiceBroadcast_Object_VALUE, -1111111);
#endif
	delay(10000);
}


void setup() {
	XSystem.setup();

	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps

	vbc.setup("VBC3200", "1");
}

void loop() {

#if (CASE_TEST_ISPLAYING == 1)
	test_isPlaying();
#endif
#if (CASE_TEST_PLAYVOICE == 1)
	test_playVoice();
#endif
#if (CASE_TEST_REPORT_OPERATOR == 1)
	test_reportOperator();
#endif
#if (CASE_TEST_REPORT_SOUND == 1)
	test_reportSound();
#endif
#if (CASE_TEST_REPORT_TIME == 1)
	test_reportTime();
#endif
#if (CASE_TEST_REPORT_DATE == 1)
	test_reportDate();
#endif
#if (CASE_TEST_REPORT_OBJECT == 1)
	test_reportObject();
#endif

	delay(10000);
}


