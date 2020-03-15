
/* XHumiture.h
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
 *     This file is a header file for XHumiture.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XHUMITURE_H__
#define __XHUMITURE_H__


#include <XBlock.h>


#define XHumiture_API_getHumidity 			(0x01)	/*!< uint8_t getHumidity() */
#define XHumiture_API_getTemperature 		(0x02)	/*!< uint8_t getTemperature() */


/*	pdata
 *		- register: float sensitive;
 *		- notify: float temperature;
 */
#define XHumiture_EVT_Temperature_Change	(0x01)

/*	pdata
 *		- register: float sensitive;
 *		- notify: float humidity;
 */
#define XHumiture_EVT_Humidity_Change		(0x02)


class XHumiture : public XNBlock {
public:
	XHumiture();
	~XHumiture();

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
	功能：	获取当前湿度值
	参数：	无
	结果：	返回湿度值，单位：%
	*/
	float getHumidity();

	/*
	功能：	获取当前温度值
	参数：	无
	结果：	返回温度值，单位：℃
	*/
	float getTemperature();


#ifdef XBRIDGE_SUPPORT
protected:
    /*!< XNBlock interface */
    int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#ifdef XBRIDGE_SUPPORT_NOTIFY
	int8_t onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
	int8_t onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize);
#endif
#endif // XBRIDGE_SUPPORT

private:
	void update();

	int8_t _portId;
	uint8_t _pin;
	float _lastHumidity;
	float _lastTemperature;
	
#ifdef XBRIDGE_SUPPORT_NOTIFY
	uint8_t	_evtMask;
	uint8_t _evtCheck;
	float _tempSensitive;
	float _humiSensitive;
	float _preHumidity;
	float _preTemperature;
#endif


};

#endif //__XHUMITURE_H__


