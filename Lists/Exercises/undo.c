//Fazer um programa que apague um erro feito pelo usuário

#include <stdio.h>
#include <stdlib.h>

typedef struct {int val; struct knot* next;}knot;

void clear() {
	#ifdef _WIN32
		system("cls");
    #endif
    #ifdef linux
		system("clear");
    #endif
}

void getVal (int *val) { //recebe valores
	scanf("%d", val);
	clearStdin();
}


int main () {
    knot* beg = NULL;
    getVal(&beg);
}
