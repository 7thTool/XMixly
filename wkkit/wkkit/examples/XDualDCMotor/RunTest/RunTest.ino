
#include <Wire.h>
#include <math.h> 
#include <HQRSystem.h>
#include <XDualDCMotor.h>
#include <XUltrasonic.h>
#include <XButton.h> 
#include <XBuzzer.h>
#include <Adafruit_TCS34725.h>


#define LEFT	1
#define FRONT	2
#define RIGHT	3


#define address 0x1E //0011110b, I2C 7bit address of HMC5883


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
XDualDCMotor ddc;
XUltrasonic uls;
XButton btn;
XBuzzer buz;


int speed;
unsigned long time;
uint8_t status1;
uint8_t status2;
uint8_t status3;
uint8_t status4;

long dis0;
long dis_cur;
long dis_pos;

int8_t speed_R = 40;
int8_t speed_L = 39;


void tcsInit()
{
	if (tcs.begin()) {
		Serial.println("Found sensor");
	} else {
		Serial.println("No TCS34725 found ... check your connections");
		while (1);
	}
}

void hmcInit()
{
	//Wire.begin();

	//Put the HMC5883 IC into the correct operating mode
	Wire.beginTransmission(address); //open communication with HMC5883
	Wire.write(0x02); //select mode register
	Wire.write(0x00); //continuous measurement mode
	Wire.endTransmission();
}

double getAngle()
{ 
	int x,y,z; //triple axis data
	double angle;
	//Tell the HMC5883 where to begin reading data
	Wire.beginTransmission(address);
	Wire.write(0x03); //select register 3, X MSB register
	Wire.endTransmission();

	//Read data from each axis, 2 registers per axis
	Wire.requestFrom(address, 6);
	if(6<=Wire.available()){
		x = Wire.read()<<8; //X msb
		x |= Wire.read(); //X lsb
		z = Wire.read()<<8; //Z msb
		z |= Wire.read(); //Z lsb
		y = Wire.read()<<8; //Y msb
		y |= Wire.read(); //Y lsb
	}
	angle= atan2((double)y,(double)x) * (180 / 3.14159265) + 180; // angle in degrees

#if 1
	//Print out values of each axis
	Serial.print("x: ");
	Serial.print(x);
	Serial.print("  y: ");
	Serial.print(y);
	Serial.print("  z: ");
	Serial.println(z);
	Serial.print("  angle: ");
	Serial.println(angle);
#endif

	return angle;
}

double getRBRate()
{
	uint16_t r, g, b, c, colorTemp, lux;
	double rate = 1.0;

	tcs.getRawData(&r, &g, &b, &c);
	//colorTemp = tcs.calculateColorTemperature(r, g, b);
	//lux = tcs.calculateLux(r, g, b);

	rate = (r*1.0)/b;

#if 1
	Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
	Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
	Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
	Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
	Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
	Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
	Serial.print("rate: "); Serial.print(rate); Serial.print(" ");
	Serial.println(" ");
#endif

	return rate;
}

void iraInit()
{
	pinMode(11, INPUT);
	pinMode(12, INPUT);
	pinMode(PIN_A2, INPUT);
	pinMode(5, INPUT);
}

uint8_t getIRA1Status()
{
	return digitalRead(11) ? 0 : 1;
}

uint8_t getIRA2Status()
{
	return digitalRead(12) ? 0 : 1;
}

uint8_t getIRA3Status()
{
	return digitalRead(PIN_A2) ? 0 : 1;
}

uint8_t getIRA4Status()
{
	return digitalRead(5) ? 0 : 1;
}


void playSound()
{
	int duration = 400;
	float fac = 0.05;
	float fa1 = 1.0;

	buz.playTone(523*fa1, duration);
	delay(duration*fac);
	buz.playTone(523*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
	buz.playTone(880*fa1, duration);
	delay(duration*fac);
	buz.playTone(880*fa1, duration);
	delay(duration*fac);
	buz.playTone(784*fa1, duration);
	delay(duration*fac);
}


// 功能：等待按钮按下开始跑
void waitStart() {
	while(!btn.isPressed());
	//while(!btn.isKnocked());
	ddc.setAllSpeed(speed_L, speed_R);
}

// 功能：通过电位器获取运行速度
int getSpeed() {
	// TODO:
}

// 功能：检查是否到达终点
// 返回：true--是终点，false--不是终点
bool checkTerminal() {
	if(getRBRate() > 3.0)
	{
		return true;
	}
	
	return false;
}

// 功能：任务完成，小车停止
void finish() {
	ddc.stopAllMotor();
	time = millis() - time;
	// 可以通过数码管显示出来（秒为单位）
	// 播放段音乐也可以
	playSound();
}

// 功能：检查岔路口状态
// 参数: dir, LEFT/FRONT/RIGHT
// 返回：true--通路，false--不通
bool checkPass(int dir) {
	if (dir == LEFT){
		status3 = getIRA3Status();
		status4 = getIRA4Status();
		if((status3 == 0) && (status4 == 0))
		{
			return true;
		}
	} else if (dir == FRONT) {
		dis_cur = uls.getDistance();
		if(dis_cur > 50)
		{
			return true;
		}
	} else if (dir == RIGHT) {
		status1 = getIRA3Status();
		status2 = getIRA4Status();
		if((status1 == 0) && (status2 == 0))
		{
			return true;
		}
	} 
	
	return false;
}

// 功能：左转90度
void turnLeft() {
    ddc.stopAllMotor();
    ddc.setAllSpeed(-30, 30);
    delay(700);
    //delayMicroseconds(500000);
    ddc.stopAllMotor();
}

// 功能：右转90度
void turnRight() {
    ddc.stopAllMotor();
    ddc.setAllSpeed(30, -30);
    delay(680);
    //delayMicroseconds(500);
    ddc.stopAllMotor();
}

// 功能：保持直行
void keepForward() {
	dis_cur = uls.getDistance();
    if(dis_cur < 500)
    {
        return;
    }
    
    ddc.setAllSpeed(speed_L, speed_R);
    dis_pos = dis0 - 500;
    while(dis_cur>dis_pos)
    {
        dis_cur = uls.getDistance();
    }
 
    ddc.stopAllMotor();
}

// 功能：掉头，180度
void turnBack() {
    ddc.stopAllMotor();
    ddc.setAllSpeed(30, -30);
    delay(1320);
    //delayMicroseconds(500);
    ddc.stopAllMotor(); 
}



void setup() {
	// TODO:
	XSystem.setup();
	Serial.begin(9600);
	iraInit();
	tcsInit();
	hmcInit();
	
	btn.setup("BTN");
	ddc.setup("DDM");
	buz.setup("BUZ");
	uls.setup("ULS3600", "1");
	
	while(uls.getDistance() == 9999);
	while(getRBRate() > 3.0);
	
	//speed = getSpeed();
	//waitStart();
	//time = millis();
}

void loop() {
	getAngle();
	delay(1000);
}