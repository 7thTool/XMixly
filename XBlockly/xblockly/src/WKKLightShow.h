/* WKKLightShow.h
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
 *     This file is a header file for WKKLightShow.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __WKKLIGHTSHOW_H__
#define __WKKLIGHTSHOW_H__


#include <XRGBLed.h>



class WKKLightShow {
public:
	WKKLightShow();
	~WKKLightShow();

	/*
	功能：	初始化
	参数：	rgb, RGB彩灯模块实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(XRGBLed *rgb);

	void reset();
	void loop();

	/*
	功能：	设置旋转灯光
	参数：	speed, 旋转速度，0--2分别表示慢、正常、快
			red/green/blue, 分别表示红、绿、蓝颜色分量，取值范围0~255
			duration, 此函数的执行时间
	结果：	无
	*/
	void showMeteor(uint8_t speed, uint8_t red, uint8_t green, uint8_t blue, int duration=0);

	/*
	功能：	设置旋转灯光
	参数：	speed, 旋转速度，0--2分别表示慢、正常、快
			value, [23:16]表示红, [15:8]表示绿，[7:0]表示蓝，取值范围都是0~255
			duration, 此函数的执行时间
	结果：	无
	*/
	void showMeteor(uint8_t speed, uint32_t value, int duration=0);

	/*
	功能：	设置呼吸灯
	参数：	speed, 呼吸速度，0--2分别表示慢、正常、快
			red/green/blue, 分别表示红、绿、蓝颜色分量，取值范围0~255
			duration, 此函数的执行时间
	结果：	无
	*/
	void showBreath(uint8_t index, uint8_t speed, uint8_t red, uint8_t green, uint8_t blue, int duration=0);

	/*
	功能：	设置呼吸灯
	参数：	speed, 呼吸速度，0--2分别表示慢、正常、快
			value, [23:16]表示红, [15:8]表示绿，[7:0]表示蓝，取值范围都是0~255
			duration, 此函数的执行时间
	结果：	无
	*/
	void showBreath(uint8_t index, uint8_t speed, uint32_t value, int duration=0);

private:
	void loopMeteor();
	void loopBreath();
	
	XRGBLed	*	_rgb;
	uint8_t		_mode;
	uint8_t		_index;
	uint8_t 	_speed;
	uint8_t 	_red;
	uint8_t 	_green;
	uint8_t 	_blue;
	uint8_t 	_step; // [7]: 0-up, 1-down, [6:0] step.
	unsigned long _timestamp;
};

#endif //__WKKLIGHTSHOW_H__



