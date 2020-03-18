
/* XIRAvoiding.h
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
 *     This file is a header file for XIRAvoiding.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XIRAVODING_H__
#define __XIRAVODING_H__

#include <XBlock.h>


class XIRAvoiding : public XNBlock {
public:
    XIRAvoiding();
    ~XIRAvoiding();

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
	功能：	开启障碍物检测，并设置敏感度
	参数：	sensitive, 敏感度，0表示关闭，1-100表示敏感度由低到高
	结果：	无
	备注：	模块setup()成功之后，默认开启了障碍物检测
	*/
	void start(uint8_t sensitive = 100);

	/*
	功能：	关闭障碍物检测
	参数：	无
	结果：	无
	*/
	void stop();

	/*
	功能：	获取前方是否有障碍物状态
	参数：	无
	结果：	1-检测到前方有障碍物，0-没检测到前方有障碍物
	*/
	uint8_t getStatus(); 

private:
	int8_t _portId;
	uint8_t _model;
	uint8_t _pin;
	uint8_t _enPin;
};

#endif //__XIRAVODING_H__

