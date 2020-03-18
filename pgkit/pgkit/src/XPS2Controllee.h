/* XPS2Controllee.h
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
 *     This file is a header file for XPS2Controllee.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __XPS2CONTROLLEE_H__
#define __XPS2CONTROLLEE_H__


#include <XBlock.h>
#include <X24GReceiver.h>


#define XPS2_BTN_LX			0		/*!< 状态：-100~0~100 */
#define XPS2_BTN_LY			1		/*!< 状态：-100~0~100 */
#define XPS2_BTN_RX			2		/*!< 状态：-100~0~100 */
#define XPS2_BTN_RY			3		/*!< 状态：-100~0~100 */

#define XPS2_BTN_L1			(8+0)	/*!< 状态：0 or 1 */
#define XPS2_BTN_L2			(8+1)	/*!< 状态：0 or 1 */
#define XPS2_BTN_R1			(8+2)	/*!< 状态：0 or 1 */
#define XPS2_BTN_R2			(8+3)	/*!< 状态：0 or 1 */
#define XPS2_BTN_UP			(16+0)	/*!< 状态：0 or 1 */
#define XPS2_BTN_DOWN		(16+1)	/*!< 状态：0 or 1 */
#define XPS2_BTN_LEFT		(16+2)	/*!< 状态：0 or 1 */
#define XPS2_BTN_RIGHT		(16+3)	/*!< 状态：0 or 1 */
#define XPS2_BTN_SELECT		(24+0)	/*!< 状态：0 or 1 */
#define XPS2_BTN_MODE		(24+1)	/*!< 状态：0 or 1 */
#define XPS2_BTN_START		(24+2)	/*!< 状态：0 or 1 */
#define XPS2_BTN_TURBO		(24+3)	/*!< 状态：0 or 1 */
#define XPS2_BTN_TRIANGLE	(32+0)	/*!< 状态：0 or 1 */
#define XPS2_BTN_XSHAPED	(32+1)	/*!< 状态：0 or 1 */
#define XPS2_BTN_SQUARE		(32+2)	/*!< 状态：0 or 1 */
#define XPS2_BTN_ROUND		(32+3)	/*!< 状态：0 or 1 */
#define XPS2_BTN_BUTTON_L	(32+4)	/*!< 状态：0 or 1 */
#define XPS2_BTN_BUTTON_R	(32+5)	/*!< 状态：0 or 1 */


class XPS2Controllee {
public:
    XPS2Controllee();
	~XPS2Controllee();

	/*
	功能：	初始化PS2控制接收设备
	参数：	receiver, 2.4G接收器的实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(X24GReceiver *receiver);

	/*
	功能：	检查是否收到PS2按键消息
	参数：	无
	结果：	无返回0，有返回1
	*/
	int available();

	/*
	功能：	检查PS2按键状态。注意要在available()返回收到消息后调用才有效
	参数：	btn, PS2按键值，如"XPS2_BTN_RX"
	结果：	返回按键状态
	*/
	int8_t checkButtonStatus(uint8_t btn);

private:
	X24GReceiver *	_24GReceiver;
	uint8_t			_lx;
	uint8_t			_ly;
	uint8_t			_rx;
	uint8_t			_ry;
	uint8_t			_btnGroup[4];
};


#endif	// __XPS2CONTROLLEE_H__