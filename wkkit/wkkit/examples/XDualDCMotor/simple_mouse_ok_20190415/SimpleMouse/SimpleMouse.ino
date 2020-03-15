
#include <math.h> 
#include <WKKSystem.h>
#include <XDualDCMotor.h>
#include <XIRTracking.h>
#include <XUltrasonic.h>
#include <XIRAvoiding.h>
#include <XButton.h> 
#include <XBuzzer.h>
#include <XSegDisplay.h>

#define S1  (uint8_t)0x01
#define S2  (uint8_t)0x02
#define S3  (uint8_t)0x04
#define S4  (uint8_t)0x08
#define S5  (uint8_t)0x10
#define S6  (uint8_t)0x20


#define MATCH(status, s)  ((status & s) == s) ? true : false
#define ONLY(status, s)   ((status ^ s) == 0) ? true : false


#define LEFT    1
#define FRONT   2
#define RIGHT   3


XDualDCMotor ddm;
XIRTracking irt;
XUltrasonic uls;
XIRAvoiding iraLeft;
XIRAvoiding iraRight;
XButton btnRed;
XButton btnBlue;
XSegDisplay sgd;
XBuzzer buz;

//M1 connect Right Motor, M2 connect Left Motor
int8_t speed_R = 30;
int8_t speed_L = 30;
unsigned long t0, t1, dt;
uint8_t statusL = 1;
uint8_t statusR = 1;
long dis;
uint8_t dir = 0; //1表示向右偏，2表示向左偏


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
    while(!btnRed.isPressed());
}

// 功能：通过电位器获取运行速度
int getSpeed() {
    // TODO:
}


// 功能：检查是否到达终点
// 返回：true--是终点，false--不是终点
bool checkTerminal() {
    // TODO:
    return false;
}

// 功能：任务完成，小车停止
void finish() {
    ddm.stopAllMotor();
    // 可以通过数码管显示出来（秒为单位）
    // 播放段音乐也可以
    //playSound();
}

#define LINETRACKING_MAX_TIMEOUT         200
int8_t highSpeed = 40;
int8_t lowSpeed = 28;
uint8_t timeout = 0;
uint16_t tracking = 0;
// 功能：保持直行
uint8_t keepForward()
{
    int8_t Lspeed = 0; //Lspeed is m1 speed, Rspeed is m2 speed
    int8_t Rspeed = 0;
    uint8_t status = irt.getStatus();

    if((dir == 0) && MATCH(status, S6) && (!MATCH(status, S1)))
    {
        dir = 2;//向左偏了
    }
    else if((dir == 0) && MATCH(status, S1) && (!MATCH(status, S6)))
    {
        dir = 1;//向右偏了
    }
        
    if (status & 0x4) //channel3 on-line
    {
        timeout = 0;
        if (status & 0x8)/* forward */ //channel4 on-line 
        {
            Lspeed = highSpeed;
            Rspeed = highSpeed;
            tracking = 10;
        } 
        else if (!(status & 0x8)) /* adjust to left*/ //channel4 off-line 
        { 
            Lspeed = lowSpeed;
            Rspeed = highSpeed;
            if (tracking>1) tracking--;
        }
    } 
    else /*if (!(status & 0x4))*/ //channel3 off-line 
    {
        if (status & 0x8) /* adjust to right */ //channel4 on-line 
        {
            timeout = 0;
            Lspeed = highSpeed;
            Rspeed = lowSpeed;
            if (tracking<20) tracking++;
        } 
        else if (!(status & 0x8)) //channel4 off-line  
        {
            timeout++;
            if(tracking > LINETRACKING_MAX_TIMEOUT)
            {
                timeout = LINETRACKING_MAX_TIMEOUT;
                return -1; //off track
            }
            if (tracking < 10) /* left circle */
            {
                Lspeed = 0;
                Rspeed = lowSpeed;
            }
            else if (tracking > 10) /* right circle */
            {
                Lspeed = lowSpeed;
                Rspeed = 0;
            }
            else 
            {
                if(timeout > LINETRACKING_MAX_TIMEOUT/2)
                {
                    Lspeed = -lowSpeed;
                    Rspeed = -lowSpeed;
                }
            }
        }
    }

    ddm.setAllSpeed(Rspeed, Lspeed); //M1 connect Right Motor, M2 connect Left Motor

    return status;
}

#define ONE_STEP_ADJUST_TIME    (200)
//功能：走一格
void runOneStep()
{
    uint8_t status;
    while(1)
    {
        status = keepForward();
        if(MATCH(status, (S1|S6))) //sensor1 and sensor6 find line
        {
            break;
        }
        if (!checkPass(FRONT)) //前面没有路
        {
            break;
        }
    }
    t0 = millis(); 
    while(1)
    {
        keepForward();
        t1 = millis();
        dt = t1 - t0;
        if(dt > ONE_STEP_ADJUST_TIME)
        {
            break;
        }
        if (!checkPass(FRONT)) //前面没有路
        {
            break;
        }
    }
    
    ddm.stopAllMotor();
    delay(5);
    status = irt.getStatus();
    while((!MATCH(status, S3)) && (!MATCH(status, S4))) //不在线上，需要调整到线上
    {
        if(dir == 2)//向左偏了,需要向右转向
        {
            ddm.setAllSpeed(-30, 30);
        }
        else
        {
            ddm.setAllSpeed(30, -30);
        }
        status = irt.getStatus();
    }
    ddm.stopAllMotor();
    
    dir = 0;
}

void detectWallInfo()
{
}

void recordWallInfo()
{
}

// 功能：左转90度
void turnLeft() {
    uint8_t status;
    
    // 向左转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(30, -30);
    delay(400);
    
    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));

    // 继续向左旋转，直至S3/S4遇上黑线
    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

    // 继续向左转50ms左右以便矫正转正90度，但如果S4脱离黑线则必须停止向左转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 100)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S4));
    
    ddm.stopAllMotor();
}

// 功能：右转90度
void turnRight() {
    uint8_t status;
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(-30, 30);
    delay(400);

    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

    // 继续向右转50ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 100)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
    
    ddm.stopAllMotor();
}

// 功能：掉头，180度
void turnBack() { 
    uint8_t status;
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(-33, 27);
    delay(400);

    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

    // 继续向右转50ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 100)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
    
    ddm.stopAllMotor();
    
    status = irt.getStatus() & 0x3F;//移除高两位
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(-33, 27);
    delay(400);

    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        delay(10);
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));
    
    // 继续向右转50ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 100)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
    
    ddm.stopAllMotor();
}



#define DISTANCE_TH    (100)
// 功能：检查岔路口状态
// 参数: dir, LEFT/FRONT/RIGHT
// 返回：true--通路，false--不通
bool checkPass(int dir) {
    
    if (dir == LEFT){
        if(iraLeft.getStatus() == 0)
        {
            return true;
        }
    } else if (dir == FRONT) {
        if(uls.getDistance() > DISTANCE_TH)
        {
            return true;
        }
    } else if (dir == RIGHT) {
        if(iraRight.getStatus() == 0)
        {
            return true;
        }
    } 
    
    return false;
}


void setup() {
    // TODO:
    XSystem.setup();
    Serial.begin(9600);
    uls.setup("ULS3600", "1");
    ddm.setup("DDM3300", "8");
    irt.setup("IRT3360", "3");
    iraLeft.setup("IRA3300", "4");
    iraRight.setup("IRA3300", "5");
    btnRed.setup("BTN3300", "2");
    btnBlue.setup("BTN3300", "7");
    sgd.setup("SGD4300", "6");
    //buz.setup("BUZ3300", "6");
    
    while(uls.getDistance() == 9999);
    waitStart();
}


void test_keepForward()
{
    while(1)
    {
        keepForward();
    }
}

void test_runOneStep()
{
    runOneStep();
    delay(5000);
}

void test_turnLeft()
{
    turnLeft();
    delay(5000);
}

void test_turnRight()
{
    turnRight();
    delay(5000);
}

void test_turnBack()
{
    turnBack();
    delay(5000);
}


void loop() {
#if 0
    //ddm.setAllSpeed(speed_R, speed_L);
    //Serial.print("status: ");Serial.println(irt.getStatus());
    //test_keepForward();
    //sgd.showNumber(uls.getDistance());
    //sgd.showNumber(iraRight.getStatus());
    //sgd.showNumber(iraLeft.getStatus());
    //test_runOneStep();
    //test_turnBack();
    test_turnLeft();
    //test_turnRight();
    //delay(1000);
#endif

#if 1
    if (checkTerminal()) {
        finish();
        while(true);
    }
    
    if (checkPass(LEFT)) {
        turnLeft();
    } else if (checkPass(FRONT)) {
    } else if (checkPass(RIGHT)) {
        turnRight();
    } else {
        turnBack();
    }

    runOneStep();
#endif
}
