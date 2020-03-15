/* WKKAudioPlayer.h
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
 *     This file is a header file for WKKAudioPlayer.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __WKKAUDIOPLAYER_H__
#define __WKKAUDIOPLAYER_H__


#include <XBlock.h>
#include <XBuzzer.h>
#include <wkkit.h>


#define WKKAudioPlayer_API_setNoteParameter	(1)	/*!< void setNoteParameter(uint8_t beatTime, uint8_t noteGap) */
#define WKKAudioPlayer_API_playNote			(2) /*!< void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat) */
#define WKKAudioPlayer_API_playMusic		(3)	/*!< void playMusic(uint8_t id) */
#define WKKAudioPlayer_API_playSound		(4)	/*!< void playSound(uint8_t id) */
#define WKKAudioPlayer_API_stop				(5)	/*!< void stop() */
#define WKKAudioPlayer_API_playTone			(6)	/*!< void playTone() */


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


class WKKAudioPlayer : public XNServer {
public:
	WKKAudioPlayer();
	~WKKAudioPlayer();

	/*
	功能：	初始化
	参数：	buz, 蜂鸣器模块实例
	结果：	成功返回0，失败返回负数
	*/
	int setup(XBuzzer *buz);

	void reset();
	void loop();

	/*
	功能：	播放音频
	参数：	frequency，声音频率
			duration，持续时长，毫秒单位
	结果：	无
	*/
	void playTone(uint16_t frequency, uint32_t duration);

	/*
	功能：	设置节拍时长
	参数：	beatTime，10ms为单位，节拍时长, 0xFF表示默认值
			noteGap，10ms为单位，音符间隔时长，0xFF表示默认值
	结果：	无
	*/
	void setNoteParameter(uint8_t beatTime = 50, uint8_t noteGap = 40);

	/*
	功能：	播放音符
	参数：	note，音符“DO, RE, ME, FA, SOL, LA, SI”，对应数值 1~7，休止符对应数值0
			scale，音高“低、中、高” 对应数值 0~2
			tone，音调“C,D,E,F,G,A,B” 对应数值 0~6
			beat，节拍“1/8, 1/4, 1/2, 1, 2” 对应数值 1,2,4,8,16
	结果：	无
	*/
	void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat);

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

#ifdef XBRIDGE_SUPPORT
protected:
	/*!< XNBlock interface */
	int8_t onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize);
#endif // XBRIDGE_SUPPORT

private:
	uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone);
		
	XBuzzer	*_buz;
	uint8_t _mode;
	uint8_t _id;
	uint16_t _beatTime;
	uint16_t _noteGap;
};

#endif //__WKKAUDIOPLAYER_H__

