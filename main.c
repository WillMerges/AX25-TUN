#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tun/tun.h"
#include "kiss/kiss.h"

// direwolf virtual TNC port
#define TNC_PORT 8001
#define TNC_ADDR "127.0.0.1"

int main(char* argv[]) {
    int tun_fd = tun_open("ax0");

    if(-1 == tun_fd) {
        exit(errno);
    }

    // // pretend this an ethernet frame
    // uint8_t buff[1500];
    //
    // ssize_t len;
    // while(1) {
    //     len = read(tun_fd, (void*)buff, 1500);
    //
    //     printf("read %lu bytes from TUN device\n", len);
    //     for(ssize_t i = 0; i < len; i++) {
    //         printf("%02x ", buff[i]);
    //     }
    //     printf("\n");
    // }

    uint8_t pay[16] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb,
                      0xc, 0xd, 0xd, 0xf};
    uint8_t frame[32 + 3]; // max of 2n + 3

    ssize_t sz = gen_kiss_frame(pay, 16, frame, 32 + 3);

    if(sz < 0) {
        printf("error generating KISS frame\n");
        exit(1);
    }

    printf("kiss frame of size %li\n", sz);

    int tnc_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == tnc_fd) {
        perror("failed to create TNC socket");
        exit(errno);
    }

    struct sockaddr_in tnc_addr;
    tnc_addr.sin_family = AF_INET;
    tnc_addr.sin_port = htons(TNC_PORT);
    tnc_addr.sin_addr.s_addr = inet_addr(TNC_ADDR);

    if(-1 == connect(tnc_fd, (struct sockaddr*)&tnc_addr, sizeof(tnc_addr))) {
        perror("failed to connect to TNC address");
        exit(errno);
    }

    while(1) {
        send(tnc_fd, (void*)frame, sz, 0);
        usleep(1000000);
    }
}
