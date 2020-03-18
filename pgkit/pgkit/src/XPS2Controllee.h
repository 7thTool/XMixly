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


#define XPS2_BTN_LX			0		/*!< ״̬��-100~0~100 */
#define XPS2_BTN_LY			1		/*!< ״̬��-100~0~100 */
#define XPS2_BTN_RX			2		/*!< ״̬��-100~0~100 */
#define XPS2_BTN_RY			3		/*!< ״̬��-100~0~100 */

#define XPS2_BTN_L1			(8+0)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_L2			(8+1)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_R1			(8+2)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_R2			(8+3)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_UP			(16+0)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_DOWN		(16+1)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_LEFT		(16+2)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_RIGHT		(16+3)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_SELECT		(24+0)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_MODE		(24+1)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_START		(24+2)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_TURBO		(24+3)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_TRIANGLE	(32+0)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_XSHAPED	(32+1)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_SQUARE		(32+2)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_ROUND		(32+3)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_BUTTON_L	(32+4)	/*!< ״̬��0 or 1 */
#define XPS2_BTN_BUTTON_R	(32+5)	/*!< ״̬��0 or 1 */


class XPS2Controllee {
public:
    XPS2Controllee();
	~XPS2Controllee();

	/*
	���ܣ�	��ʼ��PS2���ƽ����豸
	������	receiver, 2.4G��������ʵ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(X24GReceiver *receiver);

	/*
	���ܣ�	����Ƿ��յ�PS2������Ϣ
	������	��
	�����	�޷���0���з���1
	*/
	int available();

	/*
	���ܣ�	���PS2����״̬��ע��Ҫ��available()�����յ���Ϣ����ò���Ч
	������	btn, PS2����ֵ����"XPS2_BTN_RX"
	�����	���ذ���״̬
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