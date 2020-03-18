/* XSegDisplay.h
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
 *     This file is a header file for XSegDisplay.cpp.
 *
 * Version: 1.0.0
 */
 

#ifndef __XSEGDISPLAY_H__
#define __XSEGDISPLAY_H__

#include <XBlock.h>


class XSegDisplay : public XNBlock {
public:
	XSegDisplay() : XNBlock(), _portId(-1), _model(0), _impl(NULL) {}
	~XSegDisplay();

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
	���ܣ�	��ʾ��ֵ����ʾ��������(��4λ�����Ϊ��˵��):
			1. ֧�ָ�����ʾ
			2. ���������ʾ3λС��(1.234), �������2λС��(-1.23)
			3. ���������ʾ4������(1234), ���������ʾ3λ����(-123)
			4. ��������10000������ʾ0000����������-1000��ʾ-000����ʾ������
	������	num, Ҫ��ʾ����ֵ
	�����	��
	*/
	void showNumber(float num);
	
	/*
	���ܣ�	��ָ���Ľ��Ƹ�ʽ��ʾ��ֵ����ʾ��������(��4λ�����Ϊ��˵��):
			1. ��֧��0�����������ҹ̶���ʾ4���ֶΣ�0����ʾΪ��0000��
			2. ʮ���������Ϊ��9999����������Χ��ʾ��----��
			   ʮ�����������Ϊ��FFFF������65535��������Χ��ʾ��----��
			   �����������Ϊ��1111������15��������Χ��ʾ��----��
	������	num����Ҫ��ʾ����ֵ
			format, Ҫ����Ľ��ƣ�DEC--ʮ���ƣ�HEX--ʮ�����ƣ�BIN--������
					(DEC=10, HEX=16, BIN=2)
	�����	��
	*/
	void showNumber(uint32_t num, uint8_t format);

	/*
	���ܣ�	��ʾ�ַ�
	������	index, �����ҵ�����ܱ�ţ�1~N
			character����Ҫ��ʾ���ַ�, '0'~'9', 'A'~'F'
	�����	��
	*/	
	void showCharacter(uint8_t index, char character);

	/*
	���ܣ�	��ʾ����ܵ�ĳ��
	������	index, �����ҵ�����ܱ�ţ�1~N, 0��ʾ���������
			segment, ��"abcdefg."��8���ַ��ֱ��ʾ����ʾ��
	�����	��
	*/
	void showSegment(uint8_t index, char segment);

	/*
	���ܣ�	��ʾ����ܵ�ĳ��
	������	index, �����ҵ�����ܱ�ţ�1~N, 0��ʾ���������
			segData, ��bit0-7����Ӧ"abcdefg."��8�Σ������bit����1,��ö�Ӧ����ʾ����ʾ
	�����	��
	*/
	void showSegments(uint8_t index, uint8_t segData);

	/*
	���ܣ�	�����ʾ����ܵ�ĳ��
	������	index, �����ҵ�����ܱ�ţ�1~N, 0��ʾ���������
			segment, ��"abcdefg."��8���ַ��ֱ��ʾ����ʾ��
	�����	��
	*/
	void clearSegment(uint8_t index, char segment);

	/*
	���ܣ�	�����ʾ
	������	index, �����ҵ�����ܱ�ţ�1~N, 0��ʾ���������
	�����	��
	*/
	void clear(uint8_t index = 0);


private:
	float pow10(uint8_t n);
	void parsefloat(float f, uint8_t count, int *number, uint8_t *icount, uint8_t *dcount);

	int8_t	_portId;
	uint8_t _model;
	void	*_impl;
};

#endif	// __XSEGDISPLAY_H__