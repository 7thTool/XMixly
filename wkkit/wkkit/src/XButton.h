/* XButton.h
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
 *     This file is a header file for XButton.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XBUTTON_H__
#define __XBUTTON_H__


#include <XBlock.h>


#define XButton_API_isPressed		(1)	/*!< uint8_t isPressed() */
#define XButton_API_isKnocked		(2)	/*!< uint8_t isKnocked() */

/*	pdata
 *		- register: nouse
 *		- notify: uint8_t status; 0 or 1
 */
#define XButton_EVT_Change			(0x01)


class XButton : public XNBlock {
public:
	XButton();
	~XButton();

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
	功能：	检测按钮是否被按下
	参数：	无
	结果：	返回0表示没有被按下，否则表示被按下
	*/
	uint8_t isPressed();

	/*
	功能：	检测按钮是否被触动。触动是指按钮从弹起到按下的一次动作
	参数：	无
	结果：	返回0表示没有被触动，否则表示被触动了
	*/
	uint8_t isKnocked();

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#ifdef XBRIDGE_SUPPORT_NOTIFY
	int8_t onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
	int8_t onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize);
#endif
#endif // XBRIDGE_SUPPORT

private:
	int8_t	_portId;
	uint8_t	_pin;
	uint8_t	_knocked;
#ifdef XBRIDGE_SUPPORT_NOTIFY
	uint8_t	_evtMask;
	uint8_t _status;
#endif
};


#endif	// __XBUTTON_H__
