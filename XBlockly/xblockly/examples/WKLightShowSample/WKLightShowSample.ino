/* WKLightShowSample.ino
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
 *     This file is a sample code for wukong Light Show Server.
 *
 * Version: 1.0.0
 */


#include <XSystem.h>
#include <XRGBLed.h>
#include <WKLightShow.h>


XRGBLed rgb;
WKLightShow lgs;


void setup()
{
	XSystem.setup();
	rgb.setup("RGB3280", "5");
	lgs.setup(&rgb);

}

void loop()
{	
	while (true) {
		lgs.showMeteor(0, 100, 0, 0);
	}
}