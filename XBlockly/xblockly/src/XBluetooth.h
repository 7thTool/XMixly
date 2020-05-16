/* XBluetooth.h
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
 *     This file is a header file for XBluetooth.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __XBLUETOOTH_H__
#define __XBLUETOOTH_H__


#include <SoftwareSerial.h>


class XBluetooth {
public:
    XBluetooth();
	~XBluetooth();
	int setup(const char *model, const char *port);
	int setup(const char *label);
	int setup(const char *model, const uint8_t rx, const uint8_t tx);
	
	void reset();

	void setBroadcast(const char *adv);

	// �������״̬
	uint8_t isConnected();

	// ����Ƿ��н��յ�������, ���ؿ��õ����ݳ��ȣ�0��ʾû������
	int available();

	// ��ս��ջ���������
	void flush();

	// ���ó�ʱ�����ڷ��ͺͽ�������
	//void setTimeout(int ms);

	//int sendByte(char val);
	int sendBytes(uint8_t *buf, int len);

	uint8_t recvByte();
	int recvBytes(uint8_t *buf, int len);

private:
	int ATCommand(const char *cmd, char *result, uint8_t rlen);

	int8_t _portId; // -1 means no onboard block, -2 means setup failed.

	uint8_t         mIsSoftSerial;
	SoftwareSerial  *mSoftSerial;
};


#endif	// __XBLUETOOTH_H__