/* XIRTracking.h
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
 *     This file is a header file for XIRTracking.cpp.
 *
 * Version: 1.0.0
 */
 

#ifndef __XIRTRACKING_H__
#define __XIRTRACKING_H__


#include <XBlock.h>


#define XIRTracking_API_getStatus	(1)	/*!< uint8_t getStatus() */

/*	pdata
 *		- register: nouse
 *		- notify: uint8_t status;
 */
#define XIRTracking_EVT_Change		(0x01)


#define MAX_CHANNEL 2

class XIRTracking : public XNBlock  {
public:
	XIRTracking();
	~XIRTracking();

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
	���ܣ�	�������շ��Թ��״̬�����֧��8·�Թܣ���bit0~bit7��ӦS1~S8��״̬��
	������	��
	�����	ÿ��bit��һ·״̬��0��ʾ�ѹ죬1��ʾ�ڹ졣���֧��8·�Թܣ���bit0~bit7�ֱ��ӦS1~S8
	*/
	uint8_t getStatus();

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#ifdef XBRIDGE_SUPPORT_NOTIFY
	int8_t onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
	int8_t onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize);
#endif
#endif
	
private:
	int8_t _portId; // -1 means onboard block, -2 means setup failed.
    uint8_t _pin[MAX_CHANNEL];
	uint8_t _selectPin;
	uint8_t _resetPin;
	uint8_t _model;
#ifdef XBRIDGE_SUPPORT_NOTIFY
	uint8_t	_evtMask;
	uint8_t _preStatus;
#endif
};

#endif //__XIRTRACKING_H__