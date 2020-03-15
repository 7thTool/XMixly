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

#include <XBlock.h>


#define XBuzzer_API_playTone 			(0x01)	/*!< void playTone(uint16_t frequency, uint32_t duration) */


class XBuzzer : public XNBlock {
public:
	XBuzzer() : XNBlock(), _pin(0xFF) {}
	~XBuzzer ();

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
	功能：	播放音频
	参数：	frequency，声音频率
			duration，持续时长，毫秒单位
	结果：	无
	*/
	void playTone(uint16_t frequency, uint32_t duration = 0);

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t	_portId;
	uint8_t _pin;
};


#endif //__XBUZZER_H__

