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



#define DEFAULT_MAX_LED_NUMBER  	(32)


class XRGBLed {
public:
	XRGBLed();
	~XRGBLed();

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
	功能：	获取RGB灯珠的数量
	参数：	无
	结果：	RGB灯珠数量
	*/
	uint8_t getNumber() { return count_led; }

	/*
	功能：	设置RGB彩灯的颜色，需要调用show()才生效
	参数：	index, 灯的编号 1~N，0表示全部灯
			red, 红色分量的值, 0~255
			green, 红色分量的值, 0~255
			blue, 蓝色分量的值, 0~255
	结果：	无
	*/
	void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

	/*
	功能：	按setColor()设置的颜色显示
	参数：	无
	结果：	无
	*/
	void show();

	/*
	功能：	设置并显示RGB彩灯的颜色
	参数：	index, 灯的编号 1~N，0表示全部灯
			red, 红色分量的值, 0~255
			green, 红色分量的值, 0~255
			blue, 蓝色分量的值, 0~255
	结果：	无
	*/
	void showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

	/*
	功能：	清除颜色设置并熄灭RGB彩灯
	参数：	index, 灯的编号 1~N，0表示全部灯
	结果：	无
	*/
	void clear(uint8_t index = 0);

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

