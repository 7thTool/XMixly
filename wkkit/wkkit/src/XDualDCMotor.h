/* XDualDCMotor.h
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
 *     This file is a header file for XDualDCMotor.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XDualDCMotor_H__
#define __XDualDCMotor_H__


#include <XBlock.h>

#define XDualDCMotor_API_setMotorSpeed	(0x01)	/*!< void setMotorSpeed(uint8_t motor, int8_t speed) */
#define XDualDCMotor_API_setAllSpeed	(0x02)	/*!< void setAllSpeed(int8_t speed1, int8_t speed2) */
#define XDualDCMotor_API_stopMotor		(0x03)	/*!< void stopMotor(uint8_t motor) */
#define XDualDCMotor_API_stopAllMotor	(0x04)	/*!< void stopAllMotor() */


#define DDM_SPEED_VALUE_MAX		100

class XDualDCMotor : public XNBlock {
public:
	XDualDCMotor() : XNBlock(), _portId(-1), impl(NULL), _speed1(0), _speed2(0) {}
	~XDualDCMotor();

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
	功能：	设置单个电机的速度
	参数：	motor, 1表示M1电机，2表示M2电机
			speed, -100~100
				0，表示停止
				1~100，正转，从最慢到最快
				-1~-100，反转，从最慢到最快
	结果：	无
	*/
	void setMotorSpeed(uint8_t motor, int8_t speed);

	/*
	功能：	同时设置两个电机的速度
	参数：	speed1, M1电机的速度，-100~100
			speed2, M2电机的速度，-100~100
	结果：	无
	*/
	void setAllSpeed(int8_t speed1, int8_t speed2);

	/*
	功能：	停止单个电机
	参数：	motor, 1表示M1电机，2表示M2电机
	结果：	无
	*/
	void stopMotor(uint8_t motor);

	/*
	功能：	同时停止两个电机
	参数：	无
	结果：	无
	*/
	void stopAllMotor();

#ifdef XBRIDGE_SUPPORT
protected:
	/*!< XNBlock interface */
	int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t	_portId;
    void	*impl;
	int8_t _speed1;
	int8_t _speed2;
};

#endif //__XDualDCMotor_H__

