#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
//ABC Arbori
//AVL Arbori
struct Student {
	int cod; //cheie
	char* nume;
	int nrNote;
	int*note;
};
struct nodArb {
	Student inf;
	nodArb* left, *right;
	int BF; //pt AVL
};
//creez nod
nodArb* creare(Student s, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->left = st;
	nou->right = dr;
	return nou;
}
//inserare
nodArb* inserare(Student s, nodArb* rad) {
	nodArb*aux = rad;
	if (rad == NULL)
	{
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (s.cod < aux->inf.cod)
				if (aux->left != NULL)
					aux = aux->left;
				else
				{
					aux->left = creare(s, NULL, NULL);
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else {
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
				{
					return rad;//daca este cheie duplicata
				}
		}
}

//parcurgeri
void preordine(nodArb* rad) {
	if (rad != NULL) {
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
	//	printf("\nBF pentru AVL: %d", rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodArb* rad) {
	if(rad != NULL) {
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
		//printf("\nBF pentru AVL: %d", rad->BF);
		inordine(rad->right);
	}
}

void postordine(nodArb* rad) {
	if (rad != NULL) {
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
		//printf("\nBF pentru AVL: %d", rad->BF);
	}
}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb*dr = rad->right;
		free(rad->inf.nume);
		free(rad->inf.note);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}
int main()
{
	nodArb* rad = NULL;
	Student a, b, c;

	a.cod = 1;
	a.nume = (char*)malloc((strlen("Dorel") + 1) * sizeof(char));
	strcpy(a.nume, "Dorel");
	a.nrNote = 3;
	a.note = (int*)malloc(a.nrNote * sizeof(int));
	a.note[0] = 10;
	a.note[1] = 9;
	a.note[2] = 8;

	b.cod = 2;
	b.nume = (char*)malloc((strlen("Ionel") + 1) * sizeof(char));
	strcpy(b.nume, "Ionel");
	b.nrNote = 3;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 6;
	b.note[1] = 5;
	b.note[2] = 5;

	c.cod = 3;
	c.nume = (char*)malloc((strlen("Costel") + 1) * sizeof(char));
	strcpy(c.nume, "Costel");
	c.nrNote = 3;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 10;
	c.note[1] = 4;
	c.note[2] = 8;
	c.note[2] = 8;

	rad = inserare(a, rad);
	rad = inserare(b, rad);
	rad = inserare(c, rad);


	inordine(rad);
	printf("\nSubarbore stang: \n");
	inordine(rad->left);
	printf("\nSubarbore drept: \n");
	inordine(rad->right);
}

