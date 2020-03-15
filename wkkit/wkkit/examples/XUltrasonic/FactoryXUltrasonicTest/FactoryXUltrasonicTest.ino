
#include <XUltrasonic.h>
#include <XSegDisplay.h>

//#define USE_MAINBOARD_WUKONG	
#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#else
#include <YGRSystem.h>
#endif

XUltrasonic uls;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_WUKONG
	uls.setup("ULS3600", "1");
	sgd.setup("SGD4300", "2");
#else
	uls.setup("ULS3200", "1");
	sgd.setup("SGD4200", "2");
#endif

}

void loop()
{
	sgd.showNumber(uls.getDistance());
	delay(200);
}