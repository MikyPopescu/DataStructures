// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
//LIFO
struct Student {
	char* nume;
	int nrNote;
	int* note;
};
struct nodStiva {
	Student inf;
	nodStiva* next;
};

nodStiva* creezNod(Student s) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
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


void push(nodStiva** varf, Student s) {
	nodStiva* nou = creezNod(s);
	if (*varf == NULL) {
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, Student* s) {
	if (*varf == NULL) {
		return -1; 
	}
	else {
		(*s).nume = (char*)malloc((strlen((*varf)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*varf)->inf.nume);
		(*s).nrNote = (*varf)->inf.nrNote;
		(*s).note = (int*)malloc((*s).nrNote * sizeof(int));
		for (int i = 0; i < (*s).nrNote; i++) {
			(*s).note[i] = (*varf)->inf.note[i];
		}

		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux->inf.nume);
		free(aux->inf.note);
		free(aux);
		return 0; //am extras ceva
	}
}

void traversare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		printf("\nStudentul %s are %d note ", temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote > 0) {
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("\nNotele sunt: %d ", temp->inf.note[i]);
			}
		}
		temp = temp->next;
	}
}

void dezalocare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp != NULL) {
		nodStiva* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
}
int main()
{
	nodStiva* varf = NULL;
	Student a, b, c;
	a.nume = (char*)malloc((strlen("Nume 1") + 1) * sizeof(char));
	strcpy(a.nume, "Nume 1");
	a.nrNote = 3;
	a.note = (int*)malloc(a.nrNote * sizeof(int));
	a.note[0] = 10;
	a.note[1] = 9;
	a.note[2] = 8;

	b.nume = (char*)malloc((strlen("Nume 2") + 1) * sizeof(char));
	strcpy(b.nume, "Nume 2");
	b.nrNote = 3;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 6;
	b.note[1] =5;
	b.note[2] = 5;

	c.nume = (char*)malloc((strlen("Nume 3") + 1) * sizeof(char));
	strcpy(c.nume, "Nume 3");
	c.nrNote = 3;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 10;
	c.note[1] = 4;
	c.note[2] = 8;

	push(&varf, a);
	push(&varf, b);
	push(&varf, c);
	traversare(varf);
	dezalocare(varf);
}

