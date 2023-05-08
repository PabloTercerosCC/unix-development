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
    char buffer[MSGSIZE];

    mq = mq_open("/test_queue", O_RDONLY);
    if (mq == -1) {    // read messagesScreenshot from 2023-05-08 16-34-49
        perror("mq_open");
        exit(1);
    }

    while (1) {
        ssize_t bytes_read = mq_receive(mq, buffer, MSGSIZE, NULL);
        if (bytes_read == -1) {
            perror("mq_receive");
            exit(1);
        }
        printf("Received message: %s", buffer);
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }
    }

    mq_close(mq);
    return 0;
}
