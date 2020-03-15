/* WKKSystem.cpp
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
 *     This file is an implement of wukong-kit xsystem function.
 *
 * History:
 * Version: 1.0.0
 */



#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <EEPROM.h>
#include <xport.h>
#include <XI2C.h>
#include <WKKSystem.h>


_XSystem XSystem;


#define WAKEUP_PIN 						(3)
#define COPROCESSOR_I2C_RESET_PIN 		(10)
#define COPROCESSOR_I2C_SELECT_PIN 		(8)
#define COPROCESSOR_I2C_ADDRESS 		(0x3a)
#define COPROCESSOR_CMD_ADDRESS  		(0x00)

#define COPROCESSOR_BID_ADDRESS  				(0x20)
#define COPROCESSOR_BID_CHECKCODE_ADDRESS  		(0x30)





#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#ifdef WKK_SLEEP_ENABLE
volatile bool _sleeping = false;
#endif


_XSystem::_XSystem()
{
	LOGN("_XSystem::_XSystem()");
}

_XSystem::~_XSystem()
{
	LOGN("_XSystem::~_XSystem()");
}

int _XSystem::setup()
{
	LOGN("_XSystem::setup()");
	
	// reset co-processor
	pinMode(10, OUTPUT);
	digitalWrite(10, 1);
	delay(1);
	digitalWrite(10, 0);

	PortInit(); //MUST < 150ms

	delay(228); //MUST = 300ms
	return 0;
}

void _XSystem::setBaudrate(uint16_t baudrate)
{
	LOG("_XSystem::setBaudrate("); LOG(baudrate); LOGN(")");

	if ((baudrate == 9600) ||
		(baudrate == 19200) ||
		(baudrate == 38400)) {
		Serial.begin(baudrate);
	}
}

void _XSystem::printMessage(String msg, bool ln)
{
	LOG("_XSystem::printMessage("); LOG(msg); LOG(ln); LOGN(")");

	if (ln) {
		Serial.println(msg);
	} else {
		Serial.print(msg);
	}
}

void _XSystem::printInteger(long num, uint8_t format, bool ln)
{
	LOG("_XSystem::printInteger("); LOG(num); LOG(","); LOG(format); LOG(","); LOG(ln); LOGN(")");

	if ((format != DEC) && (format != HEX) && (format != BIN)) {
		format = DEC;
	}
	
	if (ln) {
		Serial.println(num, format);
	} else {
		Serial.print(num, format);
	}
}

void _XSystem::printFloat(float num, bool ln)
{
	LOG("_XSystem::printFloat("); LOG(num); LOG(","); LOG(ln); LOGN(")");

	if (ln) {
		Serial.println(num);
	} else {
		Serial.print(num);
	}
}

void _XSystem::getBID(uint8_t BID[5], uint8_t *key)
{
	XI2C.read(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_BID_ADDRESS, BID, 5);
	if(key != NULL)
		XI2C.read(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_BID_CHECKCODE_ADDRESS, key, 1);
}

void _XSystem::setBID2(uint8_t code)
{
    uint8_t buf[2];
    int8_t ret = 0;
    
    buf[0] = 0x70;
    buf[1] = code;

    ret = XI2C.write(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_CMD_ADDRESS, buf, 2);
    if(ret == -2) 
        XI2C.reset(COPROCESSOR_I2C_RESET_PIN, COPROCESSOR_I2C_SELECT_PIN);
}

uint32_t _XSystem::getSN()
{
	LOGN("_XSystem::getSN()");
	return ((uint32_t)boot_signature_byte_get(1) << 24) |	// Calibration Byte
			((uint32_t)boot_signature_byte_get(21) << 16) |	// UID Bytes
			((uint32_t)boot_signature_byte_get(22) << 8) |
			(uint32_t)boot_signature_byte_get(23);
}

unsigned long _XSystem::runtime()
{
	LOGN("_XSystem::runtime()");
	return millis();
}

void _XSystem::watchdogEnable(uint8_t timeout)
{
	LOGN("_XSystem::watchdogEnable("); LOG(timeout); LOGN(")");

	switch (timeout) {
	case 0:	// 0.5秒
		wdt_enable(WDTO_500MS);
		break;
	case 1:	// 1秒
		wdt_enable(WDTO_1S);
		break;
	case 2:	// 2秒
		wdt_enable(WDTO_2S);
		break;
	case 4:	// 4秒
		wdt_enable(WDTO_4S);
		break;
	case 8:	// 8秒
		wdt_enable(WDTO_8S);
		break;
	default:
		break;
	}
}

void _XSystem::watchdogDisable()
{
	LOGN("_XSystem::watchdogDisable()");
	wdt_disable();
}

void _XSystem::watchdogReset()
{
	LOGN("_XSystem::watchdogReset()");
	wdt_reset();
}

/* buffer byte data protocol:
 * buf[0]: bit7-4: 0x0 means set motor command 
 * buf[0]: bit7-4: 0x1 means set buzzer command 
 * buf[0]: bit7-4: 0x2 means power down command 
 *                 bit3-0: reserved
 * 				   buf[1]: reserved 
 * 				   buf[2]: reserved
 * buf[0]: bit7-4: 0x3 means sleep command 
 *                 bit3-0: reserved
 * 				   buf[1]: reserved 
 * 				   buf[2]: reserved
 * buf[0]: bit7-4: 0x4 means wakeup command 
 *                 bit3-0: reserved
 * 				   buf[1]: reserved 
 * 				   buf[2]: reserved
 * buf[0]: bit7-4: 0x5 means reset XIP45 module command 
 *                 bit3-0: reserved
 * 				   buf[1]: reserved 
 * 				   buf[2]: reserved
 * buf[0]: bit7-4: 0x6 means reboot command 
 *                 bit3-0: reserved
 * 				   buf[1]: reserved 
 * 				   buf[2]: reserved
 * buf[0]: bit7-4: 0x7 means set franchiser code
 *				   bit3-0: reserved
 *				   buf[1]: franchiser code
 *				   buf[2]: reserved
 * buf[0]: bit7-4: 0x8~0xf reserved 
 */


void _XSystem::powerOff()
{
	uint8_t buf = 0x20;
	int8_t ret = 0;

	LOGN("_XSystem::powerOff()");

	ret = XI2C.write(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_CMD_ADDRESS, &buf, 1);
	if(ret == -2) {
		XI2C.reset(COPROCESSOR_I2C_RESET_PIN, COPROCESSOR_I2C_SELECT_PIN);
	}
}

#ifdef WKK_SLEEP_ENABLE
static inline bool wasSleeping(void)
{
	bool a = _sleeping;
	_sleeping = false;
	return a;
}

static inline void handle_interrupt()
{
	if (wasSleeping())  
	{
		/*	  
		Arduino was waked up by IRQ.		  
		If you shut down external peripherals before sleeping, you	
		can reinitialize them here. Look on ATMega's datasheet for	  
		hardware limitations in the ISR when microcontroller just    
		leave any low power state.	 */
	}
	else
	{
	    /*    
	    The IRQ happened in awake state.        
	    This code is for the "normal" ISR.    
	    */
	}
}

void _XSystem::sleep(uint8_t mode)
{
	uint8_t buf = 0x30;
	int8_t ret = 0;
	LOGN("_XSystem::sleep()");

	ret = XI2C.write(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_CMD_ADDRESS, &buf, 1);
	if(ret == -2) 
		XI2C.reset(COPROCESSOR_I2C_RESET_PIN, COPROCESSOR_I2C_SELECT_PIN);

	attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), handle_interrupt, RISING);

	//let atmega328p chip self go to sleep and wait wakeup
	// FIXME: mode range
	avrSleep(mode);

	while(_sleeping==true);//enter sleep

	detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));
	
	buf = 0x40;
	ret = XI2C.write(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_CMD_ADDRESS, &buf, 1);
	if(ret == -2) 
		XI2C.reset(COPROCESSOR_I2C_RESET_PIN, COPROCESSOR_I2C_SELECT_PIN);

}

void _XSystem::avrSleep(uint8_t mode)
{
	delay(100);
	set_sleep_mode(mode); 

	_sleeping = true;
	sleep_enable();
	sleep_mode();
	sleep_disable();
 }
#endif	// WKK_SLEEP_ENABLE

void _XSystem::reboot()
{
	uint8_t buf = 0x60;
	int8_t ret = 0;

	LOGN("_XSystem::reboot()");

	ret = XI2C.write(COPROCESSOR_I2C_SELECT_PIN, COPROCESSOR_I2C_ADDRESS, COPROCESSOR_CMD_ADDRESS, &buf, 1);
	if(ret == -2) 
		XI2C.reset(COPROCESSOR_I2C_RESET_PIN, COPROCESSOR_I2C_SELECT_PIN);

	while(1);
}

void _XSystem::saveData(uint8_t pos, float value)
{
	LOGN("_XSystem::saveData("); LOG(pos); LOG(","); LOG(value); LOGN(")");

	/*!< 1024 bytes on the ATmega328P */
	EEPROM.put(pos * 4, value);
}

float _XSystem::fetchData(uint8_t pos)
{
	float value;
	LOGN("_XSystem::fetchData("); LOG(pos); LOGN(")");

	/*!< FIXME: 1024 bytes on the ATmega328P */
	EEPROM.get(pos * 4, value);
	return value;
}



