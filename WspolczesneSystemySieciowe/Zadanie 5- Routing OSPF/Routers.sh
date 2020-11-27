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
router ospf
 network 64.164.220.32/28 area 0

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
router ospf
 network 64.164.220.32/28 area 0
 network 64.164.220.112/28 area 1
 network 64.164.220.192/29 area 5

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
router ospf
 network 64.164.220.112/28 area 1
 network 64.164.220.64/28 area 2
 network 64.164.220.248/29 area 4

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
router ospf
 network 64.164.220.32/28 area 0
 network 64.164.220.64/28 area 2
 network 64.164.220.224/29 area 3
