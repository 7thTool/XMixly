/* XBuzzer.h
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
 *     This file is a header file for XBuzzer.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XBUZZER_H__
#define __XBUZZER_H__



class XBuzzer {
public:
	XBuzzer();
	~XBuzzer();

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

	int setup(const char *model, const uint8_t pinD);

	void reset();

	/*
	���ܣ�	������Ƶ
	������	frequency������Ƶ��
			duration������ʱ�������뵥λ
	�����	��
	*/
	void playTone(uint16_t frequency, uint32_t duration = 0);

	/*
	���ܣ�	���ý���ʱ��
	������	beatTime��10msΪ��λ������ʱ��, 0xFF��ʾĬ��ֵ
			noteGap��10msΪ��λ���������ʱ����0xFF��ʾĬ��ֵ
	�����	��
	*/
	void setNoteParameter(uint8_t beatTime = 50, uint8_t noteGap = 40);

	/*
	���ܣ�	��������
	������	note��������DO, RE, ME, FA, SOL, LA, SI������Ӧ��ֵ 1~7����ֹ����Ӧ��ֵ0
			scale�����ߡ��͡��С��ߡ� ��Ӧ��ֵ 0~2
			tone��������C,D,E,F,G,A,B�� ��Ӧ��ֵ 0~6
			beat�����ġ�1/8, 1/4, 1/2, 1, 2�� ��Ӧ��ֵ 1,2,4,8,16
	�����	��
	*/
	void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat);

private:
	uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone);
	
	int8_t	_portId;
	uint8_t _pin;
	uint16_t _beatTime;
	uint16_t _noteGap;
};


#endif //__XBUZZER_H__

