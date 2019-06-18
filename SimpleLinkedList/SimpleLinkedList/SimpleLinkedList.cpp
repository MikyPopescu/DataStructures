#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;
struct Student {
	char* nume;
	int nrNote;
	int* note;
};
struct nodls {
	Student inf;
	nodls* next;
};

//create a node
nodls* creezNod(Student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.nume = (char*)malloc((strlen(s.nume)+1)*sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(nou->inf.nrNote *sizeof(int));
	for (int i = 0; i < nou->inf.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->next = NULL;
	return nou;
}
//insert a node at the beginning of a list
nodls* inserareInceput(nodls* cap, Student s) {
	nodls* nou = creezNod(s);
	if (cap == NULL) {
		cap = nou;
	}
	else {
		nou->next = cap;
		cap = nou;
	}
	return cap;
}
//insert a node at the end of a list
nodls* inserareFinal(nodls* cap, Student s) {
	nodls* nou = creezNod(s);
	if (cap == NULL) {
		cap = nou;
	}
	else {
		nodls* temp = cap;
		while(temp->next!=NULL){
			temp = temp->next;
		}
		temp->next = nou;
	}
	return cap;
}
//crossing the elements of a list
void traversare(nodls* cap) {
	nodls* temp = cap;
	while (temp!=NULL) {
		printf("\nNume=%s,Nr Note=%d", temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote>0) {
			printf("\nNotele studentului sunt: ");
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("%d ", temp->inf.note[i]);
			}
		}
		temp = temp->next;
	}
}
//free memory
void dezalocare(nodls* cap) {
	nodls* temp = cap;
	while (temp!=NULL) {
		nodls* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
}
int main()
{
	int nrStudenti;
	printf("\nNumarul de studenti: ");
	scanf("%d", &nrStudenti);
	
	Student s;
	nodls* cap = NULL;
	char buffer[20];

	for (int i = 0; i < nrStudenti; i++) {
		cin.ignore();
		printf("\nNume student: ");
		
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		
		printf("\nNr de note: ");
		scanf("%d", &s.nrNote);

		printf("\nNotele: ");
		s.note = (int*)malloc(s.nrNote * sizeof(int));
		for (int j = 0; j < s.nrNote; j++) {
			scanf("%d", &s.note[j]);
		}
		//cap = inserareInceput(cap,s);
		cap = inserareFinal(cap, s);
	}
	traversare(cap);
	dezalocare(cap);

}

