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

	void reset();

	/*
	功能：	显示数值。显示规则如下(以4位数码管为例说明):
			1. 支持负数显示
			2. 正数最多显示3位小数(1.234), 负数最多2位小数(-1.23)
			3. 正数最多显示4个整数(1234), 负数最多显示3位整数(-123)
			4. 正数大于10000的数显示0000，负数大于-1000显示-000，表示超量程
	参数：	num, 要显示的数值
	结果：	无
	*/
	void showNumber(float num);
	
	/*
	功能：	以指定的进制格式显示数值。显示规则如下(以4位数码管为例说明):
			1. 仅支持0和正整数，且固定显示4个字段，0将显示为“0000”
			2. 十进制最大数为“9999”，超出范围显示“----”
			   十六进制最大数为“FFFF”，即65535，超出范围显示“----”
			   二进制最大数为“1111”，即15，超出范围显示“----”
	参数：	num，需要显示的数值
			format, 要输出的进制，DEC--十进制，HEX--十六进制，BIN--二进制
					(DEC=10, HEX=16, BIN=2)
	结果：	无
	*/
	void showNumber(uint32_t num, uint8_t format);

	/*
	功能：	显示字符
	参数：	index, 从左到右的数码管编号，1~N
			character，需要显示的字符, '0'~'9', 'A'~'F'
	结果：	无
	*/	
	void showCharacter(uint8_t index, char character);

	/*
	功能：	显示数码管的某段
	参数：	index, 从左到右的数码管编号，1~N, 0表示所有数码管
			segment, 由"abcdefg."共8个字符分别表示的显示段
	结果：	无
	*/
	void showSegment(uint8_t index, char segment);

	/*
	功能：	显示数码管的某段
	参数：	index, 从左到右的数码管编号，1~N, 0表示所有数码管
			segData, 从bit0-7，对应"abcdefg."共8段，如果该bit置上1,则该对应的显示段显示
	结果：	无
	*/
	void showSegments(uint8_t index, uint8_t segData);

	/*
	功能：	清除显示数码管的某段
	参数：	index, 从左到右的数码管编号，1~N, 0表示所有数码管
			segment, 由"abcdefg."共8个字符分别表示的显示段
	结果：	无
	*/
	void clearSegment(uint8_t index, char segment);

	/*
	功能：	清除显示
	参数：	index, 从左到右的数码管编号，1~N, 0表示所有数码管
	结果：	无
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