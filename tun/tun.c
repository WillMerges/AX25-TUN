/*
*   Interface with a TUN virtual device.
*
*   @author: Will Merges
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

/// @brief open a TUN device
/// @param dev_name     the name of the TUN device
/// @return the file descriptor to the device, or -1 on error
/// NOTE: generate off of https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/networking/tuntap.rst?id=HEAD
int tun_open(char* dev_name) {
    struct ifreq ifr;

    int fd = open("/dev/net/tun", O_RDWR);
    if(-1 == fd) {
        perror("Failed to open '/dev/net/tun'");
        return -1;
    }

    memset((void*)&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strncpy(ifr.ifr_name, dev_name, IFNAMSIZ);

    int err = ioctl(fd, TUNSETIFF, (void*)&ifr);
    if(-1 == err) {
        perror("Failed ioctl call");
        close(fd);
        return -1;
    }

    return fd;
}
