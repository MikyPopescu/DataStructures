#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct Agrafa {
	int codAgrafa;
	int dimensiune;
	char* culoare;
};
struct CutieAgrafe {
	int codCutie;
	int nrAgrafe;
	Agrafa* agrafe;
};
struct nodls {
	CutieAgrafe  inf;
	nodls* next;
};
nodls* creezNod(CutieAgrafe ca){
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.codCutie = ca.codCutie;
	nou->inf.nrAgrafe = ca.nrAgrafe;
	nou->inf.agrafe = (Agrafa*)malloc(nou->inf.nrAgrafe * sizeof(Agrafa));
	for (int i = 0; i < nou->inf.nrAgrafe; i++) {
		nou->inf.agrafe[i].codAgrafa = ca.agrafe[i].codAgrafa;
		nou->inf.agrafe[i].dimensiune = ca.agrafe[i].dimensiune;
		nou->inf.agrafe[i].culoare = (char*)malloc((strlen(ca.agrafe[i].culoare) + 1) * sizeof(char));
		strcpy(nou->inf.agrafe[i].culoare, ca.agrafe[i].culoare);
	}
	nou->next = NULL;
	return nou;
}
nodls* inserare(nodls* cap, CutieAgrafe c) {
	nodls* nou = creezNod(c);
	if (cap == NULL) {
		cap = nou;
		cap->next = cap;
	}
	else {
		nodls* temp = cap;
		while (temp->next!=cap)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->next = cap;
		
	}
	return cap;
}
void traversare(nodls* cap) {
	if (cap) {
		nodls* temp = cap;
		while (temp->next != cap) {
			printf("\nCod cutie=%d,Nr agrafe=%d", temp->inf.codCutie, temp->inf.nrAgrafe);
			if (temp->inf.nrAgrafe > 0) {
				printf("\nAgrafele sunt: ");
				for (int i = 0; i < temp->inf.nrAgrafe; i++) {
					printf("\nCod agrafa=%d,Dimensiune=%d, Culoare=%s", temp->inf.agrafe[i].codAgrafa, temp->inf.agrafe[i].dimensiune, temp->inf.agrafe[i].culoare);
				}
			}
			temp = temp->next;
		}

		printf("\nCod cutie=%d,Nr agrafe=%d", temp->inf.codCutie, temp->inf.nrAgrafe);
		if (temp->inf.nrAgrafe > 0) {
			printf("\nAgrafele sunt: ");
			for (int i = 0; i < temp->inf.nrAgrafe; i++) {
				printf("\nCod agrafa=%d,Dimensiune=%d, Culoare=%s", temp->inf.agrafe[i].codAgrafa, temp->inf.agrafe[i].dimensiune, temp->inf.agrafe[i].culoare);
			}
		}
	}

}

void dezalocare(nodls* cap) {
	nodls* temp = cap;
	while (temp->next != cap) {
		for (int i = 0; i < temp->inf.nrAgrafe; i++) {
			free(temp->inf.agrafe[i].culoare);
		}
		free(temp->inf.agrafe);
		
		nodls* temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}
int stergereInceput(nodls** cap) {
	if (*cap == NULL) {
		return -1;
	}
	else {
		nodls* deSters = *cap;
		*cap = (*cap)->next;
		free(deSters->inf.agrafe);
		free(deSters);
	}
}
int stergereCodCutie(nodls** cap,int cod) {
	int gasit = 0;
	if (*cap == NULL) {
		return -1;
	}
	//primul element are codCutie==cod
	if ((*cap)->inf.codCutie == cod) {
		gasit = 1;
		stergereInceput(cap);
	}
	else {
		nodls* deSters = (*cap)->next;
		nodls* anterior = *cap;
		while (deSters != NULL && !gasit) {
			if (deSters->inf.codCutie == cod) {
				gasit = 1;
				anterior->next = deSters->next;
				free(deSters->inf.agrafe);
				free(deSters);
			}
			anterior = deSters;
			deSters = deSters->next;
		}
	}
	return gasit == 1 ? 0 : -2;
}

int main()
{
	//Cerinta 1
	Agrafa a, b, c, d, e, f;
	a.codAgrafa = 1;
	b.codAgrafa = 2;
	c.codAgrafa = 3;
	d.codAgrafa = 4;
	e.codAgrafa = 5;
	f.codAgrafa = 6;
	a.dimensiune = 10;
	b.dimensiune = 20;
	c.dimensiune = 30;
	d.dimensiune = 40;
	e.dimensiune = 50;
	f.dimensiune = 60;
	a.culoare = (char*)malloc((strlen("Alb") + 1) * sizeof(char));
	strcpy(a.culoare, "alb");
	b.culoare = (char*)malloc((strlen("Gri") + 1) * sizeof(char));
	strcpy(b.culoare, "gri");
	c.culoare = (char*)malloc((strlen("albastru") + 1) * sizeof(char));
	strcpy(c.culoare, "albastru");
	d.culoare = (char*)malloc((strlen("verde") + 1) * sizeof(char));
	strcpy(d.culoare, "verde");
	e.culoare = (char*)malloc((strlen("rosu") + 1) * sizeof(char));
	strcpy(e.culoare, "rosu");
	f.culoare = (char*)malloc((strlen("roz") + 1) * sizeof(char));
	strcpy(f.culoare, "roz");
	
	CutieAgrafe m, n, o, p, q;
	
	m.codCutie = 100;
	m.nrAgrafe = 3;
	m.agrafe = (Agrafa*)malloc(m.nrAgrafe * sizeof(Agrafa));
	m.agrafe[0] = a;
	m.agrafe[1] = b;
	m.agrafe[2] = f;


	n.codCutie = 200;
	n.nrAgrafe = 2;
	n.agrafe = (Agrafa*)malloc(n.nrAgrafe * sizeof(Agrafa));
	n.agrafe[0] = d;
	n.agrafe[1] = f;

	o.codCutie = 300;
	o.nrAgrafe = 5;
	o.agrafe = (Agrafa*)malloc(o.nrAgrafe * sizeof(Agrafa));
	o.agrafe[0] = a;
	o.agrafe[1] = b;
	o.agrafe[2] = e;
	o.agrafe[3] = f;
	o.agrafe[4] = f;

	p.codCutie = 400;
	p.nrAgrafe = 5;
	p.agrafe = (Agrafa*)malloc(p.nrAgrafe * sizeof(Agrafa));
	p.agrafe[0] = c;
	p.agrafe[1] = b;
	p.agrafe[2] = e;
	p.agrafe[3] = b;
	p.agrafe[4] = f;

	q.codCutie = 500;
	q.nrAgrafe = 2;
	q.agrafe = (Agrafa*)malloc(q.nrAgrafe * sizeof(Agrafa));
	q.agrafe[0] = c;
	q.agrafe[1] = c;
	

	//Cerinta 2
	nodls* cap = NULL;
	cap = inserare(cap,m);
	cap = inserare(cap,n);
	cap = inserare(cap,o);
	cap = inserare(cap,p);
	cap = inserare(cap,q);
	

	//Cerinta 3
	traversare(cap);


	//Cerinta 4
	printf("\nStergere test\n");
	stergereCodCutie(&cap, 300);
	traversare(cap);

	//Cerinta 5
	//????

	dezalocare(cap);
}

