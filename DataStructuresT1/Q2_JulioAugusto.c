//Fila inteligente, função ammount conta quantos itens tem na fila, função getTicket compara todos esses valores e dependendo, adiciona na fila correta. A fila menor sempre recebe o novo usuário, estou orgulhoso do meu códgigo, espero que tu goste <3

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define menuEntries 4

typedef struct tie {int val; struct tie *next;} knot;

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

//recebe valor int
void getVal (int *val) {
	clear();
	scanf("%d", val);
	clearStdin();
}
//imprime a lista
void prntStack (knot *beg) {
	knot *read = beg;
	int pos = 0;
	if(beg == NULL) {
		printf("The line is empty!\n");
	} else {
			printf("Address\t\tTicket\tNext\n");
		do {
		    printf("%p\t%d\t%p\n", read, read->val, read->next);
			read = read->next;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar();
}

int ammount(knot *beg) {
    knot *read = beg;
    int ammount = 1;
    while (read != NULL) {
        read = read->next;
        ammount++;
    }
    return ammount;
}

void insertBottom (knot **beg, int val) {
    knot *new, *read = *beg;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("You've filled up all your memory, or something very wrong has happened!\n");
    } else {
        new->val = val;		//atribuí o valor para a variável final.
        if (*beg == NULL) { //insere o primeiro
            *beg = new;     //arruma o início
        } else {
            while (read->next != NULL) {		//até o fim da lista, já que eu não estou usando o ponteiro do final
                read = read->next;			//lê o próximo valor
            }
            read->next = new;                 // não muda o início... já que é no final, né...
        }
        new->next = NULL;
    }
}

void rmUp (knot **beg) {
	knot *read = *beg;
	if (read == NULL) {
		printf("The line is empty! Press Return to Main Menu");
        getchar();
    } else {
		if(read->next != NULL) {
			*beg = read->next;
		} else {
			*beg = NULL;
		}
		free(read);
	}
}

void mainMenu (int *menu) {
    clear();
	printf ("Main menu\n\n1-GetTicket  2-RemoveFromLine  3-PrintLists  4-Exit\n\nInsert your option: ");
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
	clearStdin();
    clear();
}

void getTicket(knot **l1, knot** l2, knot** l3, int ticket) {
    const int l1Size = ammount(*l1), l2Size = ammount(*l2), l3Size = ammount(*l3); //caso eu precise usar esses valores mais de uma
    printf("Your ticket is number %d ", ticket);
    if (l1Size <= l2Size && l1Size <= l3Size) { //l1 = menor
        insertBottom(l1, ticket);
        printf("and you should go to line 1!\n\n");
    } else if (l2Size <= l1Size && l2Size <= l3Size) { //l2 = menor
        insertBottom(l2, ticket);
        printf("and you should go to line 2!\n\n");
    } else if (l3Size <= l1Size && l3Size <= l2Size) { //l3 = menor
        printf("and you should go to line 3!\n\n");
        insertBottom(l3, ticket);
    }
    printf("Press Return to direct the client to their correct line and go back to the Main Menu");
	getchar();
    // if (l1Size < l2Size) { //primeiro menor que o segundo
    //     if(l1Size < l3Size) { //primeiro menor que o terceiro, portanto o menor de todos
    //         insertBottom(l1, ticket);
    //     } else { //primeiro menor que o segundo e maior que o terceiro
    //         insertBottom(l3, ticket); //adiciona no terceiro
    //     }
    // } else { //primeiro maior que o segundo
    //     if (l2Size < l3Size) { //e o segundo for menor do que o terceiro
    //         insertBottom(l2, ticket);
    //     } else { //segundo for maior que o terceiro
    //         insertBottom(l3, ticket);
    //     }
    // } //acho que eu não cobri todas as bases, mas chegou perto.
}

void removeFromLine (knot **l1, knot** l2, knot** l3) {
    int val;
    printf("From which line would you like to remove a person? (1, 2, 3): ");
    getVal(&val);
    while (val < 1 || val > 3) {
		printf ("Invalid option, try again: ");
		getVal(&val);
	} switch (val) {
        case 1: rmUp(l1);
                break;
        case 2: rmUp(l2);
                break;
        case 3: rmUp(l3);
                break;
    }
}

void printLists (knot **l1, knot** l2, knot** l3) {
    int val;
    printf("Which line would you like to print? (1, 2, 3): ");
    getVal(&val);
    while (val < 1 || val > 3) {
		printf ("Invalid option, try again: ");
		getVal(&val);
	} switch (val) {
        case 1: prntStack(*l1);
                break;
        case 2: prntStack(*l2);
                break;
        case 3: prntStack(*l3);
                break;
    }
}

int main () {
    knot *l1 = NULL, *l2 = NULL, *l3 = NULL; //fila 1, fila 2, fila 3;
    int menu, ticket;
    do {
		mainMenu(&menu);
		switch (menu) {
			case 1: getTicket(&l1, &l2, &l3, ++ticket);
					break;
			case 2: removeFromLine (&l1, &l2, &l3);
					break;
			case 3: printLists (&l1, &l2, &l3);
        }
    } while (menu != menuEntries);
}

