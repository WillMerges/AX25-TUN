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
#ifndef TUN_H
#define TUN_H

/// @brief open a TUN device
/// @param dev_name     the name of the TUN device
/// @return the file descriptor interfacing with the device, or -1 on error
/// NOTE: reference https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/networking/tuntap.rst?id=HEAD
int tun_open(char* dev_name);

/// @brief set the MTU of a TUN network device
/// @param dev_name  the name of the TUN network device
/// @param fd        the file descriptor interfacing with the device
/// @param mtu       the new maximum transmit unit for the device, in bytes
/// @return 0 on success, or -1 on error
// int tun_set_mtu(char* dev_name, int fd, size_t mtu);

#endif
