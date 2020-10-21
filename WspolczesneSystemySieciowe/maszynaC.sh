#!bin/bash
echo 1 > /proc/sys/net/ipv4/ip_forward
ip a add 64.164.220.66/28 dev enp0s8
ip a add 64.164.220.225/29 dev enp0s9
ip route add 64.164.220.112/28 via 64.164.220.65 dev enp0s8