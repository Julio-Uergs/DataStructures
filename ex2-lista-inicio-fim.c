#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tie {
	int val;
	struct tie *nxt;
} knot;

void pileUp (knot **beg, int val) {
    knot *new;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
    else {
        new->val = val; 				//atribuí o valor para a variável final.
		// printf("End Val: %p\tEnd Ptr: %p\n", &new->val, new);
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->nxt = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->nxt = *beg;			//se não, aponta para o "de baixo"
        }
		*beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
		printf("Press Return to Main Menu");
		getchar(), getchar();
}

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
			printf("Val\tCurrent\t\tNext\n");
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
	printf ("Main Menu\n\n1-PileUp\n2-PileDown\n3-ListaAllValues\n4-Exit\n\nInsert your option: ");
	scanf ("%d", men);
	while (*men < 1 || *men > 4) {
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
					pileUp(&beg, val);
					break;
			case 2: getVal(&val);
					pileDown(&beg, val);
			case 3: prntStack(beg);
		}
	} while (men != 4);
}

