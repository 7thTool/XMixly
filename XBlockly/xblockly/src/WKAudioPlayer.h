/* WKAudioPlayer.h
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
 *     This file is a header file for WKAudioPlayer.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __WKAUDIOPLAYER_H__
#define __WKAUDIOPLAYER_H__

#include <XBuzzer.h>



#define MUSIC_SHENGRIKUAILE		1
#define MUSIC_XIAOXINXIN		2
#define MUSIC_HUANLESONG		3
#define MUSIC_XIAOPINGGUO		4
#define MUSIC_SHANGXUEGE		5

#define MUSIC_SUM				5


#define SOUND_AMBULANCE			1
#define SOUND_FIRE_ENGINE		2
#define SOUND_POLICE_WAGON		3
#define SOUND_CAR_WHISTLING		4

#define SOUND_SUM				4  //exclude SOUND_CAR_WHISTLING


class WKAudioPlayer {
public:
	WKAudioPlayer();
	~WKAudioPlayer();

	/*
	���ܣ�	��ʼ��
	������	buz, ������ģ��ʵ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(XBuzzer *buz);

	void reset();

	/*
	���ܣ�	��������
	������	id����ο���MUSIC_XXX���궨�壬���硰MUSIC_SHENGRIKUAILE��
	�����	��
	*/
	void playMusic(uint8_t id);

	/*
	���ܣ�	������Ч
	������	id����ο���SOUND_XXX���궨�壬���硰SOUND_AMBULANCE��
	�����	��
	*/
	void playSound(uint8_t id);

	/*
	���ܣ�	ֹͣ����
	������	��
	�����	��
	*/
	void stop();

private:
		
	XBuzzer	*_buz;
	uint8_t _mode;
	uint8_t _id;
};

#endif //__WKAUDIOPLAYER_H__

