#ifndef __LISTA__
#define __LISTA__
#include "ask2.h"

typedef struct info_node * info_deikti;
typedef struct typos_komvou * typos_deikti;

info_deikti LIST_dimiourgia(info_deikti*);
void eisagogi(info_deikti* linfo,int number,mystruct *ref);
void emfanisi(info_deikti* linfo);
void lista_diagrafi(info_deikti* linfo);
mystruct * anazitisi(info_deikti* linfo, int);

#endif
