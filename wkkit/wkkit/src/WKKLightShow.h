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

#include <XBlock.h>
#include <XRGBLed.h>
#include <wkkit.h>


#define WKKLightShow_API_showColor		(1)	/*!< void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) */
#define WKKLightShow_API_showMeteor		(2)	/*!< void showMeteor(uint8_t speed, uint8_t red, uint8_t green, uint8_t blue) */
#define WKKLightShow_API_showBreath		(3)	/*!< void showBreath(uint8_t index, uint8_t speed, uint8_t red, uint8_t green, uint8_t blue) */
#define WKKLightShow_API_clear			(4)	/*!< void clear(uint8_t index) */


class WKKLightShow : public XNServer {
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

	/*
	功能：	关闭RGB彩灯
	参数：	index, RGB彩灯编号，0表示全部
	结果：	无
	*/
	void clear(uint8_t index);

#ifdef XBRIDGE_SUPPORT
protected:
	/*!< XNBlock interface */
	int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

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



