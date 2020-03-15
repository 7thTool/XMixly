

#include <XDualDCMotor.h>


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


XDualDCMotor ddc;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	ddc.setup("DDM3300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	ddc.setup("DDM3300", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	ddc.setup("DDM3200", "1");
#endif

}


void loop()
{
	ddc.setAllSpeed(-100, -100);
	delay(500);
	ddc.stopAllMotor();
	delay(500);
	ddc.setAllSpeed(100, 100);
	delay(500);
}