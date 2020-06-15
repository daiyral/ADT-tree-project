#ifndef _Implementation
#define _Implementation
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//structs
typedef struct Tree *PTree;

//functions
void ErrorMsg(char *s);
void InsertToTree(PTree* root, PTree* rootOriginal, void* key,int times, int(*isBigger_func)(void*, void*),void(*free_func)(void*));
PTree create_tree_node(void* key);
void PrintInorder(PTree root, void(*print_func)(void*));
int TreeHeight(PTree root);
void PrintInorder(PTree root, void(*print_func)(void*));
void* Find_max(PTree root);
int print_k_min(PTree root, int k,int *cnt, void(*print_func)(void*));
int search_tree(PTree root, void* key, int(*cmp_keys)(void*, void*));
void emptyTree(PTree* root, void(*free_func)(void*));
#endif // !1