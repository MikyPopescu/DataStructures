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
struct nodld {
	Student inf;
	nodld* next;
	nodld* prev;
};

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


int nrNodLS(nodls* cap) {
	int nr = 0;
	nodls* temp = cap;
	while (temp!=NULL) {
		nr++;
		temp = temp->next;
	}
	return nr;
}

nodls* nodDePePoz(nodls* cap, int poz) {
	nodls* temp = cap;
	int nr = 0;
	while (temp) {
		if (nr == poz) {
			return temp;
		}
		temp = temp->next;
		nr++;
	}
	return NULL;

}

void convert(nodls** cap, Student** vect, int *nr) {
	nodls* temp = *cap;
	
	while (temp != NULL) {

		Student* copie = (Student*)malloc((*nr) * sizeof(Student)); //copie va retine continutul lui vect pentru a nu pierde informatia la realocare
		for (int i = 0; i < *nr; i++) {
			copie[i] = (*vect)[i]; //copiez continutul lui vect
		}
		*vect = (Student*)malloc((*nr + 1) * sizeof(Student)); //realoc
		(*nr)++;  //cresc nr de elemente
		for (int i = 0; i < *nr - 1; i++) {
			(*vect)[i] = copie[i];  //pun inapoi elementele din copie in vect
		}
		(*vect)[*nr - 1] = temp->inf;  //pun pe pozitia libera informatia 
		nodls* temp2 = temp; //deplasez+eliberez memoria 
		temp = temp->next;
    	free(temp2);
		cap = NULL;
	}
}
void conversie(nodls** cap, Student** vect, int* nr) {
	nodls* temp = *cap;
	while (temp != NULL) {
		(*vect)[*nr] = temp->inf;
		(*nr)++;
		temp = temp->next;
	}

}

void sortareListaSimpla(nodls* cap) {
	int n = nrNodLS(cap);
	for (int i = 0; i < n - 1; i++) {
		nodls* temp = nodDePePoz(cap, i);
		for (int j = i + 1; j < n; j++) {
			nodls* temp2 = nodDePePoz(cap, j);
			if (temp->inf.nrNote > temp2->inf.nrNote) {
				Student aux = temp->inf;
				temp->inf = temp2->inf;
				temp2->inf = aux;
			}
		}
	}
}


nodls* cautaElemLS(nodls* cap, int poz) {
	int n = nrNodLS(cap);
	int i = 1;
	if (poz > n || poz < 1) {
		printf("\nNu exista pozitia in lista!");
	}
	else {
		nodls* temp = cap;
		while (i < n - poz + 1) {
			temp = temp->next;
			i++;
		}
		return temp;
	}
	return NULL;
}

//delete node
//0 a sters/ -1 nu a sters/ lista goala
int stergereLS_inceput(nodls** cap) {
	if (*cap == NULL) {
		return -1;
	}
	else {
		nodls* deSters = *cap;
		*cap = (*cap)->next;
		free(deSters->inf.nume);
		free(deSters->inf.note);
		free(deSters);
	}
	return 0;
}
int stergereLs_final(nodls** cap) {
	if (*cap == NULL) {
		return -1;
	}
	else if ((*cap)->next == NULL) { //lista are un singur element
		stergereLS_inceput(cap); 
	}
	else {
		//am mai multe elemente in lista
		nodls* deSters = *cap;
		nodls* anterior = deSters;
		while (deSters->next != NULL) {
			anterior = deSters;
			deSters = deSters->next;
		}
		anterior->next = NULL;
		free(deSters->inf.nume);
		free(deSters->inf.note);
		free(deSters);
	}
	return 0;
}
//stergerea unui Student dupa numarul de note(in loc de cod/id)
//0 a sters/ -1 lista e goala/ -2 nu exista
int stergereLSId(nodls** cap, int nr) {
	int gasit = 0;
	if (*cap == NULL) {
		return -1;
	}
	//primul element este cel cautat
	if ((*cap)->inf.nrNote == nr) {
		gasit = 1;
		stergereLS_inceput(cap);
	}

	else{
		//am mai multe elemente in lista
		nodls* deSters = (*cap)->next;
		nodls* anterior = *cap;
		while (deSters != NULL && !gasit) {
			if (deSters->inf.nrNote == nr) {
				gasit = 1;
				anterior->next = deSters->next;
				free(deSters->inf.nume);
				free(deSters->inf.note);
				free(deSters);
			}
			anterior = deSters;
			deSters = deSters->next;
		}
	
	}
	return gasit == 1 ? 0 : -2;
}
//sterge de pe pozitie
//0 a sters/-1 lista goala/ -2 pozitie inexistenta
int stergereLSPozitie(nodls** cap, int poz) {
	int gasit = 0;
	int nrElemente = nrNodLS(*cap);
	if (*cap == NULL) {
		return -1;
	}
	else if (poz < 0 || poz >= nrElemente) {
		return -2;
	}
	else if (poz == 0) {
		gasit = 1;
		stergereLS_inceput(cap);
	}
	else {
		int index = 1;
		nodls* deSters = (*cap)->next;
		nodls* anterior = *cap;
		while (deSters != NULL && !gasit) {
			if (index == poz) {
				gasit = 1;
				anterior->next = deSters->next;
				free(deSters->inf.nume);
				free(deSters->inf.note);
				free(deSters);
			}
			index++;
			anterior = deSters;
			deSters = deSters->next;
		}

	}
	return gasit == 1 ? 0 : -2;
}

//convert: LS to LD --problema la adaugarea in lista dubla
nodld* conversieListaDubla(nodls** cap) {
	nodld* capLD = NULL;
	if (*cap!=NULL ) { //while
		nodld* nou = (nodld*)malloc(sizeof(nodld));
		nou->inf.nume = (char*)malloc((strlen((*cap)->inf.nume) + 1) * sizeof(char));
		strcpy(nou->inf.nume, (*cap)->inf.nume);
		nou->inf.nrNote = (*cap)->inf.nrNote;
		nou->inf.note = (int*)malloc((*cap)->inf.nrNote * sizeof(int));
		for (int i = 0; i < (*cap)->inf.nrNote; i++) {
			nou->inf.note[i] = (*cap)->inf.note[i];
		}
		nou->next = NULL;
		nou->prev = NULL;
		capLD = nou;
		stergereLS_inceput(cap);
		nodld* tempLD = capLD;
		
		
		while (*cap) {
			nodld* nou = (nodld*)malloc(sizeof(nodld));
			nou->inf.nume = (char*)malloc((strlen((*cap)->inf.nume) + 1) * sizeof(char));
			strcpy(nou->inf.nume, (*cap)->inf.nume);
			nou->inf.nrNote = (*cap)->inf.nrNote;
			nou->inf.note = (int*)malloc((*cap)->inf.nrNote * sizeof(int));
			for (int i = 0; i < (*cap)->inf.nrNote; i++) {
				nou->inf.note[i] = (*cap)->inf.note[i];
			}
			nou->next = NULL;
			nou->prev = NULL;
			tempLD->next = nou;
			nou->prev = tempLD;
			tempLD = tempLD->next;
			stergereLS_inceput(cap);
		}
	}
	return capLD;
}
void traversareLD(nodld* cap) {
	nodld* temp = cap;
	while (temp != NULL) {
		printf("\nStudentul %s ", temp->inf.nume);
		temp = temp->next;
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

	sortareListaSimpla(cap);
	nodls* temp = cautaElemLS(cap, 2);
	printf("\nElementul cautat:%s ",temp->inf.nume);
	traversare(cap);

	//testam stergerile
	printf("\nAfisarea listei initiale:");
	traversare(cap);
	//stergereLS_inceput(&cap);
	//stergereLs_final(&cap);
	//stergereLSPozitie(&cap,0);
	//stergereLSId(&cap, 3);
	printf("\nAfisarea listei finale:");
	traversare(cap);
	
	//test convert
	/*Student* vect = NULL;
	int nr = 0;
	convert(&cap, &vect, &nr); 
	for (int i = 0; i < nr; i++) {
		printf("\nNume=%s ", vect[i].nume);
	}
	for (int i = 0; i < nr; i++) {
		free(vect[i].nume);
	}
	free(vect);*/

	//test conversie
	Student* vect2 = (Student*)malloc(10 * sizeof(Student));
	int nr2 = 0;
	conversie(&cap, &vect2, &nr2);
	for (int i = 0; i < nr2; i++) {
		printf("\nNume=%s ", vect2[i].nume);
	}

	//test conversie ls-ld 
	nodld* capLD = conversieListaDubla(&cap);
	printf("\nLista dubla: ");
	traversareLD(capLD); 
	if (cap == NULL) {
		printf("\nLista simpla a fost stearsa");
	}
	
	//dezalocare(cap);

}

