#include "pch.h"
#include <stdio.h>
#include<string.h>
#include<malloc.h>
//MATRICE DE ADIACENTA

struct nodStiva {
	int inf;
	nodStiva* next;
};
struct nodCoada {
	int inf;
	nodCoada* next;
};
void push(nodStiva** varf, int val) {
	nodStiva *nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

void pop(nodStiva** varf, int* val) {
	if (*varf == NULL) {
		return;
	}
	else {
		*val = (*varf)->inf;
		nodStiva* aux = *varf;//pastrez
		*varf = (*varf)->next;
		free(aux);
	}
}

void put(nodCoada **prim, nodCoada** ultim, int val) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;

	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void get(nodCoada **prim, nodCoada** ultim, int* val) {
	if (*prim != NULL && *ultim != NULL) {
		//scot de la inceput
		*val = (*prim)->inf;
		nodCoada *aux = *prim;
		*prim = (*prim)->next;
		free(aux);
	}
	if (*prim == NULL) {
		*ultim = NULL;
	}

}



int main()
{
	
	int nrNoduri = 5;
	//creez matricea
	int **mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 1; i <= nrNoduri; i++) {
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));
	}
	//umplu cu zero
	for (int i = 1; i <= nrNoduri; i++) {
		for (int j = 1; j <= nrNoduri; j++) {
			mat[i][j] = 0;
		}
	}

	//citesc nr de arce
	int nrArce=5, ii, jj;
	
	for (int i = 0; i < nrArce; i++) {
		printf("\nSursa=");
		scanf("%d", &ii);
		
		printf("\nDestinatia=");
		scanf("%d", &jj);
		 /* 1 2
			1 3
			2 4
			2 5
			3 4*/

		if (ii <= nrNoduri && jj <= nrNoduri) {
			mat[ii][jj] = 1;
			mat[jj][ii] = 1; //graf neorientat
		}
	}



	//vector de noduri vizitate:
	int* vizitat = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 1; i <= nrNoduri; i++) {
		vizitat[i] = 0;
	}

	printf("\nParcurgere in adancime de la nodul:");
	int nod;
	scanf("%d", &nod);
	nodStiva* varf = NULL;
	push(&varf, nod);
	vizitat[nod] = 1;
	while (varf != NULL) {
		pop(&varf, &nod);
		printf("%d-", nod);
		for (int k = 1; k <= nrNoduri; k++) {
			if (mat[nod][k] == 1 && vizitat[k] == 0) //exista arc intre nodul curent si alt nod k si nu a fost vizitat atunci pun pe stiva
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
		}
	}




	for (int i = 1; i <= nrNoduri; i++) {
		vizitat[i] = 0;
	}

	printf("\nParcurgere in latime de la nodul:");
	scanf("%d", &nod);
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	put(&prim, &ultim, nod);
	vizitat[nod] = 1;
	while (prim != NULL) {
		get(&prim, &ultim, &nod);
		printf("%d-", nod);
		for (int k = 1; k <= nrNoduri; k++) {
			if (mat[nod][k] == 1 && vizitat[k] == 0) //exista arc intre nodul curent si alt nod k si nu a fost vizitat atunci pun pe stiva
			{
				put(&prim, &ultim, k);
				vizitat[k] = 1;
			}
		}
	}
}




