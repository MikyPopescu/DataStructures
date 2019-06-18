
#include "pch.h"
#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct student {
	int id;
	char* name;
	int noGrades;
	int* grades;
};
struct node {
	student inf;
	node* next;
};
int main()
{
    std::cout << "Hello World!\n"; 
}

