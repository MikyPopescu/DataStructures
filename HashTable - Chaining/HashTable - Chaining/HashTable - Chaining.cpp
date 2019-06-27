#include "pch.h"
#include <iostream>
#include<malloc.h>
#include<string.h>
#include<stdio.h>
using namespace std;
struct Student {
	int cod;
	char* nume;
	int nrNote;
	int* note;
};
struct nodls {
	Student inf;
	nodls* next;
};
struct hashT {
	nodls** vect;
	int size;
};
int functieHash(hashT tabela, int cheie) {
	return cheie % tabela.size;
}
nodls* creezNod(Student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->next = NULL;
	return nou;
}
int inserare(hashT tabela, Student s) {
	int pozitie;
	if (tabela.vect != NULL) {
		pozitie = functieHash(tabela, s.cod);
		nodls* nou = creezNod(s);
		
		if (tabela.vect[pozitie] == NULL) {
			tabela.vect[pozitie] = nou;
		}
		else {
			//inserez la final
			nodls* temp = tabela.vect[pozitie];
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return pozitie; //pozitia unde am inserat
}
void traversare(hashT tabela) {
	//traversez vectorul, iar pt fieccare pozitie nenula traversez lista
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				printf("\nPozitia este %d ", i);
				nodls* temp = tabela.vect[i];
				while (temp != NULL) {
					printf("\nCod= %d, Nume=%s, Nr note= %d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
					for (int i = 0; i < temp->inf.nrNote; i++) {
						printf("\nNotele sunt %d", temp->inf.note[i]);
					}
					temp = temp->next;
				}
			}
		}
	}
}
void dezalocare(hashT tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				nodls* temp = tabela.vect[i];
				while (temp != NULL) {
					nodls* temp2 = temp->next;
					free(temp->inf.nume);
					free(temp->inf.note);
					free(temp);
					temp = temp2;
				}
			}
		}
	}
	free(tabela.vect);
}
//stergere
//cautare
int main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodls**)malloc(tabela.size * sizeof(nodls*));
	//init tot vectorul cu null
	for (int i = 0; i < tabela.size; i++) {
		tabela.vect[i] = NULL;
	}
	Student a, b, c;
	a.cod = 1;
	a.nume = (char*)malloc((strlen("Gigel") + 1) * sizeof(char));
	strcpy(a.nume, "Gigel");
	a.nrNote = 3;
	a.note = (int*)malloc(a.nrNote * sizeof(int*));
	a.note[0] = 6;
	a.note[1] = 7;
	a.note[2] = 9;

	b.cod = 2;
	b.nume = (char*)malloc((strlen("Dorel") + 1) * sizeof(char));
	strcpy(b.nume, "Dorel");
	b.nrNote = 5;
	b.note = (int*)malloc(b.nrNote * sizeof(int*));
	b.note[0] = 6;
	b.note[1] = 7;
	b.note[2] = 9;
	b.note[3] = 9;
	b.note[4] = 10;

	c.cod = 3;
	c.nume = (char*)malloc((strlen("Ionel") + 1) * sizeof(char));
	strcpy(c.nume, "Ionel");
	c.nrNote = 2;
	c.note = (int*)malloc(c.nrNote * sizeof(int*));
	c.note[0] = 9;
	c.note[1] = 7;
	
	inserare(tabela, a);
	inserare(tabela, b);
	inserare(tabela, c);

	traversare(tabela);
	dezalocare(tabela);
}
