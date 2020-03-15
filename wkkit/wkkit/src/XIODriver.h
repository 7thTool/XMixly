/* XIODriver.h
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
 *     This file is a header file for XIODriver.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XIODriver_H__
#define __XIODriver_H__

#include <XBlock.h>


#define XIODriver_API_digitalRead 			(0x01)	/*!< uint8_t digitalRead() */
#define XIODriver_API_digitalWrite			(0x02)	/*!< void digitalWrite() */
#define XIODriver_API_analogRead			(0x03)	/*!< int32_t analogRead() */




class XIODriver : public XNBlock {
public:
    XIODriver();
    ~XIODriver();
	
	/*
	���ܣ�	��ʼ������չģ�顱
	������	model, δʹ��, ������ַ��� ""
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
	���ܣ�	���ֵ�ƽ����
	������	sno, 1--S1�źţ�2--S2�ź�
	�����	0--�͵�ƽ��1--�ߵ�ƽ
	*/	
	uint8_t digitalRead(uint8_t sno);
	
	/*
	���ܣ�	���ֵ�ƽ���
	������	sno, 1--S1�źţ�2--S2�ź�
	�����	0--�͵�ƽ��1--�ߵ�ƽ
	*/		
	void digitalWrite(uint8_t sno, uint8_t value);

	/*
	���ܣ�	ģ���ƽ����
	������	sno, 1--S1�źţ�2--S2�ź�
	�����	��ƽֵ��С
	*/	
	int32_t analogRead(uint8_t sno);
	

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t _portId;
	uint8_t _pin1;
	uint8_t _pin2;
};

#endif //__XIODriver_H__

