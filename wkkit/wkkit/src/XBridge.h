/* XBridge.h
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
 *     This file is a header file for XBridge.cpp.
 *
 * Version: 1.0.0
 */

#ifndef __XBRIDGE_H__
#define __XBRIDGE_H__


#define XBRIDGE_SUPPORT
#define XBRIDGE_SUPPORT_NOTIFY
#define XBRIDGE_SUPPORT_CONNECT_HEARTBEAT


class XNBlock;
class XNServer;
class XBluetooth;


/**
 *
 */
class List {
public:
    List() :
        mLength(0),
        mHead(this, NULL) {
        mHead.mPrev = mHead.mNext = &mHead;
    }
    ~List() { clear(); }

    class Node {
    public:
        Node(List *lst, void *obj) :
            mList(lst),
            mObj(obj) {
            mPrev = mNext = NULL;
        }
        ~Node() {}

        void * obj() {
            return mObj;
        }
        void remove() { mList->remove(this); }
        Node * prev() { return (mPrev == mList->head()) ? NULL : mPrev; }
        Node * next() { return (mNext == mList->head()) ? NULL : mNext; }

    protected:
        friend class List;
        Node    *mPrev;
        Node    *mNext;

    private:
        List    *mList;
        void    *mObj;
    };

    uint8_t length() { return mLength; }
    Node * head() { return &mHead; }
    Node * begin() { return (mLength == 0) ? NULL : mHead.mNext; }
    Node * end() { return (mLength == 0) ? NULL : mHead.mPrev; }

    void pushBack(Node *node) {
        node->mPrev = mHead.mPrev;
        node->mNext = &mHead;
        mHead.mPrev->mNext = node;
        mHead.mPrev = node;
        mLength++;
    }
    void pushFront(Node *node) {
        node->mPrev = &mHead;
        node->mNext = mHead.mNext;
        mHead.mNext->mPrev = node;
        mHead.mNext = node;
        mLength++;
    }
    void remove(Node *node) {
        if (mLength > 0) {
            node->mNext->mPrev = node->mPrev;
            node->mPrev->mNext = node->mNext;
            mLength--;
        }
    }
    void clear() {
		Node *node;
        while (mHead.mNext != &mHead) {
			node = mHead.mNext; // backup to delete.
            remove(mHead.mNext);
			delete node;
        }
    }

private:
    uint8_t mLength;
    Node    mHead;
};


/**
 *  XBridge Protocol Packet.
 */
#define XBRIDGE_ACTION_DEVICE_QUERY     		(0x01)  //!< Query device name, SN, mainboard type, BID, version
#define XBRIDGE_ACTION_DEVICE_SETUP   			(0x02)  //!< Setup device, key1: 0x01--handshake, 0x02--heartbeat
#define XBRIDGE_ACTION_SESSION_SETUP			(0x03)  //!< Setup session, key1: 0x01--start, 0x02--stop
#define XBRIDGE_ACTION_BLOCK_CONSTRUCT  		(0x10)  //!< Construct block, key1 is block type, key2: 0x01--onboard, 0x02--external
#define XBRIDGE_ACTION_BLOCK_ACCESS     		(0x12)  //!< Access block, key1 is uid, key2 is api.
#define XBRIDGE_ACTION_BLOCK_NOTIFY     		(0x1A)  //!< Notify block, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_BLOCK_NOTIFY_REGISTER	(0x1B)  //!< Block register notify, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_BLOCK_NOTIFY_UNREGISTER	(0x1C)  //!< Block unregister notify, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_SERVER_CONSTRUCT 		(0x20)  //!< Construct server, key1 is server type.
#define XBRIDGE_ACTION_SERVER_ACCESS    		(0x22)  //!< Access server, key1 is uid, key2 is api.
#define XBRIDGE_ACTION_SERVER_NOTIFY    		(0x2A)  //!< Notify server, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_SERVER_NOTIFY_REGISTER	(0x2B)  //!< Server register notify, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_SERVER_NOTIFY_UNREGISTER	(0x2C)  //!< Server unregister notify, key1 is uid, key2 is evt.
#define XBRIDGE_ACTION_USER_MESSAGE    			(0x40)  //!< User message, key1 is message code.
#define XBRIDGE_ACTION_RESPONSE         		(0x80)  //!< Actual is 0x80+ACTION, key1 is the action's SNo, key2 is status.

#define XBRIDGE_MAX_DSIZE	12
#define XBRIDGE_MAX_PSIZE	16

class XBridgePacket {
public:
#define OFFSET_SNO		0
#define OFFSET_ACT		1
#define OFFSET_KEY1		2
#define OFFSET_KEY2		3
#define OFFSET_DATA		4

    XBridgePacket() :
		mEmpty(1),
		mDSize(0) {
        memset((void *)mBuffer, 0, XBRIDGE_MAX_PSIZE);
    }
    ~XBridgePacket() {}

	/*!< Call set to load the packet */
    void set(uint8_t sno, uint8_t action,
            uint8_t key1, uint8_t key2, uint8_t dsize, const uint8_t *dbuf) {
        mBuffer[OFFSET_SNO] = sno;
        mBuffer[OFFSET_ACT] = action;
        mBuffer[OFFSET_KEY1] = key1;
        mBuffer[OFFSET_KEY2] = key2;
		mDSize = (dsize > XBRIDGE_MAX_DSIZE) ? XBRIDGE_MAX_DSIZE : dsize;
        memcpy(&mBuffer[OFFSET_DATA], dbuf, mDSize);
		mEmpty = 0;
    }
    void set(uint8_t sno, uint8_t action,
            uint8_t key1, uint8_t key2, uint8_t dsize) {
        mBuffer[OFFSET_SNO] = sno;
        mBuffer[OFFSET_ACT] = action;
        mBuffer[OFFSET_KEY1] = key1;
        mBuffer[OFFSET_KEY2] = key2;
        mDSize = (dsize > XBRIDGE_MAX_DSIZE) ? XBRIDGE_MAX_DSIZE : dsize;
		mEmpty = 0;
    }
	void set(uint8_t dsize) {
		mDSize = dsize;
		mEmpty = 0;
	}
	
	/*!< Call clear to give back the packet */
	void clear() {
		mDSize = 0;
		mEmpty = 1;
		memset((void *)mBuffer, 0, XBRIDGE_MAX_PSIZE);
	}
	
	bool isEmpty() { return mEmpty ? true : false; }
    uint8_t sno() const { return mBuffer[OFFSET_SNO]; }
    uint8_t action() const { return mBuffer[OFFSET_ACT]; }
    uint8_t key1() const { return mBuffer[OFFSET_KEY1]; }
    uint8_t key2() const { return mBuffer[OFFSET_KEY2]; }
    uint8_t dlen() const { return XBRIDGE_MAX_DSIZE; }
    uint8_t * dbuf() const { return (uint8_t *)&mBuffer[OFFSET_DATA]; }
	uint8_t dsize() const { return mDSize; }
    uint8_t plen() const { return XBRIDGE_MAX_PSIZE; }
    uint8_t *pbuf() const { return (uint8_t *)mBuffer; }
	uint8_t psize() const { return mDSize + 4; }
	
private:
	uint8_t		mEmpty;
    uint8_t     mBuffer[XBRIDGE_MAX_PSIZE];
    uint8_t     mDSize;
};


enum XBridgeStatusEnum {
    XBDG_STAT_OK = 0,

    XBDG_STAT_FAIL = -1,
    XBDG_STAT_TIMEOUT = -2,
};


/**
 *  Interface of bridge transform layer.
 */
class IBridgeTransLayer {
public:
	virtual ~IBridgeTransLayer() {}

    /** \brief  Set broadcast.
     */
    virtual void setBroadcast(const char *adv) = 0;

    /** \brief  Flush all of buffers.
     */
    virtual void flush() = 0;

    /** \brief  Receive packet
     *  \return -1--disconnected, 0--no packet received, postive--number of packet received
     */
    virtual int recv(XBridgePacket *pkt) = 0;

    /*!< Send packet, 0 is ok, else failed */
    virtual int send(XBridgePacket *pkt) = 0;

	virtual uint8_t isConnected() = 0;
};

class BTBridgeTransLayer : public IBridgeTransLayer{
public:
    BTBridgeTransLayer(XBluetooth *bt);
    ~BTBridgeTransLayer() {}

	void setBroadcast(const char *adv);
    void flush();
    int recv(XBridgePacket *pkt);
    int send(XBridgePacket *pkt);
    uint8_t isConnected();

private:
    XBluetooth *	mBt;
};


/**
 *  Bridge Native.
 */
#define XBRIDGE_DEVNAME_MAX_SIZE	(11)

#define XBRIDGE_STATUS_CONNECTED		(0x01)
#define XBRIDGE_STATUS_CONNECT_ALERT	(0x02)

class XNBridgeDynamicBody {
public:
    char                name[XBRIDGE_DEVNAME_MAX_SIZE+1];
	uint32_t			sn;
    IBridgeTransLayer   *trans;
    uint8_t             sno;
    uint8_t             status;
	uint8_t      		uidSeed;
    List                blockList;
    List                serverList;
	XBridgePacket 		rpkt;
	XBridgePacket		spkt;
#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
	unsigned long		heartbeatTimeoutTimeMs;
#endif
};

class XNBridge {
public:
    XNBridge() : mBody(NULL) {}
    ~XNBridge() {
		if (mBody) {
			delete mBody->trans;
			delete mBody;
		}
	}
	int setup(XBluetooth *bt, const char *devName, uint32_t sn);
	void reset();

	bool isConnected() {
		return (mBody && (mBody->status & XBRIDGE_STATUS_CONNECTED)) ? true : false;
	}

	XNBlock * getBlockByUid(uint8_t uid);
    XNBlock * getBlockByPos(uint8_t pos);
    XNServer * getServerByUid(uint8_t uid);
    XNServer * getServerByPos(uint8_t pos);

	/*!< Check and get message to process, 0--no message, -1--connection breakup, Positive--has message */
	int8_t available();
	const XBridgePacket * getMessage();
	void handledMessage();

	/*!< Check and process "query BID" message */
	bool messageIsQueryBID() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_DEVICE_QUERY) &&
			(mBody->rpkt.key1() == 0x04)) {
			return true;
		} else {
			return false;
		}
	}
	void handledQueryBID(uint8_t BID[5]);

	/*!< Check and process "query firmware version" message */
	bool messageIsQueryFirmwareVersion() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_DEVICE_QUERY) &&
			(mBody->rpkt.key1() == 0x05)) {
			return true;
		} else {
			return false;
		}
	}
	void handledQueryFirmwareVersion(uint8_t major, uint8_t minor, uint8_t patch);

	/*!< Check and process "handshake" message */
	bool messageIsHandshake() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_DEVICE_SETUP) &&
			(mBody->rpkt.key1() == 0x01)) {
			return true;
		} else {
			return false;
		}
	}
	void handledHandshake();

	/*!< Check and process "session" message */
	bool messageIsConnect() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_SESSION_SETUP) &&
			(mBody->rpkt.key1() == 0x01)) {
			return true;
		} else {
			return false;
		}
	}
	void handledConnect();

	bool messageIsDisconnect() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_SESSION_SETUP) &&
			(mBody->rpkt.key1() == 0x02)) {
			return true;
		} else {
			return false;
		}
	}
	void handledDisconnect();

	/*!< Check and process "construct block" message */
	bool messageIsConstructBlock() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_BLOCK_CONSTRUCT)) {
			return true;
		} else {
			return false;
		}
	}
	void handledConstructBlock(XNBlock *blk, uint8_t dynamic);

	/*!< Check and process "construct server" message */
	bool messageIsConstructServer() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_SERVER_CONSTRUCT)) {
			return true;
		} else {
			return false;
		}
	}
	void handledConstructServer(XNServer *svr, uint8_t dynamic);

#if 0
	/*!< Check and process "user" message */
	bool messageIsUserMessage() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_USER_MESSAGE)) {
			return true;
		} else {
			return false;
		}

		return false;
	}
	void handledUserMessage(uint8_t ack);
#endif

private:
	/*!< UID valid range is [1--127] */
	uint8_t genUID() {
		return mBody->uidSeed++;
	}

    uint8_t genSNo() {
        if (++mBody->sno == 0) {
            mBody->sno = 1;
        }
        return mBody->sno;
    }

    void onDeviceQuery();

	uint8_t onBlockAccess();
	uint8_t onServerAccess();

	void postMessage(uint8_t noResponse=0);
	void loopServerRun();

#ifdef XBRIDGE_SUPPORT_NOTIFY
	void onBlockNotifyRegister();
	void onServerNotifyRegister();
	void loopNotifyCheck();
#endif

#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
	bool messageIsHeartbeat() {
		if (mBody && (mBody->rpkt.action() == XBRIDGE_ACTION_DEVICE_SETUP) &&
			(mBody->rpkt.key1() == 0x02)) {
			return true;
		} else {
			return false;
		}
	}
	void handledHeartbeat();
#endif

private:
	XNBridgeDynamicBody	*mBody;
};

extern XNBridge XBridge;


#endif	// __XBRIDGE_H__