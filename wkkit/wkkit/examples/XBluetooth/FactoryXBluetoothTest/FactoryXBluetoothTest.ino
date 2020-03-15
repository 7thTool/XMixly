
#include <XBuzzer.h>
#include <XBluetooth.h>


#define USE_MAINBOARD_PANGU
//#define USE_MAINBOARD_WUKONG	
//#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARD_PANGU
#include <PGKSystem.h>
#endif
#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#endif
#ifdef USE_MAINBOARD_NEZHA
#include <YGRSystem.h>
#endif


XBuzzer buz;
XBluetooth blt;


void setup()
{
	XSystem.setup();

#ifdef USE_MAINBOARD_PANGU
	blt.setup("BLT4140", "9");
#endif
#ifdef USE_MAINBOARD_WUKONG
	buz.setup("BUZ");
	blt.setup("BLT4140", "5");
#endif
#ifdef USE_MAINBOARD_NEZHA
	buz.setup("BUZ");
	blt.setup("BLT4140", "3");
#endif

	blt.setBroadcast("XBlockly");
}


uint8_t count, blt_buffer[64];

void loop()
{
	// 蓝牙将收到的字符，发送回去
	// 注意：要使用BLT工具测试，包括“连接”，“收发数据”，“断开”测试步骤	
	if (blt.available()) {
		delay(100);
		count = blt.recvBytes(blt_buffer, 64);
		if (count > 0) {
			blt.sendBytes(blt_buffer, count);
#ifndef USE_MAINBOARD_PANGU
			buz.playTone(300, 200);
#endif
		}
	}
}