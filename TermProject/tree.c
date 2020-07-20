///-----------------------------------------------------
/// @Title: Term Project_treePart
/// @Author: Tunç Gürsoy
/// @ID: 64528127274
/// @Section: 1
/// @Assignment: 3
///-----------------------------------------------------

#include "tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void Swap(node **pNode, node **pNode1);





/**
 * @def: Create new node with given value.
 * @brief gets char pointer
 * */
node* new(char* value)
{
    char a[strlen(value)];
    strcpy(a,value);
    node* temp = (node*)malloc(sizeof(node));
    temp->currentNumnerOfChild = 0 ;
    strcpy(temp->value,a);
    temp->id = size_of_tree+1 ;
    temp->parent = NULL ;
    nodes[size_of_tree] = temp ;
    size_of_tree++;
    int i;
    for ( i = 0; i <10 ; ++i) {
        temp->availablenodes[i] = 0 ;
        temp->childs[i]= NULL;
    }

    return (temp);
}
/**
 * @def Sets root
 * @details gets char pointer and set tree size to 0 and creates nodes
 *
 * */
void setroot(char* value, int linecount)
{
    if (size_of_tree==0)
    {
        nodes = (node**)malloc(sizeof(node*)*linecount);
        int j = 0 ;
        for ( j = 0; j <linecount ; ++j) {
            nodes[j]= (node*)malloc(sizeof(node));
        }
    }
    root = new(value);
}
/**
 * @def Add child to create node with given value to given parent and parentid
 * @details gets char pointer ,int , value
 * */
void addChild(const char* parent,int parentid,char* value) {
    char temp[strlen(parent)];
    int i = 0;
    for ( i = 0; i < size_of_tree; ++i) {
        if (nodes[i] != NULL) {
            strcpy(temp, nodes[i]->value);
            if (strcmp(temp, parent) == 0 && parentid == nodes[i]->id) {

                node *temp1;
                char temp2[strlen(value)];
                strcpy(temp2, value);
                temp1 = new(temp2);
                int j;
                for ( j = 0; j < 10; ++j) {
                    if (nodes[i]->availablenodes[j] == 0) {
                        (nodes[i]->childs[j]) = temp1;
                        nodes[i]->currentNumnerOfChild++;
                        temp1->parent = nodes[i];
                        nodes[i]->availablenodes[j] = temp1->id;
                        break;
                    }
                }

                break;
            }
        }
    }
    }
///@def Deletes  node is equal to given value and id
void delete(const char* value, int id)
{

    char a[256];
    strcpy(a,value);
    int i;
    for ( i = 0; i <size_of_tree ; ++i) {
        if (nodes[i] != NULL) {
            if (strcmp(nodes[i]->value, a) == 0 && id == nodes[i]->id) {
                int j;
                if (nodes[i]->parent==NULL)
                {
                    int k;
                    for ( k = 0; k < 10; ++k) {
                        if (nodes[i]->childs[k] != NULL) {

                            delete(nodes[i]->childs[k]->value, nodes[i]->childs[k]->id);

                        }
                    }
                    free(nodes[i]);
                    nodes[i] = NULL;
                    break;
                }else{
                for ( j = 0; j < 10; ++j) {
                    if (nodes[i]->parent->availablenodes[j] == id) {
                        nodes[i]->parent->availablenodes[j] = 0;
                        int k;
                        for (k = 0; k < 10; ++k) {
                            if (nodes[i]->childs[k] != NULL) {

                                delete(nodes[i]->childs[k]->value, nodes[i]->childs[k]->id);

                            }
                        }
                        if (nodes[i]->parent != NULL) {
                            nodes[i]->parent->childs[j] = NULL;
                            nodes[i]->parent->currentNumnerOfChild--;
                        }
                        free(nodes[i]);
                        nodes[i] = NULL;
                        break;
                    }
                }

                }


                break;
            }
        }
    }
}

///@def Prints to given value and id equal node and childs and equalize temp if no node equal to given value and id returns Empty String
char* print(const char* value, int id,char* temp1)
{
     char result[15000] ;
    char a[256];
    strcpy(a,value);
    int i;
    for ( i = 0; i <size_of_tree ; ++i) {

        if (nodes[i] != NULL) {
            if (strcmp(nodes[i]->value, a) == 0 && id == nodes[i]->id) {
                char temp[5];
                sprintf(temp,"%d",nodes[i]->id);
                strcpy(result, nodes[i]->value);
                strcat(result, "[");

                strcat(result, temp);
                strcat(result, "]");
                strcat(result, "\n");
                int j;
                for ( j = 0; j < 10; ++j) {
                    if (nodes[i]->availablenodes[j] != 0) {
                        strcat(result, print(nodes[i]->childs[j]->value, nodes[i]->childs[j]->id,temp1));
                    }
                }
                temp1 = result;
                return  temp1;
            }
        }
    }
    return "";
}

///@def moves node equal to firstV and FirstID under to node to equal to secondV and secondID
///@note I notice after writing code, bigO of this algortihm is so high but , using return so it has to be no problem
void move(const char * firstV,int firstID,const char * secondV,int secondID)
{
    int i;
    for ( i = 0; i <size_of_tree ; ++i) {
        char a[120];
        if (nodes[i] != NULL) {
            strcpy(a, nodes[i]->value);
            if (strcmp(a, firstV) == 0 && firstID == nodes[i]->id) {
                int j;
                for ( j = 0; j < size_of_tree; ++j) {
                    if (nodes[j] != NULL) {
                        char b[120];
                        strcpy(b, nodes[j]->value);
                        if (strcmp(b, secondV) == 0 && secondID == nodes[j]->id) {
                            int k,l,m;
                            for ( k = 0; k < 10; ++k) {
                                for ( l = 0; l < 10; ++l) {
                                    if (nodes[j]->parent!=NULL)
                                    {
                                        if (nodes[i]->parent->availablenodes[k] == firstID &&
                                            nodes[j]->parent->availablenodes[l] == secondID) {
                                            for ( m = 0; m <10 ; ++m) {
                                                if (nodes[j]->childs[m]==NULL)
                                                {
                                                    nodes[i]->parent->currentNumnerOfChild-- ;
                                                    nodes[i]->parent->availablenodes[k] = 0;
                                                    Swap(&nodes[i]->parent->childs[k],&nodes[j]->childs[m]);
                                                    nodes[i]->parent->childs[k] = NULL;
                                                    free( nodes[i]->parent->childs[k] );
                                                    nodes[j]->childs[m]->parent = nodes[j];
                                                    nodes[firstID-1] = nodes[j]->childs[m];
                                                    nodes[j]->availablenodes[m] = firstID;
                                                    nodes[j]->currentNumnerOfChild++;


                                                    return;
                                                }
                                            }




                                        }
                                    } else
                                        {
                                            if (nodes[i]->parent->availablenodes[k] == firstID ) {
                                                for ( m = 0; m <10 ; ++m) {
                                                    if (nodes[j]->childs[m]==NULL)
                                                    {
                                                        nodes[i]->parent->currentNumnerOfChild-- ;
                                                        nodes[i]->parent->availablenodes[k] = 0;
                                                        Swap(&nodes[i]->parent->childs[k],&nodes[j]->childs[m]);
                                                        nodes[i]->parent->childs[k] = NULL;
                                                        nodes[j]->childs[m]->parent = nodes[j];
                                                        nodes[firstID-1] = nodes[j]->childs[m];
                                                        nodes[j]->availablenodes[m] = firstID;
                                                        nodes[j]->currentNumnerOfChild++;


                                                        return;
                                                    }
                                                }




                                            }
                                        }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
///@def Counts node equal to given node(variable) under to node equal to parent and id
int count(const char * node, const char * parent, int id)
{
    int result = 0 ;
    int i , j;
    for ( i = 0; i <size_of_tree ; ++i) {
        if (nodes[i] != NULL) {
            char a[120];
            strcpy(a, nodes[i]->value);
            if (strcmp(a, parent) == 0 && nodes[i]->id == id) {
                if (strcmp(a, node) == 0) {
                    result++;
                }
                for ( j = 0; j < 10; ++j) {
                    if (nodes[i]->availablenodes[j] != 0) {
                        result += count(node, nodes[i]->childs[j]->value, nodes[i]->childs[j]->id);
                    }
                }
            }
        }
    }

    return result;
}



///@def Swaps two node locaiton
void Swap(node **pNode, node **pNode1) {
    node * temp = *pNode;
    *pNode = *pNode1;
    *pNode1 = temp;
}
///@def Calculate height of height
int height(struct node* node) {
    if (node ==NULL) {
        return 0;
    } else {


        int arr[10];
        int height1 = height(node->childs[0]);
        int height2 = height(node->childs[1]);
        int height3 = height(node->childs[2]);
        int height4 = height(node->childs[3]);
        int height5 = height(node->childs[4]);
        int height6 = height(node->childs[5]);
        int height7 = height(node->childs[6]);
        int height8 = height(node->childs[7]);
        int height9 = height(node->childs[8]);
        int height10 = height(node->childs[9]);
        arr[0] = height1;
        arr[1] = height2;
        arr[2] = height3;
        arr[3] = height4;
        arr[4] = height5;
        arr[5] = height6;
        arr[6] = height7;
        arr[7] = height8;
        arr[8] = height9;
        arr[9] = height10;
        int max = arr[0];
        int min = arr[0];
        int i ;
        for ( i = 1; i < 10; i++) {
            // If current element> max
            if (arr[i] > max) {
                max = arr[i];
            }

            // If current element < min
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return max+1;
    }


    }



///@def Prints given node and level in output file
void printGivenLevel(struct node* root, int level,FILE *output)
{
    if (root == NULL)
        return ;
    if (level == 1){
        fprintf(output,"%s[%d]\n",root->value,root->id);
    }
        else if (level > 1)
    {
        printGivenLevel(root->childs[0] ,level-1,output);
        printGivenLevel(root->childs[1], level-1,output);
        printGivenLevel(root->childs[2], level-1,output);
        printGivenLevel(root->childs[3], level-1,output);
        printGivenLevel(root->childs[4], level-1,output);
        printGivenLevel(root->childs[5], level-1,output);
        printGivenLevel(root->childs[6], level-1,output);
        printGivenLevel(root->childs[7], level-1,output);
        printGivenLevel(root->childs[8], level-1,output);
        printGivenLevel(root->childs[9], level-1,output);
    }
}

///@def For finding node user want  equal to given name and id
void PRINT_LEVEL(const char * name,int id, FILE *output)
{
    int h = height(root),i,t;
    for ( i = 0; i <size_of_tree ; ++i) {
        if (nodes[i] != NULL) {
            char value[120];
            strcpy(value, nodes[i]->value);
            if (strcmp(value, name) == 0 && nodes[i]->id == id) {
                for ( t = 1; t <= h; t++) {
                    printGivenLevel(nodes[i], t,output);
                }
            }

        }
    }
}



