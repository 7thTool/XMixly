

#include <XSegDisplay.h>

//#define USE_MAINBOARD_WUKONG	
#define USE_MAINBOARD_NEZHA

#ifdef USE_MAINBOARD_WUKONG
#include <HQRSystem.h>
#else
#include <YGRSystem.h>
#endif


XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_WUKONG
	sgd.setup("SGD4300", "2");
#else
	sgd.setup("SGD4200", "2");
#endif

}


void loop()
{
	uint8_t index, segdata, count;
	
	for (index=1; index<=4; index++) {
		for(count=0, segdata=0x01; count<8; count++) {
			sgd.showSegments(index, segdata);
			segdata <<= 1;
			segdata |= 0x01;
			delay(25);
		}
	}

	delay(500);
	sgd.clear();
	delay(75);
}