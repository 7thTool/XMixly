

#include <XShockSensor.h>
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

XShockSensor sks;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	sks.setup("SKS3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_WUKONG
	sks.setup("SKS3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	sks.setup("SKS3200", "1");
	sgd.setup("SGD4200", "2");
#endif
}

void loop()
{
	uint8_t l_status;

	l_status = sks.isShocking();
	
	switch (l_status) {
	case 0:
		sgd.showNumber(0);
		break;
	case 1:
        sgd.showNumber(1);
		break;
	default:
		sgd.clear();
		break;
	}

	delay(500);
}

