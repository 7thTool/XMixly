

#include <XVoiceBroadcast.h>

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


XVoiceBroadcast vbc;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	vbc.setup("VBC3300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	vbc.setup("VBC3300", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	vbc.setup("VBC3200", "1");
#endif

}


void loop()
{
	uint8_t i;

	vbc.playVoice(31);
	delay(1000);
	
#if 0
	vbc.playVoice(120);
	delay(3000);
#endif

#if 0
	for (i=1; i<=117; i++) {
		vbc.playVoice(i);
		delay(1000);
	}

	for (i=118; i<=128; i++) {
		vbc.playVoice(i);
		delay(5000);
		vbc.stop();
		delay(1000);
	}
#endif
}