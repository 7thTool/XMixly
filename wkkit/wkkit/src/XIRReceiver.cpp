/* XIRReceiver.cpp
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
 *     This file is a driver for IR Receiver module.
 *
 * Version: 1.0.0
 */
 

#include <Arduino.h>
#include <avr/interrupt.h>
#include <xport.h>
#include <XIRReceiver.h>
#include <irr_internal.h>
#include <IRR3300Impl.h>


#define IRR3000_MODEL_NAME	"IRR3000"
#define IRR3300_MODEL_NAME	"IRR3300"

#define MODEL_IRR3000		1
#define MODEL_IRR3300		2

#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


#define REPEAT 				0xffffffff


static const uint8_t irkey_code_table[XIR_KEY_TOTAL] PROGMEM = {
	0x68, // XIR_KEY_0
	0x30, // XIR_KEY_1
	0x18, // XIR_KEY_2
	0x7a, // XIR_KEY_3
	0x10, // XIR_KEY_4
	0x38, // XIR_KEY_5
	0x5a, // XIR_KEY_6
	0x42, // XIR_KEY_7
	0x4a, // XIR_KEY_8
	0x52, // XIR_KEY_9
	0xa2, // XIR_KEY_A
	0x62, // XIR_KEY_B
	0xe2, // XIR_KEY_C
	0x22, // XIR_KEY_D
	0xc2, // XIR_KEY_E
	0xb0, // XIR_KEY_F
	0x02, // XIR_KEY_UP
	0x98, // XIR_KEY_DOWN
	0xe0, // XIR_KEY_LEFT
	0x90, // XIR_KEY_RIGHT
	0xa8 // XIR_KEY_OK
};

static const uint8_t irr3300_irkey_code_table[XIR_KEY_TOTAL] PROGMEM = {
	IR_BUTTON_0, // XIR_KEY_0
	IR_BUTTON_1, // XIR_KEY_1
	IR_BUTTON_2, // XIR_KEY_2
	IR_BUTTON_3, // XIR_KEY_3
	IR_BUTTON_4, // XIR_KEY_4
	IR_BUTTON_5, // XIR_KEY_5
	IR_BUTTON_6, // XIR_KEY_6
	IR_BUTTON_7, // XIR_KEY_7
	IR_BUTTON_8, // XIR_KEY_8
	IR_BUTTON_9, // XIR_KEY_9
	IR_BUTTON_A, // XIR_KEY_A
	IR_BUTTON_B, // XIR_KEY_B
	IR_BUTTON_C, // XIR_KEY_C
	IR_BUTTON_D, // XIR_KEY_D
	IR_BUTTON_E, // XIR_KEY_E
	IR_BUTTON_F, // XIR_KEY_F
	IR_BUTTON_UP, // XIR_KEY_UP
	IR_BUTTON_DOWN, // XIR_KEY_DOWN
	IR_BUTTON_LEFT, // XIR_KEY_LEFT
	IR_BUTTON_RIGHT, // XIR_KEY_RIGHT
	IR_BUTTON_SETTING // XIR_KEY_OK
};

static volatile irparams_t irparams;
static uint8_t key_fresh;
static unsigned long key_expire;

static int MATCH(int measured, int desired) {return measured >= TICKS_LOW(desired) && measured <= TICKS_HIGH(desired);}
static int MATCH_MARK(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us + MARK_EXCESS));}
static int MATCH_SPACE(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us - MARK_EXCESS));}

XIRReceiver::XIRReceiver() :
	XNBlock(),
	_portId(-1),
	_key(0xff),
	_longPressMark(0x0),
	_model(0),
	_impl(NULL)
{
}
	
XIRReceiver::~XIRReceiver() 
{
	LOGN("XIRReceiver::~XIRReceiver()");

	if (_portId >= 0) {
		PortRelease(_portId);
	}
}

int XIRReceiver::setup(const char *model, const char *port)
{
	PortMap pmap;

	LOG("XIRReceiver::setup(");LOG(model);LOG(",");LOG(port);LOGN(")");

	if(!strcmp(model, IRR3000_MODEL_NAME)) {
		_model = MODEL_IRR3000;
		_portId = PortSetup(port, XPORT_FUNC_D1, &pmap);
		if (_portId >= 0) {
			irparams.recvpin = pmap.plat.io.D1.pin;
		} else {
			LOGN("PortSetup failed");
			_portId = -2;
			return -1;
		}
	}
	else if(!strcmp(model, IRR3300_MODEL_NAME)) {
		_model = MODEL_IRR3300;
		_portId = PortSetup(port, XPORT_FUNC_D2, &pmap);
		if (_portId >= 0) {
			_impl = new IRR3300Impl(model);
			if (!_impl) {
				LOGN("new IRR3300Impl failed");
				return -1;
			}
			((IRR3300Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
		} else {
			LOGN("PortSetup failed");
			_portId = -2;
			return -1;
		}
	}
	reset();
	return 0;
}

int XIRReceiver::setup(const char *label)
{
	PortMap pmap;
	char model[8];

	LOG("XIRReceiver::setup(");LOG(label);LOGN(")");

	if(PortOnBoardSetup(label, model, &pmap)) {
		if(!strcmp(model, IRR3000_MODEL_NAME)) {
			_model = MODEL_IRR3000;
			irparams.recvpin = pmap.plat.io.D1.pin;

		}
		else if(!strcmp(model, IRR3300_MODEL_NAME)) {
			_model = MODEL_IRR3300;
			_impl = new IRR3300Impl(model);
			if (!_impl) {
				LOGN("new IRR3300Impl failed");
				return -1;
			}
			((IRR3300Impl *)_impl)->setup(pmap.plat.io.D2.pin1, pmap.plat.io.D2.pin2);
		}
	} else{
		LOGN("PortOnBoardSetup() failed");
		_portId = -2;
		return -1;
	}

	reset();
	return 0;
}

void XIRReceiver::reset()
{
	if (_portId != -2) {
#ifdef XBRIDGE_SUPPORT_NOTIFY
		_evtMask = 0;
#endif
		if(_model == MODEL_IRR3000)
		{
			enableRecv();
		}
		else if(_model == MODEL_IRR3300)
		{
		}
		
		_key = 0xff;
	}
}

void XIRReceiver::enableLongPress(uint8_t key)
{
	if(_model == MODEL_IRR3000)
	{
		if (key == 0xFF) {
			_longPressMark = 0xFFFFFFFF;
		} else if (key < XIR_KEY_TOTAL) {
			_longPressMark |= (uint32_t)(1ul<<key);
		}
	}
	else if(_model == MODEL_IRR3300)
	{
		LOGN("IRR3300 not support long press");
	}
}

uint8_t XIRReceiver::receive()
{
	//LOGN("XIRReceiver::receive()");

	if (_portId == -2) {
		LOGN("XIRReceiver not setup");
		return 0xff;
	}

	if(_model == MODEL_IRR3000)
	{
		if ((_key != 0xFF) && (!key_fresh) && (key_expire < 110000ul)) {
			//delayMicroseconds(110000ul - key_expire);
			delay(110); // FIXME
		}

		if (irparams.rcvstate != STATE_IDLE) {
			//Serial.println("-1");
			while (irparams.rcvstate != STATE_STOP);
		} else {
			return 0xFF;
		}

		if (irparams.decstate != DECODE_IDLE) {
			//Serial.println("-2");
			while ((irparams.decstate != DECODE_END) && (irparams.decstate != DECODE_ERR));

			if (key_expire > 250000ul) {
				//Serial.println("-3");
				_key = 0xFF;
			} else {
				if (irparams.data != REPEAT) {
					uint8_t code = (irparams.data >> 8) & 0xff;
					for (_key = 0; _key < XIR_KEY_TOTAL; _key++) {
						if (pgm_read_byte_near(&irkey_code_table[_key]) == code) {
							break;
						}
					}
					if (_key == XIR_KEY_TOTAL) {
						_key = 0xFF;
					}
				} else {
					if ((_key != 0xFF) && !((_longPressMark >> _key) & 0x01)) {
						_key = 0xFF;
					}
				}
				//Serial.println("-4");
			}
			resume();
		} else {
			return 0xFF;
		}
	}
	else if(_model == MODEL_IRR3300)
	{
		if(((IRR3300Impl *)_impl)->available() <= 0)
		{
			_key = 0xFF;
		}
		else
		{
			uint8_t code = ((IRR3300Impl *)_impl)->read();
			for (_key = 0; _key < XIR_KEY_TOTAL; _key++) {
				if (pgm_read_byte_near(&irr3300_irkey_code_table[_key]) == code) {
					break;
				}
			}
			if (_key == XIR_KEY_TOTAL) {
				_key = 0xFF;
			}
		}
	}
	
	return _key;
}

#ifdef XIRReceiver_wait_ENABLE
void XIRReceiver::wait()
{
	while(receive() == 0xFF);
}

uint8_t XIRReceiver::pick()
{
	return _key;
}
#endif



void XIRReceiver::enableRecv()
{
	//LOGN("XIRReceiver::enableRecv()");
	
	cli();

	TIMER_CONFIG_NORMAL();

	TIMER_ENABLE_INTR;

	TIMER_RESET;

	sei();

	resume();

	pinMode(irparams.recvpin, INPUT);
}

void XIRReceiver::resume()
{
	//LOGN("XIRReceiver::resume()");
	
	irparams.rcvstate = STATE_IDLE;
	irparams.decstate = DECODE_IDLE;
	irparams.data = 0;
	irparams.bits = 0;
	key_fresh = 0;
}

ISR(TIMER_INTR_NAME)
{
  TIMER_RESET;

  if (key_expire < 10000000ul) {
	  key_expire += USECPERTICK;
  }

  uint8_t irdata = (uint8_t)digitalRead(irparams.recvpin);

  irparams.timer++; // One more 50us tick
  if (irparams.bits > NEC_BITS) {
    // Buffer overflow
    irparams.rcvstate = STATE_STOP;
  }
  switch(irparams.rcvstate) {
  case STATE_IDLE: // In the middle of a gap
    if (irdata == MARK) {
      if (irparams.timer < GAP_TICKS) {
        // Not big enough to be a gap.
        irparams.timer = 0;
      } 
      else {
        // gap just ended, record duration and start recording transmission
        irparams.bits = 0;
        irparams.timer = 0;
		irparams.decstate = DECODE_START;
        irparams.rcvstate = STATE_MARK;
      }
    }
    break;
  case STATE_MARK: // timing MARK
    if (irdata == SPACE) {   // MARK ended, record time
	  if(irparams.decstate == DECODE_NORMAL || irparams.decstate == DECODE_REPEAT) {
		  if (!MATCH_MARK(irparams.timer, NEC_BIT_MARK)) {
			  irparams.decstate = DECODE_ERR;
		  }
	  }
	  else if(irparams.decstate == DECODE_START) {
		  if(!MATCH_MARK(irparams.timer, NEC_HDR_MARK)) {
			  irparams.decstate = DECODE_ERR;
		  }
	  }
      irparams.timer = 0;
      irparams.rcvstate = STATE_SPACE;
    }
    break;
  case STATE_SPACE: // timing SPACE
    if (irdata == MARK) { // SPACE just ended, record it
      if (irparams.decstate == DECODE_NORMAL) {
		  if (MATCH_SPACE(irparams.timer, NEC_ONE_SPACE)) {
			  irparams.data = (irparams.data << 1) | 1;
			  irparams.bits++;
		  } 
		  else if (MATCH_SPACE(irparams.timer, NEC_ZERO_SPACE)) {
			  irparams.data <<= 1;
			  irparams.bits++;
		  } 
		  else {
			  irparams.decstate = DECODE_ERR;
		  }
	  }
	  else if (irparams.decstate == DECODE_REPEAT) {
		  irparams.decstate = DECODE_ERR;
	  }
	  else if (irparams.decstate == DECODE_START) {
		  if (MATCH_SPACE(irparams.timer, NEC_RPT_SPACE)) {
			  irparams.decstate = DECODE_REPEAT;
		  }
		  else if (MATCH_SPACE(irparams.timer, NEC_HDR_SPACE)) {
			  irparams.decstate = DECODE_NORMAL;
		  }
		  else {
			  irparams.decstate = DECODE_ERR;
		  }
	  }
      irparams.timer = 0;
      irparams.rcvstate = STATE_MARK;
    } 
    else { // SPACE
      if (irparams.timer > GAP_TICKS) {
        // big SPACE, indicates gap between codes
        // Mark current code as ready for processing
        // Switch to STOP
        // Don't reset timer; keep counting space width
        irparams.rcvstate = STATE_STOP;
		if (irparams.decstate == DECODE_REPEAT) {
			irparams.data = REPEAT;
			irparams.bits = 4;
			irparams.decstate = DECODE_END;
		}
		else if (irparams.decstate == DECODE_NORMAL) {
			irparams.decstate = DECODE_END;
		}
		key_fresh = 1;
		key_expire = 0;
      } 
    }
    break;
  case STATE_STOP: // waiting, measuring gap
    if (irdata == MARK) { // reset gap timer
      irparams.timer = 0;
    }
    break;
  }

}

#ifdef XBRIDGE_SUPPORT
int8_t XIRReceiver::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XIRReceiver::onAccess()");
	(void)param; (void)psize;

    if (api == XIRReceiver_API_receive) {
        result = fillU8(result, receive());
        *rsize = 1;
	} else {
		*rsize = 0;
		return -1;
	}
	return 0;
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
int8_t XIRReceiver::onNotifyRegister(uint8_t evt, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	LOGN("XIRReceiver::onNotifyRegister()");
	(void)param; (void)psize;
	(void)evt;

	//if (evt == XIRReceiver_EVT_Change) {
		_evtMask |= XIRReceiver_EVT_Change;
		receive();
		fillU8(result, _key);
		*rsize = 1;
	//}
	return 0;
}

int8_t XIRReceiver::onNotifyCheck(uint8_t *evt, uint8_t *result, uint8_t *rsize)
{
	LOGN("XIRReceiver::onNotifyCheck()");

	if (_evtMask & XIRReceiver_EVT_Change) {
		if (receive() != 0xFF) {
			fillU8(result, _key);
			*evt = XIRReceiver_EVT_Change;
			*rsize = 1;
			return 0;
		}
	}

	return -1;
}
#endif	// XBRIDGE_SUPPORT_NOTIFY
#endif // XBRIDGE_SUPPORT