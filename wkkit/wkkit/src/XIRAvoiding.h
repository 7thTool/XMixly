
/* XIRAvoiding.h
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
 *     This file is a header file for XIRAvoiding.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XIRAVODING_H__
#define __XIRAVODING_H__

#include <XBlock.h>


#define XIRAvoiding_API_getStatus 			(0x01)	/*!< uint8_t getStatus() */


/*	pdata 
 *		- register: nouse
 *		- notify: uint8_t status;
 */
#define XIRAvoiding_EVT_Change		(0x01)


class XIRAvoiding : public XNBlock {
public:
    XIRAvoiding();
    ~XIRAvoiding();

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
	���ܣ�	�����ϰ����⣬���������ж�
	������	sensitive, ���жȣ�0��ʾ�رգ�1-100��ʾ���ж��ɵ͵���
	�����	��
	��ע��	ģ��setup()�ɹ�֮��Ĭ�Ͽ������ϰ�����
	*/
	void start(uint8_t sensitive = 100);

	/*
	���ܣ�	�ر��ϰ�����
	������	��
	�����	��
	*/
	void stop();

	/*
	���ܣ�	��ȡǰ���Ƿ����ϰ���״̬
	������	��
	�����	1-��⵽ǰ�����ϰ��0-û��⵽ǰ�����ϰ���
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
#endif // XBRIDGE_SUPPORT

private:
	int8_t _portId;
	uint8_t _model;
	uint8_t _pin;
	uint8_t _enPin;
#ifdef XBRIDGE_SUPPORT_NOTIFY
	uint8_t	_evtMask;
	uint8_t _status;
#endif
};


#endif //__XIRAVODING_H__

