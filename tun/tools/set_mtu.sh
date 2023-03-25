#!/bin/bash

# Set the MTU of a TUN interface

if [ "$#" -ne 2 ]; then
    echo "Usage: ./set_mtu.sh (interface_name) (MTU)"
    echo "  Set the MTU of the TUN device named 'interface_name'"
    exit 1
fi

sudo ip link set dev $1 mtu $2
