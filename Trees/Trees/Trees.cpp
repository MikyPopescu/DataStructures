#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Student {
	int cod; //cheie
	char* nume;
	int nrNote;
	int*note;
};
struct nodArb {
	Student inf;
	nodArb* left, *right;
	int BF; //pt AVL
};

//ABC Arbori
//Arbore= graf complex +aciclic
//Arbore binar= abore care are cel mult 2 fii (are 0,1 sau 2 fii)
//Arbore binar de cautare= arbore binar in care nodurile sunt asezate ai sa respecte proprietatea: stanga noduri cu valori mai mici decat nodul considerat radacina, dreapta noduri cu valori mai mari decat nodul considerat radacina

//creez nod
nodArb* creare(Student s, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrNote = s.nrNote;
	nou->inf.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		nou->inf.note[i] = s.note[i];
	}
	nou->left = st;
	nou->right = dr;
	return nou;
}
//inserare
nodArb* inserare(Student s, nodArb* rad) {
	nodArb*aux = rad;
	if (rad == NULL)  //verific daca am unde sa inserez
	{  //daca nu am arbore
		aux = creare(s, NULL, NULL);
		return aux;
	}
	else  //daca am arbore
		while (true) {
			if (s.cod < aux->inf.cod)  //trebuie sa inserez in stanga
				if (aux->left != NULL) //daca mai sunt noduri
					aux = aux->left;  //avansez pana ajung la frunza
				else
				{
					aux->left = creare(s, NULL, NULL); //nu mai sunt noduri asa ca pun nodul nou
					return rad;
				}
			else
				if (s.cod > aux->inf.cod)
					if (aux->right != NULL)
						aux = aux->right;
					else {
						aux->right = creare(s, NULL, NULL);
						return rad;
					}
				else
				{
					return rad;//daca este cheie duplicata
				}
		}
}

//parcurgeri
void preordine(nodArb* rad) {
	if (rad != NULL) {
		//afisez continutul radacinii
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
	//	printf("\nBF pentru AVL: %d", rad->BF);
		//afisez ce am in stanga
		preordine(rad->left);
		//afisez ce am in dreapta
		preordine(rad->right);
	}
}

void inordine(nodArb* rad) {
	if(rad != NULL) {
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
		//printf("\nBF pentru AVL: %d", rad->BF);
		inordine(rad->right);
	}
}

void postordine(nodArb* rad) {
	if (rad != NULL) {
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Numar Note=%d ", rad->inf.cod, rad->inf.nume, rad->inf.nrNote);
		for (int i = 0; i < rad->inf.nrNote; i++) {
			printf("\nNotele: %d", rad->inf.note[i]);
		}
		//printf("\nBF pentru AVL: %d", rad->BF);
	}
}

void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb*dr = rad->right;
		free(rad->inf.nume);
		free(rad->inf.note);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

//inaltime
int maxim(int a,int b) {
	int max = a;
	if (max < b) {
		max = b;
	}
	return max;
}
int nrNiveluri(nodArb* rad) {
	if (rad != NULL) {
		return 1 + maxim(nrNiveluri(rad->left), nrNiveluri(rad->right));
	}
	else {
		return 0;

	}
}

//cautare
nodArb* cautare(nodArb* rad,int cheie){
	if (rad != NULL) { //verific daca am unde sa caut
		if (rad->inf.cod == cheie) {//daca informatia din radacina este = cu cheia
			return rad;
		}
		else {
			if (cheie < rad->inf.cod) {  //caut in stanga
				return cautare(rad->left, cheie);
			}
			else {
				return cautare(rad->right, cheie); //caut in dreapta
			}
		}
	}
	else {
		return NULL; //returnez arbore null
	}
}

//conversie arbore vector
void conversieVector(nodArb* rad, Student* vect, int* nr) {
	if (rad != NULL) {
		vect[*nr] = rad->inf;
		(*nr)++;
		conversieVector(rad->left, vect, nr);
		conversieVector(rad->right, vect, nr);
	}
}

//ABC Echilibrati/Arbori AVL= ABC + elem sortate (cand apare un dezechilibru=> trebuie sa echilibram)
//calcul factor de balans
void calculBF(nodArb* rad) {
	if (rad != NULL) {
		//h(SD)-h(SS)
		rad->BF = nrNiveluri(rad->right) - nrNiveluri(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

nodArb* rotatie_dreapta(nodArb* rad) {
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad) {
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad) {
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->left;
	nodArb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad) {
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->right;
	nodArb* nod2 = nod1->left;
	nod1->left = nod2->right;
	nod2->right = nod1;
	rad->right = nod2->left;
	nod2->left = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad) {
	calculBF(rad);
	if (rad->BF <= -2 && rad->left->BF <= -1) { //<= pt orice caz
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else if (rad->BF >= 2 && rad->right->BF >= 1) {
		rad = rotatie_stanga(rad);
		calculBF(rad);
	}
	else if (rad->BF <= -2 && rad->left->BF >= 1) {
		rad = rotatie_stanga_dreapta(rad);
		calculBF(rad);
	}
	else if (rad->BF >= 2 && rad->right->BF <= -1) {
		rad = rotatie_dreapta_stanga(rad);
		calculBF(rad);
	}
	return rad;
}

//stergeri
nodArb* stergeRad(nodArb* rad) {
	nodArb* aux = rad;
	if (aux->left) {
		rad = aux->left;
		if (aux->right) {
			nodArb* temp = aux->left;
			while (temp->right) {
				temp = temp->right;
			}
			temp->right = aux->right;
		}
	}
	else { //nu am fiu stanga
		if (aux->right) {
			rad = aux->right;
		}
		else {
			rad = NULL;
		}
		free(aux->inf.nume);
		free(aux);

	}
	return rad;

}


nodArb* stergeNod(nodArb* rad, int cheie) {
	if (rad == NULL) {
		return NULL;
	}
	else {
		if (rad->inf.cod == cheie) {
			rad = stergeRad(rad);
			return rad;
		}
		else {
			nodArb* aux = rad; //caut
			while (true) {
				if (cheie < aux->inf.cod) {
					//merg pe ramura stanga
					if (aux->left == NULL) {
						break; //nu am ce sterge
					}
					else {
						if (aux->left->inf.cod == cheie) //l-am gasit in stanga
						{
							aux->left = stergeRad(aux->left);
						}
						else {
							aux = aux->left;
							//continui cautarea pe stanga
						}
					}
				}
				else {
					if (cheie > aux->inf.cod) {
						if (aux->right == NULL) {
							break;
						}
						else {
							if (aux->right->inf.cod == cheie) {
								aux->right = stergeRad(aux->right);
							}
							else {
								aux = aux->right;
							}
						}
					}
				}
			}
		}
	}
	return rad;
}

int main()
{
	nodArb* rad = NULL;
	Student a, b, c;

	a.cod = 1;
	a.nume = (char*)malloc((strlen("Dorel") + 1) * sizeof(char));
	strcpy(a.nume, "Dorel");
	a.nrNote = 3;
	a.note = (int*)malloc(a.nrNote * sizeof(int));
	a.note[0] = 10;
	a.note[1] = 9;
	a.note[2] = 8;

	b.cod = 2;
	b.nume = (char*)malloc((strlen("Ionel") + 1) * sizeof(char));
	strcpy(b.nume, "Ionel");
	b.nrNote = 3;
	b.note = (int*)malloc(b.nrNote * sizeof(int));
	b.note[0] = 6;
	b.note[1] = 5;
	b.note[2] = 5;

	c.cod = 3;
	c.nume = (char*)malloc((strlen("Costel") + 1) * sizeof(char));
	strcpy(c.nume, "Costel");
	c.nrNote = 3;
	c.note = (int*)malloc(c.nrNote * sizeof(int));
	c.note[0] = 10;
	c.note[1] = 4;
	c.note[2] = 8;
	c.note[2] = 8;

	rad = inserare(a, rad);
	rad = inserare(b, rad);
	rad = inserare(c, rad);
	rad = reechilibrare(rad); //avl

	//parcurgere
	inordine(rad);
	printf("\nSubarbore stang: \n");
	inordine(rad->left);
	printf("\nSubarbore drept: \n");
	inordine(rad->right);

	//calcul inaltime
	printf("\nInaltime arbore este: %d", nrNiveluri(rad));
	
	//cautare
	nodArb* nodCautat = cautare(rad, 3);
	printf("\nStudentul cautat se numeste %s", nodCautat->inf.nume);
	
	//vector
	printf("\n--------------------------------------------\n");
	Student *vect = (Student*)malloc(5 * sizeof(Student));
	int nr = 0;
	conversieVector(rad, vect, &nr);
	for (int i = 0; i < nr; i++) {
		printf("\nCod=%d, Nume=%s", vect[i].cod, vect[i].nume);
	}
	free(vect); //nu am copiat numele pe componente ca sa il sterg
	

	printf("\n---------------------\n");
	rad = stergeNod(rad, 3);
	rad = reechilibrare(rad);
	inordine(rad);
	printf("\nSubarbore stang: \n");
	inordine(rad->left);
	printf("\nSubarbore drept: \n");
	inordine(rad->right);
	printf("\nInaltimea subarborelui stang: %d ", nrNiveluri(rad->left));
	printf("\nInaltimea subarborelui drept: %d ", nrNiveluri(rad->right));
	dezalocare(rad);
}

