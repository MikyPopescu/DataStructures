
#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>

struct student {
	int cod;
	char* nume;
	int nrNote;
	int* note;
};
struct nodStiva {
	student inf;
	nodStiva* next;
};
struct nodls {
	student inf;
	nodls* next;
};
nodStiva* creezNod(student s) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(nou->inf.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->next = NULL;
	return nou;
}

void push(nodStiva** varf, student s) {
	nodStiva* nou = creezNod(s);
	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}
void pop(nodStiva** varf, student* s) {
	if (*varf == NULL) {
		return;
	}
	else {
		(*s).cod = (*varf)->inf.cod;
		(*s).nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*varf)->inf.nume);
		(*s).nrNote = (*varf)->inf.nrNote;
		(*s).note = (int *)malloc((*s).nrNote * sizeof(int));
		for (int i = 0; i < (*s).nrNote; i++) {
			(*s).note[i] = (*varf)->inf.note[i];
		}

		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux->inf.note);
		free(aux->inf.nume);
		free(aux);
	}
}
void traversare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		printf("\nCod=%d,Nume=%s,Nr note=%d", temp->inf.cod, temp->inf.nume, temp->inf.nrNote);
		for (int i = 0; i < temp->inf.nrNote; i++) {
			printf("\nNotele: %d", temp->inf.note[i]);
		}
		temp = temp->next;
	}
}
void dezalocare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		nodStiva* temp2 = temp->next;
		free(temp->inf.note);
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}
void ConversieVector(nodStiva** varf, student** vect, int* nr) {
	nodStiva* temp = *varf;
	while (temp != NULL) {
		student* copie = (student*)malloc(*nr * sizeof(student));
		for (int i = 0; i < *nr; i++) {
			copie[i] = (*vect)[i];
		}

		*vect = (student*)malloc((*nr + 1) * sizeof(student));
		(*nr)++;

		for (int i = 0; i < *nr - 1; i++) {
			(*vect)[i] = copie[i];
		}

		(*vect)[*nr - 1] = temp->inf;
		nodStiva* temp2 = temp;
		temp = temp->next;

		free(temp2);
		*varf = NULL;
	}
}
//met 1
nodls* conversieLS(nodStiva** varf, student s) {
	nodls* capLS = NULL;

	while (*varf != NULL) {
		nodls* nou = (nodls*)malloc(sizeof(nodls));
		nou->inf.cod = (*varf)->inf.cod;
		nou->inf.nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy(nou->inf.nume, (*varf)->inf.nume);
		nou->inf.nrNote = (*varf)->inf.nrNote;
		nou->inf.note = (int*)malloc(nou->inf.nrNote * sizeof(int));
		for (int i = 0; i < nou->inf.nrNote; i++) {
			nou->inf.note[i] = (*varf)->inf.note[i];
		}

		nou->next = NULL;
		capLS = nou;
		nodls* temp = capLS;
		pop(varf, &s);

		while (*varf != NULL) {
			nodls* nou = (nodls*)malloc(sizeof(nodls));
			nou->inf.cod = (*varf)->inf.cod;
			nou->inf.nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
			strcpy(nou->inf.nume, (*varf)->inf.nume);
			nou->inf.nrNote = (*varf)->inf.nrNote;
			nou->inf.note = (int*)malloc(nou->inf.nrNote * sizeof(int));
			for (int i = 0; i < nou->inf.nrNote; i++) {
				nou->inf.note[i] = (*varf)->inf.note[i];
			}

			nou->next = NULL;
			temp->next = nou;
			temp = temp->next;
			pop(varf, &s);
		}

	}
	return capLS;
}
//met2
void inserareLS(nodls** cap, student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodls* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}
void traversareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp != NULL) {
		printf("\nNume din lista simpla %s", temp->inf.nume);
		temp = temp->next;
	}
}
// conversieLD
int main() {
	nodStiva* varf = NULL;

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


	push(&varf, a);
	push(&varf, b);
	push(&varf, c);
	push(&varf, d);

	pop(&varf, &a);


	/*student* vect = NULL;
	int nr = 0;
	ConversieVector(&varf, &vect, &nr);
	for (int i = 0; i < nr; i++) {
		printf("\nNume din vector: %s", vect[i].nume);
	}*/

	//met 1
	/*nodls* capLS = NULL;
	capLS = conversieLS(&varf, a);
	traversareLS(capLS);*/

	//met 2
	nodls* capLS = NULL;
	inserareLS(&capLS, a);
	inserareLS(&capLS, b);
	traversareLS(capLS);
	//traversare(varf);
	dezalocare(varf);

}
