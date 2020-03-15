/* XI2CTest.ino
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
 *     This file is a test code for X-I2C protocol.
 *
 * Version: 1.0.0
 */


#include <HQRSystem.h>
#include <XI2C.h>

#define CASE_TEST_WRITE		1
#define CASE_TEST_READ1		1	//bid code
#define CASE_TEST_READ2		1	//bid check code

#define I2C_DEV_ADDRESS 0x3a 	//HQRover/YGRover STC I2C address 

uint8_t buf[16];
uint8_t dst[16];


void setup() {
  // put your setup code here, to run once:
  XSystem.setup();
  Serial.begin(9600);
}

void loop() {

#if (CASE_TEST_WRITE == 1)
    uint8_t buf[2];
    int8_t ret = 0;
    
    buf[0] = 0x70;
    buf[1] = 0x3b;

    ret = XI2C.write(8, I2C_DEV_ADDRESS, 0x00, buf, 2);
    if(ret == -2) 
        XI2C.reset(10, 8);
	
	XI2C.read(8, I2C_DEV_ADDRESS, 0x08, dst, 1);

	Serial.print("dst[0]=");Serial.println(dst[0], HEX);
#endif

#if (CASE_TEST_READ1 == 1)
	XI2C.read(8, I2C_DEV_ADDRESS, 0x06, dst, 5);

	Serial.print("dst[0]=");Serial.println(dst[0], HEX);
	Serial.print("dst[1]=");Serial.println(dst[1], HEX);
    Serial.print("dst[2]=");Serial.println(dst[2], HEX);
    Serial.print("dst[3]=");Serial.println(dst[3], HEX);
	Serial.print("dst[4]=");Serial.println(dst[4], HEX);
#endif

#if (CASE_TEST_READ2 == 1)
    XI2C.read(8, I2C_DEV_ADDRESS, 0x0b, dst, 7);
    Serial.print("dst[0]=");Serial.println(dst[0], HEX);
    Serial.print("dst[1]=");Serial.println(dst[1], HEX);
#endif

    while(1);

}

