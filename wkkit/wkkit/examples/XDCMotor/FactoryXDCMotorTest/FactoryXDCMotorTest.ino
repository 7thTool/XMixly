

#include <XDCMotor.h>

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


XDCMotor dcm;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	dcm.setup("DCM3300", "1");
#endif
#ifdef USE_MAINBOARD_WUKONG
	dcm.setup("DCM3300", "1");
#endif
#ifdef USE_MAINBOARD_NEZHA
	dcm.setup("DCM3200", "1");
#endif

}


void loop()
{
	dcm.start(100);
	delay(500);
	dcm.stop();
	delay(500);
	dcm.start(-100);
	delay(500);

}