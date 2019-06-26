#include "pch.h"
#include <iostream>
#include<malloc.h>
#include<stdio.h>
struct student {
	char* nume;
	int nrNote;
	int* note;
};
struct nodld {
	student inf;
	nodld* next;
	nodld* prev;
};
struct nodls {
	student inf;
	nodls* next;
};
nodld* creezNod(student s) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
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
nodld* inserare(nodld* cap, nodld** coada, student s) {
	nodld* nou = creezNod(s);
	if (cap == NULL) {
		cap = nou;
		*coada = nou;
	}
	else {
		nodld* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}
void traversare(nodld* cap) {
	nodld* temp = cap;
	while (temp != NULL) {
		printf("\nNume=%s, Nr note=%d ", temp->inf.nume, temp->inf.nrNote);
		temp = temp->next;
	}
}
void traversareInvers(nodld* coada) {
	nodld* temp = coada;
	while (temp != NULL) {
		printf("\nNume=%s, Nr note=%d ", temp->inf.nume, temp->inf.nrNote);
		temp = temp->prev;
	}
}
void dezalocare(nodld* cap) {
	nodld* temp = cap;
	while (temp != NULL) {
		nodld* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
}
void stergeInceputLD(nodld** cap, nodld** coada) {
	if (*cap != NULL) {
		if (*cap == *coada) {
			free((*cap)->inf.nume);
			free((*cap)->inf.note);
			free(*cap);
			*cap = NULL;
			*coada = NULL;
		}
		else {
			nodld* temp = *cap;
			*cap = temp->next;
			free(temp->inf.nume);
			free(temp->inf.note);
			free(temp);
			(*cap)->prev = NULL;
		}
	}
}
void conversieVector(nodld** cap, student** vect, int *nr) {
	nodld* temp = *cap;
	while (temp != NULL) {
		student* copie = (student*)malloc((*nr) * sizeof(student));
		for (int i = 0; i < *nr; i++) {
			copie[i] = (*vect)[i];
		}
		*vect = (student*)malloc((*nr + 1) * sizeof(student));
		(*nr)++;
		for (int i = 0; i < *nr - 1; i++) {
			(*vect)[i] = copie[i];
		}
		(*vect)[*nr - 1] = temp->inf;
		nodld* temp2 = temp;
		temp = temp->next;
		free(temp2);
		*cap = NULL;
		
	}
}
nodls* conversieLS(nodld** cap, nodld** coada) {
	nodls* capLS = NULL;
	while (*cap != NULL) {
		nodls* nou = (nodls*)malloc(sizeof(nodls));
		nou->inf.nume = (char*)malloc((strlen((*cap)->inf.nume) + 1) * sizeof(char));
		
		strcpy(nou->inf.nume, (*cap)->inf.nume);
		nou->inf.nrNote = (*cap)->inf.nrNote;
		nou->inf.note = (int*)malloc((*cap)->inf.nrNote * sizeof(int));
		for (int i = 0; i < (*cap)->inf.nrNote; i++) {
			nou->inf.note[i] = (*cap)->inf.note[i];
		}
		nou->next = NULL;
		capLS = nou;
		stergeInceputLD(cap, coada);
		nodls* tempLS = capLS;
		while (*cap) {
			nodls* nou = (nodls*)malloc(sizeof(nodls));
			nou->inf.nume = (char*)malloc((strlen((*cap)->inf.nume) + 1) * sizeof(char));
			strcpy(nou->inf.nume, (*cap)->inf.nume);
			nou->inf.nrNote = (*cap)->inf.nrNote;
			nou->inf.note = (int*)malloc((*cap)->inf.nrNote * sizeof(int));
			for (int i = 0; i < (*cap)->inf.nrNote; i++) {
				nou->inf.note[i] = (*cap)->inf.note[i];
			}
			nou->next = NULL;
			tempLS->next = nou;
			tempLS = tempLS->next;
			stergeInceputLD(cap, coada);
		}
	}
	return capLS;

}
void traversareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp != NULL) {
		printf("\nStudentul %s", temp->inf.nume);
		temp = temp->next;
	}
}
int main()
{
	student a, b, c;
	nodld* cap = NULL;
	nodld* coada = NULL;

	a.nume = (char*)malloc((strlen("Nume 1") + 1) * sizeof(char));
	strcpy(a.nume, "Nume 1");
	a.nrNote = 2;
	a.note = (int*)malloc(a.nrNote * sizeof(int));
	a.note[0] = 6;
	a.note[1] = 8;

	b.nume = (char*)malloc((strlen("Nume 2") + 1) * sizeof(char));
	strcpy(b.nume, "Nume 2");
	b.nrNote = 3;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 10;
	b.note[1] = 10;
	b.note[2] = 10;

	c.nume = (char*)malloc((strlen("Nume 3") + 1) * sizeof(char));
	strcpy(c.nume, "Nume 3");
	c.nrNote = 1;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 7;


	cap = inserare(cap, &coada, a);
	cap = inserare(cap, &coada, b);
	cap = inserare(cap, &coada, c);
	traversare(cap);
	traversareInvers(coada);
	

	//conversie lista vector
	student* vect = NULL;
	int nr = 0;
	conversieVector(&cap, &vect, &nr);
	for (int i = 0; i < nr; i++) {
		printf("\nNume=%s ", vect[i].nume);
	}
	for (int i = 0; i < nr; i++) {
		free(vect[i].nume);
	}
	free(vect);


	//conversie in lista simpla
	nodls* capLS = conversieLS(&cap, &coada);
	printf("\nLista simpla:");
	traversareLS(capLS);
	if (cap == NULL) {
		printf("\nLista dubla a fost stearsa");
	}
	//dezalocare(cap);
}

