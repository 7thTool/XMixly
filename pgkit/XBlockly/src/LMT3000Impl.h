/* LMT3000Impl.h
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
 *     This file is a header file for LMT3000Impl.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __LMT3000IMPL_H__
#define __LMT3000IMPL_H__

class LMT3000Impl {
public:
	LMT3000Impl(const char *model);
    ~LMT3000Impl() {
		clear();
	}

    /*!< Interface */
	void setup(uint8_t rstPin, uint8_t selPin);
	
	void setBrightness(uint8_t brightness);
	void setColorInverse(uint8_t value);
	void setEffect(uint8_t effect, uint8_t speed);
	void showBitmap(uint8_t *bitmap, uint8_t len);
	void updateColumn(uint8_t column, uint8_t value);
	void updatePoint(uint8_t x, uint8_t y, uint8_t value);
	void showNumber(float num);
	void showNumberHex(uint32_t num);
	void showString(char *str);
	void showNumberPair(uint8_t a, uint8_t b);
	void showEmoticon(uint8_t emot);
	void showFlag(uint8_t flag);
	void move(int8_t x, int8_t y);
	void clear();



private:
	uint8_t _i2cAddr;
	uint8_t _selectPin;
	uint8_t _resetPin;
};

#endif //__LMT3000IMPL_H__

