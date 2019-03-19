//File: lista.c
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

 typedef struct info_node{
 	int size;
	typos_deikti arxi;
	typos_deikti telos;
 }info_node;


 typedef struct typos_komvou{
 	int page_num;
	mystruct *p;
	typos_deikti epomenos;
	typos_deikti proigoumenos;
 }typos_komvou;



 info_deikti LIST_dimiourgia(info_deikti* lista){

 	info_deikti linfo;
 	linfo = malloc(sizeof(info_node));
 	linfo->size = 0;
 	linfo->arxi = NULL;
	linfo->telos = NULL;
 	return linfo;
 }



 void eisagogi(info_deikti* linfo,int number, mystruct *ref){

 	typos_deikti prosorinos;
 	prosorinos = malloc(sizeof(typos_komvou));
 	prosorinos->page_num = number;
	prosorinos->p = ref;

	if((*linfo)->size == 0){
 		(*linfo)->arxi = prosorinos;
		(*linfo)->telos = prosorinos;
		prosorinos->epomenos = NULL;
		prosorinos->proigoumenos = NULL;
 	}
 	if((*linfo)->size > 0){
		prosorinos->proigoumenos = (*linfo)->telos;
		prosorinos->epomenos = NULL;
 		(*linfo)->telos->epomenos = prosorinos;
		(*linfo)->telos = prosorinos;
 	}
 	(*linfo)->size++;
 }

 // for debug
 void emfanisi(info_deikti* linfo){

	typos_deikti mapas = (*linfo)->arxi;
	printf(" \n ");
 	while(mapas != NULL){
 		printf("%08x\n", mapas->page_num);
		mapas = mapas->epomenos;
 	}
 }


 void lista_diagrafi(info_deikti* linfo){

 	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;
 	while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		free(mapas2);
	}
	(*linfo)->arxi = NULL;
	(*linfo)->telos = NULL;
	(*linfo)->size = 0;
	return;
 }

 mystruct * anazitisi(info_deikti* linfo, int stoixeio){

	typos_deikti mapas = (*linfo)->arxi;
	if(mapas == NULL) return NULL;

	while(1){
		unsigned int k = mapas->page_num;
		if(k == stoixeio) { return mapas->p; }
		mapas = mapas->epomenos;
		if(mapas == NULL) break;
	}

	return NULL;
 }
