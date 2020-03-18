/* IRR3300Impl.h
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
 *     This file is a header file for IRR3300Impl.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __IRR3300IMPL_H__
#define __IRR3300IMPL_H__


#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <SoftwareSerial.h>



/* NEC Code table */
#define IR_BUTTON_POWER     (0x45)
#define IR_BUTTON_A         (0x45)
#define IR_BUTTON_B         (0x46)
#define IR_BUTTON_MENU      (0x47)
#define IR_BUTTON_C         (0x47)
#define IR_BUTTON_TEST      (0x44)
#define IR_BUTTON_D         (0x44)
#define IR_BUTTON_PLUS      (0x40)
#define IR_BUTTON_UP        (0x40)
#define IR_BUTTON_RETURN    (0x43)
#define IR_BUTTON_E         (0x43)
#define IR_BUTTON_PREVIOUS  (0x07)
#define IR_BUTTON_LEFT      (0x07)
#define IR_BUTTON_PLAY      (0x15)
#define IR_BUTTON_SETTING   (0x15)
#define IR_BUTTON_NEXT      (0x09)
#define IR_BUTTON_RIGHT     (0x09)
#define IR_BUTTON_MINUS     (0x19)
#define IR_BUTTON_DOWN      (0x19)
#define IR_BUTTON_CLR       (0x0D)
#define IR_BUTTON_F     	(0x0D)
#define IR_BUTTON_0     	(0x16)
#define IR_BUTTON_1    	 	(0x0C)
#define IR_BUTTON_2     	(0x18)
#define IR_BUTTON_3     	(0x5E)
#define IR_BUTTON_4     	(0x08)
#define IR_BUTTON_5     	(0x1C)
#define IR_BUTTON_6     	(0x5A)
#define IR_BUTTON_7     	(0x42)
#define IR_BUTTON_8     	(0x52)
#define IR_BUTTON_9     	(0x4A)

class IRR3300Impl {
public:
	IRR3300Impl(const char *model);
	~IRR3300Impl();

	int setup(uint8_t keyCheckPin, uint8_t rxPin);

	int available();

	int read();

	bool buttonState();

	uint8_t getCode();

	void loop();
private:
	volatile uint8_t _RxPin;
	volatile uint8_t _KeyCheckPin;
	uint8_t _irCode;
	uint8_t _preIrCode;
	SoftwareSerial *_mSoftSerial;
};

#endif //__IRR3300IMPL_H__

