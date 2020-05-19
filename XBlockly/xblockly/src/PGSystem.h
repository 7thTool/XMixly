/* PGSystem.h
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
 *     This file is a header file for PGSystem.
 *
 * Version: 1.0.0
 */


#ifndef __PGSYSTEM_H__
#define __PGSYSTEM_H__

#include <xport.h>
#include <XSystem.h>

class _PGSystem : public _XSystem {
public:
	_PGSystem() {}
	~_PGSystem() {}

	/*
	功能：	初始化
	参数：	无
	结果：	成功返回0，失败返回负数
	*/
	int setup() {

		PortInit(); //MUST < 150ms

		delay(228); //MUST = 300ms

		return 0;
	}

};

_PGSystem XSystem;


#endif //__PGSYSTEM_H__