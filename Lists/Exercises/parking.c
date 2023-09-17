// Considere que um estacionamento da Rua Direita, em Porto Alegre, que é composto por uma única alameda que vários carros.
// Existe apenas uma entrada/saída no estacionamento, e esta extremidade da alameda dá acesso justamente à Rua Direita.

// Escreva um programa que processe um grupo de linhas de entrada.
// Cada linha de entrada contém um ‘E’ ou 1, de entrada, ou um ‘S’ ou 2 de saída, e o número da placa do carro.
// Presume-se que os carros cheguem e partam na mesma ordem que entraram no estacionamento.
// O programa deve imprimir uma mensagem sempre que um carro chegar ou sair.
// Quando um carro sair do estacionamento, a mensagem deverá incluir o número de vezes em que o carro foi manobrado para fora do estacionamento para permitir que os outros carros saíssem.
// Se chegar um cliente para retirar um carro que não seja o mais próximo da saída, todos os carros bloqueando seu caminho sairão do estacionamento.
// O carro do cliente será manobrado para fora do estacionamento, e os outros carros voltarão a ocupar a mesma sequência inicial.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "clear.c"

typedef struct tie {
    // struct tie *prev;
    int xMoved;
    struct tie *next;
} knot;

void getVal (int *val) { //recebe valoores
    scanf("%d", val);
    clearStdin();
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

knot* findCar (knot *beg, int srch) {
    knot *read = beg, *flag; //flags the car to be removed
    int index = 1; //bugado
    bool found = false;
    while (read != NULL) {
        if (found) {
            read->xMoved++;
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

void prntGarage (knot *beg) {
	knot *read = beg;
	int pos = 1;
	if(beg == NULL) {
		printf("The parking lot is empty!\n");
	} else {
			printf("Parking Spot\tLicense Plate\tTimes Moved\n");
		do {
		    printf("%.12d\t%p\t%d\n", pos++, read, read->xMoved);
			read = read->next;
	    } while (read != NULL);
	}
}

void prntStreet (knot *beg) {
	knot *read = beg;
	int pos = 1;
	if(beg == NULL) {
		printf("The street is empty!\n");
	} else {
			printf("Street Spot\tLicense Plate\tTimes Moved\n");
		do {
		    printf("%.12d\t%p\t%d\n", pos++, read, read->xMoved);
			read = read->next;
	    } while (read != NULL);
	}
	printf("\n");
}

void parkCar (knot **beg) { 	//i know it's not that way, but you get what I mean...
    knot *new, *read = *beg ; //insere embaixo
    if((new = (knot*) malloc (sizeof(knot))) == NULL) {
        printf("Memory Full!\n");
    } else {
        clear();
        if(*beg == NULL)
            *beg = new;						//atribuí o novo início, já que ele sempre vai mudar.
        else {
            while (read->next != NULL) {		//até o fim da lista
                read = read->next;			//lê o próximo xMovedor
            }
            read->next = new;
        }
        new->next = NULL;
        new->xMoved = 0;
    }
    clear();
    prntGarage(*beg);
    printf("Press Return to Garage Menu");
    /*getchar(),*/ getchar();
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
		printf("Car with plate %p was moved %d times before leaving the parking lot!\n\n", read, read->xMoved);
		free(read);
	}
}

void rmDown (knot **beg) { //remove no fim
    bool traversed = false;
    knot *read = *beg, *aux;
    if (read == NULL) {
        printf("The parking lot is empty!\n");
    } else {
        while (read->next != NULL) {
            aux = read;
            read = read->next;
            traversed = true;
        }
        printf("Car with plate %p was moved %d times before leaving the parking lot!\n\n", read, read->xMoved);
        free(read);
        if (!traversed)
            *beg = NULL;
        else
            aux->next = NULL;
    }
}

void moveCar(knot *srcMinusOne, knot **dest) { //move (source, dest);
    if (srcMinusOne == NULL) {
        printf("The parking lot is empty!\n");
    } else {
        *dest = srcMinusOne->next; //dest == the one to remove
        rmUp(dest); //dest->next == the actual car to be removed;
        srcMinusOne->next = *dest ; //dest = dest->next
        prntStreet(*dest);
        *dest = NULL;
    }
}

void mMenu (int *men) { //menu principal
    clear();
    printf ("Garage Menu:\n\n1-ParkCar\t2-RemoveCar\t3-Overview\t4-Exit\n\nInsert your option: ");
    scanf ("%d", men);
    while (*men < 1 || *men > 4) {
        printf ("Invalid option, try again: ");
        scanf ("%d", men);
    }
    clearStdin();
    clear();
}

void removeCar(knot **beg, knot *begS) {
    knot *rm, *rmAux;
    int index;
    const int garageSize = ammount(*beg);
    prntGarage(*beg); //imprime a lista da garagem com o texto correspondente, provavelmente tem um jeito melhor, mas eu não consegui pensar em um jeito bom de fazer isso
    printf("Choose the parking spot of the car to be removed: ");
    getVal(&index);
    clear();
    while (index < 0 || index > garageSize) {
        printf("Invalid parking spot, please try again! ");
        getVal(&index); //recebe valor
        clear(); //limpa a tela
    } if (index == 1) { //se for o primeiro, não pega a posição anterior, né...  switch (index) {
        findCar(*beg, index);                                                // case 1:
        rmUp(beg);  //remove da rua                                             findCar(*beg, index);
    } else if (index == garageSize) { //                                        rmUp(beg);
        rmDown(beg);                                                         // break;
    } else {                                                                 // case garageSize:
        moveCar(findCar(*beg, (index - 1)), &begS); //source dest. move pra rua e remove rmDown(beg);
    }                                                                        // break;
    prntGarage(*beg);                                                        // default:
    printf("Press Return to Garage Menu");                                   // moveCar(findCar(*beg, (index - 1)), &begS);
    getchar();
}

int main () {
    knot *begG = NULL, *begS = NULL; //begG == Garage, begS == Street
    int men;
    do {
        mMenu(&men); //imprime menu
        switch (men) {
            case 1: parkCar(&begG); //insere no fim
                    break;
            case 2: removeCar(&begG, begS); //remove o carro, peguntando para o usuário qual o carro dele
                    break;
            case 3: clear();
                    prntGarage(begG);
                    printf("Press Return to Garage Menu");
                    getchar();
                    break;
        }
    } while (men != 4);
    clear(); //fim
}
