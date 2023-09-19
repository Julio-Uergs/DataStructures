//P1, P2, Line, ir desempilhando alternado...
//Por exemplo, se foi inserido 1,2,3 sucessivamente na pilha 1 (ou seja, a ordem de cima para baixo fica 3,2,1), e 4,5,6 na 2 (6,5,4), quando desempilhar vai ficar (3,6,2,5,1,4).

#include <stdio.h>
#include <stdlib.h>

#define menuEntries 7

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

void getVal (int *val) {
	clear();
	scanf("%d", val);
	clearStdin();
}

int ammount(knot *beg) {
    knot *read = beg;
    int ammount = 0;
    while (read != NULL) {
        read = read->next;
        ammount++;
    }
    return ammount;
}

//imprime a lista
void prntStack (knot *beg) {
	knot *read = beg;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
			printf("Address\t\tVal\tNext\n");
		do {
		    printf("%p\t%d\t%p\n", read, read->val, read->next);
			read = read->next;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar();
}

void insertTop (knot **beg, char *string) {
    knot *new;
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("You've filled up all your memory, or something very wrong has happened!\n");
    else {
        printf("Please insert a value to be added to the top of the %s: ", string);
        getVal(&val);
        new->val = val; 				    //atribuí o valor para a variável final.
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->next = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->next = *beg;			//se não, aponta para o "de baixo"
        }
		*beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
}

void moveSourceToDestination(knot **source, knot **destination) {
    knot *readSrc = *source, *readDest = *destination; //source = beg, destination = end
    *source = readSrc->next;
    if (*destination == NULL) {
        readSrc->next = *destination;
        *destination = readSrc;      //isso me bugou, tava inserindo na ordem errada antes
    } else {
        while (readDest->next != NULL) {
            readDest = readDest->next;
        } //até o penúltimo
        readDest->next = readSrc;
        readSrc->next = NULL;
    }
}

void transformIntoLine(knot **line, knot **p1, knot **p2) {
    const int p1Size = ammount(*p1), p2Size = ammount(*p2); //caso eu precise usar esses valores mais de uma vez... e eles não precisam ser modificados uma vez dentro do escopo da função, já que só podem mudar fora dela;
    while (*p1 != NULL || *p2 != NULL) {
        if (*p1 != NULL) {
            moveSourceToDestination(p1, line);
        }
        if (*p2 != NULL) {
            moveSourceToDestination(p2, line);
        }
    } printf("There were %d elements in P1, %d elements in P2.\nAfter striping them into List, we ended up with %d elements added this time\n\n", p1Size, p2Size, p1Size + p2Size); //eu sou um gênio da lâmpada
    prntStack(*line);

}

void mainMenu (int *menu) {
    clear();
	printf ("Main menu\n\n1-InsertIntoP1  2-InsertIntoP2  3-TransformIntoLine  4-PrintP1  5-PrintP2  6-PrintLine  7-Exit\n\nInsert your option: ");
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
    clearStdin();
    clear();
}

int main () {
    knot *p1 = NULL, *p2 = NULL, *line = NULL;/*, *lineEnd = NULL;*/
    int menu;
    do {
		mainMenu(&menu);
		switch (menu) {
            case 1: insertTop(&p1, "P1"); //achei bonitinho fazer a função genérica e mandar a string pra informar ao usuário qual que eu realmente quero :)
					break;
            case 2: insertTop(&p2, "P2");
                    break;
			case 3: transformIntoLine(&line, &p1, &p2);
                    break;
            case 4: prntStack(p1);
                    break;
            case 5: prntStack(p2);
                    break;
            case 6: prntStack(line);
                    break;
        }
    } while (menu != menuEntries);
}
