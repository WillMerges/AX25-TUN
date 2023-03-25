#!/bin/bash

# Creates a TUN interface

if [ "$#" -ne 2 ]; then
    echo "Usage: ./create_tun.sh (interface_name) (address)"
    echo "  Create a TUN device named 'interface_name' at IPv4 CIDR address/subnet 'address'"
    exit 1
fi


sudo ip tuntap add mode tun dev $1
sudo ip addr add $2 dev $1
sudo ip link set dev $1 up
