//
//  Red_black_tree.c
//
//  Created by Federico D'Armini on 25/11/2019.
//

#include "functions.h"
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
        printf("Node created!\n");
        tree_print(root->right);
        printf("Insert number : \n");
        while (memcmp("\n",input,1)!=0 )
        {
            getInput(input,12);
            insert(root->right,root->right,atoi(input),key++);
            printf("Node created!\n");
            tree_print(root->right);
            printf("Do you want to continue? Yes -> Insert number, ENTER -> stop\n");
        }
        return 0;

}
