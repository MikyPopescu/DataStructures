#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
struct Depozit {
	int codDepozit;
	char* locatie;
	int capacitate;
	int nrCategoriiCereale;
	char** denumiriCereale;
};
struct nodArb {
	Depozit inf;
	nodArb* left, *right;
	int BF;
};
nodArb* creezNod(Depozit d, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.codDepozit = d.codDepozit;
	nou->inf.locatie = (char*)malloc((strlen(d.locatie) + 1) * sizeof(char));
	strcpy(nou->inf.locatie, d.locatie);
	nou->inf.capacitate = d.capacitate;
	nou->inf.nrCategoriiCereale = d.nrCategoriiCereale;
	nou->inf.denumiriCereale = (char**)malloc(d.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < d.nrCategoriiCereale; i++) {
		nou->inf.denumiriCereale[i] = (char*)malloc((strlen(d.denumiriCereale[i]) + 1) * sizeof(char));
		strcpy(nou->inf.denumiriCereale[i], d.denumiriCereale[i]);
	}
	nou->left = st;
	nou->right = dr;
	return nou;
}
nodArb* inserare(Depozit d, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creezNod(d, NULL, NULL);
		return aux;
	}
	else {
		while (true) {
			if (d.codDepozit < aux->inf.codDepozit) {
				if (aux->left != NULL) {
					aux = aux->left;
				}
				else {
					aux->left = creezNod(d, NULL, NULL);
					return rad;
				}
			}
			else {
				if (d.codDepozit > aux->inf.codDepozit) {
					if (aux->right != NULL) {
						aux = aux->right;
					}
					else {
						aux->right = creezNod(d, NULL, NULL);
						return rad;
					}
				}
				else {
					return rad;
				}
			}
		}
	}
}

void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("\nCod=%d,Locatie=%s,Capacitate=%d,Nr. categorii:%d",rad->inf.codDepozit,rad->inf.locatie,rad->inf.capacitate,rad->inf.nrCategoriiCereale);
		for (int i = 0; i < rad->inf.nrCategoriiCereale; i++) {
			printf("\nDenumiri cereale: %s", rad->inf.denumiriCereale[i]);
		}
		inordine(rad->right);
	}
}

int nrDepozite(nodArb* rad,const char* Secara) {
	int nr = 0;
	if (rad != NULL) {
		
		for (int i = 0; i < rad->inf.nrCategoriiCereale; i++) {
			if (strcmp(rad->inf.denumiriCereale[i], Secara) == 0) {
				nr++;
			}
		}
		return nr + nrDepozite(rad->left, Secara);
		return nr + nrDepozite(rad->right, Secara);
		
	}
	else {
		return 0;
	}
}
int main()
{
	nodArb* rad = NULL;
	Depozit a, b, c, d, e;



	a.codDepozit = 1;
	a.locatie = (char*)malloc((strlen("Bucuresti") + 1) * sizeof(char));
	strcpy(a.locatie, "Bucuresti");
	a.capacitate = 100;
	a.nrCategoriiCereale = 2;
	a.denumiriCereale = (char**)malloc(a.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < a.nrCategoriiCereale; i++) {
		a.denumiriCereale[i] = (char*)malloc((strlen("Grau") + 1) * sizeof(char));
		strcpy(a.denumiriCereale[i], "grau");
	}

	b.codDepozit = 2;
	b.locatie = (char*)malloc((strlen("Brasov") + 1) * sizeof(char));
	strcpy(b.locatie, "Brasov");
	b.capacitate = 200;
	b.nrCategoriiCereale = 5;
	b.denumiriCereale = (char**)malloc(b.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < b.nrCategoriiCereale; i++) {
		b.denumiriCereale[i] = (char*)malloc((strlen("porumb") + 1) * sizeof(char));
		strcpy(b.denumiriCereale[i], "porumb");
	}


	c.codDepozit = 3;
	c.locatie = (char*)malloc((strlen("Ilfov") + 1) * sizeof(char));
	strcpy(c.locatie, "Ilfov");
	c.capacitate = 100;
	c.nrCategoriiCereale = 3;
	c.denumiriCereale = (char**)malloc(c.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < c.nrCategoriiCereale; i++) {
		c.denumiriCereale[i] = (char*)malloc((strlen("secara") + 1) * sizeof(char));
		strcpy(c.denumiriCereale[i], "secara");
	}


	d.codDepozit = 4;
	d.locatie = (char*)malloc((strlen("Ilfov") + 1) * sizeof(char));
	strcpy(d.locatie, "Ilfov");
	d.capacitate = 150;
	d.nrCategoriiCereale = 2;
	d.denumiriCereale = (char**)malloc(d.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < d.nrCategoriiCereale; i++) {
		d.denumiriCereale[i] = (char*)malloc((strlen("secara") + 1) * sizeof(char));
		strcpy(d.denumiriCereale[i], "secara");
	}

	e.codDepozit = 5;
	e.locatie = (char*)malloc((strlen("Calarasi") + 1) * sizeof(char));
	strcpy(e.locatie, "Calarasi");
	e.capacitate = 250;
	e.nrCategoriiCereale = 4;
	e.denumiriCereale = (char**)malloc(e.nrCategoriiCereale * sizeof(char*));
	for (int i = 0; i < e.nrCategoriiCereale; i++) {
		e.denumiriCereale[i] = (char*)malloc((strlen("secara") + 1) * sizeof(char));
		strcpy(e.denumiriCereale[i], "secara");
	}
	//cerinta 1
	rad=inserare(a,rad);
	rad=inserare(b,rad);
	rad=inserare(c,rad);
	rad=inserare(d,rad);
	rad=inserare(e,rad);

	inordine(rad);

	//cerinta2 --numara prost
	printf("\n------------------------------------\n");
	printf("\nNumar de depozite: %d", nrDepozite(rad, "Secara"));
}

