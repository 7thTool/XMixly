/* XLightSensor.h
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
 *     This file is a header file for XLightSensor.cpp.
 *
 * Version: 1.0.0
 */
 

#ifndef __XLIGHTSENSOR_H__
#define __XLIGHTSENSOR_H__


#include <XBlock.h>


#define XLightSensor_API_getLuminance 		(1)	/*!< uint8_t getLuminance() */

/*	pdata
 *		- register: nouse
 *		- notify: uint8_t luminance;
 */
#define XLightSensor_EVT_Change		(0x01)


class XLightSensor : public XNBlock {
public:
    XLightSensor();
    ~XLightSensor();

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
	���ܣ�	��⻷����������
	������	��
	�����	0~100
	*/
	uint8_t getLuminance();

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
	int8_t _portId;
	uint8_t _pin;
#ifdef XBRIDGE_SUPPORT_NOTIFY
	uint8_t	_evtMask;
	uint8_t _sensitive;
	uint8_t _luminance;
#endif
};


#endif //__XLIGHTSENSOR_H__