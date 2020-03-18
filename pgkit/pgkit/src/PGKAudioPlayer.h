/* PGKAudioPlayer.h
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
 *     This file is a header file for PGKAudioPlayer.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __PGKAUDIOPLAYER_H__
#define __PGKAUDIOPLAYER_H__


#include <XBlock.h>
#include <XBuzzer.h>


#define PGKAudioPlayer_API_setNoteParameter	(1)	/*!< void setNoteParameter(uint8_t beatTime, uint8_t noteGap) */
#define PGKAudioPlayer_API_playNote			(2) /*!< void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat) */
#define PGKAudioPlayer_API_playTone			(6)	/*!< void playTone() */




class PGKAudioPlayer : public XNServer {
public:
	PGKAudioPlayer();
	~PGKAudioPlayer();

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

private:
	uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone);
		
	XBuzzer	*_buz;
	uint16_t _beatTime;
	uint16_t _noteGap;
};

#endif //__PGKAUDIOPLAYER_H__

