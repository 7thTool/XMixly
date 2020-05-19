/* WKAudioPlayer.cpp
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
 *     This file is an implement of wukong Audio Player Server.
 *
 * History:
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XI2C.h>
#include <WKAudioPlayer.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

#define AUDIOPLAY_I2C_RESET_PIN 	(10)
#define AUDIOPLAY_I2C_SELECT_PIN 	(8)
#define AUDIOPLAY_I2C_ADDRESS 		(0x3a)
#define AUDIOPLAY_CMD_ADDRESS  		(0x00)


#define MODE_STOP					0
#define MODE_PLAY_MUSIC				1
#define MODE_PLAY_SOUND				2


WKAudioPlayer::WKAudioPlayer() :
	_buz(NULL),
	_mode(MODE_STOP),
	_id(0)
{
}

WKAudioPlayer::~WKAudioPlayer()
{
	reset();
}

int WKAudioPlayer::setup(XBuzzer *buz)
{
	if (buz) {
		_buz = buz;
		reset();
		return 0;
	} else {
		return -1;
	}
}

void WKAudioPlayer::reset()
{
	stop();
}


void WKAudioPlayer::playMusic(uint8_t id)
{
	uint8_t buf[2];
	int8_t ret = 0;

	if (!_buz || ((id < 1) || (id > MUSIC_SUM)) ||
		((_mode == MODE_PLAY_MUSIC) && (_id == id))) {
		return;
	}

	/*< FIXME: */
	pinMode(4, INPUT);

	buf[0] = 0x13; 

	buf[1] = id;
	ret = XI2C.write(AUDIOPLAY_I2C_SELECT_PIN, AUDIOPLAY_I2C_ADDRESS, AUDIOPLAY_CMD_ADDRESS, buf, 2);
	if(ret == -2) 
		XI2C.reset(AUDIOPLAY_I2C_RESET_PIN, AUDIOPLAY_I2C_SELECT_PIN);

	_mode = MODE_PLAY_MUSIC;
	_id = id;

}

void WKAudioPlayer::playSound(uint8_t id)
{
	uint8_t buf[2];
	int8_t ret = 0;

	if (!_buz || ((id < 1) || (id > SOUND_SUM)) ||
		((_mode == MODE_PLAY_SOUND) && (_id == id))) {
		return;
	}

	pinMode(4, INPUT);

	buf[0] = 0x11;
	buf[1] = id;
	ret = XI2C.write(AUDIOPLAY_I2C_SELECT_PIN, AUDIOPLAY_I2C_ADDRESS, AUDIOPLAY_CMD_ADDRESS, buf, 2);
	if(ret == -2) 
		XI2C.reset(AUDIOPLAY_I2C_RESET_PIN, AUDIOPLAY_I2C_SELECT_PIN);
	
	_mode = MODE_PLAY_SOUND;
	_id = id;
}

void WKAudioPlayer::stop()
{
	uint8_t buf;
	int8_t ret = 0;
	
	if (!_buz) {
		return;
	}

	if (_mode != MODE_STOP)
	{
		/*!< FIXME: */
		pinMode(4, INPUT);
		
		buf = 0x10;
		ret = XI2C.write(AUDIOPLAY_I2C_SELECT_PIN, AUDIOPLAY_I2C_ADDRESS, AUDIOPLAY_CMD_ADDRESS, &buf, 1);
		if(ret == -2) 
			XI2C.reset(AUDIOPLAY_I2C_RESET_PIN, AUDIOPLAY_I2C_SELECT_PIN);

		_mode = MODE_STOP;
	}
}



