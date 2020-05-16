/* WKKCarDriverSample.ino
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
 *     This file is a sample code for wukong-kit Car Driver Server.
 *
 * Version: 1.0.0
 */


#include <WKKSystem.h>
#include <XDualDCMotor.h>
#include <XIRTracking.h>
#include <XUltrasonic.h>
#include <WKKCarDriver.h>


XDualDCMotor ddm;
XIRTracking irt;
XUltrasonic uls;
WKKCarDriver cdr;


void setup()
{
	XSystem.setup();
	ddm.setup("DDM");
	irt.setup("IRT3220", "1");
	uls.setup("ULS3200", "4");
	cdr.setup(&ddm);
}

void loop()
{
	cdr.forward(20);
	delay(2000);
	cdr.backward(20);
	delay(2000);
	cdr.stop();
	
	while (true) {
		cdr.autoLineTracking(&irt);
	}
}






