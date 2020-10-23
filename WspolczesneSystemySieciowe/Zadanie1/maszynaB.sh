#!bin/bash
echo 1 > /proc/sys/net/ipv4/ip_forward
ip a add 64.164.220.114/28 dev enp0s8
ip a add 64.164.220.65/28 dev enp0s9
ip route add 64.164.220.224/29 via 64.164.220.66 dev enp0s9