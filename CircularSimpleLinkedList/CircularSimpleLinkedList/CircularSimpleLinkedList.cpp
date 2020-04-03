#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<string.h>


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
nodls* creezNod(Student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(nou->inf.nrNote * sizeof(int));
	for (int i = 0; i < nou->inf.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->next = NULL;
	return nou;
}

nodls* inserare(nodls* cap, Student s) {
	nodls* nou = creezNod(s);
	if (cap == NULL) {
		cap = nou;
		cap->next = cap;
	}
	else {
		nodls* temp = cap;
		while (temp->next != cap) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->next = cap;
	}
	return cap;
}

void traversare(nodls* cap) {
	nodls* temp = cap;
	while (temp->next != cap) {
		printf("\nCod=%d,Nume=%s,Nr Note=%d",temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote > 0) {
			printf("\nNotele studentului sunt: ");
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("%d ", temp->inf.note[i]);
			}
		}
		temp = temp->next;
	}
	printf("\nCod=%d,Nume=%s,Nr Note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
	if (temp->inf.nrNote > 0) {
		printf("\nNotele studentului sunt: ");
		for (int i = 0; i < temp->inf.nrNote; i++) {
			printf("%d ", temp->inf.note[i]);
		}
	}
}
void dezalocare(nodls* cap) {
	nodls* temp = cap;
	while (temp->next != cap) {
		nodls* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
	free(temp->inf.nume);
	free(temp->inf.note);
	free(temp);
}

void stergereDupaNume(nodls** cap, const char* numeNou) {
	//daca am o lista goala
	if (*cap == NULL) {
		return;
	}
	//daca am un singur nou => verific daca e cel cautat de mine
	if (strcmp((*cap)->inf.nume, numeNou) == 0 && (*cap)->next == *cap) {
		free((*cap)->inf.nume);
		free((*cap)->inf.note);
		free(*cap);
		
		*cap = NULL;  //problema in cazul asta??
	}
	
	//Am o lista cu multe elemente si incep sa caut prin ea
	nodls* temp = *cap;
	nodls* deSters;

	//este primul element cel pe care trebuie sa il sterg?
	if (strcmp((*cap)->inf.nume, numeNou) == 0) { //???
		//ma duc la finalul listei
		while (temp->next != (*cap)) {
			temp = temp->next;
		}
		temp->next = (*cap)->next;
		free((*cap)->inf.nume);
		free((*cap)->inf.note);
		free(*cap);

		*cap = temp->next;
	}
	//ma apuc sa caut elementul de sters prin lista
	while (temp->next != (*cap) && strcmp(temp->inf.nume, numeNou) == 0) {
		temp = temp->next;
	}
	//am gasit nodul de sters
	if (strcmp(temp->inf.nume, numeNou) == 0) {
		deSters = temp->next;
		temp->next = deSters->next;
		free(deSters->inf.nume);
		free(deSters->inf.note);
		free(deSters);
	}
	//nu am gasit ce sa sterg
	else {
		printf("\nNu s-a gasit niciun nod cu proprietatea ceruta");
	}
}



int main()
{
	Student a, b, c, d;
	nodls* cap = NULL;

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
	b.nrNote = 4;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 6;
	b.note[1] = 5;
	b.note[2] = 5;
	b.note[3] = 5;


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



	//cap = inserare(cap, a);
	cap = inserare(cap, b);
	//cap = inserare(cap,c);
	//cap = inserare(cap, d);

	printf("\nLista dupa inserare");
	traversare(cap);

	stergereDupaNume(&cap, "Ionel");
	printf("\nLista dupa stergere");
	traversare(cap);


	dezalocare(cap);
}

