///-----------------------------------------------------
/// @Title: Term Project_treePartHeader 
/// @Author: Tunç Gürsoy
/// @ID: 64528127274
/// @Section: 1
/// @Assignment: 3
///-----------------------------------------------------
#ifndef TREE_H
#define TREE_H
#include <stdio.h>
struct node
{
    struct node * parent ; //parent of node
    struct node * childs[10];// Childs of node limited to 10
    int currentNumnerOfChild;//How many child node have
    int id ;//id of the node
    char value[256] ;//Name of the node
    int availablenodes[10]; //To find child of the available or not ; available if 0
}typedef  node ;
node* new(char* );// Creates new node with char pointer
node** nodes;//Arrays of the nodes in tree
node* root ;//Root of the tree
int size_of_tree;//size of the tree
void setroot(char*, int);//Sets the root
void addChild(const char*,int,char*);//add child to the parent
void delete(const char*,int );//deletes the node
char* print(const char*,int,char*);//prints tree with given parameters
void move(const char * , int, const char * ,int);//Move the node with given parameters to given parameters
int count(const char * , const char *, int);//Counts node equal to given node(variable) under to given parameter node
void PRINT_LEVEL(const char *,int ,FILE*);// Prints given node and level in output file


#endif
