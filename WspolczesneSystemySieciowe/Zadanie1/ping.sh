#!bin/bash
echo -e "Test polaczenia \e[44;97m Maszyna A(enp0s8): \e[0m"
ping -c 4 64.164.220.113 
echo -e "Test polaczenia \e[44;97m Maszyna B(enp0s8): \e[0m"
ping -c 4 64.164.220.114
echo -e "Test polaczenia \e[44;97m Maszyna B(enp0s9): \e[0m"
ping -c 4 64.164.220.65
echo -e "Test polaczenia \e[44;97m Maszyna C(enp0s8): \e[0m"
ping -c 4 64.164.220.66
echo -e "Test polaczenia \e[44;97m Maszyna C(enp0s9): \e[0m"
ping -c 4 64.164.220.225
echo -e "Test polaczenia \e[44;97m Maszyna D(enp0s8): \e[0m"
ping -c 4 64.164.220.226