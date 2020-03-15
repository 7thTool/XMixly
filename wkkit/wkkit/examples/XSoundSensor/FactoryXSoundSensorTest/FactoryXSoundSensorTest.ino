

#include <XSoundSensor.h>
#include <XSegDisplay.h>


#define USE_MAINBOARD_PANGU
//#define USE_MAINBOARD_WUKONG	
//#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARD_PANGU
#include <HQRSystem.h>
#endif
#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#endif
#ifdef USE_MAINBOARD_NEZHA
#include <YGRSystem.h>
#endif

XSoundSensor snd;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	snd.setup("SND3300", "2");
	sgd.setup("SGD4300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	snd.setup("SND");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	snd.setup("SND3200", "1");
	sgd.setup("SGD4200", "2");
#endif

}


void loop()
{
	sgd.showNumber(snd.getVolume());
	delay(100);
}

