//Após fazer uma busca por valor, insira ordenado uma lista. Ao digitar um valor, o seu código deve fazer a inserção ordenada.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tie {
	int val;
	struct tie *nxt;
} knot;

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

void prntStack (knot *beg) {
	knot *read = beg;
    #ifdef _WIN32
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Val\tAddress\t\tNext\n");
		do {
		    printf("%d\t%p\t%p\n", read->val, read, read->nxt);
			read = read->nxt;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar(), getchar();
}

void InsertValue (knot **beg) {
	knot *new = *beg, *read = *beg;
	int val;
	getVal(&val);
	if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		new->val = val;
		if(*beg == NULL) //se a lista tiver vazia
			new->nxt = NULL;
		else {
			do {
				new = read;
				if(read->val > val)
					*new = *read;
				else
					read = read->nxt;						//lê o próximo valor
			} while (read != NULL || read->val > val);	//até o fim da lista ou até achar
			if (read != NULL)
				new->nxt = NULL;
		}
		*beg = new;
	}
}

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
		prntStack(*beg);
		printf("Press Return to Main Menu");
		getchar(), getchar();
}

void pileInBtwn (knot **beg, int val) { //i know it's not that way, but you get what I mean...
    knot *new, *read = *beg;
	int pos = 0;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		if(*beg == NULL) {
			printf("The stack is empty!\n");
		} else {
			new->val = val;					//atribuí o valor para a variável final.
			do {
				//printf("%d ", pos);
				pos++;						//incrementa contador total de posições
				read = read->nxt;			//lê o próximo valor
			} while (read != NULL);			//até o fim da lista
			pos /= 2;						//pego a metade
			read = *beg;					//reset
			//printf("Val: %d\tEnd: %p\n", read->val, read->nxt);
			//printf("%p\t%p\n", new, *beg);
			for (int i = 1; i < pos; i++) {
				read = read->nxt;
				//printf("Val: %d\tEnd: %p\n", read->val, read->nxt);
			}
			//printf("saiu do loop\n");
			new->nxt = read->nxt;
			//printf("Val: %d\tEnd: %p\n", new->val, new->nxt);
			read->nxt = new;
			//printf("Val: %d\tEnd: %p\n", read->val, read->nxt);
		}
	}
}

void pileDown (knot **beg, int val) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg ; //?
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
		if(*beg == NULL) {
			printf("The stack is empty!\n");
		} else {
			new->val = val;					//atribuí o valor para a variável final.
			while (read->nxt != NULL) {		//até o fim da lista
				read = read->nxt;			//lê o próximo valor
			}
			new->nxt = NULL;
			read->nxt = new;
		}
    }
}

void srchStack (knot *beg) {
    int val;
    knot *read = beg;
    bool found = 0;
    #ifdef _WIN32
    system("cls");
    #endif
    #ifdef linux
    system("clear");
    #endif
	if(beg == NULL) {
		printf("The stack is empty!\n");
        found = 1; //no caso, found nothing, mas eu não consegui pensar numa lógica melhor...
    }
	else {
        getVal(&val);
		do {
			if(read->val == val) {
                if (!found)
                    printf("Val\tAddress\t\tNext\n");
				printf("%d\t%p\t%p\n", read->val, read, read->nxt);
                found = 1;
			}
			read = read->nxt;
		} while (read != NULL);
    }
    if (!found ) {
        #ifdef _WIN32
        system("cls");
        #endif
        #ifdef linux
        system("clear");
        #endif
        printf("Value %d not found!\n", val);
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
	printf ("Main Menu\n\n1-InsertValue\n2-ListAllValues\n3-Exit\n\nInsert your option: ");
	scanf ("%d", men);
	while (*men < 1 || *men > 3) {
		printf ("Invalid option, try again: ");
		scanf ("%d", men);
	}
}

int main () {
	knot *beg = NULL;
	int val, men;
	do {
		mMenu(&men);
		switch (men) {
			case 1: InsertValue(&beg);
					break;
			case 2: prntStack(beg);
					break;
		}
	} while (men != 3);
}
