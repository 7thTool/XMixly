/* DDM3001Impl.h
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
 *     This file is a header file for DDM3001Impl.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __DDM3001IMPL_H__
#define __DDM3001IMPL_H__

class DDM3001Impl {
public:
    DDM3001Impl(const char *model);
    ~DDM3001Impl() {
		setAllSpeed(0, 0);
	}

    /*!< Interface */
	void setup(uint8_t rstPin, uint8_t selPin);

    void setMotorSpeed(uint8_t motor, int8_t speed);
	void setAllSpeed(int8_t Lspeed, int8_t Rspeed);

private:
	uint8_t _i2cAddr;
	uint8_t _selectPin;
	uint8_t _resetPin;
};

#endif //__DDM3001IMPL_H__

