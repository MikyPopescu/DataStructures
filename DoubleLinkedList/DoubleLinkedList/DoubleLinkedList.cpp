// DoubleLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	dezalocare(cap);
}

