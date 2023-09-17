//Julio Augusto de Castilhos Borges
//Insere fim, inicio, meio, ordenado, remove fim, remove inicio, busca valor, tornar lista circular

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tie {
	// struct tie *b4;
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

void getVal (int *val) { //recebe valores
	scanf("%d", val);
	clearStdin();
}

void prntStack(knot *beg) {
	knot *end;
	bool circular = true;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
		end = beg;
		printf("Val\tCurrent\t\tNext\n");
		while(end != NULL && circular) {
			if (end->next == beg) {
				circular = false;
			}
		printf("%d\t%p\t%p\n", end->val, end, end->next);
		end = end->next;
		}
	}
}

void pileUp (knot **beg, int val) { //Insere no início
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
}

void pileInBtwn(knot **beg, int srch, int val) { //insere no meio
	// while (read != NULL || read->val == srch) {
	// 	prev = read;
	// 	read = read->next;
	// }
	knot *aux = *beg, *b4 = NULL, *new;
	bool inserted = false, found = false;
	if (*beg == NULL) {
		printf("The stack is empty!\n");
		found = true;
	} else {
		while (aux != NULL) {
			if (aux->val == srch) {
				if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito
					printf("Memory Full!\n");
				else {
					if (new != NULL) {
						new->val = val;
						if (b4 == NULL) {
							new->next = *beg;
							*beg = new;
						} else {
							new->next = aux;
							b4->next = new;
						}
					inserted = true;
					}
				}
			}
			b4 = aux;
			aux = aux->next;
		}
	} if (!inserted && !found) {
		printf("The number %d was not found\n", val);
	}
	printf("Press Return to Main Menu");
	/*getchar(), */getchar();
}

void pileDown (knot **beg, int val) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg ; //insere embaixo
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
    prntStack(*beg);
    printf("Press Return to Main Menu");
	/*getchar(),*/ getchar();
}

void srchStack (knot *beg) { //pesquisa
	knot *read = beg;
	int val;
	bool check = false;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
		printf("Insert a value to be searched for: ");
		getVal(&val);
		do {
			if(read->val == val) {
				printf("%d\t%p\n", read->val, read->next);
				check = true;
			}
			read = read->next;
		} while (read != NULL);
		if (check == false) {
		printf("Value %d not found!\n", val);
		}
	}
	printf("Press Return to Main Menu");
	/*getchar(), */getchar();
}

void rmUp (knot **beg) { //remove no início
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
	prntStack(*beg);
	printf("Press Return to Main Menu");
	/*getchar(), */getchar();
}

void rmInBtwn(knot **beg, int srch, knot *read, knot *b4) {
	knot *freeP;
	int index;
	if (read != NULL) {
		if (index == srch) {
			if (b4 == NULL) {
				*beg = read->next;
				freeP = read;
				read = read->next;
				free(freeP);
				rmInBtwn(beg, srch, read, NULL);
			} else {
				b4->next = read->next;
				freeP = read;
				read = read->next;
				free(freeP);
				rmInBtwn(beg, srch, read, b4);
			}
		} else {
			rmInBtwn(beg, srch, read->next, read);
		}
	}
}

// void removeInBtwn(knot **beg, int srch) { //insere no meio
// 	knot *aux = *beg, *b4 = NULL, *new;
// 	bool traversed = false, found = true;
// 	if (*beg == NULL) {
// 		printf("The stack is empty!\n");
// 		found = true;
// 	} else {
// 		while (aux != NULL) {
// 			traversed = true;
// 			if (aux->val == srch) {
// 				free(b4);
// 			}
// 			b4 = aux;
// 			aux = aux->next;
// 		}
// 	} if (!found) {
// 		printf("The number %d was not found\n", srch);
// 	} if (!traversed) {
// 		*beg = NULL;
// 	} else {
// 		aux->next = NULL;
// 	} printf("Press Return to Main Menu");
// 	/*getchar(), */getchar();
// }

void order (knot **beg) {
	knot *new, *read = *beg, *prev;
	int val, srch;
	getVal(&srch);
	if (beg == NULL) {
		if((new = (knot*) malloc (sizeof(knot))) == NULL) {
			printf("Memory Full!\n");
		} else {
			printf("Insert the value to be stored: ");
			getVal(&val);
			new->val = val;
			*beg = new;
			new->next = NULL;
		}
	} else {
		// prev = NULL;
		while (read != NULL || srch > read->val) {
			prev = read;
			read = read->next;
		}

	}

}

void rmDown (knot **beg) { //remove no fim
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

void circularize (knot *read, knot *aux) { //transforma em circular
	if (read == NULL) {
		printf("The stack is empty!\n");
	}
	else {
		if (aux->next == read || aux->next == NULL) {
			aux->next = read;
		}
		else {
			circularize(read, aux->next);
		}
	}
}

void swap(knot *a, knot *b) { //troca pro bblsort
  int temp = a->val;
  a->val = b->val;
  b->val = temp;
}

void bblSort(knot **beg) { //bblsort padrãozinho
	knot *current = *beg;
  	knot *read = NULL;
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		current = *beg;
		read = current->next;
		while (read != NULL) {
			if (current->val > read->val) {
				swap(current, read);
				swapped = 1;
			}
			current = read;
			read = read->next;
		}
	}
}

void mMenu (int *men) { //menu principal
    clear();
	printf ("Main Menu\n\n1-PileUp\t6-RemoveInBtwn\n2-PileInBtwn\t7-RemoveDown\n3-PileDown\t8-ListAllValues\n4-Search\t9-PileOrdered\n5-RemoveUp\t10-Circularize\n\t\t11-Exit\n\nInsert your option: ");
	scanf ("%d", men);
	while (*men < 1 || *men > 11) {
		printf ("Invalid option, try again: ");
		scanf ("%d", men);
	}
	clearStdin();
}

int main () {
	knot *beg = NULL;
	int val, srch, men;
	do {
		mMenu(&men);
		switch (men) {
			case 1: printf("Insert the value to be added to the list: ");
					getVal(&val);
					pileUp(&beg, val);
					prntStack(beg);
					printf("Press Return to Main Menu");
					/*getchar(), */getchar();
					break;
			case 2: printf("Insert the value to be added to the list: ");
					getVal(&val);
					// clear();
					printf("Insert the value in the list so your value %d can be added before it: ", val);
					getVal(&srch);
					pileInBtwn(&beg, srch, val);
					break;
			case 3: printf("Insert the value to be added to the list: ");
					getVal(&val);
					pileDown(&beg, val);
					break;
			case 4: srchStack(beg);
					break;
			case 5: rmUp(&beg);
					break;
			case 6: printf("Insert a val in the list so the one before it can be removed: ");
					getVal(&val);
					rmInBtwn(&beg, val, beg, NULL);
					break;
			case 7: rmDown(&beg);
					break;
			case 8: prntStack(beg);
					printf("Press Return to Main Menu");
					/*getchar(),*/ getchar();
					break;
			case 9: printf("Insert the value to be added to the list: ");
					getVal(&val);
					pileUp(&beg, val);
					bblSort(&beg);
					prntStack(beg);
					printf("Press Return to Main Menu");
					/*getchar(), */getchar();
					break;
			case 10:circularize(beg, beg);
		}
	} while (men != 11);
}
