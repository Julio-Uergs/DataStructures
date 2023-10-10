#include <stdio.h>
#include <stdlib.h>

#define menuEntries 4

typedef struct tie {struct tie *left; int val; struct tie *right;} knot;
//limpa a tela, independente do sistema operacional e só compila a parte necessária para cada um
void clear() {
	#ifdef _WIN32
		system("cls");
    #endif
    #ifdef linux
		system("clear");
    #endif
}
//limpa o buffer, não é perfeito, mas faz um trabalho legal. Eu já fiz uma função dessas que funciona perfeitamente, mas demora mais pra implementar
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
		printf("The stack is empty!\n");
	} else {
			printf("Left\t\tVal\tRight\n");
		do {
		    printf("%p\t%d\t%p\n", read, read->val, read->right);
			read = read->right;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar();
}
//imprime o menu e recebe os valores, por algum motivo a função de receber os valores estava bugando aqui e eu resolvi não perder tempo tentando descobrir o que tinha de errado.
void mainMenu (int *menu) {
    clear();
	printf ("Main menu\n\n1-InsertIntoTree  2-  3-Print  4-Exit\n\nInsert your option: ");
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
	clearStdin();
    clear();
}

void insertTree (knot **beg, int *val;) {
    knot *new;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) //aloca memória e verifica se houve êxito nessa operação
        printf("You've filled up all your memory, or something very wrong has happened!\n");
    else {
        new->val = val; 				    //atribuí o valor para a variável final.
    }
}
void printTree (knot *beg) {

}

//Não precisa fazer a nova lista!
int main () {
    knot *beg; //fifo
    int menu, val;
    do {
		mainMenu(&menu);
		switch (menu) {
			case 1: if (beg) {  //!= NULL

            } else {
                printf("Please insert a value to be added to the trunk");
                getVal(&val);
                insertTop(&beg);
            }
					break;
			case 2:
					break;
			case 3: ;
        }
    } while (menu != menuEntries);
    clear();
}
