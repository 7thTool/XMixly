/* xport.h
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
 *     This file is a header API file for port of WuKong mainboard.
 *
 * Version: 1.0.0
 */


#ifndef __XPORT_H__
#define __XPORT_H__

#ifdef __cplusplus
extern "C"{
#endif

#define XPORT_FUNC_D1		0x1UL			//(1<<0)		//DIO
#define XPORT_FUNC_A1		0x2UL			//(1<<1)		//AI
#define XPORT_FUNC_P1		0x4UL			//(1<<2)		//PWM
#define XPORT_FUNC_N1		0x8UL			//(1<<3)		//INT
#define XPORT_FUNC_D2		0x10UL			//(1<<4)		//DIO*2
#define XPORT_FUNC_AA		0x20UL			//(1<<5)		//AI*2
#define XPORT_FUNC_PP		0x40UL			//(1<<6)		//PWM*2
#define XPORT_FUNC_DA		0x80UL			//(1<<7)		//DIO+AI
#define XPORT_FUNC_DP		0x100UL			//(1<<8)		//DIO+PWM
#define XPORT_FUNC_DN		0x200UL			//(1<<9)		//DIO+INT
#define XPORT_FUNC_PA		0x400UL			//(1<<10)	//PWM+AI
#define XPORT_FUNC_NA		0x800UL			//(1<<11)	//INT+AI
#define XPORT_FUNC_NP		0x10000UL		//(1<<12)	//INT+PWM	


#define XPORT_FUNC_UART		0x2000000UL		//(1<<25)	//UART
#define XPORT_FUNC_I2C		0x4000000UL		//(1<<26)	//I2C
#define XPORT_FUNC_SPI		0x8000000UL		//(1<<27)	//SPI

#define XPORT_FUNC_D4		0x80000000UL	//(1<<31)	//D4



#define XPORT_IO_NC			(0xff) //this port pin not connect

#define XPORT_I2C_INVALID   (0xff) //without i2c func in the port

#define XPORT_UART_SOFTWARE	(0xff) //with software uart func in the port

//Port attribute (Only BIT0-3 avaiable, Bit4-7 reserved for internal used)
#define XPORT_ATTR_NATIVE		(1UL<<0)



typedef struct {
	uint8_t attr;
	uint32_t func;
	struct {
		union {
			struct {
				uint8_t nbr;	//XPORT_I2C_INVALID means without i2c func in the port
				uint8_t sda;
				uint8_t scl;
			} I2C;
			
			struct {
				uint8_t nbr;
			} SPI;
		} bus;
		union {
			struct {
				uint8_t pin;
			} D1;
			struct {
				uint8_t pin;
			} A1;
			struct {
				uint8_t pin;
			} P1;
			struct {
				uint8_t pin;
			} N1;
			struct {
				uint8_t pin1;
				uint8_t pin2;
			} D2;
			struct {
				uint8_t pin1;
				uint8_t pin2;
			} AA;
			struct {
				uint8_t pin1;
				uint8_t pin2;
			} PP;
			struct {
				uint8_t pinD;
				uint8_t pinA;
			} DA;
			struct {
				uint8_t pinP;
				uint8_t pinD;
			} DP;
			struct {
				uint8_t pinD;
				uint8_t pinN;
			} DN;
			struct {
				uint8_t pinP;
				uint8_t pinA;
			} PA;
			struct {
				uint8_t pinN;
				uint8_t pinA;
			} NA;
			struct {
				uint8_t pinN;
				uint8_t pinP;
			} NP;
			struct
			{
				uint8_t pin1;	//for software uart
				uint8_t pin2;	//for software uart
				uint8_t nbr;	//XPORT_UART_SOFTWARE means software uart func in the port
			}UART;
			struct {
				uint8_t pin1;
				uint8_t pin2;
				uint8_t pin3;
				uint8_t pin4;
			} D4;
		} io;
	} plat;
} PortMap;



/*! \brief  Initial all port state
 *  \no rerturn.
 */
void PortInit();
	

/*! \brief  Setup a port.
 *  \param  port: port number, "1", "1.1", "2.1"...
 *  \param  func: function used, PORT_FUNC_XXX.
 *  \param  pmap: port map infomation, mainly for platform(Arduino).
 *  \return -1 failed, else portId.
 */
int8_t PortSetup(const char *port, uint32_t func, PortMap *pmap);


/*! \brief  Release a port.
 *  \param  port: port number, "1", "1.1", "2.1"...
 *  \no rerturn.
 */
//void PortRelease(const char *port)

/*! \brief  Release a port.
 *  \param  portId: port index, 1,2...
 *  \no rerturn.
 */
void PortRelease(int8_t portId);


/*! \brief  Setup a onboard port.
 *  \param  label: label of the onboard port, "BTN1".
 *  \param  model: block model onboard.
 *  \param  pmap: port map infomation, mainly for platform(Arduino).
 *  \return 0x4x is successful, 0 means failed.
 */
int8_t PortOnBoardSetup(const char *label, char *model, PortMap *pmap);


#ifdef __cplusplus
} // extern "C"
#endif


#endif //__XPORT_H__




