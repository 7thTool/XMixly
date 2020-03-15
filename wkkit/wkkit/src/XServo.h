/* XServo.h
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
 *     This file is a header file for XServo.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XSERVO_H__
#define __XSERVO_H__

#include <XBlock.h>
#include <Servo.h>

#define XServo_API_setAngle	(0x01)
#define XServo_API_getAngle	(0x02)

class XServo : public XNBlock {
public:
    XServo() : XNBlock(), _portId(-1), _servo(NULL) {}
    ~XServo();

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
	功能：	设置舵机角度
	参数：	angle, 角度值，0~359
	结果：	无
	*/
	void setAngle(uint16_t angle);

	/*
	功能：	获取舵机角度
	参数：	无
	结果：	角度值，0~359
	*/
	uint16_t getAngle();

#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t _portId;
    Servo * _servo;
};

#endif //__XSERVO_H__

