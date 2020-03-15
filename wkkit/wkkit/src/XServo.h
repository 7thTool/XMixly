/* XServo.h
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
 *     This file is a header file for XServo.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XSERVO_H__
#define __XSERVO_H__

#include <XBlock.h>
#include <Servo.h>

#define XServo_API_setAngle	(0x01)
#define XServo_API_getAngle	(0x02)

class XServo : public XNBlock {
public:
    XServo() : XNBlock(), _portId(-1), _servo(NULL) {}
    ~XServo();

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
	���ܣ�	���ö���Ƕ�
	������	angle, �Ƕ�ֵ��0~359
	�����	��
	*/
	void setAngle(uint16_t angle);

	/*
	���ܣ�	��ȡ����Ƕ�
	������	��
	�����	�Ƕ�ֵ��0~359
	*/
	uint16_t getAngle();

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t _portId;
    Servo * _servo;
};

#endif //__XSERVO_H__

