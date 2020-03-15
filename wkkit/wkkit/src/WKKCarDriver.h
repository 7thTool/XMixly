/* WKKCarDriver.h
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
 *     This file is a header file for WKKCarDriver.cpp.
 *
 * Version: 1.0.0
 */

 
#ifndef __WKKCARDRIVER_H__
#define __WKKCARDRIVER_H__


#include <XBlock.h>
#include <XDualDCMotor.h>
#include <XIRTracking.h>
#include <XUltrasonic.h>
#include <wkkit.h>


#define WKKCarDriver_API_FORWARD	(1)	/*!< void forward(uint8_t speed) */
#define WKKCarDriver_API_BACKWARD	(2)	/*!< void backward(uint8_t speed) */
#define WKKCarDriver_API_TURN       (3)	/*!< void turn(uint8_t action, uint8_t speed, uint8_t angle) */
#define WKKCarDriver_API_STOP       (4)	/*!< void stop() */
#define WKKCarDriver_API_ALT       	(5)	/*!< void autoLineTracking(XIRTracking *irt, uint8_t speed) */
#define WKKCarDriver_API_AOA       	(6)	/*!< void autoObstacleAvoidance(XUltrasonic *uls, uint8_t speed) */


class WKKCarDriver : public XNServer {
public:
	WKKCarDriver();
	~WKKCarDriver();

	/*
	功能：	初始化行驶控制服务
	参数：	ddm, 双直流电机模块实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(XDualDCMotor *ddm);

	void reset();
	void loop();

	/*
	功能：	控制小车前进
	参数：	speed, 速度 0~100
	结果：	无
	*/
	void forward(uint8_t speed);

	/*
	功能：	控制小车后退
	参数：	speed, 速度 0~100
	结果：	无
	*/
	void backward(uint8_t speed);

	/*
	功能：	控制小车转弯
	参数：	speed, 速度 0~100
			degree, 角度 0~359
	结果：	无
	*/
	void turn(uint8_t speed, uint16_t degree);

	/*
	功能：	控制小车转弯
	参数：	action, 转弯动作，0--"左转前进", 1--"右转前进", 2--"左转后退", 3--"右转后退"
			speed, 速度 0~100
			angle, 角度 0~90
	结果：	无
	*/
	void turn(uint8_t action, uint8_t speed, uint8_t angle);

	/*
	功能：	控制小车停止
	参数：	无
	结果：	无
	*/
	void stop();

	/*
	功能：	控制小车自动巡线驾驶
	参数：	irt, 红外循迹传感器模块实例
			speed, 巡线速度，0--慢速，1--正常，2--快速
			duration, 此巡线接口调用一次的执行时长，单位毫秒
	结果：	无
	*/
	void autoLineTracking(XIRTracking *irt, uint8_t speed=2, int duration=0);

	/*
	功能：	控制小车自动巡线驾驶
	参数：	uls, 超声波测距模块实例
			speed, 巡线速度，0--慢速，1--正常，2--快速
			duration, 此巡线接口调用一次的执行时长，单位毫秒
	结果：	无
	*/
	void autoObstacleAvoidance(XUltrasonic *uls, uint8_t speed=2, int duration=0);

#ifdef XBRIDGE_SUPPORT
	friend class XBridge;
protected:
	/*!< XNBlock interface */
	int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	int8_t loopAutoLineTracking();
	int8_t loopAutoObstacleAvoidance();
	uint8_t mapSpeed(uint8_t speed);
	void calcDDMSpeed(uint8_t speed, uint16_t degree, int8_t *speed1, int8_t *speed2);	
	uint8_t mathRandomInt();
	uint16_t readUltrasonic();
	
	XDualDCMotor	*_ddm;
	XIRTracking 	*_irt;
	XUltrasonic 	*_uls;
	
	//for both service
	uint8_t 		_mode;
	uint8_t 		_speed;
	uint16_t		_degree;
	
	//for AutoLineTracking
	uint8_t 		_altTimeout;
	int8_t 			_altHighSpeed;
	int8_t 			_altLowSpeed;
	uint16_t		_tracking;
	
	//for AutoObstacleAvoidance
	uint8_t 		_aoaTimeout;
	int8_t 			_aoaRunSpeed;
	long			_dis;
	uint8_t 		_randVal;
	uint8_t 		_continueBackwardTimes;
};

#endif //__WKKCARDRIVER_H__