#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* Biblioteki z strukturami oraz potrzebnymi funckjami */
#include<netdb.h>
#include<net/if.h>
#include<netinet/in.h>
#include<netinet/ip_icmp.h>
#include<netinet/icmp6.h>  
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netinet/ip6.h>
#include <netinet/ether.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
/* Wlasne struktury */
struct naglowek_igmp{
	unsigned char wersja :4;
	unsigned char typ :4;
	unsigned char nieuzywany;
	unsigned short kontrol;
	unsigned char ip_1;
	unsigned char ip_2;
	unsigned char ip_3;
	unsigned char ip_4;
};
struct naglowek_rip{
	unsigned char polecenie;
	unsigned char wersja;
	unsigned short pole_zero_1;
	unsigned short rodzina;
	unsigned short pole_zero_2;
	unsigned char ip_1;
	unsigned char ip_2;
	unsigned char ip_3;
	unsigned char ip_4;
	unsigned int pole_zero_3;
	unsigned int pole_zero_4;
	unsigned int metryka;
};
struct naglowek_dns{
    unsigned short id; /* identyfikator */
    unsigned char qr :1; /* zapyatnie = 1 || odpowiedz = 0 */
	unsigned char opcode :4; /* typ zapytania (standardowe,odwrotne,zadanie stanu serwera, 3-15 = rezerwacja na przyszlosc */
    unsigned char aa :1; /* wiarygodnosc */
    unsigned char tc :1; /* czy obcieta wiadomosc */
    unsigned char rd :1; /* czy rekursja */
    unsigned char ra :1; /* rekursja wymagana */
	unsigned char z :3; /* rezerwacja */
	unsigned char rcode :4; /* kod odpowiedzi */    
    unsigned short q_count; /* liczba wpisow pytan */
    unsigned short ans_count; /* liczba pozycji odpowiedzi */
    unsigned short auth_count; /* liczba wpisow uprawnien */
    unsigned short add_count; /* liczba dodatkowych rekordow */
};
struct naglowek_dhcp{
    unsigned char operacja;
	unsigned char sprzet;
	unsigned char dlugosc;
	unsigned char skoki;
	unsigned int xid;
	unsigned short sekundy;
	unsigned short flagi;
	unsigned char klient_1;
	unsigned char klient_2;
	unsigned char klient_3;
	unsigned char klient_4;
	unsigned char przydzielony_1;
	unsigned char przydzielony_2;
	unsigned char przydzielony_3;
	unsigned char przydzielony_4;
	unsigned char serwer_1;
	unsigned char serwer_2;
	unsigned char serwer_3;
	unsigned char serwer_4;
	unsigned char router_1;
	unsigned char router_2;
	unsigned char router_3;
	unsigned char router_4;
	/* Adress mac klienta */
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char e;
	unsigned char f;
	unsigned char g;
	unsigned char h;
	unsigned char serwer[64];
	unsigned char startowy[128];
	unsigned char producent;
};
/* Funckje do wypisywania */
/* Dzialanie wedlug warstw */
/* ----------------------------------------------- */
void sprawdz_typ(char *napis, int rozmiar);
void wypisz_arp(char *napis, int rozmiar);
/* ----------------------------------------------- */
void wypisz_ip4(char *napis, int rozmiar);
void wypisz_ip6(char *napis, int rozmiar);
/* ----------------------------------------------- */
void pakiet_tcp(char *napis, int rozmiar);
void pakiet_udp(char *napis, int rozmiar);
void pakiet_icmp4(char *napis, int rozmiar);
void pakiet_icmp6(char *napis, int rozmiar);
void pakiet_igmp(char *napis, int rozmiar);
/* ----------------------------------------------- */
void wypisz(char *napis, int rozmiar);
void wypisz_dns(char *napis, int rozmiar);
void wypisz_rip(char *napis, int rozmiar);
void wypisz_dhcp(char *napis, int rozmiar);
void wypisz_aplikacje(char *napis, int port_zrodlo, int port_docelowy, int rozmiar);
/* ----------------------------------------------- */
static inline struct sockaddr_in PodajAdres(u_int32_t _adres) {
    struct sockaddr_in adres;
    memset(&adres, 0, sizeof(adres));
    adres.sin_addr.s_addr = _adres;
    return adres;
}
int main(){
	/* Ustawiamy pierw karte sieciowa na promisc */
    int rozmiar_adresu, wartosc;
    struct sockaddr adres_sieci;
     char *napis = ( char *) malloc(1 << 16);
    int moj_soket;
	
	moj_soket = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    if(moj_soket < 0)
    {
        printf("Blad socketu!\n");
        return 1;
    }
    while(1)
    {
        rozmiar_adresu = sizeof adres_sieci;
        /* Przechwytujemy pakiet */
        wartosc = recvfrom(moj_soket , napis , 1 << 16 , 0 , &adres_sieci , (socklen_t*)&rozmiar_adresu);
        if(wartosc < 0)
        {
            printf("Blad przechwytywania\n");
            return 1;
        }
        /* sprawdzamy inforamcje o przechwyconym pakiecie */
        sprawdz_typ(napis , wartosc);
    }
    close(moj_soket);
    return 0;
}
void sprawdz_typ(char *napis, int rozmiar){
	/* Pobieramy informacje o typie */
    struct ethhdr *naglowek = (struct ethhdr*) napis;
    
	printf("\n+----------------------------------------+\n");
	printf("| Adres docelowy MAC : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X |\n", naglowek->h_dest[0] , naglowek->h_dest[1] , naglowek->h_dest[2] , naglowek->h_dest[3] , naglowek->h_dest[4] , naglowek->h_dest[5] );
	printf("| Adres zrodlowy MAC : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X |\n", naglowek->h_source[0] , naglowek->h_source[1] , naglowek->h_source[2] , naglowek->h_source[3] , naglowek->h_source[4] , naglowek->h_source[5] );
	printf("+----------------------------------------+\n");
	/* Sprawdzamy co przechwycilismy */
	switch (ntohs(naglowek->h_proto)) {
        case ETH_P_IP:
            printf("||| IP v4 |||\n");
            wypisz_ip4(napis + sizeof(struct ethhdr), rozmiar);
            break;
        case ETH_P_IPV6:
            printf("||| IP v6 |||\n");
            wypisz_ip6(napis + sizeof(struct ethhdr), rozmiar);
            break;
        case ETH_P_ARP:
            printf("||| ARP |||\n");
            wypisz_arp(napis + sizeof(struct ethhdr), rozmiar);
            break;
        default:
            printf("Nieznany EtherType : %d\n", ntohs(naglowek->h_proto));
    }
}
void wypisz_arp(char *napis, int rozmiar) {
	struct ether_arp *arp = (struct ether_arp *) napis;
	union {
        u_int8_t ip[4];
        u_int32_t ip2;
    } arp_ip;
	int i;
	
    printf(" + Typ sprzetu : %u\n", ntohs(arp->arp_hrd));
    printf(" + Typ protokolu : 0x%04x\n", ntohs(arp->arp_pro));
    printf(" + Dlugosc adresu sprzetowego : %u\n", arp->arp_hln);
    printf(" + Dlugosc adresu protokolu : %u\n", arp->arp_pln);
    printf(" + Operacja : %u\n", ntohs(arp->arp_op));
    printf(" + Adres sprzetu nadawcy : %s\n", ether_ntoa((struct ether_addr *) arp->arp_sha));
    for (i = 0; i < 4; i++)
        arp_ip.ip[i] = arp->arp_spa[i];
    printf(" + Adres protokolu nadawcy : %s\n", inet_ntoa(PodajAdres(arp_ip.ip2).sin_addr));
    printf(" + Adres sprzetu odbiorcy : %s\n", ether_ntoa((struct ether_addr *) arp->arp_tha));
    for (i = 0; i < 4; i++)
        arp_ip.ip[i] = arp->arp_tpa[i];
    printf(" + Adres protokolu odbiorcy : %s\n", inet_ntoa(PodajAdres(arp_ip.ip2).sin_addr));
}
void wypisz_ip6(char *napis, int rozmiar) {
    struct ip6_hdr *pakiet = (struct ip6_hdr *) (napis);
	char wiadomosc[INET6_ADDRSTRLEN];
	
    printf(" + Wersja: %u\n", (ntohl(pakiet->ip6_flow) & 0xf0000000) >> 28);
    printf(" + Klasa ruchu : %u\n", (ntohl(pakiet->ip6_flow) & 0xff00000) >> 20);
    printf(" + Etykieta przeplywu : %u\n", ntohl(pakiet->ip6_flow) & 0xfffff);
    printf(" + Dlugosc danych : %u\n", ntohs(pakiet->ip6_plen));
    printf(" + Nastepny naglowek: %u\n", pakiet->ip6_nxt);
    printf(" + Limit HOP : %u\n", pakiet->ip6_hops);
    inet_ntop(AF_INET6, &(pakiet->ip6_src), wiadomosc, INET6_ADDRSTRLEN);
    printf(" + Adres zrodla : %s\n", wiadomosc);
    inet_ntop(AF_INET6, &(pakiet->ip6_dst), wiadomosc, INET6_ADDRSTRLEN);
    printf(" + Adres docelowy : %s\n", wiadomosc);


    switch (pakiet->ip6_nxt) {
        case IPPROTO_TCP:
            printf("*** TCP ***\n");
            pakiet_tcp(napis + sizeof(struct ip6_hdr), ntohs(pakiet->ip6_plen));
            break;
        case IPPROTO_UDP:
            printf("*** UDP ***\n");
            pakiet_udp(napis + sizeof(struct ip6_hdr), ntohs(pakiet->ip6_plen));
            break;
        case IPPROTO_ICMPV6:
            printf("*** ICMP v6 ***\n");
            pakiet_icmp6(napis + sizeof(struct ip6_hdr), rozmiar);
            break;
        default:
            printf("Nieznany protokol nr : %d\n", pakiet->ip6_nxt);
    }
}
void wypisz_ip4(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct iphdr *naglowek = (struct iphdr *) napis;
	
    printf(" + Wersja IP : %d\n", (unsigned int)naglowek->version);
	printf(" + Protokol : %d\n", (unsigned int)naglowek->protocol);
	printf(" + Identyfikator : %d\n", ntohs(naglowek->id));
    printf(" + Dlugosc naglowka : %d bajtow\n", ((unsigned int)(naglowek->ihl)) * 4);
	printf(" + Max czas zycia : %d\n", (unsigned int)naglowek->ttl);
	printf(" + Suma kontorlna : %d\n", ntohs(naglowek->check));
    printf(" + Max rozmiar pakietu : %d bajtow\n", ntohs(naglowek->tot_len));
    printf(" + Typ uslugi : %d\n", (unsigned int)naglowek->tos);
	printf(" + Odsuniecie fragmentu:  %#x\n", ntohs(naglowek->frag_off) & IP_OFFMASK);
	printf(" + Flagi:\n");
    printf(" + RF: %u\n", (ntohs(naglowek->frag_off) & IP_RF) != 0);
    printf(" + DF: %u\n", (ntohs(naglowek->frag_off) & IP_DF) != 0);
    printf(" + MF: %u\n", (ntohs(naglowek->frag_off) & IP_MF) != 0);
    printf(" <> Zrodlowe IP : %s\n", inet_ntoa(PodajAdres(naglowek->saddr).sin_addr));
    printf(" <> Docelowe IP : %s\n", inet_ntoa(PodajAdres(naglowek->daddr).sin_addr));
	
	switch (naglowek->protocol) {
        case IPPROTO_TCP:
            printf("*** TCP ***\n");
            pakiet_tcp(napis + (naglowek->ihl * 4), ntohs(naglowek->tot_len) - naglowek->ihl * 4);
            break;
        case IPPROTO_UDP:
            printf("*** UDP ***\n");
            pakiet_udp(napis + (naglowek->ihl * 4), ntohs(naglowek->tot_len) - naglowek->ihl * 4);
            break;
        case IPPROTO_ICMP:
            printf("*** ICMP ***\n");
            pakiet_icmp4(napis + (naglowek->ihl * 4), rozmiar);
            break;
		case 2:
            printf("*** IGMP ***\n");
            pakiet_igmp(napis + (naglowek->ihl * 4), rozmiar);
            break;
        default:
            printf("Nieznany protocol nr: %d\n", naglowek->protocol);
    }
	
}
void pakiet_icmp4(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct icmphdr *naglowek_icmp = (struct icmphdr *) napis;
    printf(" * Typ : %d\n",(unsigned int)(naglowek_icmp->type));
    printf(" * Kod : %d\n", (unsigned int)(naglowek_icmp->code));
    printf(" * Suma kontrolna : %d\n", ntohs(naglowek_icmp->checksum));
}
void pakiet_igmp(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct naglowek_igmp *igmp = (struct naglowek_igmp *) napis;
	union {
        u_int8_t ip[4];
        u_int32_t ip2;
    } igmp_ip;
    printf(" * Wersja : %d\n",ntohs(igmp->wersja));
    printf(" * Typ : %d\n", ntohs(igmp->typ));
    printf(" * Suma kontrolna : %d\n", ntohs(igmp->kontrol));
	igmp_ip.ip[0] = igmp->ip_1;
	igmp_ip.ip[1] = igmp->ip_2;
	igmp_ip.ip[2] = igmp->ip_3;
	igmp_ip.ip[3] = igmp->ip_4;
	printf("Adres : %s\n", inet_ntoa(PodajAdres(igmp_ip.ip2).sin_addr));
}
void pakiet_icmp6(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct icmp6_hdr *naglowek_icmp = (struct icmp6_hdr *) napis;
    printf(" * Typ : %d\n",(unsigned int)(naglowek_icmp->icmp6_type));
    printf(" * Kod : %d\n", (unsigned int)(naglowek_icmp->icmp6_code));
    printf(" * Suma kontrolna : %d\n", ntohs(naglowek_icmp->icmp6_cksum));
}
void pakiet_udp(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct udphdr *naglowek_udp = (struct udphdr*) napis;
    printf(" * Port zrodlowy: %u\n" , ntohs(naglowek_udp->source));
    printf(" * Port docelowy : %u\n" , ntohs(naglowek_udp->dest));
    printf(" * Dlugosc naglowka : %d\n" , ntohs(naglowek_udp->len));
    printf(" * Suma kontorlna : %d\n" , ntohs(naglowek_udp->check));
    
	wypisz_aplikacje(napis + sizeof(struct udphdr), ntohs(naglowek_udp->source), ntohs(naglowek_udp->dest), rozmiar);
}
void pakiet_tcp(char *napis, int rozmiar){
	/* Tworzymy odpowiednie struktury */
    struct tcphdr *naglowek_tcp = (struct tcphdr*) napis;
    printf(" * Port zrodlowy: %u\n", ntohs(naglowek_tcp->source));
    printf(" * Port docelowy : %u\n", ntohs(naglowek_tcp->dest));
	printf(" * Dlugosc naglowka : %d bajtow\n", (unsigned int)naglowek_tcp->doff * 4);
	printf(" * Rozmiar okna : %d\n", ntohs(naglowek_tcp->window));
    printf(" * Suma kontorlna : %d\n", ntohs(naglowek_tcp->check));
    printf(" * Wskaznik priorytetu : %d\n", naglowek_tcp->urg_ptr);
    printf(" * Numer sekwencyjny : %u\n", ntohl(naglowek_tcp->seq));
    printf(" * Numer przyznany : %u\n", ntohl(naglowek_tcp->ack_seq));
	/* Zawarte w strukturze jako unia (niedostepne )*/
    /* printf(" * Flaga CWR : %d\n", (unsigned int)naglowek_tcp->cwr); */
    /* printf(" * Flaga ECN : %d\n", (unsigned int)naglowek_tcp->ece); */
    printf(" * Flaga priorytetu : %d\n", (unsigned int)naglowek_tcp->urg);
    printf(" * Flaga przyznania : %d\n", (unsigned int)naglowek_tcp->ack);
    printf(" * Flaga wysylania : %d\n", (unsigned int)naglowek_tcp->psh);
    printf(" * Flaga resetu : %d\n", (unsigned int)naglowek_tcp->rst);
    printf(" * Flaga synchronizacji : %d\n", (unsigned int)naglowek_tcp->syn);
    printf(" * Flaga konca : %d\n", (unsigned int)naglowek_tcp->fin);
	
	wypisz_aplikacje(napis + (4 * naglowek_tcp->doff), ntohs(naglowek_tcp->source), ntohs(naglowek_tcp->dest), rozmiar - (4 * naglowek_tcp->doff));                  
}
void wypisz(char *napis , int rozmiar){
    for(int i = 0 ; i < rozmiar ; i++)
		printf("%c",(unsigned char)napis[i]);
	printf("\n");
}
void wypisz_aplikacje(char *napis, int port_zrodlo, int port_docelowy, int rozmiar) {
    int port;
	if(port_docelowy > port_zrodlo){
		port = port_zrodlo;
	} else {
		port = port_docelowy;
	}
    switch (port) {
        case 7:
            wypisz(napis, rozmiar);
            break;
        case 20:
            printf("::: FTP :::\n");
            break;
        case 21:
            printf("::: FTP :::\n");
            break;
        case 22:
            printf("::: SSH :::\n");
            break;
        case 23:
            printf("::: TELNET :::\n");
            wypisz(napis, rozmiar);
            break;
		case 25:
		/* Niezalecany */
            printf("::: SMTP :::\n");
            break;
        case 53:
            printf("::: DNS :::\n");
            wypisz_dns(napis, rozmiar);
            break;
        case 67:
            printf("::: DHCP :::\n");
			wypisz_dhcp(napis, rozmiar);
            break;
        case 68:
            printf("::: DHCP :::\n");
			wypisz_dhcp(napis, rozmiar);
            break;
        case 80:
            printf("::: HTTP :::\n");
            wypisz(napis, rozmiar);
            break;
		case 110:
            printf("::: POP3 :::\n");
            break;
		case 119:
            printf("::: NNTP :::\n");
            break;
		case 123:
            printf("::: NTP :::\n");
            break;
		case 137:
            printf("::: SMB :::\n");
            break;
		case 138:
            printf("::: SMB :::\n");
            break;
		case 139:
            printf("::: SMB :::\n");
            break;
		case 143:
            printf("::: IMAP :::\n");
            break;
		case 161:
            printf("::: SNMP :::\n");
            break;
		case 179:
            printf("::: BGP :::\n");
            break;
		case 389:
            printf("::: LDAP :::\n");
            break;
		case 433:
            printf("::: NNSP :::\n");
            break;
        case 443:
            printf("::: HTTPS :::\n");
			break;
		case 520:
            printf("::: RIP :::\n");
			wypisz_rip(napis, rozmiar);
            break;
		case 546:
            printf("::: DHCPv6 :::\n");
			wypisz_dhcp(napis, rozmiar);
            break;
        case 547:
            printf("::: DHCPv6 :::\n");
			break;
		case 563:
            printf("::: TLS :::\n");
            break;
		case 587:
            printf("::: SMTP :::\n");
            break;
		case 2049:
            printf("::: NFS :::\n");
            break;
		case 2427:
            printf("::: MGCP :::\n");
            break;
        default:
            printf("Nieznany protocol nr : %d\n", port);
    }
}
void wypisz_dns(char *napis, int rozmiar){
    /* Tworzymy odpowiednie struktury */
	struct naglowek_dns *dns = (struct naglowek_dns *) napis;
    printf(" # Identyfikator : %u\n", ntohs(dns->id));
    printf(" # Rodzaj : %s\n", dns->qr == 0 ? "pytanie" : "odpowiedz");
    printf(" # Rodzaj zapytania : %u\n", nhtos(dns->opcode));
    printf(" # Autorytatywna odpowiedz : %u\n", dns->aa);
	printf(" # Zarezerwowana : %u\n", dns->z);
    printf(" # Ucieta wiadomosc : %u\n", dns->tc);
    printf(" # Rekursja dostepna: %u\n", dns->rd);
    printf(" # Rekursja wymagana : %u\n", dns->ra);
    printf(" # Kod odpowiedzi : %u\n", ntohs(dns->rcode));
    printf(" # Liczba zapytan : %u\n", ntohs(dns->q_count));
    printf(" # Liczba odpowiedzi : %u\n", ntohs(dns->ans_count));
    printf(" # Liczba wpisow uprawnien : %u\n", ntohs(dns->auth_count));
    printf(" # Liczba dodatkowych rekordow : %u\n", ntohs(dns->add_count));
}
void wypisz_dhcp(char *napis, int rozmiar){
	struct naglowek_dhcp *dhcp = (struct naglowek_dhcp *) napis;
	union {
        u_int8_t ip[4];
        u_int32_t ip2;
    } dhcp_ip;
    printf(" # Operacja : %s\n", ntohs(dhcp->operacja) == 1 ? "BOOTREQUEST" : (ntohs(dhcp->operacja) == 2 ? "BOOTREPLY" : "nieznana"));
    printf(" # Typ sprzetu : %u\n",ntohs(dhcp->sprzet));
	printf(" # Dlugosc adresu sprzetowego : %u\n",ntohs(dhcp->dlugosc));
	printf(" # Liczba skokow : %u\n",ntohs(dhcp->skoki));
	printf(" # Identyfikator transakcji : %u\n",ntohs(dhcp->xid));
	printf(" # Liczba sekund : %u\n",ntohs(dhcp->sekundy));
	printf(" # Flaga BROADCAST : %s\n",(ntohs(dhcp->flagi) & 1) ? "TAK" : "NIE");
	dhcp_ip.ip[0] = dhcp->klient_1;
	dhcp_ip.ip[1] = dhcp->klient_2;
	dhcp_ip.ip[2] = dhcp->klient_3;
	dhcp_ip.ip[3] = dhcp->klient_4;
	printf(" # Adres klienta : %s\n", inet_ntoa(PodajAdres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->przydzielony_1;
	dhcp_ip.ip[1] = dhcp->przydzielony_2;
	dhcp_ip.ip[2] = dhcp->przydzielony_3;
	dhcp_ip.ip[3] = dhcp->przydzielony_4;
	printf(" # Adres przydzielony : %s\n", inet_ntoa(PodajAdres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->serwer_1;
	dhcp_ip.ip[1] = dhcp->serwer_2;
	dhcp_ip.ip[2] = dhcp->serwer_3;
	dhcp_ip.ip[3] = dhcp->serwer_4;
	printf(" # Adres serwera : %s\n", inet_ntoa(PodajAdres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->router_1;
	dhcp_ip.ip[1] = dhcp->router_2;
	dhcp_ip.ip[2] = dhcp->router_3;
	dhcp_ip.ip[3] = dhcp->router_4;
	printf(" # Adres routera : %s\n", inet_ntoa(PodajAdres(dhcp_ip.ip2).sin_addr));
	printf(" # Adres MAC klienta : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", ntohs(dhcp->a), ntohs(dhcp->b), ntohs(dhcp->c), ntohs(dhcp->d), ntohs(dhcp->e), ntohs(dhcp->f), ntohs(dhcp->g), ntohs(dhcp->h));
	printf(" # Nazwa serwera : %s\n", dhcp->serwer);
	printf(" # Plik startowy : %s\n", dhcp->startowy);
	printf(" # Opcje producenta : %u\n", ntohl(dhcp->producent));
	
}
void wypisz_rip(char *napis, int rozmiar){
	struct naglowek_rip *rip = (struct naglowek_rip *) napis;
	union {
        u_int8_t ip[4];
        u_int32_t ip2;
    } rip_ip;
    printf(" # Polecenie : %u\n", ntohs(rip->polecenie));
    printf(" # Wersja : %u\n",ntohs(rip->wersja));
	printf(" # Identyfikator rodziny adresow (AFI) : %u\n",ntohs(rip->rodzina));
	rip_ip.ip[0] = rip->ip_1;
	rip_ip.ip[1] = rip->ip_2;
	rip_ip.ip[2] = rip->ip_3;
	rip_ip.ip[3] = rip->ip_4;
	printf(" # Adres : %s\n", inet_ntoa(PodajAdres(rip_ip.ip2).sin_addr));
	printf(" # Metryka : %u\n", ntohs(rip->metryka));
}
