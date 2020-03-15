/* XRGBLed.h
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
 *     This file is a header file for XRGBLed.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XRGBLED_H__
#define __XRGBLED_H__


#include <XBlock.h>

#define DEFAULT_MAX_LED_NUMBER  	(32)

#define XRGBLed_API_setColor		(0x01)	/*!< void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) */
#define XRGBLed_API_setAllColor		(0x02)	/*!< void setAllColor(uint8_t red, uint8_t green, uint8_t blue) */
#define XRGBLed_API_show			(0x03)	/*!< void show() */
#define XRGBLed_API_showColor		(0x04)	/*!< void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) */
#define XRGBLed_API_showAllColor	(0x05)	/*!< void showAllColor(uint8_t red, uint8_t green, uint8_t blue) */
#define XRGBLed_API_clear			(0x06)	/*!< void clear() */


class XRGBLed : public XNBlock{
public:
	XRGBLed();
	~XRGBLed();

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
	���ܣ�	��ȡRGB���������
	������	��
	�����	RGB��������
	*/
	uint8_t getNumber() { return count_led; }

	/*
	���ܣ�	����RGB�ʵƵ���ɫ����Ҫ����show()����Ч
	������	index, �Ƶı�� 1~N��0��ʾȫ����
			red, ��ɫ������ֵ, 0~255
			green, ��ɫ������ֵ, 0~255
			blue, ��ɫ������ֵ, 0~255
	�����	��
	*/
	void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

	/*
	���ܣ�	��setColor()���õ���ɫ��ʾ
	������	��
	�����	��
	*/
	void show();

	/*
	���ܣ�	���ò���ʾRGB�ʵƵ���ɫ
	������	index, �Ƶı�� 1~N��0��ʾȫ����
			red, ��ɫ������ֵ, 0~255
			green, ��ɫ������ֵ, 0~255
			blue, ��ɫ������ֵ, 0~255
	�����	��
	*/
	void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

	/*
	���ܣ�	�����ɫ���ò�Ϩ��RGB�ʵ�
	������	index, �Ƶı�� 1~N��0��ʾȫ����
	�����	��
	*/
	void clear(uint8_t index = 0);

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int init(uint8_t pin);
	void rgbled_sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port);

	int8_t _portId;
	uint8_t count_led;
	uint8_t *pixels;
	uint8_t pinMask;
	const volatile uint8_t *ws2812_port;
};


#endif //__XRGBLED_H__
