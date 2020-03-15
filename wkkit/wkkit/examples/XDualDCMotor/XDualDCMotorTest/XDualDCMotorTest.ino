/* XDualDCMotorTest.ino
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
 *     This file is test code for DualDCMotor module.
 *
 * Version: 1.0.0
 */
 
#include <YGRSystem.h>
#include <XDualDCMotor.h>

#define CASE_TEST_SPEED		1
#define CASE_TEST_ANGLE		1

XDualDCMotor ddc;

int ret;

//speed value:[0, 100], angle value:[0,360)
void setAngle(float speed, float angle, float *mspeed1, float *mspeed2)
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
  if(angle>=0 && angle<=90)
    angle = map(angle, 0, 90, 45, 90);
  else if(angle>90 && angle<=180)
    angle = map(angle, 90, 180, 90, 135);
  else if(angle>180 && angle<=270)
    angle = map(angle, 180, 270, 225, 270);
  else if(angle>270 && angle<360)
    angle = map(angle, 270, 360, 270, 315);
  else
     angle = 0;
  
     
	if(angle>180) 
  {
    alpha = angle - 180;
    dir = 1; //back
  }
  else 
  {
    alpha = angle;
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

	/*map mspeed1 or mspeed2 to min speed(25) when its value is not 0, 
	 *because the min-limit speed is 25 to make motor run.
	 */
  if(abs(vr) < 1)
    vr = 0;
  else if(vr < 0)
    vr = -25 - map(abs(vr), 1, 100, 0, 75);
  else
    vr = 25 + map(abs(vr), 1, 100, 0, 75);

  if(abs(vl) < 1)
    vl = 0;
  else if(vl < 0)
    vl = -25 - map(abs(vl), 1, 100, 0, 75);
  else
    vl = 25 + map(abs(vl), 1, 100, 0, 75);
  
  *mspeed1 = vr;
  *mspeed2 = vl;
 
}


void setup() {
	// put your setup code here, to run once:
	XSystem.setup();
	
	Serial.begin(9600);

	ret = ddc.setup("DDM");
}

void loop() {
	float mspeed1, mspeed2;
#if (CASE_TEST_SPEED == 1)
	// put your main code here, to run repeatedly:
	ddc.setMotorSpeed(1, 100);
	delay(2000);
    ddc.setMotorSpeed(1, 30);
    delay(2000);
	ddc.setMotorSpeed(1, -100);
	delay(2000);
    ddc.setMotorSpeed(1, -30);
    delay(2000);
    ddc.stopAllMotor();
    ddc.setMotorSpeed(2, 100);
    delay(2000);
    ddc.setMotorSpeed(2, 30);
    delay(2000);
    ddc.setMotorSpeed(2, -100);
    delay(2000);
    ddc.setMotorSpeed(2, -30);
    delay(2000);
	ddc.stopAllMotor();
	delay(2000);
	ddc.setAllSpeed(-100, -100);
	delay(2000);
	ddc.stopMotor(2);
	delay(2000);
	ddc.stopMotor(1);
	delay(2000);
	ddc.setAllSpeed(100, 100);
	delay(2000);
	ddc.stopAllMotor();
	delay(2000);
#endif
#if (CASE_TEST_ANGLE == 1)
	setAngle(100, 45, &mspeed1, &mspeed2);
	Serial.print(mspeed1);Serial.print(",");Serial.println(mspeed2);
	delay(1000);
#endif
}