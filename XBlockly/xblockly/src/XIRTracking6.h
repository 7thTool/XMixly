/* XIRTracking6.h
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
 *     This file is a header file for XIRTracking6.
 *
 * Version: 1.0.0
 */
 

#ifndef __XIRTRACKING6_H__
#define __XIRTRACKING6_H__


#include <XIRTracking.h>


class XIRTracking6 : public XIRTracking  {
public:
	XIRTracking6() {}
	~XIRTracking6() {}

	int setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel)
	{
		if ( (PIN_A4 != sda) || (PIN_A5 != scl)) {
			LOGN("Connect to I2C pin failed!");
			return -1;
		}
		
		if (!strcmp(model, "IRT3360")) {
			_model = MODEL_CHANNELS_6;
			_resetPin = rst;
			_selectPin = sel;
		}
		else {
			LOG("Unknown model of ");LOGN(model);
			return -1;
		}
		return 0;
	}
};

#endif //__XIRTRACKING6_H__