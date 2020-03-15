/* XBlock.cpp
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
 *     This file is a utility file for XBlock.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <XBlock.h>


uint8_t * fetchU8(const uint8_t *param, uint8_t *val)
{
	*val = *param;
	return (uint8_t *)param + 1;
}

uint8_t * fetchU16(const uint8_t *param, uint16_t *val)
{
	*val = (param[0] << 8) | param[1];
	return (uint8_t *)param + 2;
}

uint8_t * fetchU32(const uint8_t *param, uint32_t *val)
{
	*val = ((unsigned long)param[0] << 24) |
			((unsigned long)param[1] << 16) |
			((unsigned long)param[2] << 8) |
			(unsigned long)param[3];
	return (uint8_t *)param + 4;
}

uint8_t * fetchString(const uint8_t *param, char **s)
{
	*s = (char *)param;
	return (uint8_t *)param + strlen(*s) + 1;
}

uint8_t * fetchFloat(const uint8_t *param, float *val)
{
	long v = ((unsigned long)param[0] << 24) |
				((unsigned long)param[1] << 16) |
				((unsigned long)param[2] << 8) |
				(unsigned long)param[3];
	*val = v / 1000.0;
	return (uint8_t *)param + 4;
}

uint8_t * fillU8(uint8_t *result, uint8_t val)
{
	*result = val;
	return result + 1;
}

uint8_t * fillU16(uint8_t *result, uint16_t val)
{
	result[0] = (uint8_t)((val >> 8) & 0xff);
	result[1] = (uint8_t)(val & 0xff);
	return result + 2;
}

uint8_t * fillU32(uint8_t *result, uint32_t val)
{
	result[0] = (uint8_t)((val >> 24) & 0xff);
	result[1] = (uint8_t)((val >> 16) & 0xff);
	result[2] = (uint8_t)((val >> 8) & 0xff);
	result[3] = (uint8_t)(val & 0xff);
	return result + 4;
}

uint8_t * fillString(uint8_t *result, const char *s)
{
	strcpy((char *)result, s);
	return result + strlen(s) + 1;
}

uint8_t * fillFloat(uint8_t *result, float val)
{
	long v = val * 1000;
	result[0] = (v >> 24) & 0xff;
	result[1] = (v >> 16) & 0xff;
	result[2] = (v >> 8) & 0xff;
	result[3] = v & 0xff;
	return result + 4;
}