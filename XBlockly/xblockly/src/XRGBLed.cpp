/* XRGBLed.cpp
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
 *     This file is a driver for RGB Led module.
 *
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <xport.h>
#include <XRGBLed.h>

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XRGBLed::XRGBLed()
{
	_portId = -1;
	count_led = 0;
	pixels = NULL;
	pinMask = 0;
	ws2812_port = NULL;
	_red = 0x00;
	_green = 0x00;
	_blue = 0x00;
}
	
XRGBLed::~XRGBLed()
{
	LOGN("XRGBLed::~XRGBLed()");
	
	if (pixels) {
		reset();
		free(pixels);
	}

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XRGBLed::init(uint8_t pin)
{
	LOGN("XRGBLed::init()");
	
	pixels = (uint8_t*)malloc(count_led * 3);
	if (!pixels) {
		LOGN("There is not enough space!");
		return -1;
	}
	memset(pixels, 0, count_led * 3);
	
	pinMask = digitalPinToBitMask(pin);
	ws2812_port = portOutputRegister(digitalPinToPort(pin) );
	pinMode(pin, OUTPUT);
	return 0;
}

int XRGBLed::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XRGBLed::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");

	_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
	if (_portId >= 0) {
		count_led = model[5]-'0';
		if (init(pmap.plat.io.D1.pin) < 0) {
			PortRelease(_portId);
			_portId = -1;
			return -1;
		}
	} else {
		LOGN("XRGBLed(model, port) failed!");
		return -1;
	}

	reset();
	return 0;
}

int XRGBLed::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XRGBLed::setup(");LOG(label);LOGN(")");

	if (PortOnBoardSetup(label, model, &pmap)) {
		count_led = model[5]-'0';
		if (init(pmap.plat.io.D1.pin) < 0) {
			return -1;
		}
	}
	else {
		LOGN("XRGBLed(label) failed!");
		return -1;
	}
	
	reset();
	return 0;
}

int XRGBLed::setup(const char *model, const uint8_t pinD)
{
	count_led = model[5]-'0';
	//count_led = 4;
	if (init(pinD) < 0) {
		return -1;
	}
	reset();
	return 0;
}

void XRGBLed::reset()
{
	clear(0);
}

void XRGBLed::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t i, tmp;

	LOG("XRGBLed::setColor(");LOG(index);LOG(",");LOG(red);LOG(",");LOG(green);LOG(",");LOG(blue);LOGN(")");

	if (pixels) {
		if (index == 0) {
			for (i = 0; i < count_led; i++) {
				tmp = i * 3;
				pixels[tmp] = green;
				pixels[tmp + 1] = red;
				pixels[tmp + 2] = blue;
			}
		} else if (index <= count_led) {
			tmp = (index - 1) * 3;
			pixels[tmp] = green;
			pixels[tmp + 1] = red;
			pixels[tmp + 2] = blue;
		}
	}
}

void XRGBLed::showColorIndex(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
	LOG("XRGBLed::showColor(");LOG(index);LOG(",");LOG(red);LOG(",");LOG(green);LOG(",");LOG(blue);LOGN(")");

	if (pixels) {
		setColor(index, red, green, blue);
		show();
	}
}

void XRGBLed::showColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t clearOthers)
{
		if (index <= count_led) {
			if(clearOthers != 0) {
				clear(0);
			}
			showColorIndex(index, red, green, blue);
		} else {
			return;
		}
}

void XRGBLed::showColor(uint8_t index, uint32_t value, uint8_t clearOthers)
{
	uint8_t r, g, b;

	r = (value>>16) & 0xff;
	g = (value>>8) & 0xff;
	b = value & 0xff;
	
	showColor(index, r, g, b, clearOthers);
}

void XRGBLed::clear(uint8_t index)
{
	LOG("XRGBLed::clear(");LOG(index);LOGN(")");
	
	if (index <= count_led) {
		showColorIndex(index, 0, 0, 0);
	} else {
		return;
	}

}

void XRGBLed::show(void)
{
	//LOGN("XRGBLed::show()");
	if (pixels) {
		rgbled_sendarray_mask(pixels, 3 * count_led, pinMask, (uint8_t*)ws2812_port);
	}
	delay(1);
}

/*
  This routine writes an array of bytes with RGB values to the Dataout pin
  using the fast 800kHz clockless WS2812 protocol.
 */
/* Timing in ns */
#define w_zeropulse (350)
#define w_onepulse  (900)
#define w_totalperiod (1250)

/* Fixed cycles used by the inner loop */
#define w_fixedlow  (3)
#define w_fixedhigh (6)
#define w_fixedtotal (10)

/* Insert NOPs to match the timing, if possible */
#define w_zerocycles ( ( (F_CPU / 1000) * w_zeropulse) / 1000000)
#define w_onecycles ( ( (F_CPU / 1000) * w_onepulse + 500000) / 1000000)
#define w_totalcycles ( ( (F_CPU / 1000) * w_totalperiod + 500000) / 1000000)

/* w1 - nops between rising edge and falling edge - low */
#define w1 (w_zerocycles - w_fixedlow)
/* w2   nops between fe low and fe high */
#define w2 (w_onecycles - w_fixedhigh - w1)
/* w3   nops to complete loop */
#define w3 (w_totalcycles - w_fixedtotal - w1 - w2)

#if w1 > 0
#define w1_nops w1
#else
#define w1_nops 0
#endif

/*
  The only critical timing parameter is the minimum pulse length of the "0"
  Warn or throw error if this timing can not be met with current F_CPU settings.
 */
#define w_lowtime ( (w1_nops + w_fixedlow) * 1000000) / (F_CPU / 1000)
#if w_lowtime > 550
#error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime > 450
#warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
#warning "Please consider a higher clockspeed, if possible"
#endif

#if w2 > 0
#define w2_nops w2
#else
#define w2_nops 0
#endif

#if w3 > 0
#define w3_nops w3
#else
#define w3_nops 0
#endif

#define w_nop1  "nop      \n\t"
#define w_nop2  "rjmp .+0 \n\t"
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8

void XRGBLed::rgbled_sendarray_mask(uint8_t *data, uint16_t datlen, uint8_t maskhi, uint8_t *port)
{
	uint8_t curbyte, ctr, masklo;
	uint8_t oldSREG = SREG;
	cli(); // Disables all interrupts

	masklo  = *port & ~maskhi;
	maskhi  = *port | maskhi;

	while(datlen--)
	{
		curbyte = *data++;

		asm volatile (
				"       ldi   %0,8  \n\t"
				"loop%=:            \n\t"
				"       st    X,%3 \n\t"        //  '1' [02] '0' [02] - re
		#if (w1_nops & 1)
				w_nop1
		#endif
		#if (w1_nops & 2)
				w_nop2
		#endif
		#if (w1_nops & 4)
				w_nop4
		#endif
		#if (w1_nops & 8)
				w_nop8
		#endif
		#if (w1_nops & 16)
				w_nop16
		#endif
				"       sbrs  %1,7  \n\t"       //  '1' [04] '0' [03]
				"       st    X,%4 \n\t"        //  '1' [--] '0' [05] - fe-low
				"       lsl   %1    \n\t"       //  '1' [05] '0' [06]
		#if (w2_nops & 1)
				w_nop1
		#endif
		#if (w2_nops & 2)
				w_nop2
		#endif
		#if (w2_nops & 4)
				w_nop4
		#endif
		#if (w2_nops & 8)
				w_nop8
		#endif
		#if (w2_nops & 16)
				w_nop16
		#endif
				"       brcc skipone%= \n\t"    /*  '1' [+1] '0' [+2] - */
				"       st   X,%4      \n\t"    /*  '1' [+3] '0' [--] - fe-high */
				"skipone%=:               "     /*  '1' [+3] '0' [+2] - */

		#if (w3_nops & 1)
				w_nop1
		#endif
		#if (w3_nops & 2)
				w_nop2
		#endif
		#if (w3_nops & 4)
				w_nop4
		#endif
		#if (w3_nops & 8)
				w_nop8
		#endif
		#if (w3_nops & 16)
				w_nop16
		#endif

				"       dec   %0    \n\t"       //  '1' [+4] '0' [+3]
				"       brne  loop%=\n\t"       //  '1' [+5] '0' [+4]
				: "=&d" (ctr)
				: "r" (curbyte), "x" (port), "r" (maskhi), "r" (masklo)
		);
	}

	SREG = oldSREG;
}





