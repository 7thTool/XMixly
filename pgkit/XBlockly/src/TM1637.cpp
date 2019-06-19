/* TM1637.cpp
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
 *     This file is a driver for TM1637 chip.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include "TM1637.h"

#define TM1637_NUM_DIGITS   4 // max number of digits


//0~9,A,b,C,d,E,F
static const int8_t TubeTab[] PROGMEM ={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

TM1637::TM1637(uint8_t aNumDigits)
{
	iNumDigits =  (aNumDigits > TM1637_NUM_DIGITS) ? TM1637_NUM_DIGITS : aNumDigits;
}

TM1637::~TM1637() 
{
}

void TM1637::init(uint8_t dataPin, uint8_t clkPin)
{
  _clkPin = clkPin;
  _dataPin = dataPin;
  pinMode(_clkPin,OUTPUT);
  pinMode(_dataPin,OUTPUT);
  
  Cmd_DispCtrl = 0x88 + BRIGHT_TYPICAL;//Set the brightness and it takes effect the next time it displays.
  clearDisplay();
}

void TM1637::writeByte(uint8_t wr_data)
{
  uint8_t i,count1,count2;
  count1 = 0;
  count2 = 0;
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(_clkPin,LOW);      
    if(wr_data & 0x01)digitalWrite(_dataPin,HIGH);//LSB first
    else digitalWrite(_dataPin,LOW);
    wr_data >>= 1;      
    digitalWrite(_clkPin,HIGH);
      
  }  
  digitalWrite(_clkPin,LOW); //wait for the ACK
  digitalWrite(_dataPin,HIGH);
  digitalWrite(_clkPin,HIGH);     
  pinMode(_dataPin,INPUT);
  while(digitalRead(_dataPin) && count2<5)
  { 
    count1 +=1;
    if(count1 == 200)//
    {
     pinMode(_dataPin,OUTPUT);
     digitalWrite(_dataPin,LOW);
     count1 =0;
	 count2++;
    }
    pinMode(_dataPin,INPUT);
  }
  pinMode(_dataPin,OUTPUT);
  
}

//send start signal to TM1637
void TM1637::start(void)
{
  digitalWrite(_clkPin,HIGH);//send start signal to TM1637
  digitalWrite(_dataPin,HIGH); 
  digitalWrite(_dataPin,LOW); 
  digitalWrite(_clkPin,LOW); 
} 

//End of transmission
void TM1637::stop(void)
{
  digitalWrite(_clkPin,LOW);
  digitalWrite(_dataPin,LOW);
  digitalWrite(_clkPin,HIGH);
  digitalWrite(_dataPin,HIGH); 
}

//display function.Write to full-screen.
void TM1637::display(uint8_t DispData[])
{
  int8_t SegData[4];
  uint8_t i;
  for(i = 0;i < iNumDigits;i ++)
  {
    SegData[i] = coding(DispData[i]);
  }
  //coding(SegData);
  start();          //start signal sent to TM1637 from MCU
  writeByte(0x40);//ADDR_AUTO);//
  stop();           //
  start();          //
  writeByte(0xc0);//Cmd_SetAddr);//
  for(i=0;i < iNumDigits;i ++)
  {
    writeByte(SegData[i]);        //
  }
  stop();           //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();      //
}

void TM1637::display(uint8_t BitAddr,uint8_t DispData)
{
  uint8_t SegData;
  SegData = coding(DispData);
  start();          //start signal sent to TM1637 from MCU
  writeByte(0x44);//
  stop();           //
  start();          //
  writeByte(BitAddr|0xc0);//
  writeByte(SegData);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void TM1637::updateOneChannel(uint8_t index, uint8_t DispData)
{
	display(index,DispData);
}


void TM1637::displaySegment(uint8_t BitAddr, uint8_t segData)
{
  if(BitAddr == 0)
  {
  	start();          //start signal sent to TM1637 from MCU
    writeByte(0x40);//ADDR_AUTO);//
    stop();           //
    start();          //
    writeByte(0xc0);//Cmd_SetAddr);//
    writeByte(segData);        //
    writeByte(segData);        //
    writeByte(segData);        //
    writeByte(segData);        //
    stop();           //
    start();          //
    writeByte(Cmd_DispCtrl);//
    stop();     
  }
  else 
  {
    start();		  //start signal sent to TM1637 from MCU
    writeByte(0x44);//
    stop(); 		  //
    start();		  //
    writeByte((BitAddr-1)|0xc0);//
    writeByte(segData);//
    stop(); 		   //
    start();		  //
    writeByte(Cmd_DispCtrl);//
    stop(); 
  }
}

void TM1637::clearSegment(uint8_t BitAddr, uint8_t segData)
{
	(void)segData;
	if(BitAddr == 0)
	{
		clearDisplay();
	}
	else
		display(BitAddr-1,0x7f);
}

void TM1637::clearDisplay(void)
{
  display(0x00,0x7f);
  display(0x01,0x7f);
  display(0x02,0x7f);
  display(0x03,0x7f);
}

uint8_t TM1637::coding(uint8_t DispData)
{
  //uint8_t PointData;
  //if(_PointFlag == POINT_ON)PointData = 0x80;
  //else PointData = 0; 
  if(DispData == 0x7f) DispData = 0x00;// + PointData;//The bit digital tube off
  else if(DispData == 0x40) DispData = 0x40;
  //else if(DispData > 0x7f) DispData = TubeTab[DispData - 0x80] + 0x80;
  else if(DispData > 0x7f) DispData = pgm_read_byte(&TubeTab[DispData - 0x80]) + 0x80;
  //else DispData = TubeTab[DispData];// + PointData;
  else DispData = pgm_read_byte(&TubeTab[DispData]);// + PointData;
  return DispData;
}
