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
#define XVoiceBroadcast_Number_TEN				(12)		// 十/拾/时
#define XVoiceBroadcast_Number_HUNDRED			(13)		// 百
#define XVoiceBroadcast_Number_THOUSAND			(14)		// 千
#define XVoiceBroadcast_Number_TENTHOUSAND		(15)		// 万
#define XVoiceBroadcast_Number_POINT			(16)		// 点
#define XVoiceBroadcast_Number_MINUS			(17)		// 负

#define XVoiceBroadcast_Time_MINUTE				(18)		// 分
#define XVoiceBroadcast_Time_SECOND				(19)		// 秒
#define XVoiceBroadcast_Time_YEAR				(20)		// 年
#define XVoiceBroadcast_Time_MONTH				(21)		// 月
#define XVoiceBroadcast_Time_DAY				(22)		// 日
#define XVoiceBroadcast_Time_WEEKDAY			(23)		// 星期


#define XVoiceBroadcast_UNIT_DEGREE				(24)		// 度
#define XVoiceBroadcast_UNIT_PERCENT			(25)		// 百分之
#define XVoiceBroadcast_UNIT_METER				(26)		// 米
#define XVoiceBroadcast_UNIT_CENTIMETER			(27)		// 厘米
#define XVoiceBroadcast_UNIT_MILLIMETER			(28)		// 毫米
#define XVoiceBroadcast_UNIT_KILOGRAM			(29)		// 千克
#define XVoiceBroadcast_UNIT_GRAM				(30)		// 克

#define XVoiceBroadcast_THEME_NORMAL			(31)		// 正常
#define XVoiceBroadcast_THEME_ABNORMAL			(32)		// 异常

#define XVoiceBroadcast_UNIT_VOLTS				(33)		// 伏
#define XVoiceBroadcast_UNIT_AMPERE				(34)		// 安
#define XVoiceBroadcast_UNIT_YUAN				(35)		// 元
#define XVoiceBroadcast_UNIT_JIAO				(36)		// 角
#define XVoiceBroadcast_UNIT_CENT				(37)		// 分

#define XVoiceBroadcast_THEME_TEMPERATURE		(38)		// 温度
#define XVoiceBroadcast_THEME_HUMITURE			(39)		// 湿度
#define XVoiceBroadcast_THEME_LIGHT				(40)		// 光线亮度
#define XVoiceBroadcast_THEME_SOUND				(41)		// 声音强度
#define XVoiceBroadcast_THEME_DISTANCE			(42)		// 距离
#define XVoiceBroadcast_THEME_SPEED				(43)		// 速度
#define XVoiceBroadcast_THEME_WHEIGHT			(44)		// 重量
#define XVoiceBroadcast_THEME_ANGLE				(45)		// 角度
#define XVoiceBroadcast_THEME_STATUS			(46)		// 状态
#define XVoiceBroadcast_THEME_TIME				(47)		// 时间
#define XVoiceBroadcast_THEME_VOLTAGE			(48)		// 电压
#define XVoiceBroadcast_THEME_CURRENT			(49)		// 电流
#define XVoiceBroadcast_THEME_WATERLINE			(50)		// 水位
#define XVoiceBroadcast_THEME_UNITPRICE			(51)		// 单价
#define XVoiceBroadcast_THEME_AMOUNT			(52)		// 数量
#define XVoiceBroadcast_THEME_TOTALPRICE		(53)		// 总价

#define XVoiceBroadcast_Time_TODAY				(54)		// 今天
#define XVoiceBroadcast_Time_YESTERDAY			(55)		// 昨天
#define XVoiceBroadcast_Time_TOMORROW			(56)		// 明天
#define XVoiceBroadcast_Time_MORNING			(57)		// 上午
#define XVoiceBroadcast_Time_AFTERNOON			(58)		// 下午
#define XVoiceBroadcast_Time_NIGHT				(59)		// 晚上
#define XVoiceBroadcast_Time_CURRENT			(60)		// 当前


#define XVoiceBroadcast_Operator_ADD			(61)		// 加
#define XVoiceBroadcast_Operator_MINUS			(62)		// 减
#define XVoiceBroadcast_Operator_MULTI			(63)		// 乘
#define XVoiceBroadcast_Operator_DIVIDE			(64)		// 除
#define XVoiceBroadcast_Operator_EQUAL			(65)		// 等于


#define XVoiceBroadcast_Sound_ACTION_TICKTOCK	(70)		// 时针滴答
#define XVoiceBroadcast_Sound_ACTION_WHOLEBELL	(71)		// 整点钟声
#define XVoiceBroadcast_Sound_ACTION_JO			(72)		// 激光单发
#define XVoiceBroadcast_Sound_ACTION_JOJO		(73)		// 激光两连发
#define XVoiceBroadcast_Sound_ACTION_JOJOJO		(74)		// 激光三连发

#define XVoiceBroadcast_Sound_ALARM_POLICE		(78)		// 110警车
#define XVoiceBroadcast_Sound_ALARM_FIREENGINE	(79)		// 119消防车
#define XVoiceBroadcast_Sound_ALARM_AMBULANCE	(80)		// 120急救车
#define XVoiceBroadcast_Sound_ALARM_BELL		(81)		// 上课铃
#define XVoiceBroadcast_Sound_ALARM_GUARD		(82)		// 戒备
#define XVoiceBroadcast_Sound_ALARM_REDALERT	(83)		// 红色警戒

#define XVoiceBroadcast_Sound_SCIENCE_FICTION1	(86)		// 机器运转
#define XVoiceBroadcast_Sound_SCIENCE_FICTION2	(87)		// 机器人移动
#define XVoiceBroadcast_Sound_SCIENCE_FICTION3	(88)		// 伺服电机
#define XVoiceBroadcast_Sound_SCIENCE_FICTION4	(89)		// 激光剑
#define XVoiceBroadcast_Sound_SCIENCE_FICTION5	(90)		// 飞越

#define XVoiceBroadcast_Sound_WARN1				(94)		// 打卡
#define XVoiceBroadcast_Sound_WARN2				(95)		// 叮叮
#define XVoiceBroadcast_Sound_WARN3				(96)		// 水滴
#define XVoiceBroadcast_Sound_WARN4				(97)		// 当
#define XVoiceBroadcast_Sound_WARN5				(98)		// 电话铃
#define XVoiceBroadcast_Sound_WARN6				(99)		// 拍照

#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL1 (102)		// 电波
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL2 (103)		// 说话
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL3 (104)		// 信号
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL4 (105)		// 飞船着陆
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL5 (106)		// 召唤
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL6 (107)		// 怪笑
#define XVoiceBroadcast_Sound_EXTRATERRESTRIAL7 (108)		// 警戒

#define XVoiceBroadcast_Sound_MOOD_CHEER		(110)		// 欢呼
#define XVoiceBroadcast_Sound_MOOD_SURPRISE		(111)		// 惊讶
#define XVoiceBroadcast_Sound_MOOD_HAPPY		(112)		// 开心

#define XVoiceBroadcast_Sound_MUSIC1			(118)		// 音乐：summer
#define XVoiceBroadcast_Sound_MUSIC2			(119)		// 音乐：always with me
#define XVoiceBroadcast_Sound_MUSIC3			(120)		// 音乐：铃儿响叮当
#define XVoiceBroadcast_Sound_MUSIC4			(121)		// 音乐：等风来
#define XVoiceBroadcast_Sound_MUSIC5			(122)		// 音乐：机器猫


class XVoiceBroadcast {
public:
	XVoiceBroadcast();
	~XVoiceBroadcast();

	/*
	功能：	初始化“扩展模块”
	参数：	model, 模块型号
			port, 连接到主控板的端口编号
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *model, const char *port);

	/*
	功能：	初始化“板载模块”
	参数：	label, 模块在主控板上的标贴
	结果：	成功返回0，失败返回负数
	*/
	int setup(const char *label);

	int setup(const char *model, const uint8_t sda, const uint8_t scl, const uint8_t rst, const uint8_t sel);

	void reset();

	/*
	功能：	播报指定的对象
	参数：	which, 对象，参考"XVoiceBroadcast_Object_XXX"。
	参数：	value, 数值，范围:-99999.99~99999.99，最多播放小数点后2位。
	结果：	无
	*/
	void reportObject(uint8_t which, float value);

	/*
	功能：	播报时间
	参数：	hour, 时，0~23，"其它指"表示不报时
			minute, 分，0~59，"其它指"表示不报分
			second, 秒，0~59，"其它指"表示不报秒
	结果：	无
	*/	
	void reportTime(uint8_t hour, uint8_t minute, uint8_t second);

	/*
	功能：	播报时间
	参数：	year, 年，正整数, 0表示不报年
			month, 月，1~12，0表示不报月
			day, 日，1~31，0表示不报日
			weekday, 星期，1~7，0表示不报星期
	结果：	无
	*/
	void reportDate(uint16_t year, uint8_t month, uint8_t day, uint8_t weekday = 0);
	
	/*
	功能：	播报数学运算符
	参数：	which, 对象，参考"XVoiceBroadcast_Operator_XXX"
	结果：	无
	*/
	void reportOperator(uint8_t which);

	/*
	功能：	播报音效
	参数：	which, 对象, 参考声效定义
	参数：	repeat, 0表示只播报一次, 1表示重复播报
	结果：	无
	*/
	void reportSound(uint8_t which, uint8_t repeat = 0);
	
	/*
	功能：	播放某一段语音
	参数：	segment, 0-127, 播放第segment段语音
	结果：	无
	*/
	void playVoice(uint8_t segment);
	
	/*
	功能：	按顺序连续播放一组语音
	参数：	segs，需要播放的语音段内容数组
			length, 1-32，需要连续播放的语音段总数
	结果：	无
	*/
	void playVoices(uint8_t * segs, uint8_t length);

	/*
	功能：	查询是否在播放中
	参数：	无
	结果：	0-播放结束，1-播放中
	*/
	uint8_t isPlaying();

	/*
	功能：	停止播报
	参数：	无
	结果：	无
	*/
	void stop();

private:
	uint8_t _buf[32];
	int8_t	_portId;
	uint8_t _selectPin;
	uint8_t _resetPin;
};


#endif //__XVOICEBROADCAST_H__