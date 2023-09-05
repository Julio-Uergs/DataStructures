/*  insere no inicio
	insere_meio
    insere_fim
	procura valor
    remove_inicio
	remove_meio
    remove_fim*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tie {
	// struct tie *prev;
	int val;
	struct tie *next;
} knot;

void clear() {
	#ifdef _WIN32
		system("cls");
    #endif
    #ifdef linux
		system("clear");
    #endif
}

void clearStdin() {
    int c = getchar();
    while (c != '\n') { //do while c == n || c == EOF?
        c = getchar();
    }
}

void getVal (int *val) {
	clear();
	printf("Insert any value: ");
	scanf("%d", val);
	clearStdin();
}

void pileUp (knot **beg, int val) {
    knot *new;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
    else {
        new->val = val; 				//atribuí o valor para a variável final.
		// printf("End Val: %p\tEnd Ptr: %p\n", &new->val, new);
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->next = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->next = *beg;			//se não, aponta para o "de baixo"
        }
		*beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
		printf("Press Return to Main Menu");
		/*getchar(), */getchar();
}

void pileB4Val (knot **beg, int val) { //i know it's not that way, but you get what I mean...
    knot *new, *read = *beg, *aux = *beg;
	int srch, i = 0;
	if(*beg == NULL) {
		if((new = (knot*) malloc (sizeof(knot))) == NULL) {
			printf("Memory Full!\nPress Return to Main Menu");
			getchar();
		} else {
			new->val = val;					//atribuí o valor para a variável final.
			new->next = NULL;
			*beg = new;
		}
	} else {
		getVal(&srch);
		do {
			if(read->next == NULL) { //se for o primeiro da lista
				if(read->val == srch) {

				}
			} else
			if(read->next->val == srch) {
				if((new = (knot*) malloc (sizeof(knot))) == NULL) {
					printf("Memory Full!\nPress Return to Main Menu");
					getchar();
				} else {
					new->val = val;					//atribuí o valor para a variável final.
					new->next = read->next->next;
					read->next = new;				//
				}
			} else {
				read = read->next;
			}
			//printf("Val: %d\tEnd: %p\n", read->val, read->next);
		} while (read != NULL);
		//printf("saiu do loop\n");
		new->next = read->next;
		//printf("Val: %d\tEnd: %p\n", new->val, new->next);
		read->next = new;
		// printf("Val: %d\tEnd: %p\n", read->val, read->next);
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
			while (read->next != NULL) {		//até o fim da lista
				read = read->next;			//lê o próximo valor
			}
			new->next = NULL;
			read->next = new;
		}
    }
}

void prntStack (knot *beg) {
	knot *read = beg;
	int pos = 0;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Val\tPos\tAddress\n");
		do {
		    printf("%d\t%d\t%p\n", read->val, pos++, read->next);
			read = read->next;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar(), getchar();
}

void srchStack (knot *beg) {
	knot *read = beg;
	int val;
	bool check = false;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
		getVal(&val);
		do {
			if(read->val == val) {
				printf("%d\t%p\n", read->val, read->next);
				check = true;
			}
			read = read->next;
		} while (read != NULL);
		if (check == false) {
		printf("Value %d no found!\n", val);
		}
	}
	printf("Press Return to Main Menu");
	/*getchar(),*/ getchar();
}

void rmUp (knot **beg) {
	knot *read = *beg;
	if (read == NULL)
		printf("The stack is empty!\n");
	else {
		if(read->next != NULL) {
			*beg = read->next;
		} else {
			*beg = NULL;
		}
		free(read);
		printf("Removed successfully. ");
	}
	printf("Press Return to Main Menu");
	getchar(), getchar();
}

void rmInBtwn (knot **beg) {
	int pos = 0;
	knot *read = *beg, *before;
	if (read == NULL)
		printf("The stack is empty!\n");
	else
		// do {
		// 	pos++;						//incrementa contador total de posições
		// 	read = read->next;			//lê o próximo valor
		// } while (read != NULL);			//até o fim da lista
		// 	pos /= 2;						//pego a metade
		if (pos == 0) {
			free(read);
			*beg = NULL;
		} else {
			read = *beg;					//reset
			for (int i = 1; i < pos; i++) {
				read = read->next;
			}
			before = read;
			read = read->next;
			before->next = read->next;
			free(read);
	}
	printf("Press Return to Main Menu");
	getchar(), getchar();
}

void rmDown (knot **beg) {
	bool traversed = false;
	knot *read = *beg, *aux;
	if (read != NULL) {
		while (read->next != NULL) {
			aux = read;
			read = read->next;
			traversed = true;
		}
		free(read);
		if (!traversed)
			*beg = NULL;
		else
			aux->next = NULL;
	}
}

void mMenu (int *men) {
    clear();
	printf ("Main Menu\n\n1-PileUp\n2-PileBeforeVal\n3-PileDown\n4-Search\n5-RemoveUp\n6-RemoveInBetween\n7-RemoveDown\n8-ListAllValues\n9-Exit\n\nInsert your option: ");
	scanf ("%d", men);
	while (*men < 1 || *men > 9) {
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
			case 1: getVal(&val);
					pileUp(&beg, val);
					break;
			case 2: getVal(&val);
					pileB4Val(&beg, val);
					break;
			case 3: getVal(&val);
					pileDown(&beg, val);
					break;
			case 4: srchStack(beg);
					break;
			case 5: rmUp(&beg);
					break;
			case 6: rmInBtwn(&beg);
					break;
			case 7: rmDown(&beg);
					break;
			case 8: prntStack(beg);
					break;
		}
	} while (men != 9);
}
