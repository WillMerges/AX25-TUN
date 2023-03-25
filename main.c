#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#include "tun/tun.h"

int main(char* argv[]) {
    int tun_fd = tun_open("ax0");

    if(-1 == tun_fd) {
        exit(errno);
    }

    // pretend this an ethernet frame
    uint8_t buff[1500];

    ssize_t len;
    while(1) {
        len = read(tun_fd, (void*)buff, 1500);

        printf("read %lu bytes from TUN device\n", len);
        for(ssize_t i = 0; i < len; i++) {
            printf("%02x ", buff[i]);
        }
        printf("\n");
    }
}
