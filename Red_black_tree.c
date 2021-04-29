//
//  Red_black_tree.c
//
//  Created by Federico D'Armini on 25/11/2019.
//

#include "tmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main (){
    int key=1;
    int height=1;
    char input[12];
    
    welcome();

    mynode*root=NULL;
    getInput(input,12);
    root=black_node_create(NULL,0,0);
    root->parent=NULL;
    root->right=black_node_create(root,key++,atoi(input));
    root->right->parent=root;
    printf("Nodo creato!\n");
    tree_print(root->right);
    printf("Inserisci un numero : \n");
    while (memcmp("\n",input,1)!=0 )
    {
        getInput(input,12);
        insert(root->right,root->right,atoi(input),key++);
        printf("Nodo creato!\n");
        tree_print(root->right);
        printf("Vuoi continuare? Si -> Inserisci un numero, ENTER -> termina\n");
    }
    return 0;
}