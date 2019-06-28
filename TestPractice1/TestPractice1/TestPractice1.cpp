#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Moneda {
	char cod[5];
	char* denumire;
	char* emitent;
	int sold;
};
struct nodls {
	Moneda inf;
	nodls* next;
};
struct hashT {
	nodls** vect;
	int size;
};
int functieHash(hashT tabela, char* cheie) {
	int suma = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		suma += cheie[i] % tabela.size;
	}
	return suma % tabela.size;
}
nodls* creezNod(Moneda m) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	strcpy(nou->inf.cod,m.cod);
	nou->inf.denumire = (char*)malloc((strlen(m.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, m.denumire);
	nou->inf.emitent = (char*)malloc((strlen(m.emitent) + 1) * sizeof(char));
	strcpy(nou->inf.emitent, m.emitent);
	nou->inf.sold = m.sold;
	nou->next = NULL;
	return nou;
}
int inserare(hashT tabela, Moneda m) {
	int pozitie;
	if (tabela.vect != NULL) {
		pozitie = functieHash(tabela, m.cod);
		nodls* nou = creezNod(m);

		if (tabela.vect[pozitie] == NULL) {
			tabela.vect[pozitie] = nou;
		}
		else {
		
			nodls* temp = tabela.vect[pozitie];
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return pozitie; 
}
void traversare(hashT tabela) {
	//traversez vectorul, iar pt fieccare pozitie nenula traversez lista
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				printf("\nPozitia este %d ", i);
				nodls* temp = tabela.vect[i];
				while (temp != NULL) {
					printf("\nCod= %s, Nume=%s, Emitent=%s, Sold=%d", temp->inf.cod, temp->inf.denumire, temp->inf.emitent,temp->inf.sold);
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
					free(temp->inf.denumire);
					free(temp->inf.emitent);
					free(temp);
					temp = temp2;
				}
			}
		}
	}
	free(tabela.vect);
}

Moneda cautareHashT(hashT tabela, char* cod,int soldSpecificat) {
	if (tabela.vect) {
		int poz = functieHash(tabela, cod);

		nodls* temp = tabela.vect[poz];
		while (temp && temp->inf.sold != soldSpecificat) {
			temp = temp->next;
		}
		if (temp) {
			return temp->inf;
		}
	}
	else {
		Moneda m;
		strcpy(m.cod, "n/a");
		m.denumire = NULL;
		m.emitent = NULL;
		m.sold = -1;
		
		return m;
	}
}
void modificaSold(hashT tabela, char* cheie, int soldNou) {
	int i = functieHash(tabela,cheie);
	while (i < tabela.size && strcmp(tabela.vect[i]->inf.cod, cheie) != 0) {
		i++;
	}
	if (i < tabela.size) {
		tabela.vect[i]->inf.sold = soldNou;
	}
	else {
		printf("\nCheia nu exista in tabela de dispersie");
	}
}
int main()
{
	//Cerinta 1
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodls**)malloc(tabela.size * sizeof(nodls*));
	for (int i = 0; i < tabela.size; i++) {
		tabela.vect[i] = NULL;
	}
	Moneda a, b, c, d, e;

	strcpy(a.cod, "RON");
	a.denumire = (char*)malloc((strlen("LEU ROMANESC") + 1) * sizeof(char));
	strcpy(a.denumire, "Leu Romanesc");
	a.emitent = (char*)malloc((strlen("Romania") + 1) * sizeof(char));
	strcpy(a.emitent, "Romania");
	a.sold = 100;

	strcpy(b.cod, "LV");
	b.denumire = (char*)malloc((strlen("Leva") + 1) * sizeof(char));
	strcpy(b.denumire, "Leva");
	b.emitent = (char*)malloc((strlen("Bulgaria") + 1) * sizeof(char));
	strcpy(b.emitent, "Bulgaria");
	b.sold = 200;

	strcpy(c.cod, "YTL");
	c.denumire = (char*)malloc((strlen("Lira Turceasca") + 1) * sizeof(char));
	strcpy(c.denumire, "Lira Turceasca");
	c.emitent = (char*)malloc((strlen("Turcia") + 1) * sizeof(char));
	strcpy(c.emitent, "Turcia");
	c.sold = 300;

	strcpy(d.cod, "INR");
	d.denumire = (char*)malloc((strlen("Rupie indiana") + 1) * sizeof(char));
	strcpy(d.denumire, "Rupie indiana");
	d.emitent = (char*)malloc((strlen("India") + 1) * sizeof(char));
	strcpy(d.emitent, "India");
	d.sold = 400;

	strcpy(e.cod, "USD");
	e.denumire = (char*)malloc((strlen("Dolar american") + 1) * sizeof(char));
	strcpy(e.denumire, "Dolar american");
	e.emitent = (char*)malloc((strlen("Statele Unite ale Americii") + 1) * sizeof(char));
	strcpy(e.emitent, "Statele Unite ale Americii");
	e.sold = 500;

	//Cerinta 2
	inserare(tabela, a);
	inserare(tabela, b);
	inserare(tabela, c);
	inserare(tabela, d);
	inserare(tabela, e);

	//Cerinta 3
	traversare(tabela);


	//Cerinta 4
	char ron[5];
	strcpy(ron, "RON");
	Moneda m=cautareHashT(tabela, ron, 50);
	printf( "\nMoneda cautata are soldul %d", m.sold);

	//Cerinta 5
	modificaSold(tabela, ron, 1000);
	traversare(tabela);


	dezalocare(tabela);
}

