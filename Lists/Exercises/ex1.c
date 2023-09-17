#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "clear.c"

#define menuEntries 5

typedef struct tie {
    // struct tie *prev;
    int val;
    struct tie *next, *undo;
} knot;

void getVal (int *val) { //recebe valores
	scanf("%d", val);
	clearStdin();
}

void prntStack(knot *beg) {
	knot *read;
	if(beg == NULL) {
		printf("The stack is empty!\n");
	} else {
		read = beg;
		printf("Val\tCurrent\t\tNext\n");
        while(read != NULL) {
            printf("%d\t%p\t%p\n", read->val, read, read->next);
            read = read->next;
		}
	}
}

knot* find (knot *beg, int srch) {
    knot *read = beg, *flag; //flags the car to be removed
    int index = 1; //bugado
    bool found = false;
    while (read != NULL) {
        if (found) {
            read->val++;
        }
        if (srch == index) {
            flag = read;
            found = true;
        }
        read = read->next;
        index++;
    }
    return flag;
}

void insertBeg(knot** beg) {
    knot *new;
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("Memory Full!\n");
    else {
        printf("Insert any value: ");
        getVal(&val);
        new->val = val; 				//atribuí o valor para a variável final.
		// printf("End Val: %p\tEnd Ptr: %p\n", &new->val, new);
        if (*beg == NULL)				//verifica se é o último  (ou, no caso, o único?) item da pilha
            new->next = NULL;			//se sim, salva o ponteiro como NULL, indicando que ele é o último item.
        else
            new->next = *beg;			//se não, aponta para o "de baixo"
        }
    *beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
    prntStack(*beg);
    printf("Press Return to Main Menu");
    getchar();
}

void mMenu (int *men) { //menu principal
    clear();
    printf ("Garage Menu:\n\n1-InsertBeg    2-PrntStack    3-RemoveBeg    4-Undo    5-Exit\n\nInsert your option: ");
    getVal(men);
    // printf("%d", *men);
    while (*men < 1 || *men > menuEntries) {
        printf ("Invalid option, try again: ");
        getVal(men);
    }
    // clearStdin();
    clear();
}

void rmBeg (knot **beg) {
    knot *read = *beg;
	if (read == NULL)
		printf("The stack is empty!\n");
	else {
		if(read->next != NULL)
			*beg = read->next;
		else
			*beg = NULL;
		printf("Removed %p successfully!\n", read);
		free(read);
	}
	printf("Press Return to Main Menu");
    getchar();
}

void undo (knot **beg) {

}

int main () {
    knot *beg = NULL, *begUndo = NULL; //begG == Garage, begS == Street
    int men;
    do {
        mMenu(&men); //imprime menu
        switch (men) {
            case 1: insertBeg(&beg); //insere no fim
                    break;
            case 2: prntStack(beg);
                    printf("Press Return to Menu");
                    getchar();
                    break;
            case 3: rmBeg(&beg);
                    break;
            case 4: undo(&beg);
                    break;

        }
    } while (men != menuEntries);
    clear();

}
