hostname R0
interface lo0
 ip address 127.0.0.1/8
 ipv6 address ::1/128
!
interface eth0
!
 ip address 64.164.220.35/28
 no shutdown
!
ip route 64.164.220.112/28 64.164.220.33
ip route 64.164.220.64/28 64.164.220.34
ip route 64.164.220.224/29 64.164.220.34
ip route 64.164.220.248/29 64.164.220.33
ip route 64.164.220.192/29 64.164.220.33

############################################

hostname R1
interface lo0
 ip address 127.0.0.1/8
 ipv6 address ::1/128
!
interface eth0
 ip address 64.164.220.33/28
 no shutdown
!
interface eth1
 ip address 64.164.220.113/28
 no shutdown
!
interface eth2
 ip address 64.164.220.193/29
 no shutdown
!
ip route 64.164.220.64/28 64.164.220.34
ip route 64.164.220.224/29 64.164.220.34
ip route 64.164.220.248/29 64.164.220.114

############################################

hostname R2
interface lo0
 ip address 127.0.0.1/8
 ipv6 address ::1/128
!
interface eth0
 ip address 64.164.220.114/28
 no shutdown
!
interface eth1
 ip address 64.164.220.65/28
 no shutdown
!
interface eth2
 ip address 64.164.220.249/29
 no shutdown
!
ip route 64.164.220.32/28 64.164.220.66
ip route 64.164.220.224/29 64.164.220.66
ip route 64.164.220.192/29 64.164.220.113

############################################

hostname R3
interface lo0
 ip address 127.0.0.1/8
 ipv6 address ::1/128
!
interface eth0
 ip address 64.164.220.34/28
 no shutdown
!
interface eth1
 ip address 64.164.220.66/28
 no shutdown
!
interface eth2
 ip address 64.164.220.225/29
 no shutdown
!
ip route 64.164.220.112/28 64.164.220.65
ip route 64.164.220.248/29 64.164.220.65
ip route 64.164.220.192/29 64.164.220.33
