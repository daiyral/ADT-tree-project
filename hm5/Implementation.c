#include "header.h"
typedef struct Tree
{
	PTree left,right;
	void* key;
}TreeNode;

/*
this func creates our nodes to insert into search tree
*/
PTree create_tree_node(void *key)
{
	PTree temp;
	if (!(temp = (PTree)malloc(sizeof(TreeNode))))
	{
		ErrorMsg("Could not allocate memory");
		return NULL;
	}
	//initialize data
	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	return temp;//return the node
}
/*
this func creates our tree by inserting nodes in search tree order
*/
void InsertToTree(PTree* root,PTree* rootOriginal,void *key,int times, int(*isBigger_func)(void*,void*),void(*free_func)(void*))
{
	if ((*root) == NULL)//stop condition for recursion
	{
		*root = create_tree_node(key);//create a node to enter into the tree
		if (times == 0)//check if theres no leaves in our tree
			*rootOriginal = *root;//save our head of tree
		if ((*root) == NULL)//if memory allocation failed we must empty the tree
			emptyTree(rootOriginal,free_func);//call empty tree to release all memory
	}
	else
		if (isBigger_func(key, (*root)->key))//if the new node's key is bigger			
			InsertToTree((&(*root)->right),rootOriginal,key,times,isBigger_func,free_func);
		else//new nodes key is smaller
			InsertToTree((&(*root)->left),rootOriginal,key,times, isBigger_func,free_func);
}
/*
check if a key is already in our tree
*/
int search_tree(PTree root, void* key,int(*cmp_keys)(void*,void*))
{
	int x,y ;
	if (root == NULL)return 0;//recursive condition
	if (cmp_keys(root->key, key)) return 1;//compare between 2 keys if they are equal return 1
	x=search_tree(root->left, key, cmp_keys);//return 1 or 0 into x if the key is found
	y=search_tree(root->right, key, cmp_keys);//return 1 or 0 into y if the key is found
	
	return x>0||y>0? 1:0;//if x or y is 1 the key already exists in the tree
}
/*
get our tree height
*/
int TreeHeight(PTree root)
{
	int left;
	int right;
	if (root == NULL) return -1;
	left = 1 + TreeHeight(root->left);//calculate left route height
	right = 1 + TreeHeight(root->right);//calculate right route height
	return left > right ? left : right;//return the bigger one
}

int print_k_min(PTree root, int k, int* cnt, void(*print_func)(void*))
{
	if (root == NULL) return 0;//recursive condition
	print_k_min(root->left, k, cnt, print_func);//run on left
	if (k > *cnt)//if we still have keys to print
	{
		print_func(root->key);//call specific print func
		*cnt = *cnt + 1;//count how many keys we have printed
	}
	print_k_min(root->right, k, cnt, print_func);//check right side of node
}

void PrintInorder(PTree root, void(*print_func)(void*))
{
	if (root == NULL)return;
	PrintInorder(root->left, print_func);//run on the left
	print_func(root->key);//send to specific print function to print our keys inorder
	PrintInorder(root->right, print_func);//run on the right
	
}
/*this func finds and retuns our max key*/
void* Find_max(PTree root)
{
	while (root->right != NULL)//run on the right of tree (max is found in the right of search tree)
	{
		root = root->right;
	}
	return root->key;//return the max we have found
}

void emptyTree(PTree* root,void(*free_func)(void*))
{
	if (*root == NULL) return;//run till the root is empty
	emptyTree(&(*root)->left,free_func);//run on the left 
	emptyTree(&(*root)->right,free_func);//run on the right
	free_func((*root)->key);
	free(*root);
	*root = NULL;//set node to null instead of garbage
}

void ErrorMsg(char *s)
{
	printf("%s", s);
}