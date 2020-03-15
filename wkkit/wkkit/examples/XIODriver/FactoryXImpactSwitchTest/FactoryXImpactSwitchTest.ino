

#include <XIODriver.h>
#include <XSegDisplay.h>
#include <PGKSystem.h>


XIODriver iod;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();
	iod.setup("IOD3300", "1");
	sgd.setup("SGD4300", "2");
}

void loop()
{
	sgd.showNumber(iod.digitalRead(1));
}

