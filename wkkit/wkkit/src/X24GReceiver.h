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
	功能：	初始化“扩展模块”
	参数：	model, 模块型号
			port, 连接到主控板的端口编号
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *model, const char *port);

	/*
	功能：	初始化“板载模块”
	参数：	label, 模块在主控板上的标贴
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *label);

	void reset();

	/*
	功能：	检查模块是否被连接
	参数：	无
	结果：	未连接返回0，连接返回1
	*/
	uint8_t isConnected();

	/*
	功能：	检查是否有接收到的数据
	参数：	无
	结果：	返回接收到的数据字节数，0表示没有接收到数据
	*/
	int available();

	/*
	功能：	清空接收缓冲区数据
	参数：	无
	结果：	无
	*/
	void flush();

	/*
	功能：	接收1个字节数据，注意要在available()返回有数据后调用
	参数：	无
	结果：	返回接收到的数据值
	*/
	uint8_t recvByte();

	/*
	功能：	接收最多指定长度的数据，注意要在available()返回有数据后调用
	参数：	buf，接收数据缓冲
			len，buf的长度
	结果：	返回接收到的数据字节数
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