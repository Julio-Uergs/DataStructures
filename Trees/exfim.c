//Escreva um algoritmo para excluir todas as folhas de uma árvore binária

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

struct utsname info;

typedef struct tree {
  int data;
  struct tree *left, *right;
}tree;

int getData(char string[]) {
  int data;
  printf("\n%s", string);
  scanf("%d", &data);
  return data;
}

void searchData(tree *root, int data, tree **ptr) {
  if (root) {
    *ptr = root;
    if(data > root->data) {
      root = root->right;
    }
    else {
      root = root->left;
    }
    searchData(root, data, ptr);
  }
}

void insertData(tree **root, int data) {
  tree *newData = (tree*)malloc(sizeof(tree)), *ptr = NULL;
  if (newData) {
    newData->data = data;
    if (*root == NULL) {
      *root = newData;
    }
    else {
      searchData(*root, data, &ptr);
      if (ptr->data < data) {
        ptr->right = newData;
      } else if(ptr->data > data) {
        ptr->left = newData;
      }
    }
    newData->right = NULL;
    newData->left = NULL;
  }
}

int treeHeight(tree *root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return 0;
  } else {
    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);
    if (leftHeight > rightHeight) {
      return 1 + leftHeight;
    }
    return 1 + rightHeight;
  }
}

int menu() {
  int op;
  do {
    printf("\n\t1 - inserir na arvore\n\t2 - printar simetrica");
    printf("\n\t3 - calcular altura da arvore\n\t4 - Quantidade de nos da arvore\n\t5 - remover folhas");
    printf("\n\t6 - fim\n\tEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 6 || op < 1);
  return op;
}

void printSymmetric(tree *root) {
  if (root) {
    printSymmetric(root->left);
    printf("Value: %d, Left: %p, Right: %p, Current: %p\n", root->data, root->left, root->right, root);
    printSymmetric(root->right);
  }
}

int countNodeFromTree(tree *root) {
  if (root) {
    int leftCount, rightCount;
    leftCount = countNodeFromTree(root->left);
    rightCount = countNodeFromTree(root->right);
    return 1 + leftCount + rightCount;
  }
  return 0;
}

void removeLeafFromTree(tree **root) {
  if (*root) {
    if (!(*root)->left && !(*root)->right) {
        free(root);
        *root = NULL;
    } else {
        removeLeafFromTree(&(*root)->left);
        removeLeafFromTree(&(*root)->right);
    }
  }
}

int main() {
  tree *root = NULL;
  if (uname(&info) != -1) {
        printf("Sistema operacional: %s\n", info.sysname);
        printf("Nome do host: %s\n", info.nodename);
        printf("Versão do sistema: %s\n", info.release);
        printf("Versão do kernel: %s\n", info.version);
        printf("Arquitetura: %s\n", info.machine);
    } else {
        perror("uname");
    }
  int option, data;
  do {
    option = menu();
    switch (option) {
      case 1:
        data = getData("Informe o dado: ");
        insertData(&root, data);
        break;
      case 2:
        printSymmetric(root);
        break;
      case 3:
        printf("\n\tAltura da arvore ->->-> %d", treeHeight(root) - 1);
        break;
      case 4:
        printf("\nQuantidade de nos da arvore ->->-> %d", countNodeFromTree(root));
        break;
      case 5:
        removeLeafFromTree(&root);
        break;
      default:
        printf("\nFim\n");
    }
  } while(option != 6);
  return 0;
}
