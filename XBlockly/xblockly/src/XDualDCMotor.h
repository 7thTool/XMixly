/* XDualDCMotor.h
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
 *     This file is a header file for XDualDCMotor.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XDualDCMotor_H__
#define __XDualDCMotor_H__



#define DDM_SPEED_VALUE_MAX		100

class XDualDCMotor {
public:
	XDualDCMotor();
	~XDualDCMotor();

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

	int setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel);

	void reset();

	/*
	���ܣ�	���õ���������ٶ�
	������	motor, 1��ʾM1�����2��ʾM2���
			speed, -100~100
				0����ʾֹͣ
				1~100����ת�������������
				-1~-100����ת�������������
	�����	��
	*/
	void setMotorSpeed(uint8_t motor, int8_t speed);

	/*
	���ܣ�	ͬʱ��������������ٶ�
	������	speed1, M1������ٶȣ�-100~100
			speed2, M2������ٶȣ�-100~100
	�����	��
	*/
	void setAllSpeed(int8_t speed1, int8_t speed2);

	/*
	���ܣ�	ֹͣ�������
	������	motor, 1��ʾM1�����2��ʾM2���
	�����	��
	*/
	void stopMotor(uint8_t motor);

	/*
	���ܣ�	ͬʱֹͣ�������
	������	��
	�����	��
	*/
	void stopAllMotor();

private:
	int8_t	_portId;
    void	*_impl;
	int8_t _speed1;
	int8_t _speed2;
};

#endif //__XDualDCMotor_H__

