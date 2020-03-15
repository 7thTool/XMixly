

#include <math.h> 
#include <HQRSystem.h>
#include <XDualDCMotor.h>
#include <XIRTracking.h>
#include <XUltrasonic.h>
#include <XIRAvoiding.h>
#include <XButton.h> 
#include <XBuzzer.h>
#include <XRGBLed.h>
#include <XSoundSensor.h>
#include <HQRAudioPlayer.h>
#include <HQRLightShow.h>



#define S1  (uint8_t)0x01
#define S2  (uint8_t)0x02
#define S3  (uint8_t)0x04
#define S4  (uint8_t)0x08
#define S5  (uint8_t)0x10
#define S6  (uint8_t)0x20


#define MATCH(status, s)  ((status & s) == s) ? true : false
#define ONLY(status, s)   ((status ^ s) == 0) ? true : false

#define UP_NOPASS_DISTANCE_TH    (100)


XDualDCMotor ddm;
XIRTracking irt;
XUltrasonic uls;
XIRAvoiding iraLeft;
XIRAvoiding iraRight;
XButton btn;
XSoundSensor snd;
XBuzzer buz;
HQRAudioPlayer hqrAudioPlayer;
XRGBLed rgb;
HQRLightShow lgs;

//M1 connect Right Motor, M2 connect Left Motor
unsigned long t0, t1, dt;
long dis;
uint8_t dir = 0; //1表示向右偏，2表示向左偏

#define PRO_FIND_PATH	1
#define PRO_RUN_FAST	2
uint8_t pro = PRO_FIND_PATH;

// 预先标定的目标位置坐标
const uint8_t target[4][2] = {{0,0}, {7,0}, {7,7}, {0,7}};
uint8_t flag; // 记录当前的位置索引


// 功能：等待按钮按下开始跑
void waitStart() {
    while(!btn.isPressed());
	t0 = millis(); 
    while(btn.isPressed())
    {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 1500)
        {
            pro = PRO_RUN_FAST;
		}
    }
}


#define LINETRACKING_MAX_TIMEOUT         200
int8_t highSpeed = 50;
int8_t lowSpeed = 35;
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
            if(timeout > LINETRACKING_MAX_TIMEOUT)
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
                    //Lspeed = -lowSpeed;
                    //Rspeed = -lowSpeed;
                }
            }
        }
    }

    ddm.setAllSpeed(Lspeed, Rspeed); //M1 connect Right Motor, M2 connect Left Motor

    return status;
}

#define ONE_STEP_ADJUST_TIME    (240)
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
		
        if (uls.getDistance() < UP_NOPASS_DISTANCE_TH) //前面没有路
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
        if (uls.getDistance() < UP_NOPASS_DISTANCE_TH) //前面没有路
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
            ddm.setAllSpeed(30, -30);
        }
        else
        {
            ddm.setAllSpeed(-30, 30);
        }
        status = irt.getStatus();
    }
    ddm.stopAllMotor();
    
    dir = 0;
    delay(25);
}


// 功能：左转90度
void turnLeft() {
    uint8_t status;
    
    // 向左转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(-30, 30);
    delay(400);
    
    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));

    // 继续向左旋转，直至S3/S4遇上黑线
    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

#if 0
    // 继续向左转75ms左右以便矫正转正90度，但如果S4脱离黑线则必须停止向左转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 30)  //取值大小对转弯效果影响很大
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S4));
#endif

    ddm.stopAllMotor();
    delay(25);
}

// 功能：右转90度
void turnRight() {
    uint8_t status;
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(30, -30);
    delay(400);

    do {
        status = irt.getStatus() & 0x3F;//移除高两位..
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

#if 0
    // 继续向右转75ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 30)  //取值大小对转弯效果影响很大
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
#endif
    
    ddm.stopAllMotor();
    delay(25);
}

// 功能：掉头，180度
void turnBack() { 
    uint8_t status;
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(27, -33);
    delay(400);

    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));

#if 0
    // 继续向右转75ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 30)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
#endif
    
    ddm.stopAllMotor();
    
    status = irt.getStatus() & 0x3F;//移除高两位
    
    // 向右转一点距离，约45度，让S3/S4离开黑线
    // FIXME: 可以有更好的算法
    ddm.setAllSpeed(27, -33);
    delay(400);

    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while ((!MATCH(status, S3)) && (!MATCH(status, S4)));
    
    // 继续向右旋转，直至S3/S4遇上黑线
    do {
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (!MATCH(status, (S3|S4)));
    
#if 0
    // 继续向右转75ms左右以便矫正转正90度，但如果S3脱离黑线则必须停止向右转
    t0 = millis(); 
    do {
        t1 = millis();
        dt = t1 - t0;
        if(dt > 30)
        {
            break;
        }
        status = irt.getStatus() & 0x3F;//移除高两位
    } while (MATCH(status, S3));
#endif
    
    ddm.stopAllMotor();
    delay(25);
}




// pathStat value
// 每格出口的状态值
#define PASS        0x0 // 00
#define NOPASS      0x1 // 01
#define DEAD        0x2 // 10
#define UNKNOWN     0x3 // 11

//direction value
// 出口方向使用一个字节(8比特)表示，上下左右共4个出口方向，分别占用2个比特
#define UP          0
#define DOWN        2
#define LEFT        4
#define RIGHT       6

// 实际迷宫格子数量
#define HSIZE       5
#define VSIZE       5


// 使用二维数组，记录XY轴格子的出口状态
uint8_t pos[16][16] = {0}; // 支持最多16*16的格子数量

uint8_t cur_x, cur_y; // 记录当前的格子坐标位置
uint8_t car_dir; // 记录当前小车的朝向，以格子坐标为基准

// 记录行走的格子轨迹栈，用于回溯。最大16*16的迷宫尺寸，最多256个轨迹数
uint8_t pos_stack[256] = {0};
uint8_t pos_stack_pointer = 0; // 轨迹栈指针，“空加”

// 格子出口状态设置和获取
#define PATH_SET(path, pathStat)  pos[cur_x][cur_y] &= ~(3 << path); pos[cur_x][cur_y] |= (pathStat << path)
#define PATH_GET(path)          ((pos[cur_x][cur_y] >> path) & 0x03)




// 格子轨迹压栈和出栈
#define POS_STACK_PUSH()	pos_stack[pos_stack_pointer] = (cur_x << 4) | cur_y; pos_stack_pointer++
#define POS_STACK_POP()		pos_stack[--pos_stack_pointer]

/**
检查接下来要进入的格子是否回绕
参数：path, 将从当前格子的该出口进入新格子
返回：有回绕返回true, 否则返回false
**/
bool checkIfRetrace(int path)
{
    int i;
    uint8_t x, y; // 轨迹栈里的格子坐标
    uint8_t x1, y1;	// 将要新进入的格子坐标

    x1 = cur_x;
    y1 = cur_y;
    if (path == UP) {
        y1 = cur_y + 1;
    } else if (path == DOWN) {
        y1 = cur_y - 1;
    } else if (path == LEFT) {
        x1 = cur_x - 1;
    } else {
        x1 = cur_x + 1;
    }

    // 遍历轨迹栈查询
    for (i=0; i<pos_stack_pointer; i++) {
        x = (pos_stack[i] >> 4) & 0x0f;
        y = pos_stack[i] & 0x0f;
        if ((x == x1) && (y == y1)) {
            return true; // 有回绕返回true
        }
    }

    return false;
}

void clear()
{
	memset(pos, 0, sizeof(pos)/sizeof(pos[0][0]));
	memset(pos_stack, 0, sizeof(pos_stack)/sizeof(pos_stack[0]));
	pos_stack_pointer = 0;
}

/**
检查是否找到终点
**/
bool isEnd()
{
    // TODO:
    if ((cur_x == 4) && (cur_y == 4)) {
		POS_STACK_PUSH(); //将最后一格信息也压栈
        return true;
    } else {
        return false;
    }
}

bool isFoundTarget()
{
	uint8_t next;
	
	next = flag + 1;
	if (next > 3) {
		next = 0;
	}
	
    // TODO:
    if ((cur_x == target[next][0]) && (cur_y == target[next][1])) {
		POS_STACK_PUSH(); //将最后一格信息也压栈
        return true;
    } else {
        return false;
    }	
}

#define POS_STACK_BASE_ADDR (0x20)
/**
到达终点,结束
**/
void finish()
{
    int i;
    int addr = POS_STACK_BASE_ADDR;
    ddm.stopAllMotor();
    // 可以通过数码管显示出来（秒为单位）
    // 播放段音乐也可以
	hqrAudioPlayer.playMusic(MUSIC_HUANLESONG);
	switch (flag) {
	case 0:
		lgs.showMeteor(2,  0x200000, 5);
		break;
	case 1:
		lgs.showMeteor(2,  0x001000, 5);
		break;
	case 2:
		lgs.showMeteor(2,  0x000020, 5);
		break;
	case 3:
		lgs.showMeteor(2,  0x101010, 5);
		break;
	default:
		break;
	}	
	hqrAudioPlayer.stop();
    
}


#if 1
/**
查询格子的出口
参数：inpath, 进入该格子的出口
返回：出口方向，UP/DOWN/LEFT/RIGHT, -1表示无出口
**/
int pathQuery(int inpath)
{
    uint8_t pathStat;
    int d1, d2, d3, d4;
	
    switch (flag) {
    case 0:
        d1 = RIGHT;
        d2 = DOWN;
        d3 = UP;
        d4 = LEFT;
        break;
    case 1:
        d1 = UP;
        d2 = RIGHT;
        d3 = LEFT;
        d4 = DOWN;
        break;
    case 2:
        d1 = LEFT;
        d2 = UP;
        d3 = DOWN;
        d4 = RIGHT;
        break;
    case 3:
        d1 = LEFT;
        d2 = DOWN;
        d3 = RIGHT;
        d4 = UP;
        break;
    default:
        break;
    }

    if (inpath != d1) {
        pathStat = PATH_GET(d1);
        if (pathStat == PASS) {
            return d1;
        }
    }

    if (inpath != d2) {
        pathStat = PATH_GET(d2);
        if (pathStat == PASS) {
            return d2;
        }
    }

    if (inpath != d3) {
        pathStat = PATH_GET(d3);
        if (pathStat == PASS) {
            return d3;
        }
    }

    if (inpath != d4) {
        pathStat = PATH_GET(d4);
        if (pathStat == PASS) {
            return d4;
        }
    }

    return -1;
}
#else
//random rule
int pathQuery(int inpath)
{
    uint8_t pathStat;
	int outpath = random(4) * 2;
	
	if (outpath == inpath) {
		outpath = (outpath + 4) % 8;
	}

	for (int i=0; i<4; i++) {
		pathStat = PATH_GET(outpath);
		if (pathStat == PASS) {
			return outpath;
		}
		outpath = (outpath + 2) % 8;
		if (outpath == inpath) {
			outpath = (outpath + 2) % 8;
			i++;
		}
	}
	
	return -1;
}
#endif

/**
移动到下一格子
参数：outpath，从当前格子的出口移动到下一格子
返回：从新进入的格子角度，看到的入口方向
**/
int next(int outpath)
{
	int inpath;
	
    // 首先将当前格子压栈
    POS_STACK_PUSH();

	// 移动到新格子
    if (outpath == UP) {
        if (car_dir == DOWN) {
            turnBack();
        } else if (car_dir == LEFT) {
            turnRight();
        } else if (car_dir == RIGHT) {
            turnLeft();
        }
        runOneStep();
        cur_y++;
        inpath = DOWN;
        car_dir = UP;
    }
    else if (outpath == DOWN) {
        if (car_dir == UP) {
            turnBack();
        } else if (car_dir == LEFT) {
            turnLeft();
        } else if (car_dir == RIGHT) {
            turnRight();
        }
        runOneStep();
        cur_y--;
        inpath = UP;
        car_dir = DOWN;
    }
    else if (outpath == LEFT) {
        if (car_dir == UP) {
            turnLeft();
        } else if (car_dir == DOWN) {
            turnRight();
        } else if (car_dir == RIGHT) {
            turnBack();
        }
        runOneStep();
        cur_x--;
        inpath = RIGHT;
        car_dir = LEFT;
    }
    else if (outpath == RIGHT) {
        if (car_dir == UP) {
            turnRight();
        } else if (car_dir == DOWN) {
            turnLeft();
        } else if (car_dir == LEFT) {
            turnBack();
        }
        runOneStep();
        cur_x++;
        inpath = LEFT;
        car_dir = RIGHT;
    }


    return inpath;
}

/**
回退到前一格子
返回：站在回退目标格子的角度看的入口方向
**/
int back()
{
    int inpath;
    uint8_t l, pre_x, pre_y;

    if (pos_stack_pointer == 0) {
        return -1;
    }

    l = POS_STACK_POP();
    pre_x = (l >> 4) & 0x0f;
    pre_y = l & 0x0f;

    if (pre_x == cur_x) { // Y轴回退
        if (pre_y > cur_y) {
            if (car_dir == DOWN) {
                turnBack();
            } else if (car_dir == LEFT) {
                turnRight();
            } else if (car_dir == RIGHT) {
                turnLeft();
            }
            runOneStep();
            cur_y++;
            inpath = DOWN;
            car_dir = UP;
        } else {
            if (car_dir == UP) {
                turnBack();
            } else if (car_dir == LEFT) {
                turnLeft();
            } else if (car_dir == RIGHT) {
                turnRight();
            }
            runOneStep();
            cur_y--;
            inpath = UP;
            car_dir = DOWN;
        }
    }
    else { // X轴回退
        if (pre_x > cur_x) {
            if (car_dir == UP) {
                turnRight();
            } else if (car_dir == DOWN) {
                turnLeft();
            } else if (car_dir == LEFT) {
                turnBack();
            }
            runOneStep();
            cur_x++;
            inpath = LEFT;
            car_dir = RIGHT;
        } else {
            if (car_dir == UP) {
                turnLeft();
            } else if (car_dir == DOWN) {
                turnRight();
            } else if (car_dir == RIGHT) {
                turnBack();
            }
            runOneStep();
            cur_x--;
            inpath = RIGHT;
            car_dir = LEFT;
        }
    }
	
 
    return inpath;
}

void posUpdate(int inpath)
{
    uint8_t front, left, right;
    
	front = (uls.getDistance() <= UP_NOPASS_DISTANCE_TH) ? NOPASS : PASS;
	left = iraLeft.getStatus() ? NOPASS : PASS;
	right = iraRight.getStatus() ? NOPASS : PASS;
	
	switch (inpath) {
	case DOWN:
		if (PATH_GET(UP) != DEAD) {
			PATH_SET(UP, front);
		}
		if (PATH_GET(DOWN) != DEAD) {
			PATH_SET(DOWN, PASS);
		}
		if (PATH_GET(LEFT) != DEAD) {
			PATH_SET(LEFT, left);
		}
		if (PATH_GET(RIGHT) != DEAD) {
			PATH_SET(RIGHT, right);
		}
		break;
	case UP:
		if (PATH_GET(UP) != DEAD) {
			PATH_SET(UP, PASS);
		}
		if (PATH_GET(DOWN) != DEAD) {
			PATH_SET(DOWN, front);
		}
		if (PATH_GET(LEFT) != DEAD) {
			PATH_SET(LEFT, right);
		}
		if (PATH_GET(RIGHT) != DEAD) {
			PATH_SET(RIGHT, left);
		}
		break;
	case LEFT:
		if (PATH_GET(UP) != DEAD) {
			PATH_SET(UP, left);
		}
		if (PATH_GET(DOWN) != DEAD) {
			PATH_SET(DOWN, right);
		}
		if (PATH_GET(LEFT) != DEAD) {
			PATH_SET(LEFT, PASS);
		}
		if (PATH_GET(RIGHT) != DEAD) {
			PATH_SET(RIGHT, front);
		}
		break;
	case RIGHT:
		if (PATH_GET(UP) != DEAD) {
			PATH_SET(UP, right);
		}
		if (PATH_GET(DOWN) != DEAD) {
			PATH_SET(DOWN, left);
		}
		if (PATH_GET(LEFT) != DEAD) {
			PATH_SET(LEFT, front);
		}
		if (PATH_GET(RIGHT) != DEAD) {
			PATH_SET(RIGHT, PASS);
		}
		break;
	default:
		break;
	}	
}

void setup() {
    XSystem.setup();
    Serial.begin(9600);
    ddm.setup("DDM");
    uls.setup("ULS3600", "2");
    irt.setup("IRT3360", "3");
    iraLeft.setup("IRA3300", "4");
    iraRight.setup("IRA3300", "1");
    btn.setup("BTN");
	snd.setup("SND");
    buz.setup("BUZ");
	rgb.setup("RGB");
	lgs.setup(&rgb);
	hqrAudioPlayer.setup(&buz);
    
    while(uls.getDistance() == 9999);
    waitStart();
	
	randomSeed(snd.getVolume());

}

void loop() {

	int inpath, outpath;

	// 固定从坐标（0，0）位置（固定为左下角位置）放小车，车头方向朝上
	cur_x = cur_y = 0;
	car_dir = UP;
	inpath = DOWN;
	posUpdate(inpath);
	PATH_SET(inpath, DEAD); // 标记为死路
	
	flag = 0;
	lgs.showColor(0,  0x101010);

	while (true) {			
		while (!isFoundTarget()) {
			outpath = pathQuery(inpath); // 从当前格子找到下一出口
			//while(!btnBlue.isKnocked());
			//delay(2000);
			if (outpath != -1) { // 移动到下一格子
				if (checkIfRetrace(outpath)) {
					PATH_SET(outpath, DEAD); // FIXME: 标记为死路
				} else {
					inpath = next(outpath);
					posUpdate(inpath);
				}
			} else { // 回溯到前一个格子
				inpath = back();
				if (inpath == -1) {
					break;
				} else {
					PATH_SET(inpath, DEAD); // 标记为死路
				}
			}
		}
		
		finish();
		clear();
		flag++;
		if (flag > 3) {
			flag = 0;
		}
		
		if(flag < 2) {
			posUpdate(inpath);
			inpath = DOWN;
			PATH_SET(inpath, DEAD); // 标记为死路
		} else {
			posUpdate(inpath);
			inpath = UP;
			PATH_SET(inpath, DEAD); // 标记为死路
		}
		
		switch (flag) {
		case 0:
			lgs.showColor(0,  0x101010);
			break;
		case 1:
			lgs.showColor(0,  0x200000);
			break;
		case 2:
			lgs.showColor(0,  0x001000);
			break;
		case 3:
			lgs.showColor(0,  0x000020);
			break;
		default:
			break;
		}	
	}

}