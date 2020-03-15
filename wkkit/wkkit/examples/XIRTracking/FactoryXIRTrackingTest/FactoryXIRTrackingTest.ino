
//#include <XRGBLed.h>
#include <XIRTracking.h>
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

XIRTracking irt;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	irt.setup("IRT3320", "1");
	//irt.setup("IRT3360", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_WUKONG
	irt.setup("IRT3320", "4");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	irt.setup("IRT3220", "1");
	sgd.setup("SGD4200", "2");
#endif
}

uint8_t irt_status = 0;

void loop()
{
	uint8_t l_status;

	l_status = irt.getStatus();
	
	switch (l_status) {
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x03:
		sgd.showNumber(l_status);
		break;
	case 0x3f:
		sgd.showNumber(6);
		break;
	default:
		sgd.clear();
		break;
	}
	delay(100);
}
