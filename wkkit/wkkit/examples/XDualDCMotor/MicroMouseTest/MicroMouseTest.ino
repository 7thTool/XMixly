/**
 * Copyright(C), 2016-2038, https://www.mylecon.com
 * FileName: code.ino
 * Author: XBlockly
 * LastModified_at: 2019/3/2 下午5:27:17
 */


#include <WKKSystem.h>
#include <XUltrasonic.h>
#include <XIRAvoiding.h>


#define DEBUG


XUltrasonic uls;
XIRAvoiding ira_left;
XIRAvoiding ira_right;

#define UP_NOPASS_DISTANCE_TH    (100)


// 每格出口的状态值
#define PASS        0x0 // 00
#define NOPASS      0x1 // 01
#define DEAD        0x2 // 10
#define UNKNOWN     0x3 // 11

// 出口方向使用一个字节(8比特)表示，上下左右共4个出口方向，分别占用2个比特
#define UP          0
#define DOWN        2
#define LEFT        4
#define RIGHT       6

// 实际迷宫格子数量
#define HSIZE       8
#define VSIZE       8


// 使用二维数组，记录XY轴格子的出口状态
uint8_t pos[16][16] = {0}; // 支持最多16*16的格子数量

uint8_t cur_x, cur_y; // 记录当前的格子坐标位置
uint8_t car_dir; // 记录当前小车的朝向，以格子坐标为基准

// 记录行走的格子轨迹栈，用于回溯。最大16*16的迷宫尺寸，最多256个轨迹数
uint8_t pos_stack[256] = {0};
uint8_t pos_stack_pointer = 0; // 轨迹栈指针，“空加”

// 格子出口状态设置和获取
#define PATH_SET(path, status)  pos[cur_x][cur_y] &= ~(3 << path); pos[cur_x][cur_y] |= (status << path)
#define PATH_GET(path)          ((pos[cur_x][cur_y] >> path) & 0x03)

/*
迷宫地图设置，用于测试算法。
以XY参考坐标，特别注意二维数组posTable的表示：X轴是纵向的，Y轴是横向的。这和实际迷宫图示是相反的
U--表示【上】有挡板
D--表示【下】有挡板
L--表示【左】有挡板
R--表示【右】有挡板
*/
#define U   0x01    // 0000 0001
#define D   0x04    // 0000 0100
#define L   0x10    // 0001 0000
#define R   0x40    // 0100 0000

const uint8_t posTable[16][16] = {
        /*00-------------------[Y]-----------------15*/
/*[X]00*/  D|L|R, L|R, U|L, D|L, U|L, D|L, U|L|R, U|D|L, L, L, L, L, L, L, L, L|U,
/*[X]01*/  D|L, L, U, U|D, D, U, D|L, U, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]02*/  U|D, U|D, D|R, U|R, U|D, D, U, U|D, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]03*/  U|D|R, D|R, L, L|R, U|R, U|D|R, U|D, U|D|R, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]04*/  D|L, L|R, R, L|R, U|L, D|L, 0, U|L, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]05*/  U|D, U|D|L, D|L, U|L, D, U, U|D, U|D, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]06*/  U|D, D|R, U, U|D, U|D, D|R, U, U|D|R, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]07*/  U|D|R, D|L|R, U|R, D|R, U|R, D|L|R, R, U|L|R, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]08*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]09*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]10*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]11*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]12*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]13*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]14*/  D, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, U,
/*[X]15*/  D|R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, U|R
};

// 前进一格
void forward()
{
#ifdef DEBUG
    Serial.println("forward");
#endif
}

// 掉头
void turnBack()
{
#ifdef DEBUG
    Serial.println("turnBack");
#endif
}

// 左转
void turnLeft()
{
#ifdef DEBUG
    Serial.println("turnLeft");
#endif
}

// 右转
void turnRight()
{
#ifdef DEBUG
    Serial.println("turnRight");
#endif
}


// 格子轨迹压栈和出栈
#define POS_STACK_PUSH()	pos_stack[pos_stack_pointer] = (cur_x << 4) | cur_y; pos_stack_pointer++
#define POS_STACK_POP()		pos_stack[--pos_stack_pointer]

void debugTrace()
{
    int i;
    uint8_t x, y; // 轨迹栈里的格子坐标

    Serial.print("Trace: [");
    for (i=0; i<pos_stack_pointer; i++) {
        x = (pos_stack[i] >> 4) & 0x0f;
        y = pos_stack[i] & 0x0f;
        Serial.print("(");Serial.print(x);Serial.print(",");Serial.print(y);Serial.print(")");
        Serial.print(" ");
    }
    Serial.println("]");
}

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
#ifdef DEBUG
            Serial.println("**retraced**");
#endif
            return true; // 有回绕返回true
        }
    }

    return false;
}

/**
检查是否找到终点
**/
bool isEnd()
{
	// TODO:
    if ((cur_x == 0) && (cur_y == 0)) {
        return true;
    } else {
        return false;
    }
}

/**
到达终点,结束
**/
void finish()
{
#ifdef DEBUG
    int i;
    uint8_t x, y;

	// TODO:
    Serial.println("finish");

    Serial.print("Trace: [");
    for (i=0; i<pos_stack_pointer; i++) {
        x = (pos_stack[i] >> 4) & 0x0f;
        y = pos_stack[i] & 0x0f;
        Serial.print("(");Serial.print(x);Serial.print(",");Serial.print(y);Serial.print(")");
        Serial.print(" ");
    }
    Serial.println("]");
#endif
}

/**
查询格子的出口
参数：enterPath, 进入该格子的入口
返回：出口方向，UP/DOWN/LEFT/RIGHT, -1表示无出口
**/
int pathQuery(int enterPath)
{
    uint8_t status;

#ifdef DEBUG
    Serial.print("(");Serial.print(cur_x);Serial.print(",");Serial.print(cur_y);Serial.print(")");
    Serial.print("  RLDU:[");
    Serial.print(PATH_GET(RIGHT));
    Serial.print(PATH_GET(LEFT));
    Serial.print(PATH_GET(DOWN));
    Serial.print(PATH_GET(UP));
    Serial.println("]");

    Serial.print("I: ");
    if (enterPath == UP) {
        Serial.print("U    ");
    } else if (enterPath == DOWN) {
        Serial.print("D    ");
    } else if (enterPath == LEFT) {
        Serial.print("L    ");
    } else {
        Serial.print("R    ");
    }
#endif

    if (enterPath != UP) {
        status = PATH_GET(UP);
        if (status == PASS) {
#ifdef DEBUG
            Serial.print("O: "); Serial.println("U");
#endif
            return UP;
        }
    }

    if (enterPath != DOWN) {
        status = PATH_GET(DOWN);
        if (status == PASS) {
#ifdef DEBUG
            Serial.print("O: "); Serial.println("D");
#endif
            return DOWN;
        }
    }

    if (enterPath != LEFT) {
        status = PATH_GET(LEFT);
        if (status == PASS) {
#ifdef DEBUG
            Serial.print("O: "); Serial.println("L");
#endif
            return LEFT;
        }
    }

    if (enterPath != RIGHT) {
        status = PATH_GET(RIGHT);
        if (status == PASS) {
#ifdef DEBUG
            Serial.print("O: "); Serial.println("R");
#endif
            return RIGHT;
        }
    }

#ifdef DEBUG
    Serial.print("O: "); Serial.println("X");
#endif
    return -1;
}

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
        forward();
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
        forward();
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
        forward();
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
        forward();
        cur_x++;
        inpath = LEFT;
        car_dir = RIGHT;
    }

#ifdef DEBUG	
	Serial.print("N==>  ");
    Serial.print("(");Serial.print(cur_x);Serial.print(",");Serial.print(cur_y);Serial.print(")");
    Serial.println("");
#endif

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
#ifdef DEBUG
    Serial.println("No way to escape!");
#endif
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
            forward();
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
            forward();
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
            forward();
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
            forward();
            cur_x--;
            inpath = RIGHT;
            car_dir = LEFT;
        }
    }
	
#ifdef DEBUG
	Serial.print("B==>  ");
    Serial.print("(");Serial.print(cur_x);Serial.print(",");Serial.print(cur_y);Serial.print(")");
    Serial.println("");
#endif
    return inpath;
}

void posUpdate(int inpath)
{
#if 0
    uint8_t front, left, right;
    
	front = (uls.getDistance() <= UP_NOPASS_DISTANCE_TH) ? NOPASS : PASS;
	left = ira_left.getStatus() ? NOPASS : PASS;
	right = ira_right.getStatus() ? NOPASS : PASS;
	
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
#else
	// 调试，从posTable读取
    pos[cur_x][cur_y] |= posTable[cur_x][cur_y];
#endif
}

void setup() {
    XSystem.setup();
    uls.setup("ULS3600", "1");
    ira_left.setup("IRA3300", "4");
    ira_right.setup("IRA3300", "5");

#ifdef DEBUG
	Serial.begin(9600);
    Serial.println("start");
#endif
}

void loop() {
    int inpath, outpath;
#if 0
	// 固定从坐标（0，0）位置放小车，方向朝上
    cur_x = 0;
	cur_y = 0;
    car_dir = UP;
    inpath = DOWN;
#elif 0
    // 固定从坐标（7，0）位置放小车，方向朝右
    cur_x = 7;
    cur_y = 0;
    car_dir = RIGHT;
    inpath = DOWN;
#elif 0        
    // 固定从坐标（7，7）位置放小车，方向朝上
    cur_x = 7;
    cur_y = 7;
    car_dir = UP;
    inpath = UP;
#else	
    // 固定从坐标（0，7）位置放小车，方向朝左
    cur_x = 0;
    cur_y = 7;
    car_dir = LEFT;
    inpath = UP;
#endif

    PATH_SET(inpath, DEAD); // 标记为死路
    posUpdate(inpath);

	// 循环，直至找到终点
    while (!isEnd()) {
#ifdef DEBUG
        Serial.println("");
#endif
        debugTrace();
        outpath = pathQuery(inpath); // 从当前格子找到下一出口
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
    while(true);
}