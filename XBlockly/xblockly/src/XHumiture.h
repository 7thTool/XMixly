
/* XHumiture.h
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
 *     This file is a header file for XHumiture.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XHUMITURE_H__
#define __XHUMITURE_H__


class XHumiture {
public:
	XHumiture();
	~XHumiture();

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

	int setup(const char *model, const uint8_t dat);

	void reset();
	
	/*
	功能：	获取当前湿度值
	参数：	无
	结果：	返回湿度值，单位：%
	*/
	float getHumidity();

	/*
	功能：	获取当前温度值
	参数：	无
	结果：	返回温度值，单位：℃
	*/
	float getTemperature();

private:
	void update();

	int8_t _portId;
	uint8_t _pin;
	float _lastHumidity;
	float _lastTemperature;
};

#endif //__XHUMITURE_H__


