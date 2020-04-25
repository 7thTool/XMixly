/* XIRReceiver.h
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
 *     This file is a header file for XIRReceiver.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XIRRECEIVER_H__
#define __XIRRECEIVER_H__

#include <XBlock.h>


#define XIRReceiver_wait_ENABLE


#define XIR_KEY_0		(0)		// '0'
#define XIR_KEY_1		(1)		// '1'
#define XIR_KEY_2		(2)		// '2'
#define XIR_KEY_3		(3)		// '3'
#define XIR_KEY_4		(4)		// '4'
#define XIR_KEY_5		(5)		// '5'
#define XIR_KEY_6		(6)		// '6'
#define XIR_KEY_7		(7)		// '7'
#define XIR_KEY_8		(8)		// '8'
#define XIR_KEY_9		(9)		// '9'
#define XIR_KEY_A		(10)	// 'A'
#define XIR_KEY_B		(11)	// 'B'
#define XIR_KEY_C		(12)	// 'C'
#define XIR_KEY_D		(13)	// 'D'
#define XIR_KEY_E		(14)	// 'E'
#define XIR_KEY_F		(15)	// 'F'
#define XIR_KEY_UP		(16)	// UP
#define XIR_KEY_DOWN	(17)	// DOWN
#define XIR_KEY_LEFT	(18)	// LEFT
#define XIR_KEY_RIGHT	(19)	// RIGHT
#define XIR_KEY_OK		(20)	// OK


#define XIR_KEY_TOTAL	(21)


class XIRReceiver : public XNBlock  {
public:
	XIRReceiver();
	~XIRReceiver();

	/*
	功能：	初始化“扩展模块”
	参数：	model, 模块型号
			port, 连接到主控板的端口编号
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *model, const char *port);

	/*
	功能：	初始化“板载模块”
	参数：	label, 模块在主控板上的标贴
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *label);

	void reset();

	/*
	功能：	查询接收红外按键消息
	参数：	无
	结果：	返回接收到的红外消息值，无消息返回 0xFF
	*/
	uint8_t receive();

#ifdef XIRReceiver_wait_ENABLE
	/*
	功能：	等待接收到红外按键消息
	参数：	无
	结果：	无
	*/
	void wait();

	/*
	功能：	获取之前等待接收到的消息
	参数：	无
	结果：	消息值，见“XIR_KEY_X”，比如"XIR_KEY_0"
	*/
	uint8_t pick();
#endif

	/*
	功能：	使能长按功能
	参数：	key, 要使能长按功能的键值，0xFF表示所有的按键
	结果：	无
	*/
	void enableLongPress(uint8_t key);

private:
    /** \brief
     *   Enable timer interrupt to begin receive IR message.
     *  \param 
     *   None.
     *  \return
     *   None.
     */ 
    void enableRecv();

    /** \brief
     *   Disable timer interrupt to stop receive IR message.
     *  \param 
     *   None.
     *  \return
     *   None.
     */ 
    //void stopRecv();

    /** \brief
     *   Decodes the received IR message.
     *  \param 
     *   [IN] results: decoded data struct.
     *  \return
     *   length of data decoded.
     */ 
    //uint8_t decode(decode_results *results);

    /** \brief
     *   Resume received IR message data buffer.
     *  \param 
     *   None.
     *  \return
     *   None.
     */ 
    void resume();

	int8_t _portId;	// -1 means no onboard block, -2 means setup failed.
	uint8_t _key;
	uint32_t _longPressMark;
	uint8_t _model;
	void	*_impl;
};


#endif //__XIRRECEIVER_H__

