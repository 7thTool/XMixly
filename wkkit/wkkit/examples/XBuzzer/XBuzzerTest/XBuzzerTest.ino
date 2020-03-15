/* XBuzzerTest.ino
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
 *     This file is test code for Buzzer module.
 *
 * Version: 1.0.0
 */


#include <YGRSystem.h>
#include <XBuzzer.h>


#define CASE_TEST_PLAY_MUSIC	1
#define CASE_TEST_PLAY_SOUND	1



XBuzzer buz;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_ES1 41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_ES2 82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_ES3 165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_ES4 330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_ES5 659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_ES6 1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_ES7 2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


const static uint16_t KFrequencyTable[3][14]  = {
  {0, NOTE_C3,NOTE_D3,NOTE_E3,NOTE_F3,NOTE_G3,NOTE_A3,NOTE_B3,NOTE_CS4,NOTE_DS4,NOTE_ES4,NOTE_FS4,NOTE_GS4,NOTE_AS4}, // SCALE_LOW
  {0, NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_CS5,NOTE_DS5,NOTE_ES5,NOTE_FS5,NOTE_GS5,NOTE_AS5}, // SCALE_MID
  {0, NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_CS6,NOTE_DS6,NOTE_ES6,NOTE_FS6,NOTE_GS6,NOTE_AS6} // SCALE_HIGH
};

uint16_t getFrequency(uint8_t note, uint8_t scale, uint8_t tone)
{  
  uint16_t freq=0;

  if (note != 0) {
    return KFrequencyTable[scale][note+tone];
  }
  
  return freq;
}

//#define ONE_PAT_TIME  (1000)  //ms
#define ONE_PAT_TIME  (500)  //ms
#define ONE_PAT_RATE  (8000/ONE_PAT_TIME) 

uint16_t _beatTime = 500;
uint16_t _noteGap = 40;

void setNoteParameter(uint8_t beatTime, uint8_t noteGap)
{
  if(beatTime == 0xff) {  //default one beat time
    _beatTime = 500; //ms
  } else {
    _beatTime = beatTime*10;
  }

  if(noteGap == 0xff) { //default one beat time
    _noteGap = 40; //ms
  } else {
    _noteGap = noteGap*10;
  }
}

void playNote(uint8_t note, uint8_t scale, uint8_t tone, uint8_t beat)
{
  uint16_t frequency = 0;
  uint32_t noteDuration = _beatTime * beat/8;
  //int pauseBetweenNotes = 0;

  if(note == 0) {
    //delay(noteDuration);
    delay(noteDuration/4);
  } else {
    frequency = getFrequency(note, scale, tone);
    buz.playTone(frequency, noteDuration);
  }

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  //pauseBetweenNotes = noteDuration * 0.1;
  //delay(pauseBetweenNotes);
  delay(_noteGap);
}


#if 1
uint16_t shengrikuaile[][4] =
{
	// note, scale, tone, time
	//5 5 6 5 1. 7 0
	{5,1,0,4}, {5,1,0,4}, {6,1,0,8}, {5,1,0,8}, {1,2,0,8}, {7,1,0,8}, {0,0,0,8}, 
	//5 5 6 5 2. 1. 0
	{5,1,0,4}, {5,1,0,4}, {6,1,0,8}, {5,1,0,8}, {2,2,0,8}, {1,2,0,8}, {0,0,0,8}, 
	//5 5 5. 3. 1. 7 6 0
	{5,1,0,4}, {5,1,0,4}, {5,2,0,8}, {3,2,0,8}, {1,2,0,8}, {7,1,0,8}, {6,1,0,8}, 
{0,0,0,4},
	//4. 4. 3. 1. 2. 1. 0
	{4,2,0,4}, {4,2,0,4}, {3,2,0,8}, {1,2,0,8}, {2,2,0,8}, {1,2,0,8}, {0,0,0,8},
};

uint16_t xiaoxinxin[][4] =
{
	// note, scale, tone, time
	{1,2,0,8}, {1,2,0,8}, {5,2,0,8}, {5,2,0,8}, {6,2,0,8}, {6,2,0,8}, {5,2,0,8}, 
{0,0,0,8}, 
	{4,2,0,8}, {4,2,0,8}, {3,2,0,8}, {3,2,0,8}, {2,2,0,8}, {2,2,0,8}, {1,2,0,8}, 
{0,0,0,8},
	{5,2,0,8}, {5,2,0,8}, {4,2,0,8}, {4,2,0,8}, {3,2,0,8}, {3,2,0,8}, {2,2,0,8}, 
{0,0,0,8},
	{5,2,0,8}, {5,2,0,8}, {4,2,0,8}, {4,2,0,8}, {3,2,0,8}, {3,2,0,8}, {2,2,0,8}, 
{0,0,0,8},
	{1,2,0,8}, {1,2,0,8}, {5,2,0,8}, {5,2,0,8}, {6,2,0,8}, {6,2,0,8}, {5,2,0,8}, 
{0,0,0,8},
	{4,2,0,8}, {4,2,0,8}, {3,2,0,8}, {3,2,0,8}, {2,2,0,8}, {2,2,0,8}, {1,2,0,8}, 
{0,0,0,8},
};

uint16_t huanlesong[][4] =
{
	// note, scale, tone, time
	{3,1,1,8}, {3,1,1,8}, {4,1,1,8}, {5,1,1,8},
	{5,1,1,8}, {4,1,1,8}, {3,1,1,8}, {2,1,1,8},
	{1,1,1,8}, {1,1,1,8}, {2,1,1,8}, {3,1,1,8},
	{3,1,1,12}, {2,1,1,4}, {2,1,1,8}, {0,0,0,8},

	{3,1,1,8}, {3,1,1,8}, {4,1,1,8}, {5,1,1,8},
	{5,1,1,8}, {4,1,1,8}, {3,1,1,8}, {2,1,1,8},
	{1,1,1,8}, {1,1,1,8}, {2,1,1,8}, {3,1,1,8},
	{2,1,1,12}, {1,1,1,4}, {1,1,1,8}, {0,0,0,8},

	{2,1,1,8}, {2,1,1,8}, {3,1,1,8}, {1,1,1,8},
	{2,1,1,8}, {3,1,1,4}, {4,1,1,4}, {3,1,1,8}, {1,1,1,8},
	{2,1,1,8}, {3,1,1,4}, {4,1,1,4}, {3,1,1,8}, {2,1,1,8},
	{1,1,1,8}, {2,1,1,8}, {5,0,1,4}, {3,1,1,4},

	{3,1,1,4}, {3,1,1,8}, {4,1,1,8}, {5,1,1,8},
	{5,1,1,8}, {4,1,1,8}, {3,1,1,8}, {4,1,1,4},{2,1,1,4},
	{1,1,1,8}, {1,1,1,8}, {2,1,1,8}, {3,1,1,8},
	{2,1,1,12}, {1,1,1,4}, {1,1,1,8}, {0,0,0,8}
};



void playShengrikuaile()
{
	setNoteParameter(50, 4);
	for (int thisNote = 0; thisNote < sizeof(shengrikuaile)/sizeof(shengrikuaile[
0]); thisNote++) {
		playNote(shengrikuaile[thisNote][0], shengrikuaile[thisNote][1], 
shengrikuaile[thisNote][2], shengrikuaile[thisNote][3]);
	}
}

void playXiaoxinxin()
{
	setNoteParameter(50, 5);
	for (int thisNote = 0; thisNote < sizeof(xiaoxinxin)/sizeof(xiaoxinxin[0]); 
thisNote++) {
		playNote(xiaoxinxin[thisNote][0], xiaoxinxin[thisNote][1], xiaoxinxin[
thisNote][2], xiaoxinxin[thisNote][3]);
	}
}

void playHuanlesong()
{
	setNoteParameter(40, 4);
	for (int thisNote = 0; thisNote < sizeof(huanlesong)/sizeof(huanlesong[0]); 
thisNote++) {
		playNote(huanlesong[thisNote][0], huanlesong[thisNote][1], huanlesong[
thisNote][2], huanlesong[thisNote][3]);
	}
}
#endif

void playSound()
{
	int duration = 400;
	float fac = 0.05;
	float fa1 = 1.0;

	buz.playTone(523*fa1, duration);
	delay(duration*fac);
	buz.playTone(523*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
	buz.playTone(880*fa1, duration);
	delay(duration*fac);
	buz.playTone(880*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
}

void setup() {
	XSystem.setup();
	Serial.begin(9600); //opens serial port,sets data rate to 9600 bps

	buz.setup("BUZ");
}

void loop() {
#if (CASE_TEST_PLAY_MUSIC == 1)
	// no need to repeat the melody.
	playShengrikuaile();
	delay(1000);
	playXiaoxinxin();
	delay(1000);
	playHuanlesong();
	delay(1000);
#endif
#if (CASE_TEST_PLAY_SOUND == 1)
	playSound();
	delay(1000);//Pause for a while.
#endif
}
