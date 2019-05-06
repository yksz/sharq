#include "sharq.h"

/*
 * MEMO:
 * - ACK/NACKはqueueに入れずすぐに送信する
 * - 受信中に送信処理は割り込めない
 * - 受信時の処理
 *   1. DATAを受信したらACK or NACKを送信する
 *   2. ACKを受信したら送信queueの先頭を消す
 *   3. NACKを受信したら送信queueの先頭を再送する
 * - 送信時の処理
 *   1. DATAはqueueに入れてから送信する
 *   2. ACK/NACKはqueueに入れずに送信する
 *   3. 再送時は先頭queueのみ再送する
 *   4. 一定回数リトライする
 */

/*
 *
 * Acknowledge of frames:
 * A ----> B   DATA [Seq No = 1]
 * A <---- B   DATA [Seq No = 4]
 * A <---- B    ACK [Seq No = 2]
 * A ----> B    ACK [Seq No = 5]
 * 
 * Negative acknowledge of frame:
 * A ----> B   DATA [Seq No = 1]
 * A <---- B   NACK [Seq No = 1]
 * A ----> B   DATA [Seq No = 1]
 * 
 * Acknowledge frame lost:
 * A ----> B   DATA [Seq No = 1]
 * A  X<-- B    ACK [Seq No = 2]
 * *Timeout*
 * A ----> B   DATA [Seq No = 1]
 *
 */

enum {
    kMaxPacket = 1024
};

typedef enum {
    kData,
    kAck,
    kNack
} FrameType;

typedef unsigned int SeqNum;

typedef struct {
    FrameType type;
    SeqNum seq;
    unsigned char packet[kMaxPacket];
} Frame;

static void parse()
{

}

static void encode(const char* packet, size_t packetlen, Frame* frame)
{

}

static void decode(const Frame* frame, char* packet, size_t packetlen)
{

}

int Sharq_receive(Sharq* self, char* buf, size_t len)
{
    Frame frame;
    int parseResult;

    while (1) {
        parseResult = parse(&frame);
        if (parseResult != 0) {
            return parseResult;
        }

        result = parseFrame(frame);
        if (result == 0) {
            buf = frame->packet; // TODO: copy
            return frame->packetlen;
        }
    }
}

static int parseFrame(Frame* frame)
{
    switch (frame->type) {
        case kData:
            if (frame->fcsOK) {
                transmitAck(frame);
                return 0;
            }
            transmitNack(frame);
            return -1;

        case kAck:
            onTransmitOK(frame);
            return -1;

        case kNack:
            retransmit(frame);
            return -1;

        default:
            /* silently discard */
            /* TODO: provide event handler */
            return -1;
    }
}

int Sharq_transmit(Sharq* self, const char* buf, size_t len)
{
    Frame frame;

    encode(buf, len, &frame);
    return transmitFrame(&frame);
}

static int transmitFrame(Frame* frame)
{
    char bytes[512];
    int byteslen;

    toBytes(frame, bytes, byteslen);
    return sendFunc(bytes, byteslen);
}

static void transmitAck(Frame* frame)
{

}

static void transmitNack(Frame* frame)
{

}

static void onTransmitOK(Frame* frame)
{

}

static void retransmit(Frame* frame)
{

}
