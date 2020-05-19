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
	功能：	初始化
	参数：	buz, 蜂鸣器模块实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(XBuzzer *buz);

	void reset();

	/*
	功能：	播放音乐
	参数：	id，请参考“MUSIC_XXX”宏定义，比如“MUSIC_SHENGRIKUAILE”
	结果：	无
	*/
	void playMusic(uint8_t id);

	/*
	功能：	播放音效
	参数：	id，请参考“SOUND_XXX”宏定义，比如“SOUND_AMBULANCE”
	结果：	无
	*/
	void playSound(uint8_t id);

	/*
	功能：	停止播放
	参数：	无
	结果：	无
	*/
	void stop();

private:
		
	XBuzzer	*_buz;
	uint8_t _mode;
	uint8_t _id;
};

#endif //__WKAUDIOPLAYER_H__

