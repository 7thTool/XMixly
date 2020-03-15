/* XBridge.cpp
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
 *     This file is an implement of X-Bridge protocol.
 *
 * Version: 1.0.0
 */

#include <Arduino.h>
#include <avr/boot.h>
#include <XBlock.h>
#include <XBridge.h>
#include <XBluetooth.h>


#if 0
#include <XDebug.h>
#define LOG(x)		XDebug.print(x)
#define LOGN(x)		XDebug.println(x)
#else
#define LOG(x)
#define LOGN(x)
#endif


//#define BTRECV_DETAIL
//#define BTSEND_DETAIL


#ifdef BTRECV_DETAIL
#include <XDebug.h>
static unsigned long runtime=0;
#endif

// Enable BTBridgeTranslayer checksum function.
#define BTT_CHECKSUM_ENABLE

XNBridge XBridge;


BTBridgeTransLayer::BTBridgeTransLayer(XBluetooth *bt) :
	mBt(bt)
{
}

void BTBridgeTransLayer::setBroadcast(const char *adv)
{
	mBt->setBroadcast(adv);
}

int BTBridgeTransLayer::recv(XBridgePacket *pkt)
{
#define TIMEOUT		(400ul)	// 400ms
	char startChar=0;
	uint8_t rsize, psize;
	uint8_t *pbuf = pkt->pbuf();
	uint8_t checkSum;
	unsigned long timeout;

	if (!mBt->available()) {
#ifdef BTRECV_DETAIL
		if (runtime++ > 20000) {
			XDebug.print('.');
			runtime = 0;
		}
#endif
		return 0;
	}
#ifdef BTRECV_DETAIL
	XDebug.println("");
#endif

	/*!< First check if received minimum data enough to parse. */
	/*!< 8Bytes: 2B("XB") + 1B(PSize) + 1B(SNo) + 1B(Action) + 1B(Key1) + 1B(Key2) + 0B(Data) + 1B(CheckSum) */	
	rsize = mBt->available();
	if (rsize < 8) {
		timeout = millis();
		while (rsize < 8) {
			if (millis() > timeout + TIMEOUT) { // timeout.
#ifdef BTRECV_DETAIL
				XDebug.print("rsize=");
				XDebug.print(rsize);
				XDebug.println(", rsize < 8 check timeout");
#endif
				goto cleanup;
			}
			rsize = mBt->available();
		}
	}

#if 0
	char rchar;
	/*!< Search start bytes of "XB". */
	while (startChar != 'B') {
		if (!mBt->available()) {
			LOGN("not found \"XB\"");
			goto cleanup;
		}

		rchar = mBt->recvByte();
#ifdef BTRECV_DETAIL
		XDebug.print(rchar); XDebug.print(',');
#endif
		if (((startChar == 0) && (rchar != 'X')) ||
			((startChar == 'X') && (rchar != 'B'))) {
			startChar = 0;
		} else {
			startChar = rchar;
		}
	}

	/*!< receive pakcet size and check if data enough */
	rsize = mBt->available();
	//LOG("2: rsize=");
	//LOGN(rsize);
	if (rsize < 6) { // 1B(PSize) + 1B(SNo) + 1B(Action) + 1B(Key1) + 1B(Key2) + 0B(Data) + 1B(CheckSum)
		timeout = millis();
		while (rsize < 6) {
			if (millis() > timeout + TIMEOUT) { // timeout.
				LOGN("rsize < 6 check timeout");
				goto cleanup;
			}
			rsize = mBt->available();
			//LOG("--: rsize=");
			//LOGN(rsize);
		}
	}
#else // Don't search "XB" head, just discard.
	startChar = mBt->recvByte();
#ifdef BTRECV_DETAIL
	XDebug.print(startChar); XDebug.print(',');
#endif
	if (startChar != 'X') {
#ifdef BTRECV_DETAIL
		XDebug.println("1st startchar is not X");
#endif
		goto cleanup;
	}

	startChar = mBt->recvByte();
#ifdef BTRECV_DETAIL
		XDebug.print(startChar); XDebug.print(',');
#endif
	if (startChar != 'B') {
#ifdef BTRECV_DETAIL
		XDebug.println("2nd startchar is not B");
#endif
		goto cleanup;
	}

	rsize -= 2;
#endif

	psize = mBt->recvByte();
#ifdef BTRECV_DETAIL
	XDebug.print(psize, HEX); XDebug.print(',');
#endif
	// 1B(SNo) + 1B(Action) + 1B(Key1) + 1B(Key2) + 0B(Data)
	if ((psize < 4) || (psize > XBRIDGE_MAX_PSIZE)) {
#ifdef BTRECV_DETAIL
		XDebug.println("psize error");
#endif
		goto cleanup;
	}
	rsize -= 1;

	/*!< read SNo, Action, Key1, Key2 */
	pbuf[0] = mBt->recvByte(); // SNo
	pbuf[1] = mBt->recvByte(); // Action
	pbuf[2] = mBt->recvByte(); // Key1
	pbuf[3] = mBt->recvByte(); // Key2
	rsize -= 4;
	psize -= 4;
#ifdef BTRECV_DETAIL
	XDebug.print(pbuf[0], HEX); XDebug.print(',');
	XDebug.print(pbuf[1], HEX); XDebug.print(',');
	XDebug.print(pbuf[2], HEX); XDebug.print(',');
	XDebug.print(pbuf[3], HEX); XDebug.print(',');
#endif

	/*!< wait and receive packet "data" */
	if (rsize < psize + 1/*checkSum*/) {
		timeout = millis();
		while (rsize < psize + 1/*checkSum*/) {
			if (millis() > timeout + 600ul) { // timeout.
#ifdef BTRECV_DETAIL
				XDebug.print("rsize=");
				XDebug.print(rsize);
				XDebug.println(", rsize < (psize + 1) check timeout");
#endif
				goto cleanup;
			}
			rsize = mBt->available();
		}
	}
	if (psize > 0) {
		mBt->recvBytes(&pbuf[4], psize);
#ifdef BTRECV_DETAIL
		for (rsize = 0; rsize < psize; rsize++) {
			XDebug.print(pbuf[4+rsize], HEX); XDebug.print(',');
		}
#endif
	}

	/*!< CheckSum */
	checkSum = mBt->recvByte();
#ifdef BTRECV_DETAIL
	XDebug.println(checkSum, HEX);
#endif
#ifdef BTT_CHECKSUM_ENABLE
	uint8_t i, l;
	l = 'X' + 'B' + (psize + 4);
	for (i=0; i<(psize+4); i++) {
		l += pbuf[i];
	}
	if (checkSum != l) {
		LOG("checkSum failed ("); LOG(checkSum); LOG(" != "); LOG(l); LOGN(")");
		goto cleanup;
	}
#endif

	/*!< complete */
	pkt->set(psize); // dsize, except "SNo, Action, Key1, Key2" 4 bytes
	return 1;
cleanup:
	mBt->flush();
	return 0;
}

void BTBridgeTransLayer::flush()
{
	mBt->flush();
}

int BTBridgeTransLayer::send(XBridgePacket *pkt)
{
	uint8_t sbuf[XBRIDGE_MAX_PSIZE + 4]/*2B("XB") + 1B(plen) + 1B(checkSum)*/, size=0;

	/*!< start bytes */
	sprintf((char *)sbuf, "XB");
	size += 2;

	/*!< psize */
	sbuf[size] = pkt->psize();
	size += 1;

	/*!< pdata */
	memcpy(&sbuf[size], pkt->pbuf(), pkt->psize());
	size += pkt->psize();

	/*!< checksum */
#ifdef BTT_CHECKSUM_ENABLE
	uint8_t checksum, i;
	for (checksum=0, i=0; i<size; i++) {
		checksum += sbuf[i];
	}
	sbuf[size] = checksum;
#else
	sbuf[size] = 0;
#endif
	size += 1;

#ifdef BTSEND_DETAIL
	XDebug.print((char)sbuf[0]); XDebug.print(',');
	XDebug.print((char)sbuf[1]); XDebug.print(',');
	for (uint8_t i=2; i<size; i++) {
		XDebug.print(sbuf[i], HEX);
		if (i < size-1) {
			XDebug.print(',');
		}
	}
	XDebug.println("");
#endif
	return mBt->sendBytes(sbuf, size);
}

uint8_t BTBridgeTransLayer::isConnected()
{
#if 0	// For ROM sapce problem.
	return mBt->isConnected();
#else
	return 0;
#endif
}

int XNBridge::setup(XBluetooth *bt, const char *devName, uint32_t sn) {
	char adv[24];

	LOG("XNBridge::setup("); LOG(devName); LOG(","); LOG(sn); LOGN(")");

	if (!bt) {
		LOGN("bt must not be NULL");
		return -1;
	}

	mBody = new XNBridgeDynamicBody();
	if (!mBody) {
		LOGN("new XNBridgeDynamicBody failed");
		return -1;
	}

	mBody->trans = new BTBridgeTransLayer(bt);
	if (!mBody->trans) {
		LOGN("new BTBridgeTransLayer failed");
		delete mBody;
		return -1;
	}

	reset();
	mBody->sn = sn;
	strncpy(mBody->name, devName, XBRIDGE_DEVNAME_MAX_SIZE);
	mBody->name[XBRIDGE_DEVNAME_MAX_SIZE] = '\0';

	sprintf(adv, "%s;%04X%04X;", mBody->name, (uint16_t)(mBody->sn >> 16) & 0xffff, (uint16_t)mBody->sn & 0xffff);
	mBody->trans->setBroadcast(adv);
	return 0;
}

void XNBridge::reset()
{
	LOGN("XNBridge::reset()");

	if (mBody) {
		uint8_t sum;
		XNBlock *blk;
		XNServer *svr;
		sum = mBody->serverList.length();
		while (sum > 0) {
			svr = getServerByPos(sum-1);
			if (svr->isDynamic()) {
				delete svr;
			} else {
				svr->reset();
			}
			sum--;
		}
		sum = mBody->blockList.length();
		while (sum > 0) {
			blk = getBlockByPos(sum-1);
			if (blk->isDynamic()) {
				delete blk;
			} else {
				blk->reset();
			}
			sum--;
		}

		mBody->sno = 0;
		mBody->uidSeed = 1;	// 0 reserved, MUST start from 1.
		mBody->status = 0;
		mBody->sno = 0;
		mBody->blockList.clear();
		mBody->serverList.clear();
		mBody->rpkt.clear();
		mBody->spkt.clear();
#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
		mBody->heartbeatTimeoutTimeMs = 0ul;
#endif
	}
}

XNBlock * XNBridge::getBlockByUid(uint8_t uid)
{
    XNBlock *blk;

	if (mBody) {
		List::Node *node = mBody->blockList.begin();
		while (node) {
			blk = (XNBlock *)node->obj();
			if (blk->uid() == uid) {
				return blk;
			}
			node = node->next();
		}
	}

    return NULL;
}

XNBlock * XNBridge::getBlockByPos(uint8_t pos)
{
	XNBlock *blk;

	if (mBody) {
		List::Node *node = mBody->blockList.begin();
		while (node) {
			if (pos == 0) {
				blk = (XNBlock *)node->obj();
				return blk;
			}
			node = node->next();
			pos--;
		}
	}

    return NULL;
}

XNServer * XNBridge::getServerByUid(uint8_t uid)
{
    XNServer *svr;

	if (mBody) {
		List::Node *node = mBody->serverList.begin();
		while (node) {
			svr = (XNServer *)node->obj();
			if (svr->uid() == uid) {
				return svr;
			}
			node = node->next();
		}
	}

    return NULL;
}

XNServer * XNBridge::getServerByPos(uint8_t pos)
{
	XNServer *svr;

	if (mBody) {
		List::Node *node = mBody->serverList.begin();
		while (node) {
			if (pos == 0) {
				svr = (XNServer *)node->obj();
				return svr;
			}
			node = node->next();
			pos--;
		}
	}

    return NULL;
}

int8_t XNBridge::available()
{
	if (!mBody || (mBody->trans->recv(&mBody->rpkt) <= 0)) {
		if (mBody && (mBody->status & XBRIDGE_STATUS_CONNECTED)) {
#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
			if ((mBody->heartbeatTimeoutTimeMs != 0ul) && (millis() > mBody->heartbeatTimeoutTimeMs)) {
#if 0	// For ROM sapce problem.
				if (!mBody->trans->isConnected() || (mBody->status & XBRIDGE_STATUS_CONNECT_ALERT)) {
#else
				if (mBody->status & XBRIDGE_STATUS_CONNECT_ALERT) {
#endif
					reset();
					return -1;
				} else {
					mBody->status |= XBRIDGE_STATUS_CONNECT_ALERT;
					mBody->heartbeatTimeoutTimeMs = millis() + 2000ul;
					return 0;
				}
			}
#endif
			loopServerRun();
#ifdef XBRIDGE_SUPPORT_NOTIFY
			loopNotifyCheck();
#endif
		}
		return 0;
	}

	LOG("sno="); LOG(mBody->rpkt.sno());
	LOG(",action="); LOG(mBody->rpkt.action()); 
	LOG(",key1="); LOG(mBody->rpkt.key1());
	LOG(",key2="); LOG(mBody->rpkt.key2());
	LOG(",dsize="); LOGN(mBody->rpkt.dsize());

	if (!(mBody->status & XBRIDGE_STATUS_CONNECTED) &&
		((mBody->rpkt.action() != XBRIDGE_ACTION_DEVICE_QUERY) &&
		((mBody->rpkt.action() != XBRIDGE_ACTION_DEVICE_SETUP) || messageIsHeartbeat()) &&
		(mBody->rpkt.action() != XBRIDGE_ACTION_SESSION_SETUP))) {
		LOGN("Device has not been connected");
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + mBody->rpkt.action(), mBody->rpkt.sno(), -1, 0);
		postMessage();
		return 0;
	}

	return 1;
}

const XBridgePacket * XNBridge::getMessage()
{
	if (!mBody || mBody->rpkt.isEmpty()) {
		return NULL;
	} else {
		return (const XBridgePacket *)&mBody->rpkt;
	}
}

void XNBridge::postMessage(uint8_t noResponse)
{
	mBody->rpkt.clear();
	if (!noResponse) {
		mBody->trans->send(&mBody->spkt);
	}
	mBody->spkt.clear();
	LOGN("responsed");

#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
	// 任何有效数据包，都认为是能延续alive状态。
	// 这样在数据交互比较繁忙的时候，keep alive包即使有延迟或者丢失，
	// 设备端也能保持会话连接的alive。
	if (mBody->heartbeatTimeoutTimeMs != 0ul) {
		mBody->heartbeatTimeoutTimeMs = millis() + 1500ul;
		mBody->status &= ~XBRIDGE_STATUS_CONNECT_ALERT;
	}
#endif
}

void XNBridge::handledMessage()
{
	uint8_t noResponse = 0;

	LOGN("XNBridge::handledMessage()");
	//assert(!mBody->rpkt.isEmpty());
	//assert(mBody->rpkt.action() != XBRIDGE_ACTION_BLOCK_CONSTRUCT);
	//assert(mBody->rpkt.action() != XBRIDGE_ACTION_SERVER_CONSTRUCT);
	//assert(mBody->rpkt.action() != XBRIDGE_ACTION_USER_MESSAGE);

	if (!mBody || mBody->rpkt.isEmpty()) {
		return;
	}

	if (messageIsHandshake()) {
		return handledHandshake();
#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
	} else if (messageIsHeartbeat()) {
		return handledHeartbeat();
#endif
	} if (messageIsConnect()) {
		return handledConnect();
	} else if (messageIsDisconnect()) {
		return handledDisconnect();
	} else if (messageIsConstructBlock()) {
		return handledConstructBlock(NULL, 0);
	} else if (messageIsConstructServer()) {
		return handledConstructServer(NULL, 0);
#if 0
	} else if (messageIsUserMessage()) {
		return handledUserMessage(0xFF);
#endif
	}

	switch (mBody->rpkt.action()) {
		case XBRIDGE_ACTION_DEVICE_QUERY:
			onDeviceQuery();
			break;
		case XBRIDGE_ACTION_BLOCK_ACCESS:
			noResponse = onBlockAccess();
			break;
		case XBRIDGE_ACTION_SERVER_ACCESS:
			noResponse = onServerAccess();
			break;
#ifdef XBRIDGE_SUPPORT_NOTIFY
		case XBRIDGE_ACTION_BLOCK_NOTIFY_REGISTER:
			onBlockNotifyRegister();
			break;

		case XBRIDGE_ACTION_SERVER_NOTIFY_REGISTER:
			onServerNotifyRegister();
			break;
#endif	// XBRIDGE_SUPPORT_NOTIFY
		default:
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + mBody->rpkt.action(), mBody->rpkt.sno(), -1, 0);
			break;
	}

	postMessage(noResponse);
}

void XNBridge::handledQueryBID(uint8_t BID[5])
{
	LOGN("XNBridge::handledQueryBID()");

	if (mBody) {
		memcpy((char *)mBody->spkt.dbuf(), (const void *)BID, 5);
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), 0, 5);
		postMessage();
	}
}

void XNBridge::handledQueryFirmwareVersion(uint8_t major, uint8_t minor, uint8_t patch)
{
	LOGN("XNBridge::handledQueryFirmwareVersion()");

	if (mBody) {
		mBody->spkt.dbuf()[0] = major;
		mBody->spkt.dbuf()[1] = minor;
		mBody->spkt.dbuf()[2] = patch;
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), 0, 3);
		postMessage();
	}
}

void XNBridge::handledHandshake()
{
	LOGN("XNBridge::handledHandshake()");

	if (mBody) {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_SETUP, mBody->rpkt.sno(), 0, 0);
		postMessage();
	}
}

#ifdef XBRIDGE_SUPPORT_CONNECT_HEARTBEAT
void XNBridge::handledHeartbeat()
{
	LOGN("XNBridge::handledHeartbeat()");

	if (mBody) {
		mBody->heartbeatTimeoutTimeMs = millis() + mBody->rpkt.key2() * 1000ul;
		mBody->status &= ~XBRIDGE_STATUS_CONNECT_ALERT;
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_SETUP, mBody->rpkt.sno(), 0, 0);
		postMessage();
	}
}
#endif

void XNBridge::handledConnect()
{
	LOGN("XNBridge::handledConnect()");
	//assert(mRPkt.action() == XBRIDGE_ACTION_SESSION_SETUP);

	if (mBody) {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SESSION_SETUP, mBody->rpkt.sno(), 0, 0);
		postMessage();
		mBody->status |= XBRIDGE_STATUS_CONNECTED;
	}
}

void XNBridge::handledDisconnect()
{
	LOGN("XNBridge::handledDisconnect()");

	if (mBody) {
		mBody->status &= ~XBRIDGE_STATUS_CONNECTED;
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SESSION_SETUP, mBody->rpkt.sno(), 0, 0);
		postMessage();

		reset();
	}
}

void XNBridge::handledConstructBlock(XNBlock *blk, uint8_t dynamic)
{
	LOGN("XNBridge::handledConstructBlock()");
	//LOG(" type="); LOGN(blk->type());
	//LOG(" dynamic="); LOGN(dynamic);
	//assert(mBody->rpkt.action() == XBRIDGE_ACTION_BLOCK_CONSTRUCT);

	if (mBody) {
		if (blk) {
			uint8_t *sbuf = mBody->spkt.dbuf();
			List::Node *node = new List::Node(&mBody->blockList, (void *)blk);
			blk->setFlag(genUID(), dynamic);
			mBody->blockList.pushBack(node);
			LOG("uid="); LOGN(blk->uid());
			sbuf[0] = blk->uid();
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_CONSTRUCT, mBody->rpkt.sno(), 0, 1);
		} else {
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_CONSTRUCT, mBody->rpkt.sno(), -1, 0);
		}

		postMessage();
	}
}

void XNBridge::handledConstructServer(XNServer *svr, uint8_t dynamic)
{
	LOGN("XNBridge::handledConstructServer()");
	//LOG(" type="); LOGN(svr->type());
	//LOG(" dynamic="); LOGN(dynamic);
	//assert(mBody->rpkt.action() == XBRIDGE_ACTION_SERVER_CONSTRUCT);

	if (mBody) {
		if (svr) {
			uint8_t *sbuf = mBody->spkt.dbuf();
			List::Node *node = new List::Node(&mBody->serverList, (void *)svr);
			svr->setFlag(genUID(), dynamic);
			mBody->serverList.pushBack(node);
			LOG("uid="); LOGN(svr->uid());
			sbuf[0] = svr->uid();
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_CONSTRUCT, mBody->rpkt.sno(), 0, 1);
		} else {
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_CONSTRUCT, mBody->rpkt.sno(), -1, 0);
		}

		postMessage();
	}
}

#if 0
void XNBridge::handledUserMessage(uint8_t ack)
{
	LOG("XNBridge::handledUserMessage()");
	LOG(" ack="); LOGN(ack);
	//assert(mBody->rpkt.action() == XBRIDGE_ACTION_USER_MESSAGE);

	if (mBody) {
		uint8_t *sbuf = mBody->spkt.dbuf();
		sbuf[0] = ack;
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_USER_MESSAGE, mBody->rpkt.sno(), 0, 1);

		postMessage();
	}
}
#endif

uint8_t XNBridge::onBlockAccess()
{
    XNBlock *blk;
    uint8_t uid = mBody->rpkt.key1();
    uint8_t api = mBody->rpkt.key2();
    uint8_t dsize = mBody->spkt.dlen();
    int8_t ret;

	//LOG("XNBridge::onBlockAccess()");
	//LOG(" uid="); LOG(uid);
	//LOG(",api="); LOGN(api);

	blk = getBlockByUid(uid & 0x7F);
	if (blk) {
		ret = blk->onAccess(api, mBody->rpkt.dbuf(), mBody->rpkt.dsize(), mBody->spkt.dbuf(), &dsize);
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_ACCESS,
				mBody->rpkt.sno(), ret, dsize);
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_ACCESS,
				mBody->rpkt.sno(), -1, 0);
	}

	return uid & 0x80;
}

uint8_t XNBridge::onServerAccess()
{
    XNServer *svr;
    uint8_t uid = mBody->rpkt.key1();
    uint8_t api = mBody->rpkt.key2();
    uint8_t dsize = mBody->spkt.dlen();
    int8_t ret;

	//LOG("XNBridge::onServerAccess()");
	//LOG(" uid="); LOG(uid);
	//LOG(",api="); LOGN(api);

	svr = getServerByUid(uid & 0x7F);
	if (svr) {
		ret = svr->onAccess(api, mBody->rpkt.dbuf(), mBody->rpkt.dsize(), mBody->spkt.dbuf(), &dsize);
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_ACCESS,
				mBody->rpkt.sno(), ret, dsize);
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_ACCESS,
				mBody->rpkt.sno(), -1, 0);
	}

	return uid & 0x80;
}

void XNBridge::onDeviceQuery()
{
#if 0
    uint8_t dsize;
	uint8_t key1 = mBody->rpkt.key1();
    uint8_t *dbuf = mBody->spkt.dbuf();

	//LOG("XNBridge::onDeviceQuery()");
	//LOG(" key1="); LOGN(key1);
	//LOG(" key2="); LOGN(mBody->rpkt.key2());

	if (key1 == 0x01) {	/*!< device name */
		strcpy((char *)dbuf, mBody->name);
		dsize = strlen(mBody->name) + 1;
	} else if (key1 == 0x02) {	/*!< device SN */
		memcpy(dbuf, &mBody->sn, 4);
		dsize = 4;
	} else if (key1 == 0x03) {	/*!< mainboard type */
		strcpy((char *)dbuf, BOARD_NAME);
		dsize = strlen(BOARD_NAME) + 1;
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), -1, 0);
		return;
	}

    /*!< pack mSendPacket */
    mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), 0, dsize);
#else
	uint8_t key1 = mBody->rpkt.key1();

	//LOG("XNBridge::onDeviceQuery()");
	//LOG(" key1="); LOGN(key1);
	//LOG(" key2="); LOGN(mBody->rpkt.key2());

	if (key1 == 0x02) {	/*!< device SN */
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), 0, 4, (const uint8_t *)&mBody->sn);
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_DEVICE_QUERY, mBody->rpkt.sno(), -1, 0);
	}
#endif
}

void XNBridge::loopServerRun()
{
    XNServer *svr;
    List::Node *node = mBody->serverList.begin();

    while (node) {
        svr = (XNServer *)node->obj();
        svr->loop();
        node = node->next();
    }
}

#ifdef XBRIDGE_SUPPORT_NOTIFY
void XNBridge::onBlockNotifyRegister()
{
    XNBlock *blk;
    uint8_t uid = mBody->rpkt.key1();
    uint8_t evt = mBody->rpkt.key2();
	uint8_t dsize = mBody->spkt.dlen();
    int8_t ret;

	blk = getBlockByUid(uid);
	if (blk) {
		ret = blk->onNotifyRegister(evt, mBody->rpkt.dbuf(), mBody->rpkt.dsize(), mBody->spkt.dbuf(), &dsize);
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_NOTIFY_REGISTER,
				mBody->rpkt.sno(), ret, dsize);
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_BLOCK_NOTIFY_REGISTER,
				mBody->rpkt.sno(), -1, 0);
	}
}

void XNBridge::onServerNotifyRegister()
{
    XNServer *svr;
    uint8_t uid = mBody->rpkt.key1();
    uint8_t evt = mBody->rpkt.key2();
	uint8_t dsize = mBody->spkt.dlen();
    int8_t ret;

	svr = getServerByUid(uid);
	if (svr) {
		ret = svr->onNotifyRegister(evt, mBody->rpkt.dbuf(), mBody->rpkt.dsize(), mBody->spkt.dbuf(), &dsize);
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_NOTIFY_REGISTER,
				mBody->rpkt.sno(), ret, dsize);
	} else {
		mBody->spkt.set(genSNo(), XBRIDGE_ACTION_RESPONSE + XBRIDGE_ACTION_SERVER_NOTIFY_REGISTER,
				mBody->rpkt.sno(), -1, 0);
	}
}

void XNBridge::loopNotifyCheck()
{
	XNBlock *blk;
    XNServer *svr;
    List::Node *node;
	uint8_t evt, dsize;
	int8_t ret;

	node = mBody->blockList.begin();
    while (node) {
		dsize = mBody->spkt.dlen();
        blk = (XNBlock *)node->obj();
        while ((ret = blk->onNotifyCheck(&evt, mBody->spkt.dbuf(), &dsize)) >= 0) {
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_BLOCK_NOTIFY, blk->uid(), evt, dsize);
			mBody->trans->send(&mBody->spkt);
			delay(10);

			mBody->spkt.clear();
			if (ret == 0) {
				break;
			}
			dsize = mBody->spkt.dlen();
		}
        node = node->next();
    }

	node = mBody->serverList.begin();
    while (node) {
		dsize = mBody->spkt.dlen();
        svr = (XNServer *)node->obj();
        while ((ret = svr->onNotifyCheck(&evt, mBody->spkt.dbuf(), &dsize)) >= 0) {
			mBody->spkt.set(genSNo(), XBRIDGE_ACTION_SERVER_NOTIFY, svr->uid(), evt, dsize);
			mBody->trans->send(&mBody->spkt);
			delay(10);

			mBody->spkt.clear();
			if (ret == 0) {
				break;
			}
			dsize = mBody->spkt.dlen();
		}
        node = node->next();
    }
}
#endif	// XBRIDGE_SUPPORT_NOTIFY