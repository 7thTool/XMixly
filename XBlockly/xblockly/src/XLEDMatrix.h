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

	int setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel);

	void reset();

	/*
	功能：	设置显示亮度
	参数：	brightness, 0-7，0最暗，7最明亮，默认为4
	结果：	无
	*/
	void setBrightness(uint8_t brightness);

	/*
	功能：	设置显示是否反色
	参数：	value， 0-正常色，1-反色
	结果：	无
	*/
	void setColorInverse(uint8_t value);
	
	/*
	功能：	设置显示效果
	参数：	effect, 显示效果类型，XLEDMatrix_EFFECT_XXX, 
			speed，显示效果速度，0-慢速，1-正常，2-快速
	结果：	无
	*/
	void setEffect(uint8_t effect, uint8_t speed=1);

	/*
	功能：	显示位图
	参数：	bitmap，需要显示的位图buffer指针
			len，位图字节数
	结果：	无
	*/
	void showBitmap(uint8_t *bitmap, uint8_t len);
	
	/*
	功能：	更新某一列显示数据
	参数：	column，需要更新数据的列号
			value，需要更新的那一列数据
	结果：	无
	*/
	void updateColumn(uint8_t column, uint8_t value);
	
	/*
	功能：	更新某一点显示数据
	参数：	x，需要更新数据的那一点的x坐标
			y，需要更新数据的那一点的y坐标
			value，0--熄灭，1--点亮
	结果：	无
	*/
	void updatePoint(uint8_t x, uint8_t y, uint8_t value);
	
	/*
	功能：	显示数值，每个数字占用像素3*8。显示规则如下(以“16*8”的LED面板矩阵为例说明):
			1. 支持负数显示
			2. 正数最多显示3位小数(1.234), 负数最多2位小数(-1.23)
			3. 正数最多显示4个整数(1234), 负数最多显示3位整数(-123)
			4. 正数大于10000的数显示0000，负数大于-1000显示-000，表示超量程
	参数：	num，需要显示的数值
	结果：	无
	*/
	void showNumber(float num);
	
	/*
	功能：	以16进制显示数值，每个数字占用像素3*8。显示规则如下(以“16*8”的LED面板矩阵为例说明):
			1. 仅支持0和正整数，且固定显示4个字段，0将显示为“0000”
			2. 最大数为“FFFF”，即65535，超出范围显示“----”
	参数：	num，需要显示的数值
	结果：	无
	*/
	void showNumberHex(uint32_t num);
	
	/*
	功能：	显示字符串，每个字符占用像素6*8
	参数：	str，需要显示的字符串指针, 最长支持16个字符
	结果：	无
	*/
	void showString(char *str);
	
	/*
	功能：	显示数字比值，比如时钟或比分，12:03。每个数字占用像素3*8
	参数：	a，时钟时值或左边比分值，最多两位数字
			b，时钟分值或右边比分值，最多两位数字
	结果：	无
	*/
	void showNumberPair(uint8_t a, uint8_t b);
	
	/*
	功能：	显示表情
	参数：	emot，需要显示的表情类别, XLEDMatrix_EMOTICON_XXX
	结果：	无
	*/
	void showEmoticon(uint8_t emot);
	
	/*
	功能：	显示标识
	参数：	flag，需要显示的标识类别, XLEDMatrix_FLAG_XXX
	结果：	无
	*/
	void showFlag(uint8_t flag);
	
	/*
	功能：	移动位图
	参数：	x，横向像素移动值，负数表示向左移动， 0表示不移动， 正数表示向右移动
			y，纵向像素移动值，负数表示向下移动， 0表示不移动， 正数表示向上移动
	结果：	无
	*/
	void move(int8_t x, int8_t y);

	/*
	功能：	清除和关闭显示
	参数：	无
	结果：	无
	*/
	void clear();

private:
	int8_t	_portId;
	void	*_impl;

};

#endif	// __XLEDMATRIX_H__