R0:
ifconfig eth0 64.164.220.35/28
route add -net 64.164.220.112/28 64.164.220.33
route add -net 64.164.220.64/28 64.164.220.34
route add -net 64.164.220.224/29 64.164.220.34
route add -net 64.164.220.248/29 64.164.220.33
route add -net 64.164.220.192/29 64.164.220.33

R1:
ifconfig eth0 64.164.220.33/28
ifconfig eth1 64.164.220.113/28
ifconfig eth2 64.164.220.193/29
route add -net 64.164.220.64/28 64.164.220.34
route add -net 64.164.220.224/29 64.164.220.34
route add -net 64.164.220.248/29 64.164.220.114

R2:
ifconfig eth0 64.164.220.114/28
ifconfig eth1 64.164.220.65/28
ifconfig eth2 64.164.220.249/29
route add -net 64.164.220.32/28 64.164.220.66
route add -net 64.164.220.224/29 64.164.220.66
route add -net 64.164.220.192/29 64.164.220.113

R3:
ifconfig eth0 64.164.220.34/28
ifconfig eth1 64.164.220.66/28
ifconfig eth2 64.164.220.225/29
route add -net 64.164.220.112/28 64.164.220.65
route add -net 64.164.220.248/29 64.164.220.65
route add -net 64.164.220.192/29 64.164.220.33
