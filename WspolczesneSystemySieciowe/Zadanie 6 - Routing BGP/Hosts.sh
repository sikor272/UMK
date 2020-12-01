hostname S3_H1
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.226/29
route add default 64.164.220.225
rpcbind
inetd

############################################

hostname S3_H2
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.227/29
route add default 64.164.220.225
rpcbind
inetd

############################################

hostname S4_H1
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.250/29
route add default 64.164.220.249
rpcbind
inetd

############################################

hostname S4_H2
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.251/29
route add default 64.164.220.249
rpcbind
inetd

############################################

hostname S5_H1
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.194/29
route add default 64.164.220.193
rpcbind
inetd

############################################

hostname S5_H2
ifconfig lo0 inet 127.0.0.1/8
ifconfig lo0 inet6 ::1/128
ifconfig eth0 inet 64.164.220.195/29
route add default 64.164.220.193
rpcbind
inetd