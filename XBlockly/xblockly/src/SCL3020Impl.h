/* SCL3020Impl.h
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
 *     This file is a header file for SCL3020Impl.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __SCL3020IMPL_H__
#define __SCL3020IMPL_H__

class SCL3020Impl {
public:
    SCL3020Impl() {}
    ~SCL3020Impl() {
		clear(0);
	}

    /*!< Interface */
	void setup(uint8_t rstPin, uint8_t selPin);

    void showColor(uint8_t index, uint8_t color);
	void clear(uint8_t index);

private:
	uint8_t _selectPin;
	uint8_t _resetPin;
};

#endif //__SCL3020IMPL_H__

