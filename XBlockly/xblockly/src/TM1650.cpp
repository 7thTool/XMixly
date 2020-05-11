/* TM1650.cpp
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
 *     This file is a driver for TM1650 chip.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <Wire.h>
#include <TM1650.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define TM1650_DISPLAY_BASE 0x34 // Address of the left-most digit 
#define TM1650_DCTRL_BASE   0x24 // Address of the control register of the left-most digit
#define TM1650_NUM_DIGITS   16 // max number of digits
#define TM1650_MAX_STRING   128 // number of digits

#define TM1650_BIT_ONOFF	0b00000001
#define TM1650_MSK_ONOFF	0b11111110
#define TM1650_BIT_DOT		0b00000001
#define TM1650_MSK_DOT		0b11110111
#define TM1650_BRIGHT_SHIFT	4
#define TM1650_MSK_BRIGHT	0b10001111
#define TM1650_MIN_BRIGHT	0
#define TM1650_MAX_BRIGHT	7

//0~9,A,b,C,d,E,F
static const int8_t TubeTab[] PROGMEM ={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

TM1650::TM1650(uint8_t aNumDigits) 
{
	iNumDigits =  (aNumDigits > TM1650_NUM_DIGITS) ? TM1650_NUM_DIGITS : aNumDigits;
}

TM1650::~TM1650() 
{
#ifndef USE_DIO_CTRL
	//Wire.end();
#endif
}

/** Initialization
 * initializes the driver. Turns display on, but clears all digits.
 */
void TM1650::init(uint8_t dataPin, uint8_t clkPin)
{
	uint8_t i;

	LOGN("TM1650::init()");

	for (i=0; i<iNumDigits; i++) {
		iBuffer[i] = 0;
		iCtrl[i] = 0;
	}
#ifndef USE_DIO_CTRL
	Wire.begin();

    Wire.beginTransmission(TM1650_DISPLAY_BASE);
    iActive = (Wire.endTransmission(true) == 0) ? 1 : 0;
	clearDisplay();
	displayOn();
#else
	_clkPin = clkPin;
	_dataPin = dataPin;
	pinMode(_clkPin,OUTPUT);
	pinMode(_dataPin,OUTPUT);

	clearDisplay();
	displayOn();
#endif

	//设置亮度	
	for (i=0; i<iNumDigits; i++) {
		iCtrl[i] = (iCtrl[i] & TM1650_MSK_BRIGHT) | ( BRIGHT_TYPICAL << TM1650_BRIGHT_SHIFT );
		writeCmd(TM1650_DCTRL_BASE+i,  iCtrl[i]);
	}
}

void TM1650::display(uint8_t DispData[])
{
	uint8_t val;
	uint8_t dot;

	LOGN("TM1650::display()");
#ifndef USE_DIO_CTRL	
	if (!iActive) return;
#endif
	for (uint8_t i=0; i<iNumDigits; i++) {
		LOG("DispData[");LOG(i);LOG("]=");LOGN(DispData[i]);
		if (DispData[i] == 0x7f)
		{
			iBuffer[i]= 0x0;
			dot = 0x0;
		}
		else 
		{ 
			if(DispData[i] == 0x40) //"-"
			{
				iBuffer[i]= 0x40;
				dot = 0x0;
			}
			else
			{
				val = DispData[i] & 0x7f;
				dot = DispData[i] & 0x80;

				LOG("val=");LOGN(val);
				iBuffer[i] = pgm_read_byte_near(TubeTab + val);
			}
		}

		LOG("iBuffer[");LOG(i);LOG("]=");LOGN(iBuffer[i]);
		LOG("dot=");LOGN(dot);

		writeCmd(TM1650_DISPLAY_BASE+i,  iBuffer[i] | dot);
	}
	
	displayOn();
}

void TM1650::updateOneChannel(uint8_t index, uint8_t DispData)
{
	uint8_t val;

	LOGN("TM1650::updateOneChannel()");
#ifndef USE_DIO_CTRL	
	if (!iActive) return;
#endif

	if (DispData == 0x7f)
	{
		iBuffer[index] = 0x0;
	}
	else 
	{ 
		if(DispData == 0x40) //"-"
		{
			iBuffer[index]= 0x40;
		}
		else
		{
			val = DispData & 0x7f;
	
			LOG("val=");LOGN(val);
			iBuffer[index] = pgm_read_byte_near(TubeTab + val);
		}
	}

	for (uint8_t i=0; i<iNumDigits; i++) {
		LOG("iBuffer[");LOG(i);LOG("]=");LOGN(iBuffer[i]);
		writeCmd(TM1650_DISPLAY_BASE+i,  iBuffer[i]);
	}
	
	displayOn();
}


/** Clear all digits. Keep the display on.
 */
void TM1650::clearDisplay(void)
{
	// clears all digits
#ifndef USE_DIO_CTRL
	if (!iActive) return;
#endif
	for (uint8_t i=0; i<iNumDigits; i++) {
		iBuffer[i] = 0;
		writeCmd(TM1650_DISPLAY_BASE+i,  0);
	}

	displayOff();

}

void TM1650::displaySegment(uint8_t BitAddr, uint8_t segData)
{
	LOGN("TM1650::displaySegment()");
	LOG("BitAddr=");LOGN(BitAddr);
	LOG("segData=");LOGN(segData);
#ifndef USE_DIO_CTRL
	if (!iActive) return;
#endif
	if(BitAddr == 0)
	{
		for (uint8_t i=0; i<iNumDigits; i++) {
			iBuffer[i] = segData;
			writeCmd(TM1650_DISPLAY_BASE+i,  segData);
		}   
	}
	else 
	{
		iBuffer[BitAddr-1] = segData;
		//writeCmd(TM1650_DISPLAY_BASE+BitAddr-1,  segData);
		for (uint8_t i=0; i<iNumDigits; i++) {
			writeCmd(TM1650_DISPLAY_BASE+i,  iBuffer[i]);
		} 
	}

	displayOn();
}

void TM1650::clearSegment(uint8_t BitAddr, uint8_t segData)
{
#ifndef USE_DIO_CTRL
	if (!iActive) return;
#endif
	if(BitAddr == 0)
	{
		for (uint8_t i=0; i<iNumDigits; i++) {
			iBuffer[i] &= ~segData;
			writeCmd(TM1650_DISPLAY_BASE+i,  iBuffer[i]);
		}
	}
	else
	{
		iBuffer[BitAddr-1] &= ~segData;
		writeCmd(TM1650_DISPLAY_BASE+BitAddr-1,  iBuffer[BitAddr-1]);
	}
}

/** Turns the display on
 */
void TM1650::displayOn()
// turn all digits on
{
#ifndef USE_DIO_CTRL
  if (!iActive) return;
#endif
  for (uint8_t i=0; i<iNumDigits; i++) {
  	iCtrl[i] = (iCtrl[i] & TM1650_MSK_ONOFF) | TM1650_BIT_DOT;
	writeCmd(TM1650_DCTRL_BASE+i,  iCtrl[i]);
  }
}

/** Turns the display off
 */
void TM1650::displayOff()
// turn all digits off
{
#ifndef USE_DIO_CTRL
  if (!iActive) return;
#endif
  for (uint8_t i=0; i<iNumDigits; i++) {
  	iCtrl[i] = (iCtrl[i] & TM1650_MSK_ONOFF);
	writeCmd(TM1650_DCTRL_BASE+i,  iCtrl[i]);
  }
}

void TM1650::writeCmd(uint8_t cmdAddr,  uint8_t cmdData)
{
#ifndef USE_DIO_CTRL
	Wire.beginTransmission(cmdAddr);
	Wire.write(cmdData);
	Wire.endTransmission();
#else
	//写显存必须从高地址开始写
	I2CStart();
	I2CWrByte(cmdAddr<<1); //第一个显存地址
	I2Cask();
	I2CWrByte(cmdData);
	I2Cask();
	I2CStop();;
#endif
}

#ifdef USE_DIO_CTRL
void TM1650::I2CStart(void)	//开始信号
{
	digitalWrite(_clkPin,HIGH);//send start signal to TM1650
	pinMode(_dataPin,OUTPUT);
	digitalWrite(_dataPin,HIGH); 
	delayMicroseconds(5);
	digitalWrite(_dataPin,LOW); 
}

void TM1650::I2Cask(void) //ACK信号
{
	uint8_t timeout = 1;
	digitalWrite(_clkPin,HIGH);
	delayMicroseconds(5);
	digitalWrite(_clkPin,LOW);
	pinMode(_dataPin,INPUT);
	while(digitalRead(_dataPin) && timeout<=100)
	{
	  timeout++;	
	}
	pinMode(_dataPin,OUTPUT);
	delayMicroseconds(5);
	digitalWrite(_clkPin,LOW);

}

void TM1650::I2CStop(void) //停止信号
{
	digitalWrite(_clkPin,HIGH);
	pinMode(_dataPin,OUTPUT);
	digitalWrite(_dataPin,LOW); 
	delayMicroseconds(5);
	digitalWrite(_dataPin,HIGH); 
}

void TM1650::I2CWrByte(uint8_t oneByte) //写一个字节高位在前，低位在后
{
	uint8_t i,t;
	digitalWrite(_clkPin,LOW);
	delayMicroseconds(1);
	pinMode(_dataPin,OUTPUT);
	for(i=0;i<8;i++)
	{	
		t  = oneByte & 0x80;
		oneByte = oneByte<<1;
		if(t == 0x80)
		{
			digitalWrite(_dataPin,HIGH); 
		}
		else
		{
			digitalWrite(_dataPin,LOW); 
		}
		digitalWrite(_clkPin,LOW);
		delayMicroseconds(5);
		digitalWrite(_clkPin,HIGH);
		delayMicroseconds(5);
		digitalWrite(_clkPin,LOW);
	}
}
#endif

