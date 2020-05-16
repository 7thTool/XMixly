/* XLEDMatrix.h
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
 *     This file is a header file for XLEDMatrix.cpp.
 *
 * Version: 1.0.0
 */
 

#ifndef __XLEDMATRIX_H__
#define __XLEDMATRIX_H__



#define XLEDMatrix_EFFECT_NONE					(0)
#define XLEDMatrix_EFFECT_UP_ROLL				(1)
#define XLEDMatrix_EFFECT_DOWN_ROLL				(2)
#define XLEDMatrix_EFFECT_LEFT_ROLL				(3)
#define XLEDMatrix_EFFECT_RIGHT_ROLL			(4)
#define XLEDMatrix_EFFECT_FLICKER				(5)


#define XLEDMatrix_FLAG_X						(0)
#define XLEDMatrix_FLAG_RECTANGLE				(1)
#define XLEDMatrix_FLAG_TRIGANLE				(2)
#define XLEDMatrix_FLAG_CIRCLE					(3)
#define XLEDMatrix_FLAG_UP						(4)
#define XLEDMatrix_FLAG_DOWN					(5)
#define XLEDMatrix_FLAG_LEFT					(6)
#define XLEDMatrix_FLAG_RIGHT					(7)
#define XLEDMatrix_FLAG_STOP					(8)
#define XLEDMatrix_FLAG_FORWARD_LEFT			(9)
#define XLEDMatrix_FLAG_FORWARD_RIGHT			(10)
#define XLEDMatrix_FLAG_BACKWARD_LEFT			(11)
#define XLEDMatrix_FLAG_BACKWARD_RIGHT			(12)
#define XLEDMatrix_FLAG_CUP						(13)
#define XLEDMatrix_FLAG_BANNER					(14)


#define XLEDMatrix_EMOTICON_COOL	      		(0)
#define XLEDMatrix_EMOTICON_SMILE      			(1)
#define XLEDMatrix_EMOTICON_LAUGH				(2)
#define XLEDMatrix_EMOTICON_GRIEVANCE			(3)
#define XLEDMatrix_EMOTICON_ANGRY				(4)
#define XLEDMatrix_EMOTICON_ANGER				(5)
#define XLEDMatrix_EMOTICON_CRY					(6)
#define XLEDMatrix_EMOTICON_NAUGHTY				(7)
#define XLEDMatrix_EMOTICON_LOVE				(8)




class XLEDMatrix {
public:
	XLEDMatrix();
	~XLEDMatrix();

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
	���ܣ�	������ʾ����
	������	brightness, 0-7��0���7��������Ĭ��Ϊ4
	�����	��
	*/
	void setBrightness(uint8_t brightness);

	/*
	���ܣ�	������ʾ�Ƿ�ɫ
	������	value�� 0-����ɫ��1-��ɫ
	�����	��
	*/
	void setColorInverse(uint8_t value);
	
	/*
	���ܣ�	������ʾЧ��
	������	effect, ��ʾЧ�����ͣ�XLEDMatrix_EFFECT_XXX, 
			speed����ʾЧ���ٶȣ�0-���٣�1-������2-����
	�����	��
	*/
	void setEffect(uint8_t effect, uint8_t speed=1);

	/*
	���ܣ�	��ʾλͼ
	������	bitmap����Ҫ��ʾ��λͼbufferָ��
			len��λͼ�ֽ���
	�����	��
	*/
	void showBitmap(uint8_t *bitmap, uint8_t len);
	
	/*
	���ܣ�	����ĳһ����ʾ����
	������	column����Ҫ�������ݵ��к�
			value����Ҫ���µ���һ������
	�����	��
	*/
	void updateColumn(uint8_t column, uint8_t value);
	
	/*
	���ܣ�	����ĳһ����ʾ����
	������	x����Ҫ�������ݵ���һ���x����
			y����Ҫ�������ݵ���һ���y����
			value��0--Ϩ��1--����
	�����	��
	*/
	void updatePoint(uint8_t x, uint8_t y, uint8_t value);
	
	/*
	���ܣ�	��ʾ��ֵ��ÿ������ռ������3*8����ʾ��������(�ԡ�16*8����LED������Ϊ��˵��):
			1. ֧�ָ�����ʾ
			2. ���������ʾ3λС��(1.234), �������2λС��(-1.23)
			3. ���������ʾ4������(1234), ���������ʾ3λ����(-123)
			4. ��������10000������ʾ0000����������-1000��ʾ-000����ʾ������
	������	num����Ҫ��ʾ����ֵ
	�����	��
	*/
	void showNumber(float num);
	
	/*
	���ܣ�	��16������ʾ��ֵ��ÿ������ռ������3*8����ʾ��������(�ԡ�16*8����LED������Ϊ��˵��):
			1. ��֧��0�����������ҹ̶���ʾ4���ֶΣ�0����ʾΪ��0000��
			2. �����Ϊ��FFFF������65535��������Χ��ʾ��----��
	������	num����Ҫ��ʾ����ֵ
	�����	��
	*/
	void showNumberHex(uint32_t num);
	
	/*
	���ܣ�	��ʾ�ַ�����ÿ���ַ�ռ������6*8
	������	str����Ҫ��ʾ���ַ���ָ��, �֧��16���ַ�
	�����	��
	*/
	void showString(char *str);
	
	/*
	���ܣ�	��ʾ���ֱ�ֵ������ʱ�ӻ�ȷ֣�12:03��ÿ������ռ������3*8
	������	a��ʱ��ʱֵ����߱ȷ�ֵ�������λ����
			b��ʱ�ӷ�ֵ���ұ߱ȷ�ֵ�������λ����
	�����	��
	*/
	void showNumberPair(uint8_t a, uint8_t b);
	
	/*
	���ܣ�	��ʾ����
	������	emot����Ҫ��ʾ�ı������, XLEDMatrix_EMOTICON_XXX
	�����	��
	*/
	void showEmoticon(uint8_t emot);
	
	/*
	���ܣ�	��ʾ��ʶ
	������	flag����Ҫ��ʾ�ı�ʶ���, XLEDMatrix_FLAG_XXX
	�����	��
	*/
	void showFlag(uint8_t flag);
	
	/*
	���ܣ�	�ƶ�λͼ
	������	x�����������ƶ�ֵ��������ʾ�����ƶ��� 0��ʾ���ƶ��� ������ʾ�����ƶ�
			y�����������ƶ�ֵ��������ʾ�����ƶ��� 0��ʾ���ƶ��� ������ʾ�����ƶ�
	�����	��
	*/
	void move(int8_t x, int8_t y);

	/*
	���ܣ�	����͹ر���ʾ
	������	��
	�����	��
	*/
	void clear();

private:
	int8_t	_portId;
	void	*_impl;

};

#endif	// __XLEDMATRIX_H__