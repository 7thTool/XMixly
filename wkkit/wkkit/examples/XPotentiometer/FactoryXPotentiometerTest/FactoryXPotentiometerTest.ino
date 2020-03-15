

#include <XPotentiometer.h>
#include <XSegDisplay.h>

#define USE_MAINBOARDA_PANGU
//#define USE_MAINBOARD_WUKONG	
//#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARDA_PANGU
#include <PGKSystem.h>
#endif
#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#endif
#ifdef USE_MAINBOARD_NEZHA
#include <YGRSystem.h>
#endif

XPotentiometer ptm;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARDA_PANGU
	ptm.setup("PTM3300", "2");
	sgd.setup("SGD4300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	ptm.setup("PTM3300", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	ptm.setup("PTM3200", "1");
	sgd.setup("SGD4200", "2");
#endif

}


void loop()
{	
	sgd.showNumber(ptm.getValue());
}

