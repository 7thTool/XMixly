/* XMP3.cpp
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
 *     This file is a driver for Bluetooth module.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <XMP3.h>


#define BTT_BAUDRATE	9600



const static uint8_t cmdBuf[][4] =
{
	{0x00, 0x00, 0x00, 0x00},
	{0xAA, 0x01, 0x00, 0xAB},  //查询播放状态
	{0xAA, 0x02, 0x00, 0xAC},  //播放
	{0xAA, 0x03, 0x00, 0xAD},  //暂停
	{0xAA, 0x04, 0x00, 0xAE},  //停止
	{0xAA, 0x05, 0x00, 0xAF},  //播放上一曲
	{0xAA, 0x06, 0x00, 0xB0},  //播放下一曲
	{0xAA, 0x10, 0x00, 0xBA},  //结束播放
	{0xAA, 0x14, 0x00, 0xBE},  //音量加
	{0xAA, 0x15, 0x00, 0xBF},  //音量减
};

XMP3::XMP3()
{
}

XMP3::~XMP3()
{
}


int XMP3::setup()
{
	Serial.begin(BTT_BAUDRATE);
}

void XMP3::sendCmd(uint8_t cmdId)
{
	if(cmdId <= 8)
	{
		sendBytes(cmdBuf[cmdId], 4);
	}
}

void XMP3::setId(uint8_t id)
{
	uint8_t buf[6];
	buf[0] = 0xAA;
	buf[1] = 0x07;
	buf[2] = 0x02;
	buf[3] = 0x00;
	buf[4] = id;
	buf[5] = buf[0]+buf[1]+buf[2]+buf[3]+buf[4];

	sendBytes(buf, 6);
}

int XMP3::sendBytes(uint8_t *buf, int len)
{
	return Serial.write(buf, len);
}

uint8_t XMP3::recvByte()
{
	return Serial.read();
}

int XMP3::recvBytes(uint8_t *buf, int len)
{
	return Serial.readBytes(buf, len);
}