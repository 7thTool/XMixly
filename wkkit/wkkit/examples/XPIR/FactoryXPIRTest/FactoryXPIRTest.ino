

#include <XPIR.h>
#include <XSegDisplay.h>

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

XPIR pir;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	pir.setup("PIR3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_WUKONG
	pir.setup("PIR3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	pir.setup("PIR3200", "1");
	sgd.setup("SGD4200", "2");
#endif
}

void loop()
{
	sgd.showNumber(pir.isHumanMotionDetected());

	delay(100);
}

