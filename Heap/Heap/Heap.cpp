#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Student {
	int cod;
	char* nume;
	int nrNote;
	int* note;
};
struct Heap {
	Student* vect;
	int nrElem;
};
void filtrare(Heap h, int index) { //se apeleaza in main de la baza spre varf
	int indexMax = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;

	if (indexS<h.nrElem && h.vect[indexS].cod>h.vect[indexMax].cod) {
		indexMax = indexS;
	}
	if (indexD<h.nrElem && h.vect[indexD].cod>h.vect[indexMax].cod) {
		indexMax = indexD;
	}
	if (index != indexMax) {
		//nu se respecta conditia de filtrare
		Student aux = h.vect[index];
		h.vect[index] = h.vect[indexMax];
		h.vect[indexMax] = aux;

		filtrare(h, indexMax);
	}

}

void afisare(Heap h) {
	printf("\nElemente heap: ");

	for (int i = 0; i < h.nrElem; i++) {
		printf("\nCod=%d, Nume=%s, Numar note=%d", h.vect[i].cod, h.vect[i].nume, h.vect[i].nrNote);
		for (int j = 0; j < h.vect[i].nrNote; j++) {
			printf("\nNotele sunt:%d ", h.vect->note[j]);
		}
	}
}


void inserare(Heap*h, Student elem) {
	Student* vect1 = (Student*)malloc(((*h).nrElem + 1) * sizeof(Student));

	for (int i = 0; i < (*h).nrElem; i++) {
		vect1[i] = (*h).vect[i];
	}

	vect1[(*h).nrElem] = elem;
	(*h).nrElem++;

	free((*h).vect);
	(*h).vect = vect1;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
		filtrare(*h, i);
	}
}

void extragere(Heap* h, Student* elem) {
	Student* vect1 = (Student*)malloc(((*h).nrElem - 1) * sizeof(Student));
	
	//interschimbare primul elem cu ult
	Student aux = (*h).vect[0];
	(*h).vect[0] = (*h).vect[(*h).nrElem - 1];
	(*h).vect[(*h).nrElem - 1] = aux;

	*elem = (*h).vect[(*h).nrElem - 1];

	for (int i = 0; i < (*h).nrElem - 1; i++) {
		vect1[i] = (*h).vect[i];
	}

	(*h).nrElem--;
	free((*h).vect);
	(*h).vect = vect1;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
		filtrare(*h, i);
	}
}

int main()
{
	Heap h;
	h.nrElem = 3;
	h.vect = (Student*)malloc(h.nrElem * sizeof(Student));
	Student a, b, c;

	a.cod = 10;
	a.nume = (char*)malloc((strlen("Dorel") + 1) * sizeof(char));
	strcpy(a.nume, "Dorel");
	a.nrNote = 3;
	a.note = (int*)malloc(a.nrNote * sizeof(int));
	a.note[0] = 10;
	a.note[1] = 9;
	a.note[2] = 8;
	
	b.cod = 20;
	b.nume = (char*)malloc((strlen("Ionel") + 1) * sizeof(char));
	strcpy(b.nume, "Ionel");
	b.nrNote = 3;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 6;
	b.note[1] = 5;
	b.note[2] = 5;
	
	
	c.cod = 30;
	c.nume = (char*)malloc((strlen("Gigel") + 1) * sizeof(char));
	strcpy(c.nume, "Gigel");
	c.nrNote = 3;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 10;
	c.note[1] = 4;
	c.note[2] = 8;


	h.vect[0] = a;
	h.vect[1] = b;
	h.vect[2] = c;


	for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisare(h);

//test inserare
	Student s;
	s.cod = 100;
	s.nume = (char*)malloc((strlen("Marcel") + 1) * sizeof(char));
	strcpy(s.nume, "Marcel");
	s.nrNote = 5;
	s.note = (int*)malloc(s.nrNote * sizeof(int));
	s.note[0] = 10;
	s.note[1] = 4;
	s.note[2] = 8;
	s.note[3] = 10;
	s.note[4] = 8;
	inserare(&h, s);
	afisare(h);

//test extragere
	Student elem;
	extragere(&h, &elem);
	printf("\nElement extras are codul %d si numele %s" , elem.cod, elem.nume);

	Student* vectSortat = (Student*)malloc(h.nrElem * sizeof(Student));
	int n = h.nrElem;
	int m = h.nrElem;
	for (int i = 0; i < n; i++) {
		extragere(&h, &elem);//scot elem din heap
		vectSortat[i] = elem;//il bag in vect sortat 
		//la final vect va fi sortat descresc
	}


	/*printf("\nAfisare dupa extragere\n");
	afisare(h);*/


	//printf("\nVector sortat: ");
	//for (int i = 0; i < n; i++) {
	//	printf("%d ", vectSortat[i].cod);
	//}

	//
	//for (int i = 0; i < m; i++) {
	//	//crapa la eliberare
	//	//free(h.vect[i].nume);
	//	//free(h.vect[i].note);
	//}
	//free(h.vect);
	//free(vectSortat);

}
