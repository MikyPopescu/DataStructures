#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Produs {
	char* denumireProdus;
	int cantitate;
	char unitateDeMasura[10];
};
struct Comanda {
	int idComanda;
	char* denumireClient;
	int nrProduse;
	Produs* produseComandate;
	char* dataLivrare;
};
struct nodArb {
	Comanda inf;
	nodArb* left, *right;
};
nodArb* creezNod(Comanda c, nodArb* st, nodArb*dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.idComanda = c.idComanda;
	nou->inf.denumireClient = (char*)malloc((strlen(c.denumireClient) + 1) * sizeof(char));
	strcpy(nou->inf.denumireClient, c.denumireClient);
	nou->inf.nrProduse = c.nrProduse;
	nou->inf.produseComandate = (Produs*)malloc(c.nrProduse * sizeof(Produs));
		for (int i = 0; i < c.nrProduse; i++) {
			nou->inf.produseComandate[i].denumireProdus = (char*)malloc((strlen(c.produseComandate[i].denumireProdus) + 1) * sizeof(char));
			strcpy(nou->inf.produseComandate[i].denumireProdus, c.produseComandate[i].denumireProdus);
			nou->inf.produseComandate[i].cantitate = c.produseComandate[i].cantitate;
			strcpy(nou->inf.produseComandate[i].unitateDeMasura , c.produseComandate[i].unitateDeMasura);
		}
		nou->inf.dataLivrare = (char*)malloc((strlen(c.dataLivrare) + 1) * sizeof(char));
		strcpy(nou->inf.dataLivrare, c.dataLivrare);
		nou->left = st;
		nou->right = dr;
		return nou;
}

nodArb* inserare(Comanda c, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creezNod(c, NULL, NULL);
		return aux;
	}
	else {
		while (true) {
			if (c.idComanda < aux->inf.idComanda) {
				if (aux->left != NULL) {
					aux = aux->left;
				}
				else {
					aux->left = creezNod(c, NULL, NULL);
					return rad;
				}
			}
			else {
				if (c.idComanda > aux->inf.idComanda) {
					if (aux->right != NULL) {
						aux = aux->right;
					}
					else {
						aux->right = creezNod(c, NULL, NULL);
					}
				}
				else {
					return rad;
				}
			}
		}
	}
}

void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("\nId=%d, Denumire=%s, Nr produse=%d,Data Livrare=%s", rad->inf.idComanda, rad->inf.denumireClient, rad->inf.nrProduse, rad->inf.dataLivrare);
		for (int i = 0; i < rad->inf.nrProduse; i++) {
			printf("\nDenumire Produs: %s, Cantitate: %d, Unit de masura:%s", rad->inf.produseComandate[i].denumireProdus, rad->inf.produseComandate[i].cantitate, rad->inf.produseComandate[i].unitateDeMasura);
		}
		inordine(rad->right);
	}
}
void dezalocare(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->inf.denumireClient);
		free(rad->inf.produseComandate);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}
void vectorId(nodArb* rad, int** vect, int *nr,char* dataSpecificata) {
	if (rad != NULL) {
		if (strcmp(rad->inf.dataLivrare, dataSpecificata) == 0) {
			if (*vect) {
				int* copie = (int*)malloc(*nr * sizeof(int));
				for (int i = 0; i < *nr; i++) {
					copie[i] = (*vect)[i];
				}


				*vect = (int*)malloc((*nr + 1) * sizeof(int));
				(*nr)++;
				for (int i = 0; i < *nr - 1; i++) {
					(*vect)[i] = copie[i];
				}


				(*vect)[*nr - 1] = rad->inf.idComanda;
			}
			else {
				*nr = 1;
				* vect = (int*)malloc(sizeof(int));
				(*vect)[0] = rad->inf.idComanda;
			}
		}
		vectorId(rad->left, vect, nr, dataSpecificata);
		vectorId(rad->right, vect, nr, dataSpecificata);
	}
	
}
int nrFrunze(nodArb* rad, char* client) {
	if (rad) {
		if (rad->left == NULL && rad->right == NULL && strcmp(client, rad->inf.denumireClient) == 0) {
			return 1;
		}
		else {
			return nrFrunze(rad->left, client) + nrFrunze(rad->right, client);
		}
	}
	else {
		return 0;
	}
}
//void modificareComanda(nodArb* rad, int idCom, int nrProd, Produs* produse, char* denProd, int cantit, char* um) {
//	if (rad){
//		if (rad->inf.idComanda == idCom) {
//			for (int i = 0; i < rad->inf.nrProduse; i++) {
//				free(rad->inf.produseComandate[i].denumireProdus);
//				
//			}
//			
//		}
//	}
//}

int main()
{
	nodArb* rad = NULL;
	Produs a, b, c, d, e;
	Comanda x, y, z;

	a.denumireProdus = (char*)malloc((strlen("Pizza") + 1) * sizeof(char));
	strcpy(a.denumireProdus, "Pizza");
	a.cantitate = 300;
	strcpy(a.unitateDeMasura, "g");

	b.denumireProdus = (char*)malloc((strlen("Fries") + 1) * sizeof(char));
	strcpy(b.denumireProdus, "Fries");
	b.cantitate = 500;
	strcpy(b.unitateDeMasura, "g");

	c.denumireProdus = (char*)malloc((strlen("Coke") + 1) * sizeof(char));
	strcpy(c.denumireProdus, "Coke");
	c.cantitate = 1;
	strcpy(c.unitateDeMasura, "l");

	d.denumireProdus = (char*)malloc((strlen("Nuggets") + 1) * sizeof(char));
	strcpy(d.denumireProdus, "Nuggets");
	d.cantitate = 250;
	strcpy(d.unitateDeMasura, "g");

	e.denumireProdus = (char*)malloc((strlen("Sprite") + 1) * sizeof(char));
	strcpy(e.denumireProdus, "Sprite");
	e.cantitate = 250;
	strcpy(e.unitateDeMasura, "ml");


	x.idComanda = 1;
	x.denumireClient = (char*)malloc((strlen("Client 1") + 1) * sizeof(char));
	strcpy(x.denumireClient, "Client 1");
	x.nrProduse = 3;
	x.produseComandate = (Produs*)malloc(x.nrProduse * sizeof(Produs));
	x.produseComandate[0] = e;
	x.produseComandate[1] = d;
	x.produseComandate[2] = d;
	x.dataLivrare = (char*)malloc(strlen("20.06.2019") + 1 * sizeof(char));
	strcpy(x.dataLivrare, "20.06.2019");

	y.idComanda = 2;
	y.denumireClient = (char*)malloc((strlen("Client 2") + 1) * sizeof(char));
	strcpy(y.denumireClient, "Client 2");
	y.nrProduse = 5;
	y.produseComandate = (Produs*)malloc(y.nrProduse * sizeof(Produs));
	y.produseComandate[0] = e;
	y.produseComandate[1] = d;
	y.produseComandate[2] = b;
	y.produseComandate[3] = a;
	y.produseComandate[4] = c;
	y.dataLivrare = (char*)malloc((strlen("25.06.2019") + 1) * sizeof(char));
	strcpy(y.dataLivrare, "25.06.2019");

	z.idComanda = 3;
	z.denumireClient = (char*)malloc((strlen("Client 3") + 1) * sizeof(char));
	strcpy(z.denumireClient, "Client 3");
	z.nrProduse = 2;
	z.produseComandate = (Produs*)malloc(z.nrProduse * sizeof(Produs));
	z.produseComandate[0] = e;
	z.produseComandate[1] = d;
	z.dataLivrare = (char*)malloc((strlen("07.01.2019") + 1 )* sizeof(char));
	strcpy(z.dataLivrare, "01.07.2019");
	

	rad = inserare(x, rad);
	rad = inserare(y, rad);
	rad = inserare(z, rad);

	//cerinta 2
	inordine(rad);
	
	//cerinta 3
	//test vector
	int* vect = NULL;
	int nr = 0;
	char dataSpecif[20];
	strcpy(dataSpecif, "01.07.2019");
	vectorId(rad, &vect, &nr, dataSpecif);
	for (int i = 0; i < nr; i++) {
		printf("\nVector id-uri: %d", vect[i]);
	}

	//cerinta 4
	char client[20];
	strcpy(client, "Client 3");
	printf("\nNr frunze: %d", nrFrunze(rad, client));
	dezalocare(rad);
}

