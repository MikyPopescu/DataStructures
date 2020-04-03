#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
//FIFO
struct Student {
	char* nume;
	int nrNote;
	int* note;
};
struct nodls {
	Student inf;
	nodls* next;
};
struct nodCoada {
	Student inf;
	nodCoada* next;
};
nodCoada* creezNod(Student s) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
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
void put(nodCoada** prim, nodCoada** ultim, Student s) {
	nodCoada* nou = creezNod(s);
	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void get(nodCoada** prim, nodCoada** ultim, Student* s) {
	if (*prim != NULL && *ultim != NULL) {
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).nrNote = (*prim)->inf.nrNote;
		(*s).note = (int*)malloc((*prim)->inf.nrNote * sizeof(int));
		for (int i = 0; i < (*prim)->inf.nrNote; i++) {
			(*s).note[i] = (*prim)->inf.note[i];
		}

		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux->inf.nume);
		free(aux->inf.note);
	}
	else {
		if (*prim == NULL) {
			*ultim = NULL;
		}
	}
}

void traversare(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp != NULL) {
		printf("\nStudentul %s are %d note ", temp->inf.nume, temp->inf.nrNote);
		for (int i = 0; i < temp->inf.nrNote; i++) {
			printf("\nNotele: %d", temp->inf.note[i]);
		}
		temp = temp->next;
	}
}
void dezalocare(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp != NULL) {
		nodCoada* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
}


//conversie stiva lista simpla
void inserareLS(nodls** cap, Student s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
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
		printf("\nNume=%s,Nr Note=%d", temp->inf.nume, temp->inf.nrNote);
		if (temp->inf.nrNote > 0) {
			printf("\nNotele studentului sunt: ");
			for (int i = 0; i < temp->inf.nrNote; i++) {
				printf("%d ", temp->inf.note[i]);
			}
		}
		temp = temp->next;
	}
}

void dezalocareLS(nodls** cap) {
	nodls* temp = *cap;
	while (temp != NULL) {
		nodls* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp->inf.note);
		free(temp);
		temp = temp2;
	}
}

void ConversieVector(nodCoada** prim, Student** vect, int* nr) {
	nodCoada* temp = *prim;
	while (temp != NULL) {
		Student* copie = (Student*)malloc(*nr * sizeof(Student));
		for (int i = 0; i < *nr; i++) {
			copie[i] = (*vect)[i];
		}

		*vect = (Student*)malloc((*nr + 1) * sizeof(Student));
		(*nr)++;

		for (int i = 0; i < *nr - 1; i++) {
			(*vect)[i] = copie[i];
		}

		(*vect)[*nr - 1] = temp->inf;
		nodCoada* temp2 = temp;
		temp = temp->next;

		free(temp2);
		*prim = NULL;
	}
}
int main()
{
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
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
	b.note[1] = 5;
	b.note[2] = 5;

	c.nume = (char*)malloc((strlen("Nume 3") + 1) * sizeof(char));
	strcpy(c.nume, "Nume 3");
	c.nrNote = 3;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 10;
	c.note[1] = 4;
	c.note[2] = 8;

	put(&prim,&ultim, a);
	put(&prim,&ultim, b);
	put(&prim,&ultim,c);
	put(&prim,&ultim,c);
	get(&prim, &ultim, &c);
	
	traversare(prim);
	Student* vect = NULL;
	int nr = 0;
	ConversieVector(&prim, &vect, &nr);
	for (int i = 0; i < nr; i++) {
		printf("\nNume din vector: %s", vect[i].nume);
	};
	
	for (int i = 0; i < nr; i++) {
		free(vect[i].note);
		free(vect[i].nume);
	}
	free(vect);
	
	
	//LS
	nodls* cap = NULL;
	inserareLS(&cap, a);
	inserareLS(&cap, b);
	inserareLS(&cap, c);
	traversareLS(cap);
	dezalocareLS(&cap);

	
	
	dezalocare(prim);
}

