#!/usr/local/bin/bash
ROUTER="R0 R1 R2 R3 S5_H1 S5_H2 S4_H1 S4_H2 S3_H1 S3_H2"
for r in $ROUTER; do
    echo "##" $r 
        hcp super_ping.sh $r:/tmp
        himage $r bash /tmp/super_ping.sh
done
 
HOSTS="64.164.220.33 64.164.220.34 64.164.220.35 64.164.220.113 64.164.220.114 64.164.220.65 64.164.220.66 64.164.220.225 64.164.220.226 64.164.220.227 64.164.220.249 64.164.220.250 64.164.220.251 64.164.220.193 64.164.220.194 64.164.220.195"
for ip in $HOSTS; do
    PING_OUT=`ping -c 1 -W 0.5 -q $ip|grep packet | grep -v ' 0.0% packet'`
    if [ -z "$PING_OUT" ];
    then
        echo "Route to" $ip "OK"
    else
        echo "No route to" $ip
    fi
done