#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define menuEntries 10

typedef struct tie {struct tie *prev; int val; struct tie *next;} knot; //let's go!'

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

void clearVerifier (long unsigned int size, char *string) { //NEM sempre é bom limpar o buffer
    // printf("%ld %ld\n", size, strlen(string));
    if (strlen(string) + 1 == size) {
        clearStdin();
    }
}

void getVal (int *val) {
	clear();
	scanf("%d", val);
	clearStdin();
}

knot* srchChain (knot *beg) {
	int srch;
	knot *read = beg;
	printf("Insert a value to be added to be found in the knot: ");
	getVal(&srch);
	do {
		read = read->next;
	} while (srch != read->val);//será que funciona
	return read;
}

//imprime a knota
void prntChain (knot *beg, knot *end) {
	knot *read = beg;
	if(beg == NULL) {
		printf("There are no values stored in memory!\n");
	} else {
			printf("\tBeg:\t%p\n\nPrev\t\tCurrent\t\tVal\tNext\n%p\t\t%p\t%d\t%p\n", beg, read->prev, read, read->val, read->next);
			read = read->next;
		while (read != NULL) {
		    printf("%p\t%p\t%d\t%p\n", read->prev, read, read->val, read->next);
			read = read->next;
	    }
	    printf("\n\tEnd:\t%p\n\n", end);
	}
	printf("Press Return to Main Menu");
	getchar();
}


void addBeg (knot **beg, knot **end) {
	knot *new;
	int val;
    if ((new = (knot*) malloc (sizeof(knot))) == NULL) {//aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
		getchar();
    } else {
		printf("Insert a value to be added to the beginning of the knot: ");
		getVal (&val);
        new->val = val; 				//atribuí o valor
		new->next = *beg;			//insere no início
		new->prev = NULL;			//não existe um anterior ao primeiro
		if (*beg != NULL) {			//(*beg != NULL) == (*beg)
			(*beg)->prev = new;		//o anterior do início recebe o início (próximo do novo)
		} else {
			*end = new;
		}
		*beg = new;
		// printf("Press Return to Main Menu");
		// getchar();
	}
}


void addMid (knot **beg, knot **end) {
    knot *new, *read = *beg;
	int val, srch;
	bool found = false;
    if ((new = (knot*) malloc (sizeof(knot))) == NULL) {//aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
		getchar();
    } else {
		printf("Insert a value to be found in the knot: ");
		getVal(&srch);
		while (srch != read->val && read != NULL) { //será que funciona
			read = read->next;
			found = true;
		}
		printf("Insert a value to be added to the middle of the knot: ");
		getVal (&val);
		new->val = val;
		if (found) {
			read = read->prev; 			//volta 1
			new->next = read->next;	//anterior prox prox
			read->next = new;
			new->prev = read;
		} else {
			new->next = *beg;			//insere no início
			new->prev = NULL;			//não existe um anterior ao primeiro
			if (*beg != NULL) {			//(*beg != NULL) == (*beg)
				(*beg)->prev = new;		//o anterior do início recebe o início (próximo do novo)
			} else {
				*end = new;
			}
			*beg = new;
		}
	}
}

void addEnd (knot **beg, knot **end) {
    knot *new;
	int val;
    if ((new = (knot*) malloc (sizeof(knot))) == NULL) {//aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
		getchar();
    } else {
		printf("Insert a value to be added to the beginning of the knot: ");
		getVal (&val);
        new->val = val; 				//atribuí o valor
		new->next = NULL;			//insere no início
		new->prev = *end;			//não existe um anterior ao primeiro
		if (*end != NULL) {			//(*beg != NULL) == (*beg)
			(*end)->next = new;
		} else {
			*beg = new;
		}
		*end = new;
		// printf("Press Return to Main Menu");
		// getchar();
	}
}

void mainMenu (int *menu) {
    clear();
	printf ("Main menu\n\n1-InsertBeginning\t2-RemoveBeginning\t3-InsertMid\t4-RemoveMid\n5-InsertEnd\t\t6-RemoveEnd\t\t7-PrintValues\t8-Search\n9-Circularize\t\t10-Exit\n\nInsert your option: ");
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
	clearStdin();
    clear();
}

//remove o primeiro item, se o primeiro for também o último, remove o último :P
void rmBeg (knot **beg, knot **end) {
	knot *aux = *beg;
	if (aux != NULL) { 			//se houverem itens
		if (aux->next != NULL) {	//se houver mais de 1 item
			aux->next->prev = NULL;
			*beg = aux->next;
			free(aux);
		} else {
			free(aux);
			*beg = NULL;
			*end = NULL;
		}
    } else {
		printf("The line is empty! Press Return to Main Menu");
        getchar();
	}
}

void rmMid (knot **beg, knot **end) {
    knot *remove, *read = *beg;
	int val, srch;
	bool found = false;
	printf("Insert a value to be removed in the knot: ");
	getVal(&srch);
	while (srch != read->val && read != NULL) { //será que funciona
		read = read->next;
		found = true;
	} if (found) {
		read = read->prev; 			//volta 1
		if (read->next != NULL) { //meio
			read->next = read->next->next;
		} else { //fim
			read->next = NULL;
		}
		free(remove);
	} else { //início
		if (read->next != NULL) {	//se houver mais de 1 item
			read->next->prev = NULL;
			*beg = read->next;
			free(read);
		} else {
			free(read);
			*beg = NULL;
			*end = NULL;
		}
	}
}


//remove o último item, se o último for também o primeiro, remove o primeiro :P
void rmEnd (knot **beg, knot **end) {
	knot *aux = *end;
	if (aux != NULL) { 			//se houverem itens
		if (aux->prev != NULL) {	//se houver mais de 1 item
			aux->prev->next = NULL;
			*end = aux->prev;
			free(aux);
		} else {
			free(aux);
			*beg = NULL;
			*end = NULL;
		}
    } else {
		printf("The line is empty! Press Return to Main Menu");
        getchar();
	}
}

void uncircularize(knot **beg, knot *aux) {
	if (*beg != NULL && aux != NULL) {
		if (aux->next == *beg) {
			aux->next->prev = NULL;
			aux->next = NULL;
		} else {
			uncircularize(beg, aux->next);
		}
	}
}

void circularize(knot *start, knot *end) {
	if (start != NULL) {
		if (end->next != NULL) {
			circularize(start, end->next);
		} else {
			end->next = start;
			start->prev = end;
		}
	}
}

void prntCircular(knot *beg, knot *auxPrint, bool first) {
	if (beg != NULL ) {
		if (auxPrint != beg || first) {
			printf("%p\t%p\t%d\t%p\n", auxPrint->prev, auxPrint, auxPrint->val, auxPrint->next);
			prntCircular(beg, auxPrint->next, false);
		}
	}
	else {
		printf("The line is empty! ");
	}
}

int main () {
    knot *beg = NULL, *end = NULL;
    int menu;
    do {
		mainMenu(&menu);
		switch (menu) {
			case 1: addBeg(&beg, &end);
					break;
			case 2: rmBeg (&beg, &end);
					break;
			case 3: addMid(&beg, &end);
					break;
			case 4: rmMid(&beg, &end);
					break;
			case 5: addEnd(&beg, &end);
					break;
			case 6: rmEnd(&beg, &end);
					break;
			case 7: prntChain(beg, end);
					break;
			case 8: srchChain(beg);
					break;
			case 9: circularize(beg, end);
					printf("\tBeg:\t%p\n\nPrev\t\tCurrent\t\tVal\tNext\n", beg);
					prntCircular(beg, beg, true);
					printf("\n\tEnd:\t%p\n\n", end);
					uncircularize(&beg, beg);
					printf("Press Return to Main Menu");
					getchar();
					break;
        }
    } while (menu != menuEntries);
    clear();
}
