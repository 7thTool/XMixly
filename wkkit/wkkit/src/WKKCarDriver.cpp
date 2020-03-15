/* WKKCarDriver.cpp
 *
 * Copyright (C) 2017-2022 Shanghai Mylecon Electronic Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;
 *
 * Description: 
 *     This file is an implement of wukong-kit Car Driver Server.
 *
 * History:
 * Version: 1.0.0
 */


#include <Arduino.h>
#include <XBlock.h>
#include <XBridge.h>
#include <WKKCarDriver.h>


#define AUTOLINETRACKING_MAX_TIMEOUT 		200
#define AUTOOBSTACLEAVOIDANCE_MAX_TIMEOUT	100


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif

#define MODE_STOP					0
#define MODE_FORWARD				1
#define MODE_BACKWARD				2
#define MODE_TURN					3
#define MODE_AUTOLINETRACKING		4
#define MODE_AUTOOBSTACLEAVOIDANCE	5

WKKCarDriver::WKKCarDriver():
	_ddm(NULL),
	_irt(NULL),
	_uls(NULL),
	_mode(MODE_STOP),
	_speed(0),
	_degree(0),
	_altTimeout(0),
	_altHighSpeed(0),
	_altLowSpeed(0),
	_tracking(0),
	_aoaTimeout(0),
	_aoaRunSpeed(0),
	_dis(0), 
	_randVal(255),
	_continueBackwardTimes(0)
{
}

WKKCarDriver::~WKKCarDriver()
{
	reset();
}

int WKKCarDriver::setup(XDualDCMotor *ddm)
{
	if(ddm != NULL)
		_ddm = ddm;
	else
		return -1;

	reset();
	return 0;
}

void WKKCarDriver::reset()
{
	stop();
}

void WKKCarDriver::loop()
{
	if (!_ddm) {
		return;
	}

	if(_mode == MODE_AUTOLINETRACKING) {
		loopAutoLineTracking();
	}
	else if(_mode == MODE_AUTOOBSTACLEAVOIDANCE) {
		loopAutoObstacleAvoidance();
	}
}

void WKKCarDriver::forward(uint8_t speed)
{
	LOGN("WKKCarDriver::forward()");
	LOG("speed=");LOGN(speed);

	if (!_ddm) {
		return;
	}

	if (speed > 100) {
		speed = 100;
	}

	if ((_mode != MODE_FORWARD) || (_speed != speed)) {
		if (_mode != MODE_FORWARD) {
			stop();
		}
		int8_t l = (int8_t)mapSpeed(speed);
		_ddm->setAllSpeed(l, l);
		_speed = speed;
		_mode = MODE_FORWARD;
	}
}

void WKKCarDriver::backward(uint8_t speed)
{
	LOGN("WKKCarDriver::backward()");
	LOG("speed=");LOGN(speed);

	if (!_ddm) {
		return;
	}

	if (speed > 100) {
		speed = 100;
	}

	if ((_mode != MODE_BACKWARD) || (_speed != speed)) {
		if (_mode != MODE_BACKWARD) {
			stop();
		}
		int8_t l = ((int8_t)mapSpeed(speed)) * -1;
		_ddm->setAllSpeed(l, l);
		_speed = speed;
		_mode = MODE_BACKWARD;
	}
}

void WKKCarDriver::turn(uint8_t speed, uint16_t degree)
{
	int8_t l1, l2;

	LOGN("WKKCarDriver::turn()");
	LOG("speed=");LOG(speed);LOG(",degree=");LOGN(degree);

	if (!_ddm) {
		return;
	}

	if (speed > 100) {
		speed = 100;
	}
	degree = degree > 360 ? 360 : degree;

	if ((_mode != MODE_TURN) || (_speed != speed) || (_degree != degree))
	{
		if(degree == 90) {
			forward(speed);
		}
		else if(degree == 270) {
			backward(speed);
		}
		else {
			if (_mode != MODE_TURN) {
				stop();
			}

			/*map speed1 or speed2 to min speed(25) when its value is not 0, 
			*because the min-limit speed is 25 to make motor run.
			*/
	#if 0
			calcDDMSpeed(mapSpeed(speed), degree, &l1, &l2);
			if(abs(l1) < 25) l1 = 0; 
			if(abs(l2) < 25) l2 = 0;
	#else
			calcDDMSpeed(speed, degree, &l1, &l2);

			if(l1 < 0) l1 = -mapSpeed(-l1);
			else if(l1 > 0) l1 = mapSpeed(l1);

			if(l2 < 0) l2 = -mapSpeed(-l2);
			else if(l2 > 0) l2 = mapSpeed(l2);
	#endif
			_ddm->setAllSpeed(l1, l2);
			_speed = speed;
			_degree = degree;
			_mode = MODE_TURN;
		}
	}
}

void WKKCarDriver::turn(uint8_t action, uint8_t speed, uint8_t angle)
{
	uint16_t degree = 0;

	LOGN("WKKCarDriver::turn()");
	LOG("action=");LOG(action);LOG(",speed=");LOG(speed);LOG(",angle=");LOGN(angle);

	if (!_ddm) {
		return;
	}

	if (speed > 100) {
		speed = 100;
	}
	angle = angle > 80 ? 90 : angle;
	angle = map(angle, 0, 90, 0, 45);

	/*if((action == 2 || action == 3) && (angle==90)) { //limit angle to 89 when angle=90 for backward turn
		angle = 89;
	}*/

	switch (action) {
		case 0:
			degree = 90 + angle;
			break;
		case 1:
			degree = 90 - angle;
			break;
		case 2:
			degree = 270 - angle;
			break;
		case 3:
			degree = 270 + angle;
			break;
		default:
			return;
	}

	turn(speed, degree);
}


void WKKCarDriver::stop()
{
	LOGN("WKKCarDriver::stop()");

	if (!_ddm || (_mode == MODE_STOP)) {
		return;
	}

	_ddm->setAllSpeed(0, 0);
	_speed = 0;
	_mode = MODE_STOP;
	_altTimeout = 0;
	_aoaTimeout = 0;
	_irt = NULL;
	_uls = NULL;
}

void WKKCarDriver::autoLineTracking(XIRTracking *irt, uint8_t speed, int duration)
{
	LOGN("WKKCarDriver::autoLineTracking()");

	if (!_ddm || !irt) {
		return;
	}

	if ((irt != _irt) || (_mode != MODE_AUTOLINETRACKING) || (_speed != speed)) {
		stop();

		if (speed >=2) { // 2 is max speed for aoa
			_altHighSpeed = 60;
			_altLowSpeed = 35;
		}
		else if(speed == 1) {
			_altHighSpeed = 50;
			_altLowSpeed = 32;
		}
		else if(speed == 0) {
			_altHighSpeed = 40;
			_altLowSpeed = 29;
		}

		_irt = irt;
		_speed = speed;
		_altTimeout = 0;
		_tracking = 0;
		_mode = MODE_AUTOLINETRACKING;
	}

	if (duration == 0) {
		loop();
	} else if (duration < 0) {
		while (true) {
			loop();
		}
	} else if(duration > 0) {
		unsigned long now = millis();
		do {
			loop();
		} while (millis() < now + (duration * 1000ul));
		stop();
	}

}

void WKKCarDriver::autoObstacleAvoidance(XUltrasonic *uls, uint8_t speed, int duration)
{
	LOGN("WKKCarDriver::autoObstacleAvoidance()");

	if (!_ddm || !uls) {
		return;
	}

	if ((uls != _uls) || (_mode != MODE_AUTOOBSTACLEAVOIDANCE) || (_speed != speed)) {
		stop();

		if (speed >= 2) { // 2 is max speed for aoa
			_aoaRunSpeed = 65;
		}
		else if(speed == 1) {
			_aoaRunSpeed = 50;
		}
		else if(speed == 0) {
			_aoaRunSpeed = 35;
		}

		_uls = uls;
		_speed = speed;
		_aoaTimeout = 0;
		_mode = MODE_AUTOOBSTACLEAVOIDANCE;
	}

	if (duration == 0) {
		loop();
	} else if (duration < 0) {
		while (true) {
			loop();
		}
	} else if(duration > 0) {
		unsigned long now = millis();
		do {
			loop();
		} while (millis() < now + (duration * 1000ul));
		stop();
	}
	/*else if(duration == 0) {}*/
}

#ifdef XBRIDGE_SUPPORT
int8_t WKKCarDriver::onAccess(uint8_t api, const uint8_t *param, uint8_t psize, uint8_t *result, uint8_t *rsize)
{
	uint8_t action;
	uint8_t speed;
	uint8_t angle;
	uint8_t uid;
	XIRTracking *irt = NULL;
	XUltrasonic *uls = NULL;

	LOGN("WKKCarDriver::onAccess()");
	(void)psize; (void)result;
	*rsize = 0;

	if (api == WKKCarDriver_API_FORWARD) {	
		param = fetchU8(param, &speed);
		forward(speed);
	}
	else if (api == WKKCarDriver_API_BACKWARD) {
		param = fetchU8(param, &speed);
		backward(speed);
	}
	else if (api == WKKCarDriver_API_TURN) {
		param = fetchU8(param, &action);
		param = fetchU8(param, &speed);
		param = fetchU8(param, &angle);
		turn(action, speed, angle);
	}
	else if (api == WKKCarDriver_API_STOP) {
		stop();
	}
	else if (api == WKKCarDriver_API_ALT) {
		param = fetchU8(param, &uid);
		param = fetchU8(param, &speed);
		irt = (XIRTracking *)XBridge.getBlockByUid(uid);
		if(irt == NULL) {
			return -1;
		}
		autoLineTracking(irt, speed);
	}
	else if (api == WKKCarDriver_API_AOA) {	
		param = fetchU8(param, &uid);
		param = fetchU8(param, &speed);
		uls = (XUltrasonic *)XBridge.getBlockByUid(uid);
		if(uls == NULL) {
			return -1;
		}
		autoObstacleAvoidance(uls , speed);
	}
	else {
		return -1;
	}

	return 0;
}
#endif // XBRIDGE_SUPPORT

int8_t WKKCarDriver::loopAutoLineTracking()
{
	int8_t Lspeed = 0; //Lspeed is m1 speed, Rspeed is m2 speed
	int8_t Rspeed = 0; 
	uint8_t status;
	
	LOGN("WKKCarDriver::loopAutoLineTracking()");
	
	status = _irt->getStatus();
	LOG("status = ");LOGN(status);
	
	if (status & 0x1) //channel1 on-line
	{
		_altTimeout = 0;
		if (status & 0x2)/* forward */ //channel2 on-line 
		{
			Lspeed = _altHighSpeed;
			Rspeed = _altHighSpeed;
			_tracking = 10;
		} 
		else if (!(status & 0x2)) /* turn left*/ //channel2 off-line 
		{ 
			Lspeed = _altLowSpeed;
			Rspeed = _altHighSpeed;
			if (_tracking>1) _tracking--;
		}
	} 
	else /*if (!(status & 0x1))*/ //channel1 off-line 
	{
		if (status & 0x2) /* turn right */ //channel2 on-line 
		{
			_altTimeout = 0;
			Lspeed = _altHighSpeed;
			Rspeed = _altLowSpeed;
			if (_tracking<20) _tracking++;
		} 
		else if (!(status & 0x2)) //channel2 off-line  
		{
			_altTimeout++;
			if(_tracking > AUTOLINETRACKING_MAX_TIMEOUT)
			{
				_altTimeout = AUTOLINETRACKING_MAX_TIMEOUT;
				return -1; //off track
			}
			if (_tracking < 10) /* left circle */
			{
				Lspeed = 0;
				Rspeed = _altLowSpeed;
			}
			else if (_tracking > 10) /* right circle */
			{
				Lspeed = _altLowSpeed;
				Rspeed = 0;
			}
			else 
			{
				if(_altTimeout > AUTOLINETRACKING_MAX_TIMEOUT/2)
				{
					Lspeed = -_altLowSpeed;
					Rspeed = -_altLowSpeed;
				}
			}
		}
	}

	_ddm->setAllSpeed(Lspeed, Rspeed);

	return 0;
}


int8_t WKKCarDriver::loopAutoObstacleAvoidance()
{
	int8_t ret = 0;
	LOGN("WKKCarDriver::loopAutoObstacleAvoidance()");
	
	if (_dis == 0) {
		_dis = readUltrasonic();
	}
	LOG("_dis = ");LOGN(_dis);
	if (_randVal == 255) {
		_randVal = mathRandomInt();  
	}

	if(_continueBackwardTimes > 0) //continue backward
	{
		LOGN("loopAutoObstacleAvoidance()------------0");
		delay(100);
		_continueBackwardTimes--;
		if(_continueBackwardTimes == 0)
		{
			_ddm->setAllSpeed(-_aoaRunSpeed/2,-_aoaRunSpeed/2); //slow speed change
			delay(20);
			_ddm->stopAllMotor();
			//delay(10);
		}
		ret = -1;
	}
	else if (_dis>0 && _dis<=80) {
		LOGN("loopAutoObstacleAvoidance()------------1");	
		_aoaTimeout++;
		if(_aoaTimeout > AUTOOBSTACLEAVOIDANCE_MAX_TIMEOUT)
		{
			_aoaTimeout = AUTOOBSTACLEAVOIDANCE_MAX_TIMEOUT;
			ret = -1;  //robot maybe in trouble
		}
		_ddm->setAllSpeed(-_aoaRunSpeed,-_aoaRunSpeed);
		delay(100);  //can not delay too long, because it will block other program
		_continueBackwardTimes = 4; //continue backward next time until enough space for car
		_dis = 0;
	}
	else if (_dis>80 && _dis<=320) {
		uint16_t var;
		int i;
		LOGN("loopAutoObstacleAvoidance()------------2");
		_aoaTimeout++;
		if(_aoaTimeout > AUTOOBSTACLEAVOIDANCE_MAX_TIMEOUT)
		{
			_aoaTimeout = AUTOOBSTACLEAVOIDANCE_MAX_TIMEOUT;
			ret = -1;  //robot maybe in trouble
		}
		switch(_randVal) {
			case 0: 
			_ddm->setAllSpeed(-_aoaRunSpeed, _aoaRunSpeed);
			break;
			case 1:
			_ddm->setAllSpeed(_aoaRunSpeed, -_aoaRunSpeed);
			break;
		}
		_dis = 0;
		for (i=0; i<3; i++) {
			delay(100);
			var = readUltrasonic();
			if (var <= 80 || var > 320) {
				_dis = var;
				_ddm->stopAllMotor();
				delay(10);
				break;
			}
		}
		//delay(200);
	}
	else if ((_dis == 0) || (_dis > 320)) {  //_dis=0 means no obstacle
		LOGN("loopAutoObstacleAvoidance()------------3");
		_aoaTimeout = 0;
		_ddm->setAllSpeed(_aoaRunSpeed, _aoaRunSpeed);
		_randVal = 255;
		_dis = 0;
		delay(50);
	}

	return ret;
}

/*map speed to min speed(25) when its value is not 0, 
*because the min-limit speed is 25 to make motor run.
* map 1-100 to 25-100
*/
uint8_t WKKCarDriver::mapSpeed(uint8_t speed) {
	//return (speed == 0) ? 0 : (25 + map(speed, 1, 100, 0, 75));
	return (speed == 0) ? 0 : (25 + map(speed, 1, 100, 0, 55)); //limit speed to 80 max
}

//speed value:[0, 100], degree value:[0,360)
void WKKCarDriver::calcDDMSpeed(uint8_t speed, uint16_t degree, int8_t *speed1, int8_t *speed2)
{
	float v1, v2;
	float vl, vr;
	float alpha;
	float sp = 0;
	float mp = 0;
	int dir = 0;

	/*make mspeed1 not opposite to mspeed2 in order to seeing turn obvious 
	*by mapping angle from 0-90 to 45-90.
	*/
	/*if(degree<=90)
		degree = map(degree, 0, 90, 45, 90);
	else if((degree>90) && (degree<=180))
		degree = map(degree, 90, 180, 90, 135);
	else if((degree>180) && (degree<=270))
		degree = map(degree, 180, 270, 225, 270);
	else if((degree>270) && (degree<360))
		degree = map(degree, 270, 360, 270, 315);
	else
		degree = 0;*/

	if(degree>180) 
	{
		alpha = degree - 180;
		dir = 1; //back
	}
	else 
	{
		alpha = degree;
		dir = 0; //forward
	}

	//map mspeed1 or mspeed2 to max speed(100) becasue it is max-limit speed 
	mp = max(abs(cos(PI*alpha/180))+ abs(sin(PI*alpha/180)), 1.0);
	sp = speed/(mp);

	v2 = (sp*(sin(PI*alpha/180)+cos(PI*alpha/180)));
	v1 = (sp*(sin(PI*alpha/180)-cos(PI*alpha/180)));

	if(dir == 0)
	{
		vr = v1;
		vl = v2;    
	}
	else // if(dir == 1)
	{
		vr = -v2;
		vl = -v1;
	}

	if(abs(vr) < 1)
		vr = 0;

	if(abs(vl) < 1)
		vl = 0;

	*speed1 = (int8_t)vl;
	*speed2 = (int8_t)vr;
}

uint8_t WKKCarDriver::mathRandomInt()
{
	return (rand() % 2);
}

uint16_t WKKCarDriver::readUltrasonic()
{
#if 0
	uint16_t Var;
	while (1) {
		Var = _uls->getDistance();
		if (Var >= 5000) {
			//	_ddm->stopAllMotor();
		}
		else {
			break;
		}
	}
	return Var;
#else
	return _uls->getDistance();
#endif
}
