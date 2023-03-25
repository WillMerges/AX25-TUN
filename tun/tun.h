#ifndef TUN_H
#define TUN_H

/// @brief open a TUN device
/// @param dev_name     the name of the TUN device
/// @return the file descriptor to the device, or -1 on error
/// NOTE: generate off of https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/networking/tuntap.rst?id=HEAD
int tun_open(char* dev_name);

/// TODO
/// int set_mtu(int fd);

#endif
