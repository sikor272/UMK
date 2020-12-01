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
router bgp 65004
 bgp router-id r0
 redistribute connected
 neighbor 64.164.220.33 remote-as 65001
 neighbor 64.164.220.34 remote-as 65003

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
router bgp 65001
 bgp router-id r1
 redistribute connected
 neighbor 64.164.220.34 remote-as 65003
 neighbor 64.164.220.35 remote-as 65004
 neighbor 64.164.220.114 remote-as 65002

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
router bgp 65002
 bgp router-id r2
 redistribute connected
 neighbor 64.164.220.113 remote-as 65001
 neighbor 64.164.220.66 remote-as 65003

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
router bgp 65003
 bgp router-id r3
 redistribute connected
 neighbor 64.164.220.65 remote-as 65002
 neighbor 64.164.220.33 remote-as 65001
 neighbor 64.164.220.35 remote-as 65004