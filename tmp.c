#include "tmp.h"

#define BLACK 1 
#define RED 0

// BLACK -> "\033[1;30m"
// RED ->  "\033[1;31m"
// GREEN -> "\033[0;32m"
// YELLOW -> "\033[0;33m"

// RESET COLOR  -> "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

extern int errno;

typedef struct tree mynode;   //definizione nodo


typedef struct tuple_t tuple;
struct tuple_t
{
    int val;
    char color;
};

mynode* red_node_create(mynode*p,int Key, int Value) {
    mynode* parent=(mynode*) calloc(1, sizeof(mynode));
    parent->color=RED;
    parent->value=Value;
    parent->key=Key;
    parent->left=NULL;
    parent->right=NULL;
    parent->parent=p;
    printf("Inserito nodo rosso : %d\n",Value);
    return parent;
}

mynode* black_node_create(mynode*p,int Key, int Value) {
    mynode* parent= (mynode*) calloc(1, sizeof(mynode));
    parent->color=BLACK;
    parent->value=Value;
    parent->key=Key;
    parent->left=NULL;
    parent->right=NULL;
    parent->parent=p;
    printf("Inserito nodo nero : %d\n",Value);
    return parent;
}

int max (int a, int b)
{
    if (a >= b) return a;
    else if ( b > a ) return b;
    else 
    {
        printf("Error while calculating max bwteen : %d and %d\n",a,b);
        return -1;
    }
}

int height (mynode* node)
{
    if (node==NULL) return 0;
    else if (node!=NULL)
        return 1 + max ( height(node->right), height(node->left) );
    else 
    {
        printf("Error while calculating height\n");
        return -1;
    }
}

void filler(tuple** line,mynode* root,int level)
{
    if (root==NULL) 
    {
        line[level]++;
        return;
    }
    else if (root!=NULL) 
    {
        (*line[level]).val=root->value;
        (*line[level]).color=root->color;
        line[level]++;
        filler(line,root->left,level+1);
        filler(line,root->right,level+1);
        return;
    }
    else printf("Error in filler\n");
}

void print_line(tuple**print_t,int level,int size)
{
        int i;
        char * line;
        line = (char*)malloc(size* sizeof(char)); //lunghezza riga
        char*elem;
        elem = (char*)malloc( 10 * sizeof(char));
        strncpy(line,"\0",1);
        char* numbers;
        numbers = (char*)malloc((size-20)*sizeof(char));
        strncpy(line,"\0",1);
        if (level==0)
        {
            if ( (print_t[level][0]).color==RED )
            {
                printf("\033[1;31m                                                         %d\033[0m",(print_t[0][0]).val);
                free(numbers);
                free(elem);
                free(line);
                return;
            }
            else if ( (print_t[level][0]).color==BLACK )
            { 
                printf("\033[1;30m                                                         %d\033[0m",(print_t[0][0]).val);//1;30m
                free(numbers);
                free(elem);
                free(line);
                return;
            }
            else
            {
                printf("Error while printing level 0\n");
                return;
            } 
        }
        else if (level>0)
        {
            for(i=0; i<(1<<level) ;i++)
            {
                int val = (print_t[level][i]).val;
                int size = (snprintf(elem,10,"%d",val) ) +1 ;
                numbers = strncat( numbers, elem, size );
            }
            //strlen di numbers -> so quanti numeri ci sono su una linea
            //120 - strlen, sono gli spazi rimasti sulla riga
            // un blocco di spazi = 120 -strlen / (1<<level)+1
            //printf("denominatore : %d\n",( (1<<level) +1) );
            int block_space = (size - ( (strnlen(numbers, 99) ))) / ((1<<level)+1) ;
            snprintf(numbers,1,"%s",""); //riciclo numbers come block space
            for( i=0; i< block_space;i++ )
                numbers = strncat(numbers, " ", 1);
            // stampo : blocco spazi - intero - blocco spazi - intero...
            if ( (print_t[level][0]).color==RED )
                printf("\033[1;31m%s%d\033[0m",numbers,(print_t[level][0]).val);
            else if ( (print_t[level][0]).color==BLACK )
                printf("\033[1;30m%s%d\033[0m",numbers,(print_t[level][0]).val);//1;30m
            else printf("\033[1;31m%s \033[0m",numbers);
            for(i=1; i<(1<<level) ;i++)
            {
                if ( (print_t[level][i]).color == -1 ) 
                    printf("\033[1;31m%s \033[0m",numbers);
                else if ( (print_t[level][i]).color==RED )
                  printf("\033[1;31m%s%d\033[0m",numbers,(print_t[level][i]).val);
                else if ( (print_t[level][i]).color==BLACK )
                 printf("\033[1;30m%s%d\033[0m",numbers,(print_t[level][i]).val);//1;30m
                else printf("Errore nello stampare elemento in posizione %d\n",i);
            }
            free(numbers);
            free(elem);
            free(line);
            return;
        }
        else 
        {
            printf("Error while getting level\n");
            free(numbers);
            free(elem);
            free(line);
            return;
        }
        free(numbers);
        free(elem);
        free(line);
        return;
}

void tree_print(mynode*node){
    //alloco spazio per matrice con valori albero
    printf("Stampo l'albero : \n");
    tuple**print_t=(tuple**)malloc(8*sizeof(tuple*)); //tuple **
    int i;
    int j;
    int h_tree = height(node);
    for (i=0;i<8;i++)
        print_t[i]=(tuple*)malloc((1<<i)*sizeof(tuple));
    tuple **array ;
    array = (tuple**) malloc (8*sizeof(tuple*)); 
    //salvo i puntatori per recuperarli dopo
    for (i=0;i<8;i++)
        array[i]= print_t[i];
    for (i=0;i<8;i++) 
        print_t[i]=array[i]; //saves all print_t pointers in "array"
    for (i=0;i<8;i++)
    {
        for (j=0;j< (1<<i);j++)
           print_t[i][j].color =-1; //fill print_t with -1
    }
    filler(print_t,node,0);
    int k;
    for (i=0;i<8;i++) print_t[i]=array[i];
    for ( i=0 ; i < h_tree ; i++ )
    {
            print_line(print_t,i,120); //default value is 120
            printf("\n");
    }
    for (i=0;i<8;i++)
        free(print_t[i]);
    free(print_t); 
    free (array);
    return;
}

void welcome(){
   printf("\nBenvenuto nel Red-Black Tree Builder dove creeremo un albero rosso-nero nodo per nodo!\n"
           "I nodi hanno delle chiavi che gestirò io per te!\n"
           "Inserisci un valore intero qualsiasi : \n");
           return;
}

void node_free (mynode* node)
 {
    if (node==NULL) return;
    free(node);
    node=NULL;
    return;
}

void rightRotate (mynode * root)
{
    mynode*tmp=root->parent;
    int ins=0; //Se rimane 0 inserirò a sinistra
    if(tmp->right==root)
        ins=1; //Inserirò a destra
        if (root==NULL ||  (root)->left==NULL)
        {
            printf ("Errore in RightRotate()\n");
            return ;
        }
        mynode *x = root->left;
        mynode *y = x->right;
        x->right = root;
        root->left = y;
        if(y!=NULL)
            y->parent=root;

        x->parent=tmp;
        root->parent=x;
 
    if(ins==0) tmp->left=x;
    else tmp->right=x;
    printf("Rotazione conclusa\n");
    return ;
}

void leftRotate(mynode *root)
{
    mynode*tmp=root->parent;
    int ins=0; //Se rimane 0 inserirò a sinistra
    if(tmp->right==root)
        ins=1; //Inserirò a destra
    if (root==NULL ||  (root)->right==NULL)
    {
        printf ("Erroe in leftRotate()\n");
        return ;
     }
    mynode *y = root->right;        
    mynode *x = y->left;      
 
    y->left = root;     
    root->right = x;
                                 
    y->parent=tmp;
    root->parent=y;
    if(x!=NULL)     
        x->parent=root;

    if(ins==0) tmp->left=y;
    else tmp->right=y;
    printf("Rotazione conclusa\n");
    return ;
}

void case1(mynode*node,int ruota)
{
    printf("case1 su nodo : %d\n",node->value);
    node->parent->parent->color=RED;
    node->parent->color=BLACK;
    mynode*tmp = node->parent;
    if (ruota==0) rightRotate(node->parent->parent);
    else if (ruota==1) leftRotate(node->parent->parent);
    else printf("Case1 fa cose strane\n");
}

void case2(mynode*node,int ruota)
{
    printf("case2 su nodo : %d\n",node->value);
    mynode*p=node->parent;
    if(ruota==0) 
        rightRotate(node->parent);
    else if (ruota==1) 
        leftRotate(node->parent);
    else 
    {
        printf("Case2 fa cose strane\n");
        return;
    }
    if(ruota==0)
        case1(p,1);
    else if (ruota==1)
        case1(p,0);
    return;
} 

void case3 (mynode*node,mynode*root,int n)
{
    printf("case3 su nodo : %d\n",node->value);
    if(node==NULL)
    {
         printf("Invalid arguments case 3\n");
        return;
    }
    else if ( node->parent==NULL ) 
    {
        printf("Siamo finiti dove non dovremmo\n");
        return;
    }
    else if (node->parent->parent==NULL) { //Radice, ricoloro di nero
    printf("Ricoloro la radice\n");
        node->color=BLACK;
        return;
    }
    else {
        if(node->parent->color==BLACK) return;
        printf("Proseguo con case 3\n");
        mynode*gp = node->parent->parent;
        gp->right->color = BLACK;
        gp->left->color = BLACK;
        gp->color = RED;
        tree_print(root);
        return;
    }
    return;
}

mynode* getGrandParent(mynode*node) {return node->parent->parent;}

mynode* getRightUncle(mynode*node) {return ( getGrandParent(node) )->right;}

mynode* getLeftUncle(mynode*node) {return ( getGrandParent(node) )->left;}

void fix(mynode*node,mynode*root) {
    printf("Fixing up\n");
    if (node==NULL) {
        printf("Errore fix su NULL\n");
        return;
    }
    else if (root==node) {
        root->color=BLACK;
        return;
    }
    else if (node->parent==root) {
        root->color=BLACK;
        return;
    }
    else {
        mynode* gp = getGrandParent(node);
        if(gp==NULL) return;
        mynode* rightUncle = getRightUncle(node);
        mynode* leftUncle = getLeftUncle(node);
        if(node->color==RED && node->parent->color==RED) { //violazione
        printf("violation!\n");
            if( (rightUncle!=NULL && leftUncle!=NULL ) && rightUncle->color==RED && leftUncle->color==RED) 
                {
                    case3(node,root,0);
                    fix(gp,root);
                    return;
                }
            else {
                if( rightUncle==NULL || rightUncle != node->parent ) { //zio sta nel ramo destro, padre ramo sinistro
                    if(node->parent->left==node) { //figlio sinistro su ramo sinistro
                        case1(node,0); 
                        return;
                    }
                    else { //figlio destro su ramo sinistro
                        case2(node,1);
                        return;
                    }
                }
                else { //zio ramo sinistro e padre ramo destro
                    if(node->parent->right==node) //figlio destro su ramo destro
                    {
                        case1(node,1);
                        return;
                    }
                    else { //figlio sinistro su ramo destro
                        case2(node,0);
                        return;
                    }
                }
            }
        }
    }
}

void insert(mynode*node,mynode*root,int val, int key) {
    if(node==NULL) {
        printf("Errore ritorno NULL\n");
        return ;
    }
    else 
    {
        if(val <= node->value ) {
            if(node->left==NULL){
                printf("Inserisco valore %d a sinistra del nodo : %d\n",val,node->value);
                node->left=red_node_create(node,key,val);
                tree_print(root);
                fix(node->left,root);
            }
            else {
                printf("Il valore da inserire %d è minore del nodo : %d, vado a sinistra\n",val,node->value);
                insert(node->left,root,val,key);
            }
        }
        else if (val > node->value){
            if(node->right==NULL)
            {
                printf("Inserisco valore %d a destra del nodo : %d\n",val,node->value);
                node->right=red_node_create(node,key,val);
                tree_print(root);
                fix(node->right,root);
            }
            else {
                printf("Il valore da inserire %d è maggiore del nodo : %d, vado a destra\n",val,node->value);
                insert(node->right,root,val,key);
            }
        }
    }
    return;
}

void tree_free(mynode* node){
    if (node==NULL) return;
    else 
    {
        tree_free(node -> left);
        tree_free(node -> right);
        node_free(node);
        return;
    }
}

int isInt (char* string)
{ 
  int k=0;
  while( string[k] != '\0')
  {
    if ( isdigit(string[k++])==0)
      return 1;
  }
  return 0;
}

int getInput(char* string, size_t string_max) // add parameter to get buffer size
{
    int inp_as_int;
    errno=0;
    char * t;
    while (1)
    {
       fflush(stdout);
       fgets(string,string_max,stdin);
       if (memcmp("\n",string,1)==0) return-1;
       else 
       {
           char* zero = strchr(string, '\n'); // find newline character
           if (zero != NULL) *zero = '\0'; // remove 
           if(isInt(string)==0 )
            {
                inp_as_int=strtol(string,&t,10);
                if(inp_as_int==0 && errno==EINVAL )
                    printf("Riprova\n");
                else if (inp_as_int==0 && errno!=EINVAL) {
                    printf("Valore preso : %d\n", inp_as_int);
                    return 0;
                }
                else if (inp_as_int < 0) 
                    printf("inserisci un valore valido!\n");
                else
                { 
                    printf("Valore preso : %d\n",inp_as_int);
                    return inp_as_int;
                }
            }
            else printf("Inserisci un valore\n");
        }
    }
    printf("Errore return -1\n");
    return -1;
}




