#Potrzebna pakiety
apt-get install make gcc protobuf-compiler gawk texinfo pkg-config
apt-get install autoconf libtool libreadline-dev libc-ares-dev git
#Przygotowanie Quaggi
git clone git://git.savannah.nongnu.org/quagga.git
cd quagga
./bootstrap.sh
./configure
#Kompilacja
make
make install
#Dodanie sciezki
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
cat SERVICES >> /etc/services
#Uruchomienie zebry
zebra -d -u root

telnet localhost 2601
vtysh
#	
#	?
#	list
#	show interface
#	show ip route
#
