/* xport.c
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
 *     This file is an port file for PanGu mainboard.
 *
 * Version: 1.0.0
 */


#include <arduino.h>
#include <assert.h>
#include <pins_arduino.h>
#include <xport.h>


//#define SUPPORT_D4_INTERFACE  //PanGu not support D4 interface

//Port attribute (Only Bit4-7 available for internal used, Bit0-3 used external)
#define XPORT_ATTR_TYPE_XIP45 		(1UL<<4) //whether XIP45 port, else XDIP6 port


#define CHECKBIT(value, bit) (((value&bit) == bit)?true:false)

#define PORT_NUMS 9
static uint8_t portState[PORT_NUMS] = {0};

#define LABEL_ONBOARD_NUMS 2


//port
const char p1_port[] PROGMEM="1";
const char p2_port[] PROGMEM="2";
const char p3_port[] PROGMEM="3";
const char p4_port[] PROGMEM="4";
const char p5_port[] PROGMEM="5";
const char p6_port[] PROGMEM="6";
const char p7_port[] PROGMEM="7";
const char p8_port[] PROGMEM="8";
const char p9_port[] PROGMEM="9";





//block onboard
//const char btn_label[] PROGMEM="BTN";
const char svo1_label[] PROGMEM="SVO1";
const char svo2_label[] PROGMEM="SVO2";



const char * const portNames[] PROGMEM = {
	p1_port,
	p2_port,
	p3_port,
	p4_port,
	p5_port,
	p6_port,
	p7_port,
	p8_port,
	p9_port,
	//btn_label,
	svo1_label,
	svo2_label,
};


//const char btn_model[] PROGMEM="BTN3000";
const char svo1_model[] PROGMEM="SVO3000";
const char svo2_model[] PROGMEM="SVO3000";


const char * const models[] PROGMEM = {
	//btn_model,
	svo1_model,
	svo2_model,
};



typedef struct PortProperty{
	uint8_t number; //port number, 1-9 for PanGu, only valid for RJ25 port
	uint8_t attr;
	uint32_t func;
	struct {
		union {
			struct {
				uint8_t	nbr;
				uint8_t sda;
				uint8_t scl;
			} I2C;
			
			struct {
				uint8_t	nbr;
			} SPI;
		} bus;
		
		struct {
			struct
			{
				uint8_t	nbr;   //0xff means software uart
			}UART;
			
			uint8_t pin1;
			uint8_t pin2;
#ifdef SUPPORT_D4_INTERFACE
			uint8_t pin3;
			uint8_t pin4;
#endif			
			uint8_t pin1DFunc;	// because D1/P1/TI/N1 is multiplex, it use to confirm which func support in pin1
			uint8_t pin2DFunc;	// because D1/P1/TI/N1 is multiplex, it use to confirm which func support in pin2
		} io;
	}plat;
} PortProperty;


static const PortProperty PanGuPortProperty[] PROGMEM =
{
	{
        //port name = "1",
		.number = 0x1,
        .attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_D1 | XPORT_FUNC_P1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 9,
				.pin2 = 8,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1,
				.pin2DFunc = XPORT_FUNC_D1,
			},
        },
    },
	{
		//port name = "2",
		.number = 0x2,
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_AA | XPORT_FUNC_D2 | XPORT_FUNC_DA 
				| XPORT_FUNC_A1 | XPORT_FUNC_D1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = PIN_A0,
				.pin2 = PIN_A1,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_A1,
				.pin2DFunc = XPORT_FUNC_D1 | XPORT_FUNC_A1,
			},
		},
	},
	{
		//port name = "3",
		.number = 0x3,
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_D1 | XPORT_FUNC_P1 
				| XPORT_FUNC_N1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 11,
				.pin2 = 2,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1,
				.pin2DFunc = XPORT_FUNC_D1 | XPORT_FUNC_N1,
			},
		},
	},
	{
		//port name = "4",
		.number = 0x4,
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_D1 | XPORT_FUNC_P1 
				| XPORT_FUNC_N1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 3,
				.pin2 = 4,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1 | XPORT_FUNC_N1,
				.pin2DFunc = XPORT_FUNC_D1,
			},
		},
	},
	{
        //port name = "5",
		.number = 0x5,
        .attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_PP | XPORT_FUNC_D1 
				| XPORT_FUNC_P1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 5,
				.pin2 = 6,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1,
				.pin2DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1,
			},
        },
    },
    {
        //port name = "6",
		.number = 0x6,
        .attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_DA | XPORT_FUNC_A1 
				| XPORT_FUNC_D1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 12,
				.pin2 = PIN_A2,
				.pin1DFunc = XPORT_FUNC_D1,
				.pin2DFunc = XPORT_FUNC_D1 | XPORT_FUNC_A1,
			},
        },
    },
	{
		//port name = "7",
		.number = 0x7,
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_DA | XPORT_FUNC_A1 
				| XPORT_FUNC_D1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 13,
				.pin2 = PIN_A3,
				.pin1DFunc = XPORT_FUNC_D1,
				.pin2DFunc = XPORT_FUNC_D1 | XPORT_FUNC_A1,
			},
		},
	},

	{
		//port name = "8",
		.number = 0x8,
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_D2 | XPORT_FUNC_D1 | XPORT_FUNC_P1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.pin1 = 10,
				.pin2 = 7,
				.pin1DFunc = XPORT_FUNC_D1 | XPORT_FUNC_P1,
				.pin2DFunc = XPORT_FUNC_D1,
			},
		},
	},
	{
		//port name = "9",
		.number = 0x9,
		.attr = XPORT_ATTR_NATIVE | XPORT_ATTR_TYPE_XIP45,
		.func = XPORT_FUNC_I2C | XPORT_FUNC_UART | XPORT_FUNC_D2 | XPORT_FUNC_D1,
		.plat = {
			.bus = {
				.I2C = {
					.nbr = 0,
					.sda = PIN_A4,
					.scl = PIN_A5,
				},
			},
			.io = {
				.UART = {
					.nbr = 0,
				},
				.pin1 = 0,
				.pin2 = 1,
				.pin1DFunc = XPORT_FUNC_D1,
				.pin2DFunc = XPORT_FUNC_D1,
			},
		},
	},
	{
		//label = "SVO1", model = "SVO3000",
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_D1,
		.plat = {
			.io = {
				.pin1 = 9,
				.pin2 = XPORT_IO_NC,
				.pin1DFunc = XPORT_FUNC_D1,
			},
        },
	},
	{
		//label = "SVO2", model = "SVO3000",
		.attr = XPORT_ATTR_NATIVE,
		.func = XPORT_FUNC_D1,
		.plat = {
			.io = {
				.pin1 = 10,
				.pin2 = XPORT_IO_NC,
				.pin1DFunc = XPORT_FUNC_D1,
			},
        },
	},


};


static void portMapSetting(const PortProperty *portProp, uint32_t func, PortMap *pmap)
{
	uint8_t pin1, pin2;

	pmap->func = func;
	pmap->attr = pgm_read_byte(&portProp->attr) & 0xf; //only bit0-3 used external
	
	if(CHECKBIT(func, XPORT_FUNC_I2C))
	{
		pmap->plat.bus.I2C.nbr = pgm_read_byte(&portProp->plat.bus.I2C.nbr);
		pmap->plat.bus.I2C.sda = pgm_read_byte(&portProp->plat.bus.I2C.sda);
		pmap->plat.bus.I2C.scl = pgm_read_byte(&portProp->plat.bus.I2C.scl);
		pmap->plat.io.D2.pin1 = pgm_read_byte(&portProp->plat.io.pin1); //I2C reset pin
		pmap->plat.io.D2.pin2 = pgm_read_byte(&portProp->plat.io.pin2); //I2C select pin

		//number==0 也即板载I2C模块是不用在初始化的时候reset的，外接的I2C模块必须在初始化的时候reset下
		if(pgm_read_byte(&portProp->number)) 
		{
			pinMode(pmap->plat.io.D2.pin1, OUTPUT);
			digitalWrite(pmap->plat.io.D2.pin1, 1);  //set high to reset this I2C-interface module
			delayMicroseconds(500);
			digitalWrite(pmap->plat.io.D2.pin1, 0);

			pinMode(pmap->plat.io.D2.pin2, OUTPUT);
			digitalWrite(pmap->plat.io.D2.pin2, 0);  //set selPin to low

			delay(300); //MUST = 300ms
		}
	}
	else if(CHECKBIT(func, XPORT_FUNC_SPI))
	{
		pmap->plat.bus.SPI.nbr = pgm_read_byte(&portProp->plat.bus.SPI.nbr);
	}

	if(CHECKBIT(func, XPORT_FUNC_A1))
	{
		pmap->plat.io.A1.pin = pgm_read_byte(&portProp->plat.io.pin2);  //func A1 only with pin2
	}
	else if(CHECKBIT(func, XPORT_FUNC_D1)
		|| CHECKBIT(func, XPORT_FUNC_P1)
		|| CHECKBIT(func, XPORT_FUNC_N1))
	{
		pin1 = pgm_read_byte(&portProp->plat.io.pin1);
		pin2 = pgm_read_byte(&portProp->plat.io.pin2);
		
		/*
		 *initial all pin mode to input to avoid pin signal conflict 
		 *because pin1 connect to pin2 for some module
		 */
		//因为有些外接扩展模块的pin1脚和pin2脚是相连的，为了避免一个没用到的pin脚对
		//另外一个用到的pin脚产生干扰，需要将不用到的管脚配置成输入模式，
		//由于不知道是哪个用到了，哪个没用到，所以两个都配置成输入模式，模块setup函数中
		//会将用到的pin脚重新配置成功能脚所需要的模式
		if(pin1 != XPORT_IO_NC)
		{
			pinMode(pin1, INPUT);
		}

		if(pin2 != XPORT_IO_NC)
		{
			pinMode(pin2, INPUT);
		}

		if(func & pgm_read_byte(&portProp->plat.io.pin1DFunc)) //pin1 support this single func
			pmap->plat.io.D1.pin = pin1;
		else //pin2 support this single-pin func
			pmap->plat.io.D1.pin = pin2;
		
		/* this equals to
			pmap->plat.io.P1.pin = pgm_read_byte(&portProp->plat.io.pin1);
			or 
			pmap->plat.io.T1.pin = pgm_read_byte(&portProp->plat.io.pin1);
			or 
			pmap->plat.io.N1.pin = pgm_read_byte(&portProp->plat.io.pin1);
		*/
	}

	if(CHECKBIT(func, XPORT_FUNC_D2)
		|| CHECKBIT(func, XPORT_FUNC_AA)
		|| CHECKBIT(func, XPORT_FUNC_PP)
		|| CHECKBIT(func, XPORT_FUNC_DA)
		|| CHECKBIT(func, XPORT_FUNC_DP)
		|| CHECKBIT(func, XPORT_FUNC_DN)
		|| CHECKBIT(func, XPORT_FUNC_PA)
		|| CHECKBIT(func, XPORT_FUNC_NA)
		|| CHECKBIT(func, XPORT_FUNC_NP))
	{
		pmap->plat.io.D2.pin1 = pgm_read_byte(&portProp->plat.io.pin1);
		pmap->plat.io.D2.pin2 = pgm_read_byte(&portProp->plat.io.pin2);
		/* this equals to
		pmap->plat.io.DA.pinD = pgm_read_byte(&portProp->plat.io.pin1);
		pmap->plat.io.DA.pinA = pgm_read_byte(&portProp->plat.io.pin2);
		*/
	}

	if(CHECKBIT(func, XPORT_FUNC_UART))
	{
		pmap->plat.io.UART.nbr = pgm_read_byte(&portProp->plat.io.UART.nbr);
		pmap->plat.io.UART.pin1 = pgm_read_byte(&portProp->plat.io.pin1);
		pmap->plat.io.UART.pin2 = pgm_read_byte(&portProp->plat.io.pin2);
	}

#ifdef SUPPORT_D4_INTERFACE
	if(CHECKBIT(func, XPORT_FUNC_D4))
	{
		pmap->plat.io.D4.pin1 = pgm_read_byte(&portProp->plat.io.pin1);
		pmap->plat.io.D4.pin2 = pgm_read_byte(&portProp->plat.io.pin2);
		pmap->plat.io.D4.pin3 = pgm_read_byte(&portProp->plat.io.pin3);
		pmap->plat.io.D4.pin4 = pgm_read_byte(&portProp->plat.io.pin4);
	}
#endif
}

void PortInit()
{
	uint8_t i;
	
	//initial port1-8 default mode to be output low 
	for(i=2;i<=PIN_A3;i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
}

int8_t PortSetup(const char *port, uint32_t func, PortMap *pmap)
{
    int i;
	uint8_t portNum;
	int8_t portId;
	const PortProperty *portProp = NULL;

	assert(port != NULL);
	assert(pmap != NULL);

	memset(pmap, 0x00, sizeof(PortMap));

	for(i=0;i<PORT_NUMS;i++)
	{
		if((strcasecmp_P(port, (char*)pgm_read_word(&(portNames[i]))) == 0)
			&& CHECKBIT(pgm_read_dword(&PanGuPortProperty[i].func), func))
		{
			portNum = pgm_read_byte(&PanGuPortProperty[i].number); //bit0-5

			//check whether this port has been setup or not
			if(portState[portNum - 1] == 1) return -1;

			portState[portNum - 1] = 1;
				
			portProp = &PanGuPortProperty[i];	
			portId = i;
			
			break;
		}
	}

	if(portProp == NULL)
	{
		//printf("There is no port match this func!");
		return -1;
	}
	
	portMapSetting(portProp, func, pmap);

	return portId;

}


void PortRelease(int8_t portId)
{
	uint8_t portNum;

	assert(portId >=0);
	
	if(portId == 0x41)
	{
		portState[0] = 0;  //release SVO1 port
	}
	else if(portId == 0x42)
	{
		portState[7] = 0;  //release SVO2 port
	}
	else 
	{
		portNum = pgm_read_byte(&PanGuPortProperty[portId].number); 
		
		portState[portNum - 1] = 0;
	}

}

int8_t PortOnBoardSetup(const char *label, char *model, PortMap *pmap)
{
	int i;
	uint32_t func;
	uint8_t lbl = 0x0;
	const PortProperty *portProp = NULL;

	assert(label != NULL);
	assert(model != NULL);
	assert(pmap != NULL);

	memset(pmap, 0x00, sizeof(PortMap));

	//label begin from position after all RJ25 map port
	for(i=0;i<LABEL_ONBOARD_NUMS;i++)
	{
		if(strcasecmp_P(label, (char*)pgm_read_word(&(portNames[i+PORT_NUMS]))) == 0)
		{				
			portProp = &PanGuPortProperty[i+PORT_NUMS];
			
			strcpy_P(model,(char*)pgm_read_word(&(models[i])));
			
			func = pgm_read_dword(&PanGuPortProperty[i+PORT_NUMS].func);

			//check whether this port has been setup or not
			if(i == 0) //SVO1, use port1
			{
				if(portState[0] == 1) 
				{
					return 0;
				}

				portState[0] = 1;
				lbl = 0x1;
			}
			else if(i == 1) //SVO2, use port8
			{
				if(portState[7] == 1) 
				{
					return 0;
				}

				portState[7] = 1;
				lbl = 0x2;
			}
			
			break;
		}
	}

	if(portProp == NULL)
	{
		//printf("There is no port match this func!");
		return 0;
	}


	portMapSetting(portProp, func, pmap);

	return (0x40 | lbl); //bit6 use onboard port mark
}

