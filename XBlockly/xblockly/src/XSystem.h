/* XSystem.h
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
 *     This file is a header file for XSystem.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XSYSTEM_H__
#define __XSYSTEM_H__



class _XSystem {
public:
	_XSystem();
	~_XSystem();

	/*
	功能：	初始化
	参数：	无
	结果：	成功返回0，失败返回负数
	*/
	int setup();

	/*
	功能：	设置串口波特率
	参数：	baudrate, 可选 9600, 19200, 38400
	结果：	无
	*/
	void setBaudrate(uint16_t baudrate=9600);

	/*
	功能：	串口打印文本字符
	参数：	msg, 要打印的字符
			ln, 是否要换行
	结果：	无
	*/
	void printMessage(String msg, bool ln=true);

	/*
	功能：	串口打印整数
	参数：	num, 要打印的整数值
			format, 要输出的进制，DEC--十进制，HEX--十六进制，BIN--二进制
					(DEC=10, HEX=16, BIN=2)
			ln, 是否要换行
	结果：	无
	*/
	void printInteger(long num, uint8_t format=DEC, bool ln=true);

	/*
	功能：	串口打印小数，也可以打印整数
	参数：	num, 要打印的数值
			ln, 是否要换行
	结果：	无
	*/
	void printFloat(float num, bool ln=true);

	/*
	功能：	获取系统开机后运行的时长
	参数：	无
	结果：	以毫秒为单位的时长
	*/
	unsigned long runtime();

	/*
	功能：	设置看门狗的超时时长
	参数：	timemout, 0--0.5秒，1--1秒，2--2秒，4--4秒，8--8秒
	结果：	无
	*/
	void watchdogEnable(uint8_t timeout);

	/*
	功能：	关闭看门狗
	参数：	无
	结果：	无
	*/
	void watchdogDisable();

	/*
	功能：	复位看门狗
	参数：	无
	结果：	无
	*/
	void watchdogReset();
	
	/*
	功能：	保存数据
	参数：	pos, 要保存数据的位置，有效区间是 0~255
			value, 要保存的数值
	结果：	无
	*/
	void saveData(uint8_t pos, float value);

	/*
	功能：	读取数据
	参数：	pos, 要读取数据的位置，有效区间是 0~255
	结果：	读取到的数值
	*/
	float fetchData(uint8_t pos);

};


extern _XSystem XSystem;


#endif //__XSYSTEM_H__