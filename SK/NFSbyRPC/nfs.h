/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _NFS_H_RPCGEN
#define _NFS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct pliczek {
	int plik;
	int pusty;
};
typedef struct pliczek pliczek;

struct polacz {
	int tryb;
	char nazwa[2048];
};
typedef struct polacz polacz;

struct pobieranie {
	int plik;
	int pozycja;
	int przesun;
};
typedef struct pobieranie pobieranie;

struct zwroc {
	int ilosc;
	char dane[2048];
};
typedef struct zwroc zwroc;

struct wyslij {
	int plik;
	char dane[2048];
};
typedef struct wyslij wyslij;

#define NFS 0x2d24ffa2
#define NFS_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define start 1
extern  pliczek * start_1(polacz *, CLIENT *);
extern  pliczek * start_1_svc(polacz *, struct svc_req *);
#define pull 2
extern  zwroc * pull_1(pobieranie *, CLIENT *);
extern  zwroc * pull_1_svc(pobieranie *, struct svc_req *);
#define push 3
extern  int * push_1(wyslij *, CLIENT *);
extern  int * push_1_svc(wyslij *, struct svc_req *);
#define koniec 4
extern  int * koniec_1(int *, CLIENT *);
extern  int * koniec_1_svc(int *, struct svc_req *);
extern int nfs_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define start 1
extern  pliczek * start_1();
extern  pliczek * start_1_svc();
#define pull 2
extern  zwroc * pull_1();
extern  zwroc * pull_1_svc();
#define push 3
extern  int * push_1();
extern  int * push_1_svc();
#define koniec 4
extern  int * koniec_1();
extern  int * koniec_1_svc();
extern int nfs_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_pliczek (XDR *, pliczek*);
extern  bool_t xdr_polacz (XDR *, polacz*);
extern  bool_t xdr_pobieranie (XDR *, pobieranie*);
extern  bool_t xdr_zwroc (XDR *, zwroc*);
extern  bool_t xdr_wyslij (XDR *, wyslij*);

#else /* K&R C */
extern bool_t xdr_pliczek ();
extern bool_t xdr_polacz ();
extern bool_t xdr_pobieranie ();
extern bool_t xdr_zwroc ();
extern bool_t xdr_wyslij ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_NFS_H_RPCGEN */
