/* XBuzzer.h
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
 *     This file is a header file for XBuzzer.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XBUZZER_H__
#define __XBUZZER_H__



class XBuzzer {
public:
	XBuzzer();
	~XBuzzer();

	/*
	åŠŸèƒ½ï¼š	åˆå§‹åŒ–â€œæ‰©å±•æ¨¡å—â€
	å‚æ•°ï¼š	model, æ¨¡å—å‹å·
			port, è¿æ¥åˆ°ä¸»æ§æ¿çš„ç«¯å£ç¼–å·
	ç»“æœï¼š	æˆåŠŸè¿”å›0ï¼Œå¤±è´¥è¿”å›è´Ÿæ•°
	*/
	int setup(const char *model, const char *port);

	/*
	åŠŸèƒ½ï¼š	åˆå§‹åŒ–â€œæ¿è½½æ¨¡å—â€
	å‚æ•°ï¼š	label, æ¨¡å—åœ¨ä¸»æ§æ¿ä¸Šçš„æ ‡è´´
	ç»“æœï¼š	æˆåŠŸè¿”å›0ï¼Œå¤±è´¥è¿”å›è´Ÿæ•°
	*/
	int setup(const char *label);

	int setup(const char *model, const uint8_t pinD);

	void reset();

	/*
	¹¦ÄÜ£º	²¥·ÅÒôÆµ
	²ÎÊı£º	frequency£¬ÉùÒôÆµÂÊ
			duration£¬³ÖĞøÊ±³¤£¬ºÁÃëµ¥Î»
	½á¹û£º	ÎŞ
	*/
	void playTone(uint16_t frequency, uint32_t duration = 0);

	/*
	¹¦ÄÜ£º	ÉèÖÃ½ÚÅÄÊ±³¤
	²ÎÊı£º	beatTime£¬10msÎªµ¥Î»£¬½ÚÅÄÊ±³¤, 0xFF±íÊ¾Ä¬ÈÏÖµ
			noteGap£¬10msÎªµ¥Î»£¬Òô·û¼ä¸ôÊ±³¤£¬0xFF±íÊ¾Ä¬ÈÏÖµ
	½á¹û£º	ÎŞ
	*/
	void setNoteParameter(uint8_t beatTime = 50, uint8_t noteGap = 40);

	/*
	¹¦ÄÜ£º	²¥·ÅÒô·û
	²ÎÊı£º	note£¬Òô·û¡°DO, RE, ME, FA, SOL, LA, SI¡±£¬¶ÔÓ¦ÊıÖµ 1~7£¬ĞİÖ¹·û¶ÔÓ¦ÊıÖµ0
			scale£¬Òô¸ß¡°µÍ¡¢ÖĞ¡¢¸ß¡± ¶ÔÓ¦ÊıÖµ 0~2
			tone£¬Òôµ÷¡°C,D,E,F,G,A,B¡± ¶ÔÓ¦ÊıÖµ 0~6
			beat£¬½ÚÅÄ¡°1/8, 1/4, 1/2, 1, 2¡± ¶ÔÓ¦ÊıÖµ 1,2,4,8,16
	½á¹û£º	ÎŞ
	*/
	void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat);

private:
	uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone);
	
	int8_t	_portId;
	uint8_t _pin;
	uint16_t _beatTime;
	uint16_t _noteGap;
};


#endif //__XBUZZER_H__

