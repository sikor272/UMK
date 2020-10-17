#!bin/bash
echo 1 > /proc/sys/net/ipv4/ip_forward
ip a add 64.164.220.113/28 dev enp0s8
ip route add 64.164.220.64/28 via 64.164.220.114 dev enp0s8
ip route add 64.164.220.224/28 via 64.164.220.114 dev enp0s8