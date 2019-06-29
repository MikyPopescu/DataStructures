#include "pch.h"
#include <stdio.h>
#include<string.h>
#include<malloc.h>
struct student {
	int cod;
	char* nume;
	int nrNote;
	int* note;
};
struct nodld {
	student inf;
	nodld* next;
	nodld* prev;
};

nodld* creezNod(student s) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->prev = NULL;
	nou->next = NULL;
	return nou;
}
void inserare(nodld** cap, nodld** coada, student s) {
	nodld* nou = creezNod(s);
	if (*cap == NULL) {
		*cap = nou;
		nou->next = *cap;
		nou->prev = *cap;
		*coada = nou;
	}
	else {
		nodld* temp = *cap;
		while (temp->next != *cap) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;

		*coada = nou;
		(*coada)->next = *cap;
		(*cap)->prev = *coada;
	}
	
}
void traversare(nodld* cap) {
	nodld* temp = cap;
	while (temp->next != cap) {
		printf("\nCod=%d, Nume=%s, Nr. note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote>0) {
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("\nNotele studentului: %d", temp->inf.note[i]);
			}
		}
		temp = temp->next;
	}
	printf("\nCod=%d, Nume=%s, Nr. note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
	if (temp->inf.nrNote>0) {
		for (int i = 0; i < temp->inf.nrNote; i++) {
			printf("\nNotele studentului: %d", temp->inf.note[i]);
		}
	}
}
void traversareInvers(nodld* coada) {
	nodld* temp = coada;
	while (temp->prev != coada) {
		printf("\nCod=%d, Nume=%s, Nr. note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote>0) {
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("\nNotele studentului: %d", temp->inf.note[i]);
			}
		}
		temp = temp->prev;
	}
	printf("\nCod=%d, Nume=%s, Nr. note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
	if (temp->inf.nrNote>0) {
		for (int i = 0; i < temp->inf.nrNote; i++) {
			printf("\nNotele studentului: %d", temp->inf.note[i]);
		}
	}
}

void dezalocare(nodld* cap) {
	nodld* temp = cap;
	while (temp->next != cap) {
		nodld* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
	free(temp->inf.nume);
	free(temp->inf.note);
	free(temp);
}
int main() {
	nodld* cap = NULL;
	nodld* coada = NULL;
	student a, b, c, d;

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

	d.cod = 40;
	d.nume = (char*)malloc((strlen("Costel") + 1) * sizeof(char));
	strcpy(d.nume, "Costel");
	d.nrNote = 2;
	d.note = (int*)malloc(d.nrNote * sizeof(int));
	d.note[0] = 10;
	d.note[1] = 8;

	inserare(&cap, &coada, a);
	inserare(&cap, &coada, b);
	inserare(&cap, &coada, c);
	inserare(&cap, &coada, d);


	traversare(cap);
	traversareInvers(coada);


	dezalocare(cap);

}