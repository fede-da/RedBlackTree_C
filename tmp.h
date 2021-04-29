#ifndef _TMP_H
#define _TMP_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tree mynode; 
struct tree{                    
    int value;
    int key;
    char color;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
};

mynode* red_node_create(mynode*node, int key, int val);

mynode* black_node_create(mynode*node, int key, int val);


void tree_print(mynode*node);


void insert ( mynode*node,mynode*root,int val,int key);

void node_free (mynode* node);

void tree_free (mynode* root);

void welcome();

int isInt (char* string);

int getInput(char* string, size_t string_max); // add parameter to get buffer size
#endif