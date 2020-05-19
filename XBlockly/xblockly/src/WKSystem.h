/* WKSystem.h
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
 *     This file is a header file for WKSystem.
 *
 * Version: 1.0.0
 */


#ifndef __WKSYSTEM_H__
#define __WKSYSTEM_H__

#include <xport.h>
#include <XSystem.h>

class _WKSystem : public _XSystem {
public:
	_WKSystem() {}
	~_WKSystem() {}

	/*
	功能：	初始化
	参数：	无
	结果：	成功返回0，失败返回负数
	*/
	int setup() {

		// reset co-processor
		pinMode(10, OUTPUT);
		digitalWrite(10, 1);
		delay(1);
		digitalWrite(10, 0);

		PortInit(); //MUST < 150ms

		delay(228); //MUST = 300ms

		return 0;
	}

};

_WKSystem XSystem;


#endif //__WKSYSTEM_H__