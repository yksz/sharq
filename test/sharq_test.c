#include "sharq.h"
#include "nanounit.h"

static char s_fifo[1024];

static int readByte()
{
}

static void writeByte()
{
}

static int test_receive(void)
{
    const char txmsg[] = "tx";
    char rxmsg[256] = {0};
    int rxbytes = -1;

    /* setup: init the library */
    sharq_init(readByte, writeByte);

    /* when: transmit a message */
    sharq_transmit(txmsg, sizeof(txmsg));

    /* then: receive the message */
    rxbytes = sharq_receive(rxmsg, sizeof(rxmsg));
    nu_assert_eq_int(sizeof(txmsg), rxbytes);
    nu_assert_eq_str(txmsg, rxmsg);

    return 0;
}

int main(int argc, char* argv[])
{
    nu_run_test(test_receive);
    nu_report();
}
