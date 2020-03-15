

#include <XRGBLed.h>

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


XRGBLed rgb;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	rgb.setup("RGB3340", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	rgb.setup("RGB3340", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	rgb.setup("RGB3280", "1");
#endif

}


void loop()
{
	rgb.showColor(0, 0x20, 0x20, 0x20);
	delay(300);
	rgb.showColor(0, 0x20, 0, 0);
	delay(300);
	rgb.showColor(0, 0, 0x20, 0);
	delay(300);
	rgb.showColor(0, 0, 0, 0x20);
	delay(300);
	rgb.clear();
	delay(200);
}
