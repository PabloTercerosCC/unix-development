#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MSGSIZE 256

int main()
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MSGSIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSGSIZE;
    attr.mq_curmsgs = 0;

    mq_unlink("/test_queue");
    mq = mq_open("/test_queue", O_CREAT | O_RDWR, 0666, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    while (1) {
        printf("Enter message to send (or 'exit' to quit): ");
        fgets(buffer, MSGSIZE, stdin);
        if (mq_send(mq, buffer, strlen(buffer)+1, 0) == -1) {
            perror("mq_send");
            exit(1);
        }
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    mq_close(mq);
    return 0;
}
