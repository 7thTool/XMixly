/* X24GReceiver.h
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
 *     This file is a header file for X24GReceiver.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __X24GRECEIVER_H__
#define __X24GRECEIVER_H__


/*!< Defination of if use software serial */
//#define X24R_ENABLE_USE_SOFTWARE_SERIAL


#include <XBlock.h>
#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#endif


class X24GReceiver {
public:
    X24GReceiver() : _portId(-2) {
#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
		mIsSoftSerial = 0;
		mSoftSerial = NULL;
#endif
	}
	~X24GReceiver();

	/*
	���ܣ�	��ʼ������չģ�顱
	������	model, ģ���ͺ�
			port, ���ӵ����ذ�Ķ˿ڱ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *model, const char *port);

	/*
	���ܣ�	��ʼ��������ģ�顱
	������	label, ģ�������ذ��ϵı���
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *label);

	void reset();

	/*
	���ܣ�	���ģ���Ƿ�����
	������	��
	�����	δ���ӷ���0�����ӷ���1
	*/
	uint8_t isConnected();

	/*
	���ܣ�	����Ƿ��н��յ�������
	������	��
	�����	���ؽ��յ��������ֽ�����0��ʾû�н��յ�����
	*/
	int available();

	/*
	���ܣ�	��ս��ջ���������
	������	��
	�����	��
	*/
	void flush();

	/*
	���ܣ�	����1���ֽ����ݣ�ע��Ҫ��available()���������ݺ����
	������	��
	�����	���ؽ��յ�������ֵ
	*/
	uint8_t recvByte();

	/*
	���ܣ�	�������ָ�����ȵ����ݣ�ע��Ҫ��available()���������ݺ����
	������	buf���������ݻ���
			len��buf�ĳ���
	�����	���ؽ��յ��������ֽ���
	*/
	int recvBytes(uint8_t *buf, int len);

private:
	int8_t _portId; // -1 means no onboard block, -2 means setup failed.
#ifdef X24R_ENABLE_USE_SOFTWARE_SERIAL
	uint8_t         mIsSoftSerial;
	SoftwareSerial  *mSoftSerial;
#endif
};


#endif	// __X24GRECEIVER_H__