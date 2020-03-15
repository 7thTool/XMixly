

#include <XIRAvoiding.h>
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

XIRAvoiding ira;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	ira.setup("IRA3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_WUKONG
	ira.setup("IRA3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	ira.setup("IRA3400", "1");
	sgd.setup("SGD4200", "2");
#endif
}

void loop()
{
	ira.start();
	sgd.showNumber(ira.getStatus());
}

