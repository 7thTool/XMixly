/* XBlock.h
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
 *     This file is a header file for XBlock.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XBLOCK_H__
#define __XBLOCK_H__


#include <XBridge.h>


/**
 *  Definition of block type.
 */
#define XBLOCK_TYPE_XButton       		(0x01)
#define XBLOCK_TYPE_XDualDCMotor		(0x02)
#define XBLOCK_TYPE_XUltrasonic    		(0x03)
#define XBLOCK_TYPE_XIRTracking    		(0x04)
#define XBLOCK_TYPE_XLightSensor   		(0x05)
#define XBLOCK_TYPE_XBuzzer        		(0x06)
#define XBLOCK_TYPE_XHumiture       	(0x07)
#define XBLOCK_TYPE_XRGBLed        		(0x08)
#define XBLOCK_TYPE_XAcceGyro      		(0x09)
#define XBLOCK_TYPE_XSoundSensor   		(0x0A)
#define XBLOCK_TYPE_XPIR           		(0x0B)
#define XBLOCK_TYPE_XSegDisplay    		(0x0C)
#define XBLOCK_TYPE_XIRSender      		(0x0D)
#define XBLOCK_TYPE_XIRReceiver    		(0x0E)
#define XBLOCK_TYPE_XIPC    			(0x0F)
#define XBLOCK_TYPE_XServo				(0x10)
#define XBLOCK_TYPE_XDCMotor			(0x11)
#define XBLOCK_TYPE_XIRAvoiding			(0x12)
#define XBLOCK_TYPE_XVoiceBroadcast		(0x13)
#define XBLOCK_TYPE_XLEDMatrix			(0x14)
#define XBLOCK_TYPE_XSevenColorLight	(0x15)
#define XBLOCK_TYPE_X24GReceiver		(0x16)
#define XBLOCK_TYPE_XPotentiometer		(0x17)


/**
 *  Interface of bridge port for Native.
 */
uint8_t * fetchU8(const uint8_t *param, uint8_t *val);
uint8_t * fetchU16(const uint8_t *param, uint16_t *val);
uint8_t * fetchU32(const uint8_t *param, uint32_t *val);
uint8_t * fetchString(const uint8_t *param, char **s);
uint8_t * fetchFloat(const uint8_t *param, float *val);

uint8_t * fillU8(uint8_t *result, uint8_t val);
uint8_t * fillU16(uint8_t *result, uint16_t val);
uint8_t * fillU32(uint8_t *result, uint32_t val);
uint8_t * fillString(uint8_t *result, const char *s);
uint8_t * fillFloat(uint8_t *result, float val);


/**
 *  Base class of Block Native. A block is a port of the bridge.
 */
class XNBlock {
public:
    XNBlock() : mFlag(0x00) {}
    virtual ~XNBlock() {}

	/*!< Reset block to initial status */
	virtual void reset() {}

#ifdef XBRIDGE_SUPPORT	
	friend class XNBridge;
protected:
	void setFlag(uint8_t uid, uint8_t dynamic) { mFlag = (dynamic ? 0x80 : 0x00) | (uid & 0x7F); }
	uint8_t uid() const { return mFlag & 0x7F; }
	uint8_t isDynamic() const { return (mFlag & 0x80) ? 1 : 0; }

    /*!< Called from Proxy to access API through XNBridge */
    virtual int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize,
							uint8_t *result, uint8_t *rsize) {
								(void)api; (void)param; (void )psize; (void)result; (void)rsize;
								return -1;
							}

    /*!< Notify event to Proxy through XNBridge */
#ifdef XBRIDGE_SUPPORT_NOTIFY
	virtual int8_t onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize) {
		(void)evt; (void)param; (void)psize; (void)result; (void)rsize;
		return -1;
	}
	/*!< -1--no any event happend, 0--only this one event happend, else there has more event should be checked continously */
	virtual int8_t onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize) {
		(void)evt; (void)result; (void)rsize;
		return -1;
	}
#endif
#endif // XBRIDGE_SUPPORT

private:
	/*!< [7]--constructed dynamically, [6:0]--uid */
	uint8_t	mFlag;
};


class XNServer : public XNBlock {
public:
    XNServer() : XNBlock() {}
    virtual ~XNServer() {}

	virtual void loop() = 0;
};


#endif  // __XBLOCK_H__