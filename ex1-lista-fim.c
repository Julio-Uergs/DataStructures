#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tie {
	int val;
	struct tie *nxt;
} knot;

//adiciona no final
void pileDown (knot **beg, int val) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg ; //?
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		new->val = val;					//atribuí o valor para a variável final.
		if(*beg == NULL) {
			*beg = new;
			new->nxt = NULL;
		} else {
			while (read->nxt != NULL) {		//até o fim da lista
				read = read->nxt;			//lê o próximo valor
			}
			read->nxt = new;
			new->nxt = NULL;
		}
    }
}

//imprime a lista
void prntStack (knot *beg) {
	knot *read = beg;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Val\tCurrent\tNext\n");
		do {
		    printf("%d\t%p\t%p\n", read->val, read, read->nxt);
			read = read->nxt;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar(), getchar();
}

void mMenu (int *men) {
    #ifdef _WIN32
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif
	printf ("Main Menu\n\n1-PileDown\n2-ListaAllValues\n3-Exit\n\nInsert your option: ");
	scanf ("%d", men);
	while (*men < 1 || *men > 3) {
		printf ("Invalid option, try again: ");
		scanf ("%d", men);
	}
}

void getVal (int *val) {
	#ifdef _WIN32
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif
	printf("Insert any value: ");
	scanf("%d", val);
}


int main () {
	knot *beg = NULL;
	int val, men;
	do {
		mMenu(&men);
		switch (men) {
			case 1: getVal(&val);
					pileDown(&beg, val);
					break;
			case 2: prntStack(beg);
		}
	} while (men != 3);
}

