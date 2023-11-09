#include <stdio.h>
#include <stdlib.h>

/*          22
       12       30
    8     20 25    40     */

#define menuEntries 7

typedef struct tree {int data; struct tree *left, *right;} tree;
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
//procura na árvore, recursivamente;
void searchData(tree *root, int data, tree **ptr) {
    if (root) {
        *ptr = root;
        if(data > root->data) {
            root = root->right;
        } else {
            root = root->left;
        }
        searchData(root, data, ptr);
    }
}
//Insere na árvore, se o valor já não existir
void insertData(tree **root, int data) {
    tree *newData = (tree*) malloc(sizeof(tree)), *ptr = NULL;
    if (newData) {
        newData->data = data;
        if (*root == NULL) {
            *root = newData;
        } else {
            searchData(*root, data, &ptr);
            if (ptr->data < data) {
                ptr->right = newData;
            } else
                if (ptr->data > data)
                        ptr->left = newData;
        }
        newData->right = NULL;
        newData->left = NULL;
    }
}

//imprime o menu e recebe os valores, por algum motivo a função de receber os valores estava bugando aqui e eu resolvi não perder tempo tentando descobrir o que tinha de errado.
void mainMenu (int *menu) {
    // clear();
	printf ("Main Menu\n\n1-InsertIntoTree  2-PrintTree  3-PreOrder  4-InOrder  5-PostOrder  %d-Exit\n\nInsert your option: ", menuEntries);
	scanf ("%d", menu);
	while (*menu < 1 || *menu > menuEntries) {
		printf ("Invalid option, try again: ");
		scanf ("%d", menu);
	}
	clearStdin();
    // clear(); //não limpei a tela, caso tu queira ver todos os resultados ao mesmo tempo :)
}
//esse foi de boas, tomara que seja só isso e não precise fazer nenhuma correção depois
void preOrder(tree *root, int level) {
    if (root) {
        printf("%d  ", root->data);
        preOrder(root->left, level + 1);
        preOrder(root->right, level + 1);
    }
}
//1 2 3 5 7 6 4 -- O Gabriel Camargo me passou a call nesse aqui
void postOrder(tree *root, int level) {
    if (root) {
        if (root->left) {
            postOrder(root->left, level + 1);
        } else {
            printf("%d  ", root->data);
            if (root->right) {
                postOrder(root->right, level + 1);
            }
            return;
        }
        if (root->right) {
            postOrder(root->right, level + 1);
        } else {
            printf("%d  ", root->data);
            if (root->left) {
                postOrder(root->right, level + 1);
            }
            return;
        }
        printf("%d  ", root->data);
    }
}

void batata (tree *root, int level) {
    if (root) {
        batata(root->left, level + 1);
        batata(root->right, level + 1);
        printf("%d  ", root->data);
    }
}

//simétrica
void inOrder(tree *root, int level) {
    if (root) {
        inOrder(root->left, level + 1);
        printf("%d  ", root->data);
        inOrder(root->right, level + 1);
    }
}
// essa é a preOrder só que com um print mais detalhada.
void printTree(tree *root, int level) {
    if (root) {
        printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
        printTree(root->left, level + 1);
        printTree(root->right, level + 1);
    }
}

int main () {
    tree *beg;
    int menu, val;
    do {
		mainMenu(&menu);
		switch (menu) {
            case 1: printf("Please insert a value to be added to the tree: ");
                    getVal(&val);
                    insertData(&beg, val);
                    break;
			case 2: printTree(beg, 0);
					break;
			case 3: preOrder(beg, 0);
                    printf("\n");
                    break;
            case 4: inOrder(beg, 0);
                    printf("\n");
                    break;
            case 5: postOrder(beg, 0);
                    printf("\n");
                    break;
            case 6 : batata (beg, 0);
        }
    } while (menu != menuEntries);
    clear();
}
