/* XSegDisplay.cpp
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
 *     This file is a driver for 7-Segment Display module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <xport.h>
#include <XSegDisplay.h>
#include <TM1650.h>

//#define TM1637_ENABLE

#ifdef TM1637_ENABLE
	#include <TM1637.h>
#endif

#define SGD4200_MODEL_NAME "SGD4200"  //use TM1650 Control
#define SGD4300_MODEL_NAME "SGD4300"  //use TM1650 Control
#define SGD4400_MODEL_NAME "SGD4400"  //use TM1637 Control

#define MODEL_TM1650		1
#define MODEL_TM1637		2


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


XSegDisplay::XSegDisplay()
{
	_portId = -1;
	_model = 0;
	_impl = NULL; 
}

XSegDisplay::~XSegDisplay()
{
	LOGN("~XSegDisplay()");
	
    if (_impl != NULL) {
		reset();
		/*!< FIXME: */
        delete (TM1650 *)_impl;
    }

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XSegDisplay::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XSegDisplay::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");

	_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
	if (_portId < 0) {
		LOGN("PortSetup() failed");
		return -1;
    }

	if ((!strcmp(model, SGD4200_MODEL_NAME))
		||(!strcmp(model, SGD4300_MODEL_NAME))) {
		_model = MODEL_TM1650;
		_impl = (void *)new TM1650();
		if(_impl == NULL) {
			LOGN("new TM1650() failed");
			PortRelease(_portId);
			return -1;
		}
		((TM1650 *)_impl)->init(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
#ifdef TM1637_ENABLE
	} else if(!strcmp(model, TM1637_MODEL_NAME)) {
		_model = MODEL_TM1637;
		_impl = (void *)new TM1637();
		if(_impl == NULL) {
			LOGN("new TM1637() failed");
			PortRelease(_portId);
			return -1;
		}
		((TM1637 *)_impl)->init(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
#endif
	} else {
		LOG("Unknown model of ");LOGN(model);
		return -1;
	}

	reset();
	return 0;
}

int XSegDisplay::setup(const char *label)
{
	LOG("XSegDisplay::setup(");LOG(label);LOGN(")");
	(void)label;
	return -1;
}

int XSegDisplay::setup(const char *model, const uint8_t dat, const uint8_t clk)
{
	if ((!strcmp(model, SGD4200_MODEL_NAME))
		||(!strcmp(model, SGD4300_MODEL_NAME))) {
		_model = MODEL_TM1650;
		_impl = (void *)new TM1650();
		if(_impl == NULL) {
			LOGN("new TM1650() failed");
			return -1;
		}
		((TM1650 *)_impl)->init(dat, clk);
#ifdef TM1637_ENABLE
	} else if(!strcmp(model, TM1637_MODEL_NAME)) {
		_model = MODEL_TM1637;
		_impl = (void *)new TM1637();
		if(_impl == NULL) {
			LOGN("new TM1637() failed");
			return -1;
		}
		((TM1637 *)_impl)->init(dat, clk);
#endif
	} else {
		LOG("Unknown model of ");LOGN(model);
		return -1;
	}

	reset();
	return 0;
}

void XSegDisplay::reset()
{
	clear();
}

void XSegDisplay::clear(uint8_t index)
{
	LOGN("XSegDisplay::clear()");

	if(_model == MODEL_TM1650) {
		((TM1650 *)_impl)->clearSegment(index, 0xff);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->clearSegment(index, 0xff);
	}
#endif
}

float XSegDisplay::pow10(uint8_t n)
{
	float f=1;
	while (n) {
		f *= 10;
		n--;
	}
	return f;
}

void XSegDisplay::parsefloat(float f, uint8_t count, int *number, uint8_t *icount, uint8_t *dcount)
{
	uint8_t i;

	// 检查是否超过范围，超过了则返回全0
	if (f >= pow10(count)) {
		*number = 0;
		*icount = count;
		*dcount = 0;
		return;
	}

	// 计算数字、整数位数、小数位数
	for (i=1; i<=count; i++) {
		if (f < pow10(i)) {
			*number = f * pow10(count - i);
			*icount = i;
			*dcount = count - i;
			break;
		}
	}

	// 移除小数尾巴上的无效0
	i = *dcount;
	while (i > 0) {
		if ((*number % 10) == 0) {
			*number /= 10;
			(*dcount)--;
		} else {
			break;
		}
		i--;
	}
}

void XSegDisplay::showNumber(float f)
{
	int number=0;
	uint8_t digCount, isNegative, count, icount=0, dcount=0, i;
	uint8_t disp[] = {0x7f, 0x7f, 0x7f, 0x7f};

	LOG("XSegDisplay::showNumber(");LOG(f);LOGN(")");

	if (!_impl) {
		LOGN("XSegDisplay not setup");
		return;
	}

	/*!< FIXME: */
	digCount = 4;

	if (f < 0) {
		isNegative = 1;
		count = digCount - 1;
	} else {
		isNegative = 0;
		count = digCount;
	}

	parsefloat(abs(f), count, &number, &icount, &dcount);
	LOG("number=");LOGN(number);
	LOG("icount=");LOGN(icount);
	LOG("dcount=");LOGN(dcount);

	if (isNegative && ((number != 0) || (icount == count))) {
		disp[digCount - (icount + dcount) - 1] = 0x40;
	}
	for (i=0; i < icount + dcount; i++) {
		disp[digCount - i - 1] = number % 10;
		number /= 10;
	}
	if (dcount != 0) {
		disp[digCount - dcount - 1] += 0x80;
	}

	if(_model == MODEL_TM1650) {
		((TM1650 *)_impl)->display(disp);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->display(disp);
	}
#endif
}

void XSegDisplay::showNumber(uint32_t num, uint8_t format)
{
	uint8_t disp[] = {0x40, 0x40, 0x40, 0x40};

	if (!_impl) {
		LOGN("XSegDisplay not setup");
		return;
	}
	
	if((format != BIN) && (format != HEX)) {
		return showNumber(num);
	} else if(format == BIN) {
		if (num <= 15) {
			disp[0] = (num & 0x08)?1:0;
			disp[1] = (num & 0x04)?1:0;
			disp[2] = (num & 0x02)?1:0;
			disp[3] = num & 0x01;
		} 
	} else if(format == HEX) {
		/*!< FIXME: 仅支持4位数码管 */
		if (num <= 65535UL) {
			disp[0] = (num >> 12) & 0x0f;
			disp[1] = (num >> 8) & 0x0f;
			disp[2] = (num >> 4) & 0x0f;
			disp[3] = num & 0x0f;
		} 
	}
	
	if(_model == MODEL_TM1650) {
		((TM1650 *)_impl)->display(disp);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->display(disp);
	}
#endif
}

void XSegDisplay::showCharacter(uint8_t index, char character)
{
	uint8_t disp[] = {0x7f, 0x7f, 0x7f, 0x7f};
	uint8_t val;

	if (!_impl) {
		LOGN("XSegDisplay not setup");
		return;
	}
	
	if((character >= '0') && (character <= '9')) { //0-9
		val = character - '0';
	} else if((character >= 'A') && (character <= 'F')){
		val = character - 'A' + 10;
	} else if((character >= 'a') && (character <= 'f')){
		val = character - 'a' + 10;
	} else {
		val = 0x40; //"-"
	}

	if (index == 0) {
		disp[0] = disp[1] = disp[2] = disp[3] = val;
		if(_model == MODEL_TM1650) {
			((TM1650 *)_impl)->display(disp);
		}
#ifdef TM1637_ENABLE
		else if(_model == MODEL_TM1637) {
			((TM1637 *)_impl)->display(disp);
		}
#endif
	} else {
		if(_model == MODEL_TM1650) {
			((TM1650 *)_impl)->updateOneChannel(index-1, val);
		}
#ifdef TM1637_ENABLE
		else if(_model == MODEL_TM1637) {
			((TM1637 *)_impl)->updateOneChannel(index-1, val);
		}
#endif
	}
	

}

void XSegDisplay::showSegment(uint8_t index, char segment)
{
	uint8_t segData = 0x00;

	if (!_impl) {
		return;
	}

	if(_model == MODEL_TM1650) {
		if (index > 4) {
			return;
		}
		if (segment == '.') {
			segData = 1 << 7;
		} else if ((segment >= 'a') && (segment <= 'g')) {
			segData = 1 << (segment - 'a');
		} else {
			return;
		}
		((TM1650 *)_impl)->displaySegment(index, segData);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->displaySegment(index, 1<<(segment-'a'));
	}
#endif
}

void XSegDisplay::showSegments(uint8_t index, uint8_t segData)
{
	if (!_impl) {
		LOGN("XSegDisplay not setup");
		return;
	}

	if(_model == MODEL_TM1650) {
		if (index > 4) {
			return;
		}
		((TM1650 *)_impl)->displaySegment(index, segData);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->displaySegment(index, segData);
	}
#endif
}

void XSegDisplay::clearSegment(uint8_t index, char segment)
{
	uint8_t segData = 0x00;

	if (!_impl) {
		LOGN("XSegDisplay not setup");
		return;
	}

	if(_model == MODEL_TM1650) {
		if (index > 4) {
			return;
		}
		if (segment == '.') {
			segData = 1 << 7;
		} else if ((segment >= 'a') && (segment <= 'g')) {
			segData = 1 << (segment - 'a');
		} else {
			return;
		}
		((TM1650 *)_impl)->clearSegment(index, segData);
	}
#ifdef TM1637_ENABLE
	else if(_model == MODEL_TM1637) {
		((TM1637 *)_impl)->clearSegment(index, 1<<(segment-'a'));
	}
#endif
}
