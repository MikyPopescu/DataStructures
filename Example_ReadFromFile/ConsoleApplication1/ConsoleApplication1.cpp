// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
using namespace std;
struct student {
	int cod;
	char* nume;
	float medie;
	int nrNote;
	int* note;
};
int main()
{
	student s;
	char buffer[50];
	FILE* f = fopen("fisier.txt", "r");
	int nrElemente;
	fscanf(f, "%d", &nrElemente);
	printf("Nr elemente: %d ", nrElemente);

	for (int i = 0; i < nrElemente; i++) {
		//cod
		fscanf(f, "%d", &s.cod);
		printf("\nCod: %d ", s.cod);

		//nume fara spatii
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nNume: %s ", s.nume);

		//medie
		fscanf(f, "%f", &s.medie);
		printf("\nMedie: %5.2f ", s.medie);

		//nrNote
		fscanf(f, "%d", &s.nrNote);
		printf("\nNr note: %d ", s.nrNote);

		//note
		s.note = (int*)malloc(s.nrNote * sizeof(int));
		for (int i = 0; i < s.nrNote; i++) {
			fscanf(f, "%d", &s.note[i]);
			printf("\nNota: %d ", s.note[i]);
		}
	}
}
