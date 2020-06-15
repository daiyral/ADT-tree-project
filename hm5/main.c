#include "header.h"
int is_int_Bigger(void* var1, void* var2)//return 1 if var1>var2, else 0
{
	return *(int*)var1 > *(int*)var2;
}
int is_float_Bigger(void* var1, void* var2)//return 1 if var1>var2, else 0
{
	return *(float*)var1 > * (float*)var2;
}
int is_char_Bigger(void* var1, void* var2)//return 1 if var1>var2, else 0
{
	return *(char*)var1 > *(char*)var2;
}
int cmp_int_keys(void *current_key,void *key)//return 1 if two given keys are equal as integer
{
	if (*(int*)current_key == *(int*)key)
		return 1;
	return 0;
}
int cmp_float_keys(void* current_key, void* key)//return 1 if two given keys are equal as float
{
	if (*(float*)current_key == *(float*)key)
		return 1;
	return 0;
}
int cmp_char_keys(void* current_key, void* key)//return 1 if two given keys are equal as float
{
	if (*(char*)current_key == *(char*)key)
		return 1;
	return 0;
}
void print_int(void* key)//print to output file a given key as integer
{
	FILE* out;
	if (!(out = fopen("output.txt", "a")))
		ErrorMsg("cant open ouput file");
	fprintf(out, "%d ", *(int*)key);
	fclose(out);
}
void print_float(void* key)//print to output file a given key as float
{
	FILE* out;
	if (!(out = fopen("output.txt", "a")))
		ErrorMsg("cant open ouput file");
	fprintf(out, "%.2f ", *(float*)key);
	fclose(out);
}
void print_char(void* key)//print to output file a given key as char
{
	FILE* out;
	if (!(out = fopen("output.txt", "a")))
		ErrorMsg("cant open ouput file");
	fprintf(out, "%c ", *(char*)key);
	fclose(out);
}
void free_func(void* key)//free the memory of a given key
{
	free(key);
}
void* get_key_int(FILE *in)
{
	void* new_key;
	if(!(new_key = (int*)malloc(sizeof(int))))
		return 0;
	fscanf(in, "%d", new_key);//get the key to be added from file
	return new_key;
}
void* get_key_float(FILE* in)
{
	void* new_key;
	if (!(new_key = (float*)malloc(sizeof(float))))
		return 0;
	fscanf(in, "%f", new_key);//get the key to be added from file
	return new_key;
}
void* get_key_char(FILE* in)
{
	void* new_key;
	if (!(new_key = (char*)malloc(sizeof(char))))
		return 0;
	fscanf(in, "%c", new_key);//get the key to be added from file
	return new_key;
}
void main()
{
	FILE* in, * out;
	int func,height,k,times=0,cnt=0;
	PTree root = NULL;
	void *max,*key,(*print_func)(void*), (*get_key)(FILE*),*cmp_func,*isBigger_func;
	key = NULL;
	print_func = print_int;
	get_key = get_key_int;
	cmp_func = cmp_int_keys;
	isBigger_func = is_int_Bigger;
	if (!(in = fopen("Instructions.txt", "r")))//open input file and check if opened
	{
		ErrorMsg("couldnt open in file");
		exit(1);
	}
	while (fscanf(in, "%d", &func) != EOF)//run until end of in file
	{
		if (!(out = fopen("output.txt", "a")))//open output file and check if succeded
		{
			ErrorMsg("couldnt open output file");
			emptyTree(&root,free_func);
			exit(1);
		}
		switch (func)//we get func from input file(option 1 to 5)
		{
		case 1:
			if (!(key = get_key_int(in)))//memory allocation for new key and check for success
			{
				ErrorMsg("Could not allocate memory for new key");
				emptyTree(&root, free_func);//if failed than empty the current tree
				exit(1);
			}
			//fscanf(in, "%c", ch_key);//get the key to be added from file
			if (!search_tree(root, key, cmp_func))//if search tree return 1 that means the key is in tree,else 0
			{
				InsertToTree(&root, &root, key,times,isBigger_func,free_func);//insert the new key to the tree
				times++;//count new node in tree
				(*print_func)(key);
				fprintf(out, "was added to the tree\n");
			}
			else//if the current key is already in tree
			{
				(*print_func)(key);
				fprintf(out,"is already in tree\n");
				free(key);//free the memory of current key that we dont use
			}
			break;
		case 2:
			fprintf(out,"The tree elements in in-order print are:");
			fclose(out);
			PrintInorder(root,print_func);
			if (!(out = fopen("output.txt", "a")))//open output file and check if succeded
			{
				ErrorMsg("couldnt open output file");
				emptyTree(&root, free_func);
				exit(1);
			}
			fprintf(out, "\n");
			fclose(out);
			break;
		case 3:
			height = TreeHeight(root);
			fprintf(out, "The height of your tree is: %d\n", height);
			break;
		case 4:
			max = Find_max(root);
			fprintf(out, "The maximum is: ");
			fclose(out);
			(*print_func)(max);
			break;
		case 5:
			fscanf(in, "%d", &k);
			if (k >times||k<=0)//check if the given k is valid
				fprintf(out, "\nThere are no %d elements in the tree", k);
			else
			{
				fprintf(out, "\nThere are %d small elements in this tree:",k);
				fclose(out);
				print_k_min(root, k,&cnt, print_func);
				cnt = 0;
			}
			break;
		}
		fclose(out);
	}
	fclose(in);
}

