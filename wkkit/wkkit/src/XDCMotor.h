/* XDCMotor.h
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
 *     This file is a header file for XDCMotor.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XDCMotor_H__
#define __XDCMotor_H__


#include <XBlock.h>

#define XDCMotor_API_start		(0x01)	/*!< void start(int8_t speed) */
#define XDCMotor_API_stop		(0x02)	/*!< void stop() */


#define DDM_SPEED_VALUE_MAX		100

class XDCMotor : public XNBlock {
public:
	XDCMotor() : XNBlock(), _portId(-1){}
	~XDCMotor();

	/*
	���ܣ�	��ʼ������չģ�顱
	������	model, ģ���ͺ�
			port, ���ӵ����ذ�Ķ˿ڱ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *model, const char *port);

	/*
	���ܣ�	��ʼ��������ģ�顱
	������	label, ģ�������ذ��ϵı���
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *label);

	void reset();

	/*
	���ܣ�	���õ�����ٶ�
	������	speed, -100~100
	�����	��
	*/
	void start(int8_t speed);

	/*
	���ܣ�	ֹͣ���
	������	��
	�����	��
	*/
	void stop();


#ifdef XBRIDGE_SUPPORT
protected:
#if 1
	/*!< XNBlock interface */
	int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif
#endif // XBRIDGE_SUPPORT

private:
	int8_t	_portId;
   	uint8_t _pwmPin;
	uint8_t _dirPin;
	uint8_t _portType;
};

#endif //__XDCMotor_H__

