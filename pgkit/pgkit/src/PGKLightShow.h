/* PGKLightShow.h
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
 *     This file is a header file for PGKLightShow.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __PGKLIGHTSHOW_H__
#define __PGKLIGHTSHOW_H__

#include <XBlock.h>
#include <XRGBLed.h>


#define PGKLightShow_API_showColor		(1)	/*!< void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) */
#define PGKLightShow_API_clear			(4)	/*!< void clear(uint8_t index) */


class PGKLightShow : public XNServer {
public:
	PGKLightShow();
	~PGKLightShow();

	/*
	功能：	初始化
	参数：	rgb, RGB彩灯模块实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(XRGBLed *rgb);

	void reset();
	void loop();

	/*
	功能：	设置显示色彩
	参数：	index, RGB彩灯编号，0表示全部
			red/green/blue, 分别表示红、绿、蓝颜色分量，取值范围0~255
			closeOthers, 是否关闭其他的RGB灯
	结果：	无
	*/
	void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t clearOthers=0);
	
	/*
	功能：	设置显示色彩
	参数：	index, RGB彩灯编号，0表示全部
			value, [23:16]表示红, [15:8]表示绿，[7:0]表示蓝，取值范围都是0~255
			closeOthers, 是否关闭其他的RGB灯
	结果：	无
	*/
	void showColor(uint8_t index, uint32_t value, uint8_t clearOthers=0);

	/*
	功能：	关闭RGB彩灯
	参数：	index, RGB彩灯编号，0表示全部
	结果：	无
	*/
	void clear(uint8_t index);

private:
	XRGBLed	*	_rgb;
};

#endif //__PGKLIGHTSHOW_H__



