

#include <XHumiture.h>
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

XHumiture hum;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
#ifdef USE_MAINBOARD_PANGU
	hum.setup("HUM4200", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_WUKONG
	hum.setup("HUM4200", "1");
	sgd.setup("SGD4300", "2");
#endif
#ifdef USE_MAINBOARD_NEZHA
	hum.setup("HUM3200", "1");
	sgd.setup("SGD4200", "2");
#endif

}

void loop()
{
	float value = 0;

	value = hum.getHumidity();
	sgd.showNumber(value);
	delay(500);
	value = hum.getTemperature();
	sgd.showNumber(value);
	delay(500);
}

