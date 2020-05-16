/* XVoiceBroadcast.h
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
 *     This file is a header file for XVoiceBroadcast.cpp.
 *
 * Version: 1.0.0
 */


#ifndef __XVOICEBROADCAST_H__
#define __XVOICEBROADCAST_H__



#define XVoiceBroadcast_Object_VALUE			(0)
#define XVoiceBroadcast_Object_LIGHT			(1)
#define XVoiceBroadcast_Object_SOUND			(2)
#define XVoiceBroadcast_Object_TEMPERATURE		(3)
#define XVoiceBroadcast_Object_HUMIDITY			(4)
#define XVoiceBroadcast_Object_DISTANCE			(5)
#define XVoiceBroadcast_Object_SPEED			(6)
#define XVoiceBroadcast_Object_STATUS			(7)


//voices part
#define XVoiceBroadcast_Number_ZERO				(2)			// 0
#define XVoiceBroadcast_Number_ONE				(3)			// 1
#define XVoiceBroadcast_Number_TWO				(4)			// 2
#define XVoiceBroadcast_Number_THREE			(5)			// 3
#define XVoiceBroadcast_Number_FOUR				(6)			// 4		
#define XVoiceBroadcast_Number_FIVE				(7)			// 5	
#define XVoiceBroadcast_Number_SIX				(8)			// 6	
#define XVoiceBroadcast_Number_SEVEN			(9)			// 7	
#define XVoiceBroadcast_Number_EIGHT			(10)		// 8	
#define XVoiceBroadcast_Number_NINE				(11)		// 9
#define XVoiceBroadcast_Number_TEN				(12)		// ʮ/ʰ/ʱ
#define XVoiceBroadcast_Number_HUNDRED			(13)		// ��
#define XVoiceBroadcast_Number_THOUSAND			(14)		// ǧ
#define XVoiceBroadcast_Number_TENTHOUSAND		(15)		// ��
#define XVoiceBroadcast_Number_POINT			(16)		// ��
#define XVoiceBroadcast_Number_MINUS			(17)		// ��

#define XVoiceBroadcast_Time_MINUTE				(18)		// ��
#define XVoiceBroadcast_Time_SECOND				(19)		// ��
#define XVoiceBroadcast_Time_YEAR				(20)		// ��
#define XVoiceBroadcast_Time_MONTH				(21)		// ��
#define XVoiceBroadcast_Time_DAY				(22)		// ��
#define XVoiceBroadcast_Time_WEEKDAY			(23)		// ����


#define XVoiceBroadcast_UNIT_DEGREE				(24)		// ��
#define XVoiceBroadcast_UNIT_PERCENT			(25)		// �ٷ�֮
#define XVoiceBroadcast_UNIT_METER				(26)		// ��
#define XVoiceBroadcast_UNIT_CENTIMETER			(27)		// ����
#define XVoiceBroadcast_UNIT_MILLIMETER			(28)		// ����
#define XVoiceBroadcast_UNIT_KILOGRAM			(29)		// ǧ��
#define XVoiceBroadcast_UNIT_GRAM				(30)		// ��

#define XVoiceBroadcast_THEME_NORMAL			(31)		// ����
#define XVoiceBroadcast_THEME_ABNORMAL			(32)		// �쳣

#define XVoiceBroadcast_UNIT_VOLTS				(33)		// ��
#define XVoiceBroadcast_UNIT_AMPERE				(34)		// ��
#define XVoiceBroadcast_UNIT_YUAN				(35)		// Ԫ
#define XVoiceBroadcast_UNIT_JIAO				(36)		// ��
#define XVoiceBroadcast_UNIT_CENT				(37)		// ��

#define XVoiceBroadcast_THEME_TEMPERATURE		(38)		// �¶�
#define XVoiceBroadcast_THEME_HUMITURE			(39)		// ʪ��
#define XVoiceBroadcast_THEME_LIGHT				(40)		// ��������
#define XVoiceBroadcast_THEME_SOUND				(41)		// ����ǿ��
#define XVoiceBroadcast_THEME_DISTANCE			(42)		// ����
#define XVoiceBroadcast_THEME_SPEED				(43)		// �ٶ�
#define XVoiceBroadcast_THEME_WHEIGHT			(44)		// ����
#define XVoiceBroadcast_THEME_ANGLE				(45)		// �Ƕ�
#define XVoiceBroadcast_THEME_STATUS			(46)		// ״̬
#define XVoiceBroadcast_THEME_TIME				(47)		// ʱ��
#define XVoiceBroadcast_THEME_VOLTAGE			(48)		// ��ѹ
#define XVoiceBroadcast_THEME_CURRENT			(49)		// ����
#define XVoiceBroadcast_THEME_WATERLINE			(50)		// ˮλ
#define XVoiceBroadcast_THEME_UNITPRICE			(51)		// ����
#define XVoiceBroadcast_THEME_AMOUNT			(52)		// ����
#define XVoiceBroadcast_THEME_TOTALPRICE		(53)		// �ܼ�

#define XVoiceBroadcast_Time_TODAY				(54)		// ����
#define XVoiceBroadcast_Time_YESTERDAY			(55)		// ����
#define XVoiceBroadcast_Time_TOMORROW			(56)		// ����
#define XVoiceBroadcast_Time_MORNING			(57)		// ����
#define XVoiceBroadcast_Time_AFTERNOON			(58)		// ����
#define XVoiceBroadcast_Time_NIGHT				(59)		// ����
#define XVoiceBroadcast_Time_CURRENT			(60)		// ��ǰ


#define XVoiceBroadcast_Operator_ADD			(61)		// ��
#define XVoiceBroadcast_Operator_MINUS			(62)		// ��
#define XVoiceBroadcast_Operator_MULTI			(63)		// ��
#define XVoiceBroadcast_Operator_DIVIDE			(64)		// ��
#define XVoiceBroadcast_Operator_EQUAL			(65)		// ����


#define XVoiceBroadcast_Sound_ACTION_TICKTOCK	(70)		// ʱ��δ�
#define XVoiceBroadcast_Sound_ACTION_WHOLEBELL	(71)		// ��������
#define XVoiceBroadcast_Sound_ACTION_JO			(72)		// ���ⵥ��
#define XVoiceBroadcast_Sound_ACTION_JOJO		(73)		// ����������
#define XVoiceBroadcast_Sound_ACTION_JOJOJO		(74)		// ����������

#define XVoiceBroadcast_Sound_ALARM_POLICE		(78)		// 110����
#define XVoiceBroadcast_Sound_ALARM_FIREENGINE	(79)		// 119������
#define XVoiceBroadcast_Sound_ALARM_AMBULANCE	(80)		// 120���ȳ�
#define XVoiceBroadcast_Sound_ALARM_BELL		(81)		// �Ͽ���
#define XVoiceBroadcast_Sound_ALARM_GUARD		(82)		// �䱸
#define XVoiceBroadcast_Sound_ALARM_REDALERT	(83)		// ��ɫ����

#define XVoiceBroadcast_Sound_SCIENCE_FICTION1	(86)		// ������ת
#define XVoiceBroadcast_Sound_SCIENCE_FICTION2	(87)		// �������ƶ�
#define XVoiceBroadcast_Sound_SCIENCE_FICTION3	(88)		// �ŷ����
#define XVoiceBroadcast_Sound_SCIENCE_FICTION4	(89)		// ���⽣
#define XVoiceBroadcast_Sound_SCIENCE_FICTION5	(90)		// ��Խ

#define XVoiceBroadcast_Sound_WARN1				(94)		// ��
#define XVoiceBroadcast_Sound_WARN2				(95)		// ����
#define XVoiceBroadcast_Sound_WARN3				(96)		// ˮ��
#define XVoiceBroadcast_Sound_WARN4				(97)		// ��
#define XVoiceBroadcast_Sound_WARN5				(98)		// �绰��
#define XVoiceBroadcast_Sound_WARN6				(99)		// ����

#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL1 (102)		// �粨
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL2 (103)		// ˵��
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL3 (104)		// �ź�
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL4 (105)		// �ɴ���½
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL5 (106)		// �ٻ�
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL6 (107)		// ��Ц
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL7 (108)		// ����

#define XVoiceBroadcast_Sound_MOOD_CHEER		(110)		// ����
#define XVoiceBroadcast_Sound_MOOD_SURPRISE		(111)		// ����
#define XVoiceBroadcast_Sound_MOOD_HAPPY		(112)		// ����

#define XVoiceBroadcast_Sound_MUSIC1			(118)		// ���֣�summer
#define XVoiceBroadcast_Sound_MUSIC2			(119)		// ���֣�always with me
#define XVoiceBroadcast_Sound_MUSIC3			(120)		// ���֣�����춣��
#define XVoiceBroadcast_Sound_MUSIC4			(121)		// ���֣��ȷ���
#define XVoiceBroadcast_Sound_MUSIC5			(122)		// ���֣�����è


class XVoiceBroadcast {
public:
	XVoiceBroadcast();
	~XVoiceBroadcast();

	/*
	���ܣ�	��ʼ������չģ�顱
	������	model, ģ���ͺ�
			port, ���ӵ����ذ�Ķ˿ڱ��
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *model, const char *port);

	/*
	���ܣ�	��ʼ��������ģ�顱
	������	label, ģ�������ذ��ϵı���
	�����	�ɹ�����0��ʧ�ܷ��ظ���
	*/
	int setup(const char *label);

	int setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel);

	void reset();

	/*
	���ܣ�	����ָ���Ķ���
	������	which, ���󣬲ο�"XVoiceBroadcast_Object_XXX"��
	������	value, ��ֵ����Χ:-99999.99~99999.99����ಥ��С�����2λ��
	�����	��
	*/
	void reportObject(uint8_t which, float value);

	/*
	���ܣ�	����ʱ��
	������	hour, ʱ��0~23��"����ָ"��ʾ����ʱ
			minute, �֣�0~59��"����ָ"��ʾ������
			second, �룬0~59��"����ָ"��ʾ������
	�����	��
	*/	
	void reportTime(uint8_t hour, uint8_t minute, uint8_t second);

	/*
	���ܣ�	����ʱ��
	������	year, �꣬������, 0��ʾ������
			month, �£�1~12��0��ʾ������
			day, �գ�1~31��0��ʾ������
			weekday, ���ڣ�1~7��0��ʾ��������
	�����	��
	*/
	void reportDate(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday = 0);
	
	/*
	���ܣ�	������ѧ�����
	������	which, ���󣬲ο�"XVoiceBroadcast_Operator_XXX"
	�����	��
	*/
	void reportOperator(uint8_t which);

	/*
	���ܣ�	������Ч
	������	which, ����, �ο���Ч����
	������	repeat, 0��ʾֻ����һ��, 1��ʾ�ظ�����
	�����	��
	*/
	void reportSound(uint8_t which, uint8_t repeat = 0);
	
	/*
	���ܣ�	����ĳһ������
	������	segment, 0-127, ���ŵ�segment������
	�����	��
	*/
	void playVoice(uint8_t segment);
	
	/*
	���ܣ�	��˳����������һ������
	������	segs����Ҫ���ŵ���������������
			length, 1-32����Ҫ�������ŵ�����������
	�����	��
	*/
	void playVoices(uint8_t * segs, uint8_t length);

	/*
	���ܣ�	��ѯ�Ƿ��ڲ�����
	������	��
	�����	0-���Ž�����1-������
	*/
	uint8_t isPlaying();

	/*
	���ܣ�	ֹͣ����
	������	��
	�����	��
	*/
	void stop();

private:
	uint8_t _buf[32];
	int8_t	_portId;
	uint8_t _selectPin;
	uint8_t _resetPin;
};


#endif //__XVOICEBROADCAST_H__