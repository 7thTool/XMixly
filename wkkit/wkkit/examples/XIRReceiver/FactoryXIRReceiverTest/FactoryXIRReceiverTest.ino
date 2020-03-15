

#include <PGKSystem.h>
#include <XIRReceiver.h>
#include <XSegDisplay.h>


XIRReceiver irr;
XSegDisplay sgd;


void setup()
{
	XSystem.setup();

	irr.setup("IRR3300", "1");
	sgd.setup("SGD4300", "2");
}

void test_receive()
{
	uint8_t key = irr.receive();

	if(key != 0xFF) {
		switch(key) {
		case XIR_KEY_A:
			sgd.showNumber(10);
			break;
		case XIR_KEY_B:
			sgd.showNumber(11);
			break;
		case XIR_KEY_C:
			sgd.showNumber(12);
			break;
		case XIR_KEY_D:
			sgd.showNumber(13);
			break;
		case XIR_KEY_E:
			sgd.showNumber(14);
			break; 
		case XIR_KEY_F:
			sgd.showNumber(15);
			break; 
		case XIR_KEY_0:
			sgd.showNumber(0);
			break;
		case XIR_KEY_1:
			sgd.showNumber(1);
			break;
		case XIR_KEY_2:
			sgd.showNumber(2);
			break;
		case XIR_KEY_3:
			sgd.showNumber(3);
			break;
		case XIR_KEY_4:
			sgd.showNumber(4);
			break; 
		case XIR_KEY_5:
			sgd.showNumber(5);
			break;
		case XIR_KEY_6:
			sgd.showNumber(6);
			break;
		case XIR_KEY_7:
			sgd.showNumber(7);
			break;
		case XIR_KEY_8:
			sgd.showNumber(8);
			break;
		case XIR_KEY_9:
			sgd.showNumber(9);
			break; 
		case XIR_KEY_OK:
			sgd.showNumber(16);
			break;
		case XIR_KEY_LEFT:
			sgd.showNumber(17);
			break;
		case XIR_KEY_RIGHT:
			sgd.showNumber(18);
			break; 
		case XIR_KEY_UP:
			sgd.showNumber(19);
			break;
		case XIR_KEY_DOWN:
			sgd.showNumber(20);
			break;
		default:
			sgd.showNumber(100);
			break;                   
		}
	}
}




void loop()
{
	test_receive();
}
