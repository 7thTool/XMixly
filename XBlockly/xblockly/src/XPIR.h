/* XPIR.h
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
 *     This file is a header file for XPIR.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XPIR_H__
#define __XPIR_H__



class XPIR {
public:
    XPIR();
    ~XPIR();
	
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

	int setup(const char *model, const uint8_t sta);
	
	void reset();

	/*
	功能：	获取前方是否有人移动
	参数：	无
	结果：	1-检测到前方有人移动，0-没检测到前方有人移动
	*/
	uint8_t isHumanMotionDetected(); 


private:
	int8_t _portId;
	uint8_t _pin;
};

#endif //__XPIR_H__


