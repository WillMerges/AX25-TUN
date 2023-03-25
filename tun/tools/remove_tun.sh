#!/bin/bash

# Removed a TUN interface

if [ "$#" -ne 1 ]; then
    echo "Usage: ./remove_tun.sh (interface_name)"
    echo "  Remove the TUn device named 'interface_name'"
    exit 1
fi

sudo ip link del $1
