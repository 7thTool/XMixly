/* XSevenColorLight.h
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
 *     This file is a header file for XSevenColorLight.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XSEVENCOLORLIGHT_H__
#define __XSEVENCOLORLIGHT_H__



#define SCL_COLOR_BLACK		0
#define SCL_COLOR_RED		1
#define SCL_COLOR_GREEN		2
#define SCL_COLOR_YELLOW	3
#define SCL_COLOR_BLUE		4
#define SCL_COLOR_MAGENTA	5
#define SCL_COLOR_CHING		6
#define SCL_COLOR_WHITE		7


class XSevenColorLight {
public:
	XSevenColorLight();
	~XSevenColorLight();

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

	int setup(const char *model, const uint8_t pin1, const uint8_t pin2);

	void reset();

	/*
	功能：	点亮七彩灯
	参数：	index，0-所有灯，1-灯1, 2-灯2, ...
			color，显示颜色，0-黑，1-红，2-绿，4-蓝，3-黄（红+绿），5-品红（红+蓝），6-青（蓝+绿），7-白
	结果：	无
	*/
	void showColor(uint8_t index, uint8_t color);
	
	/*
	功能：	熄灭七彩灯
	参数：	index，0-所有灯，1-灯1, 2-灯2, ...
	结果：	无
	*/
	void clear(uint8_t index);

private:
	int8_t	_portId;
    void	*_impl;
};


#endif //__XSEVENCOLORLIGHT_H__

