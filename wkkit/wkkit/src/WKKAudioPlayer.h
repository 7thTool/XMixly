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
	���ܣ�	��ʼ��
	������	buz, ������ģ��ʵ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(XBuzzer *buz);

	void reset();
	void loop();

	/*
	���ܣ�	������Ƶ
	������	frequency������Ƶ��
			duration������ʱ�������뵥λ
	�����	��
	*/
	void playTone(uint16_t frequency, uint32_t duration);

	/*
	���ܣ�	���ý���ʱ��
	������	beatTime��10msΪ��λ������ʱ��, 0xFF��ʾĬ��ֵ
			noteGap��10msΪ��λ���������ʱ����0xFF��ʾĬ��ֵ
	�����	��
	*/
	void setNoteParameter(uint8_t beatTime = 50, uint8_t noteGap = 40);

	/*
	���ܣ�	��������
	������	note��������DO, RE, ME, FA, SOL, LA, SI������Ӧ��ֵ 1~7����ֹ����Ӧ��ֵ0
			scale�����ߡ��͡��С��ߡ� ��Ӧ��ֵ 0~2
			tone��������C,D,E,F,G,A,B�� ��Ӧ��ֵ 0~6
			beat�����ġ�1/8, 1/4, 1/2, 1, 2�� ��Ӧ��ֵ 1,2,4,8,16
	�����	��
	*/
	void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat);

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

