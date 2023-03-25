/*******************************************************************************
*
*  Name: tun.c
*
*  Purpose: Interfaces with a TUN device. The TUN kernel module allows for
*           creating network interfaces where the operation is implemented in
*           user space, essentially making virtual network interfaces.
*           TUN operates on the IPv4 protocol (layer 3).
*
*  Author: Will Merges
*
*******************************************************************************/
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
/// NOTE: reference https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/networking/tuntap.rst?id=HEAD
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

    if(ioctl(fd, TUNSETIFF, (void*)&ifr) < 0) {
        perror("Failed ioctl TUNSETIFF call");
        close(fd);
        return -1;
    }

    return fd;
}

/// @brief set the MTU of a TUN network device
/// @param dev_name  the name of the TUN network device
/// @param fd        the file descriptor interfacing with the device
/// @param mtu       the new maximum transmit unit for the device, in bytes
/// @return 0 on success, or -1 on error
// int tun_set_mtu(char* dev_name, int fd, size_t mtu) {
//     struct ifreq ifr;
//
//     ifr.ifr_addr.sa_family = AF_INET;
//     ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
//     strncpy(ifr.ifr_name, dev_name, IFNAMSIZ);
//     ifr.ifr_mtu = mtu;
//
//     if(ioctl(fd, SIOCSIFMTU, (void*)&ifr) < 0) {
//         perror("Failed ioctl SIOCSIFMTU call");
//         return -1;
//     }
//
//     return 0;
// }
