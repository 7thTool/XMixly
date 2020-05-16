/* XIRTracking.h
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
 *     This file is a header file for XIRTracking.cpp.
 *
 * Version: 1.0.0
 */
 

#ifndef __XIRTRACKING_H__
#define __XIRTRACKING_H__



#define MAX_CHANNEL 2

class XIRTracking {
public:
	XIRTracking();
	~XIRTracking();

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

	int setup(const char *model, const uint8_t s1, const uint8_t s2);

	void reset();

	/*
	功能：	检测红外收发对光的状态。最多支持8路对管，从bit0~bit7对应S1~S8的状态。
	参数：	无
	结果：	每个bit是一路状态，0表示脱轨，1表示在轨。最多支持8路对管，从bit0~bit7分别对应S1~S8
	*/
	uint8_t getStatus();
	
private:
	int8_t _portId; // -1 means onboard block, -2 means setup failed.
    uint8_t _pin[MAX_CHANNEL];
	uint8_t _selectPin;
	uint8_t _resetPin;
	uint8_t _model;
};

#endif //__XIRTRACKING_H__