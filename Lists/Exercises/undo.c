//Fazer um programa que apague um erro feito pelo usuário

#include <stdio.h>
#include <stdlib.h>
#include "clear.c"

typedef struct tie{int val; struct tie* next;}knot;

void getVal (int *val) { //recebe valores
	scanf("%d", val);
	clearStdin();
}

void prntStack(knot *beg) {
	knot *end;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
		end = beg;
		printf("Val\tCurrent\t\tNext\n");
		while(end != NULL) {
          printf("%d\t%p\t%p\n", end->val, end, end->next);
          end = end->next;
		}
	}
}
//really enjoyed this, but there are way too many cases that can happen, this is good enough as it is
void undo (knot **src, knot **dst) {
    knot *read = *src, *prev;
    if (read == NULL) {
        printf("Can't undo!");
    } else {
        if (read->next == NULL) {
            *src = NULL;
            *dst = read;
        } else {
            do {
                prev = read;
                read = read->next;
            } while (read->next != NULL); //ou, se eu tivesse um ponteiro de final, o que eu ainda não gosto de ter...
            prev->next = NULL;
            *dst = read; //fim
        }
        prntStack(*src);
        prntStack(*dst);
    }
    getchar();
}

void pileUp (knot **beg) { //Insere no início
    knot *new;
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
    else {
        printf("Insert a value to be added to the top of the list: ");
        getVal(&val);
        new->val = val; 				//atribuí o valor para a variável final.
		// printf("End Val: %p\tEnd Ptr: %p\n", &new->val, new);
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->next = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->next = *beg;			//se não, aponta para o "de baixo"
        *beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
        }
}

void pileDown (knot **beg) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg ; //insere embaixo
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		if(*beg == NULL) {
			pileUp(beg);
		} else {
            printf("Insert a value to be added to the bottom of the list: ");
            getVal(&val);
			new->val = val;					//atribuí o valor para a variável final.
			while (read->next != NULL) {		//até o fim da lista
				read = read->next;			//lê o próximo valor
			}
			new->next = NULL;
			read->next = new;
		}
    }
    clear();
    prntStack(*beg);
    printf("Press Return to Main Menu");
	getchar();
}

void mMenu (int *men) { //menu principal
    clear();
	printf ("Main Menu\n\n1-Insert  2-Overview  3-Undo  4-Exit\n\nInsert your option: ");
	getVal(men);
	while (*men < 1 || *men > 4) {
		printf ("Invalid option, try again: ");
		getVal(men);
	}
    clear();
}

int main () {
    knot* begC = NULL, *begU = NULL;
    int menu;
    do {
		mMenu(&menu);
		switch (menu) {
            case 1: pileDown(&begC);
                    break;
            case 2: prntStack(begC);
                    printf("Press Return to Main Menu");
                    getchar();
                    break;
            case 3: undo(&begC, &begU);
                    break;
        }
    }while (menu != 4);
}
