//Inserir no final, já que é uma lista. Quando a soma é selecionada, todos os valores da lista são somados ao valor inserido. Por fim, este valor inserido é adicioado no fim da lista, também :)

#include <stdio.h>
#include <stdlib.h>

#define menuEntries 4

typedef struct tie {int val; struct tie *next;} knot;
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
			printf("Address\t\tVal\tNext\n");
		do {
		    printf("%p\t%d\t%p\n", read, read->val, read->next);
			read = read->next;
	    } while (read != NULL);
	}
	printf("Press Return to Main Menu");
	getchar();
}
//só insere
void insertBottom (knot **beg) {
    knot *new, *read = *beg;
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("You've filled up all your memory, or something very wrong has happened!\n");
    } else {
        printf("Please insert a value to be added to the list: ");
        getVal(&val);
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
//a questão em si, podia só ter chamado o inserir no final, mas aí ia fazer 2 loops completos na lista, assim faz só 1.
void sum (knot **beg) {
    knot *new, *read = *beg;
    int val;
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("You've filled up all your memory, or something very wrong has happened!\n");
    } else {
        printf("Please insert a value to be summed into all values of the list: ");
        getVal(&val);
        new->val = val;
        if (beg == NULL) { //insere o primeiro
            printf("There were no values to be summed into, but the value has been added to the list!");
            *beg = new;     //arruma o início
        } else {
            while (read->next != NULL) {		//até o penúltimo item da lista, já que eu não estou usando o ponteiro do final
                read->val += val;            //soma todos os valores da lista com o que eu quero somar
                read = read->next;		    //lê o próximo valor
            }
            read->next = new;                // não muda o início... já que é no final, né...
            read->val += val;                //soma todos os valores da lista com o que eu quero somar
        }
        new->next = NULL;
    }
}
//imprime o menu e recebe os valores, por algum motivo a função de receber os valores estava bugando aqui e eu resolvi não perder tempo tentando descobrir o que tinha de errado.
void mainMenu (int *menu) {
    clear();
	printf ("Main menu\n\n1-InsertIntoList  2-Sum  3-Print  4-Exit\n\nInsert your option: ");
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
	clearStdin();
    clear();
}

//Não precisa fazer a nova lista!
int main () {
    knot *beg; //fifo
    int menu;
    do {
		mainMenu(&menu);
		switch (menu) {
			case 1: insertBottom (&beg); //inserir no final
					break;
			case 2: sum (&beg);
					break;
			case 3: prntStack(beg);
        }
    } while (menu != menuEntries);
    clear();
}
