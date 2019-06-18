#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Student {
	char* nume;
	int nrNote;
	int* note;
};
struct nodls {
	Student inf;
	nodls* next;
};
int main()
{
	int nrStudenti;
	printf("\nNumarul de studenti: ");
	scanf("%d", &nrStudenti);
	
	Student s;
	nodls* cap = NULL;
	char buffer[20];

	for (int i = 0; i < nrStudenti; i++) {
		printf("\nNume student: ");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		
		printf("\nNr de note: ");
		scanf("%d", &s.nrNote);

		printf("\nNotele: ");
		s.note = (int*)malloc(s.nrNote * sizeof(int));
		for (int j = 0; j < s.nrNote; j++) {
			scanf("%d", &s.note[i]);
		}
	}


}

