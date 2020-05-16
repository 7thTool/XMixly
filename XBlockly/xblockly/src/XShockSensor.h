/* XShockSensor.h
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
 *     This file is a header file for XShockSensor.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XShockSensor_H__
#define __XShockSensor_H__



class XShockSensor {
public:
    XShockSensor();
    ~XShockSensor();
	
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

	int setup(const char *model, const uint8_t pinD);
	
	void reset();

	/*
	���ܣ�	��ȡ�Ƿ�����
	������	��
	�����	1-��⵽���𶯣�0-û��⵽����
	*/
	uint8_t isShocking(); 


private:
	int8_t _portId;
	uint8_t _pin;
};

#endif //__XShockSensor_H__


