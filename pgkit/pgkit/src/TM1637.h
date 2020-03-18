/* TM1637.h
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
 *     This file is a header file for TM1637.cpp.
 *
 * Version: 1.0.0
 */


#ifndef TM1637_h
#define TM1637_h
#include <inttypes.h>
#include <Arduino.h>

/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

class TM1637
{
public:
	TM1637(uint8_t aNumDigits = 4);
	~TM1637(); 
	void init(uint8_t dataPin, uint8_t clkPin);        //To clear the display
	void display(uint8_t DispData[]);
	void updateOneChannel(uint8_t index, uint8_t DispData);
	void clearDisplay(void);
	void displaySegment(uint8_t BitAddr, uint8_t segData);
	void clearSegment(uint8_t BitAddr, uint8_t segNum);

private:
	void writeByte(uint8_t wr_data);//write 8bit data to tm1637
	void start(void);//send start bits
	void stop(void); //send stop bits
	uint8_t coding(uint8_t DispData);
	void display(uint8_t BitAddr,uint8_t DispData);

	uint8_t _clkPin;
	uint8_t _dataPin;
	uint8_t	iNumDigits;
	uint8_t Cmd_DispCtrl;
};
#endif
