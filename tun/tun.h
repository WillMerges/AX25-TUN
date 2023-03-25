#ifndef TUN_H
#define TUN_H

/// @brief open a TUN device
/// @param dev_name     the name of the TUN device
/// @return the file descriptor interfacing with the device, or -1 on error
/// NOTE: generate off of https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/networking/tuntap.rst?id=HEAD
int tun_open(char* dev_name);

/// TODO
/// @brief set the MTU of a network device
/// @param fd       the file descriptor interfacing with the device
/// @param mtu      the new maximum transmit unit for the device, in bytes
/// int set_mtu(int fd, size_t mtu);

#endif
