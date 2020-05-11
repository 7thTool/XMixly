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

private:
	uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone);
		
	XBuzzer	*_buz;
	uint16_t _beatTime;
	uint16_t _noteGap;
};

#endif //__PGKAUDIOPLAYER_H__

