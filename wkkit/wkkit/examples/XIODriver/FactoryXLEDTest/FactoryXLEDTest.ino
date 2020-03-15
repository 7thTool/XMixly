

#include <XIODriver.h>


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

XIODriver iod;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	iod.setup("IOD3300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	iod.setup("IOD3300", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	iod.setup("IOD3200", "1");
#endif
}

void loop()
{
	iod.digitalWrite(1, 0);
	
	delay(300);

	iod.digitalWrite(1, 1);

	delay(300);
}

