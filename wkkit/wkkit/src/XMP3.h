

#ifndef __XMP3_H__
#define __XMP3_H__


#define CMD_NONE			0
#define CMD_QUERY			1
#define CMD_PALY			2
#define CMD_PAUSE			3
#define CMD_STOP			4
#define CMD_PLAY_PREVIOUS	5
#define CMD_PLAY_NEXT		6
#define CMD_VOL_UP			7
#define CMD_VOL_DOWN		8


class XMP3 {
public:
    XMP3();
	~XMP3();

	int setup();
	void sendCmd(uint8_t cmdId);
	void setId(uint8_t id);


private:
	//int sendByte(char val);
	int sendBytes(uint8_t *buf, int len);

	uint8_t recvByte();
	int recvBytes(uint8_t *buf, int len);

};


#endif	// __XMP3_H__