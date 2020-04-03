#include"pch.h"
#include <stdio.h>
#include<string.h>
#include<malloc.h>
struct student
{
	int id;
	char* nume;
};

struct nodlp;

struct nodls
{
	nodls* next;
	nodlp* info;
};

struct nodlp
{
	nodls* vecini;//lista de vecini
	student info;
	nodlp* next;
};

nodlp* inserareLP(nodlp* cap, student s)
{
	nodlp *nou = (nodlp*)malloc(sizeof(nodlp));
	nou->info.id = s.id;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);

	nou->vecini = NULL;
	nou->next = NULL;

	if (cap)
	{
		nodlp *p = cap;
		while (p->next)
			p = p->next;
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

nodls* inserareLS(nodls* cap, nodlp* info)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = info;
	nou->next = NULL;
	if (cap)
	{
		nodls *p = cap;
		while (p->next)
			p = p->next;
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

nodlp* cautareDupaId(nodlp*cap, int id)
{
	nodlp* temp = cap;
	while (temp && temp->info.id != id)
	{
		temp = temp->next;
	}
	return temp;
}

void inserareArcInGraf(nodlp* graf, int idStart, int idStop)
{
	if (graf)
	{
		nodlp* nodStart = cautareDupaId(graf, idStart);
		nodlp* nodStop = cautareDupaId(graf, idStop);
		if (nodStart && nodStop)
		{
			nodStart->vecini = inserareLS(nodStart->vecini, nodStop);//daca am orientat ma opresc asa
			nodStop->vecini = inserareLS(nodStop->vecini, nodStart);
		}
	}
}

void traversareLS(nodls *cap)
{
	nodls* temp = cap;
	while (temp)
	{
		printf("    %d.%s\n", temp->info->info.id + 1, temp->info->info.nume);
		temp = temp->next;
	}
}

void traversareLP(nodlp*cap)
{
	nodlp *temp = cap;
	while (temp)
	{
		printf("%d.%s are urmatorii vecini: \n", temp->info.id + 1, temp->info.nume);
		traversareLS(temp->vecini);
		temp = temp->next;
	}
}

//pt parcurgere in adancime
struct NodStiva
{
	int id;
	NodStiva* next;
};

NodStiva* push(NodStiva* cap, int id)
{
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->next = NULL;
	nou->id = id;
	if (cap == NULL)
		return nou;
	else
	{
		nou->next = cap;
		cap = nou;
		return cap;
	}
}

int pop(NodStiva* &cap)
{
	if (cap)
	{
		int id = cap->id;
		NodStiva* temp = cap;
		cap = cap->next;
		free(temp);
		return id;
	}
	else
	{
		return -1;
	}
}

int calculareNumarNoduri(nodlp* graf)
{
	int contor = 0;
	nodlp *temp = graf;
	while (temp)
	{
		contor++;
		temp = temp->next;
	}
	return contor;
}

//parcurgere in adancime
void parcurgereAdancime(nodlp* graf, int idNodStart)
{
	if (graf)
	{
		NodStiva* stiva = NULL;
		int nrNoduri = calculareNumarNoduri(graf);
		int* vizitate = (int*)malloc(sizeof(int)*nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitate[i] = 0;
		}

		stiva = push(stiva, idNodStart);
		vizitate[idNodStart] = 1;

		while (stiva)
		{
			int idNodCurent = pop(stiva);

			nodlp *nodCurent = cautareDupaId(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.nume);

			nodls *p = nodCurent->vecini;
			while (p)
			{
				if (vizitate[p->info->info.id] == 0)
				{
					stiva = push(stiva, p->info->info.id);
					vizitate[p->info->info.id] = 1;
				}
				p = p->next;
			}
		}
	}
}

void dezalocareLS(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		nodls *temp2 = temp->next;
		free(temp);
		//free(temp->info->info.nume);
		//free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodlp* cap) {
	nodlp* temp = cap;
	while (temp) {
		nodlp *temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters %s", temp->info.nume);
		free(temp->info.nume);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	nodlp* graf = NULL;
	int nrNoduri;
	printf("Nr de noduri: ");
	scanf("%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)//citesc studenti
	{
		//id-ul va fi i-ul, numele citit de la tast
		student s;
		s.id = i;
		char buffer[20];
		printf("Numele studentului : ");
		scanf("%s", &buffer);
		s.nume = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
		strcpy(s.nume, buffer);
		graf = inserareLP(graf, s);
	}

	//inserare arce(vecinii pt fiecare nod)
	int nrArce = 0;
	printf("Nr de arce: ");
	scanf("%d", &nrArce);

	for (int i = 0; i < nrArce; i++)
	{
		int idStart;
		printf("Sursa: ");
		scanf("%d", &idStart);
		int idStop;
		printf("Destinatie: ");
		scanf("%d", &idStop);
		inserareArcInGraf(graf, idStart, idStop);
	}

	//afisare
	traversareLP(graf);
	//parcurgere in adancime
	parcurgereAdancime(graf, 0);

	dezalocareLP(graf);
}