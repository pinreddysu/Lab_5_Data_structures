#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char str[30];
	int freq;
	struct node *leftp, *rightp;
}node_t;


void print_tree (node_t *tree);
int recur_print (node_t *tree, int level);
node_t* create_node(char word[30]);
void inorder_trav(node_t* root, FILE *fp);
node_t* insert_leaf(node_t* root, char word[30]);
node_t* search_leaf(node_t * root,char data[30]);
int total_nodes(node_t *tree);
void concordance_file_write(node_t *root);
void tree_check(node_t *root, char word[30]);


/*
 AUTHOR: Yash Nikumb, Suchith Pinreddy
 FILENAME: problem1.c
 SPECIFICATION: To find the number of unique words, the unique words, and the number of times each unique word occurs in the text file
 FOR: CS 2413 Data addresss Section 002
*/
int main()
{
    FILE *infile;
    char data[30];
    int nodes;
    node_t *root = NULL;
    infile = fopen("text.txt","r");
    while(fscanf(infile,"%s", data)==1){
        for(int i = 0; i<=(strlen(data));i++){
            if (data[i]>=65 && data[i] <=90){
                data[i] = data[i] + 32;
            }
            if (!((data[strlen(data)-1]) >= 'a' && (data[strlen(data)-1]) <= 'z')){
                data[strlen(data)-1] = '\0';
            }
        }
        root = insert_leaf(root, data);
    }
    concordance_file_write(root);
    char word[30] = "in";
    char word1[30] = "shut";
    for(int j = 0; j<=(strlen(word)+1);j++){
        if (word[j]>=65 && word[j]<=90){
            word[j] = word[j] + 32;
        }
        if (!((word[strlen(word)-1]) >= 'a' && (word[strlen(word)-1]) <= 'z')){
                word[strlen(word)-1] = '\0';
            }
    }
    for(int k = 0; k<=strlen(word1);k++){
        if (word1[k]>=65 && word1[k]<=90){
            word1[k] = word1[k] + 32;
        }
        if (!((word1[strlen(word1)-1]) >= 'a' && (word1[strlen(word1)-1]) <= 'z')){
                word1[strlen(word1)-1] = '\0';
            }
    }    
    tree_check(root, word);
    tree_check(root, word1);
	return 0;
} 

/* NAME: create_node
 PARAMETERS: char word[30]
 PURPOSE: the purpose of the function is to ceate a node in the Binary Search tree(BST)
 PRECONDITION: The actual variable passed in the main function is to be an array of charecters
 POSTCONDITION: It returns the temporary node address when the function is called. 
*/
node_t* create_node(char word[30])
{
	node_t* newp
		= (node_t*)malloc(sizeof(node_t));
	strncpy(newp->str, word, 30);
	newp->str[strlen(word)] = '\0';
	newp->leftp = newp->rightp = NULL;
	newp->freq = 1;
	return newp;
}

/* NAME: inorder_trav
 PARAMETERS: node_t* node, char word[30]
 PURPOSE: Traversing in ascending order 
 PRECONDITION:  Actual variable should be a node address and a FILE pointer
 POSTCONDITION: It prints in the file 
*/
void inorder_trav(node_t* root, FILE *fp)
{
	if (root != NULL) {
		inorder_trav(root->leftp, fp);
	    fprintf(fp, "%s \t %d \n", root->str, root->freq);
		inorder_trav(root->rightp, fp);
		
	}
}
 
/* NAME: insert_leaf
 PARAMETERS: node_t* node, char word[30]
 PURPOSE: Inserts nodes into the binary search tree if it is not a repeated word or else it increases the frequency
 PRECONDITION: The actual parameters passed should be a node address and an array of charecters(string) 
 POSTCONDITION: It returns the root address according to the conditional statements
*/
 
node_t* insert_leaf(node_t* root, char word[30])
{
	
	if (root == NULL){
		return create_node(word); 
	}
	if (strncmp(word, root->str,30)==0){
	    root->freq +=1;
	    return root;  
	}
	if (strncmp(word,root->str,30)<0)
		root->leftp = insert_leaf(root->leftp, word);
	else if (strncmp(word,root->str,30)>0)
		root->rightp = insert_leaf(root->rightp, word);
	return root;
}
 
/* NAME: search_leaf
 PARAMETERS: node_t * root,char data[30]
 PURPOSE: Searches the word inside the BST
 PRECONDITION: Root address and and char array passed as an actual variable 
 POSTCONDITION: Returns root address 
*/
node_t * search_leaf(node_t * root,char data[30]) {
    if (root == NULL || strncmp(root->str,data,30)==0){
        return root;
    }
    else if (strncmp(data,root->str,30)<0){
        return search_leaf(root->leftp,data);
    }
    else{
        return search_leaf(root->rightp,data);
    }
}
 
 /* NAME: print_tree
 PARAMETERS: node_t *tree
 PURPOSE:  Prints the height 
 PRECONDITION: Should be a node address
 POSTCONDITION: Returns height in int value 
*/
void print_tree (node_t *tree) {
  int x = recur_print(tree,0);
  
}

/* NAME: recur_print
 PARAMETERS: node_t *tree, int level
 PURPOSE: The function computes the average of the list of numbers given as input
 PRECONDITION: The variable should be a node address and integer value 
 POSTCONDITION: Calculates the height and returns it 
*/
int recur_print (node_t *tree, int level) {
    int i;
    if (tree != NULL) {
        for (i = 0; i < level; i++){ 
        }
        recur_print (tree->leftp,level+1); 
        recur_print (tree->rightp,level+1); 
    }
    else{
        return level;
    }
}
/* NAME: total_nodes
 PARAMETERS: node_t *tree
 PURPOSE: its purpose is to calculate the total nodes in the tree
 PRECONDITION: The actual parameter passed should be a node address
 POSTCONDITION: The function should return the total no. of nodes or 0 if the tree is empty
*/
int total_nodes(node_t *tree){
    if(tree==NULL){
        return 0;
    }
    else{
        return total_nodes(tree->leftp) + total_nodes(tree->rightp)+1;
    }
} 

/* NAME: concordance_file_write
 PARAMETERS: node_t *root
 PURPOSE: Its purpose is to print the distinct words in the text file in the concordance.txt
 PRECONDITION: The actual parameter passed should be a node address
 POSTCONDITION: It should display the distinct words of the file and create and write it in the concordance file
*/

void concordance_file_write(node_t *root){
    FILE *outfile;
    int nodes;
    outfile = fopen("concordance.txt", "w");
    nodes = total_nodes(root);
    fprintf(outfile, "There are %d distinct words in the text file:\n", nodes);
    inorder_trav(root,outfile);
    fclose(outfile);
}

/* NAME: tree_check
 PARAMETERS: node_t *root, char word[30]
 PURPOSE: This fuction displays the tree check, height and size of a tree. It also finds the frequency of the words in the text file
 PRECONDITION: The actual parameters passed shold be an array of charecter string and a node address
 POSTCONDITION: The function should display the information for the tree address like its height and size and also the frequency of words 
*/ 

void tree_check(node_t *root, char word[30]){
    node_t *val;
    printf("Tree Check:\n");
    int height = recur_print(root,0);
    printf("\tTree Height: %d\n", height);
    int nodes = total_nodes(root);
    printf("\tTree Size: %d nodes\n", nodes);
    val = search_leaf(root,word);
    if(val){
        printf("\t%s is found and as a frequency %d\n", word, val->freq);
    }
    else{
        printf("\t%s is not found\n",word);
    }
} 


/* 
Output: 

Tree Check:
        Tree Height: 7
        Tree Size: 13 nodes
        in is found and as a frequency 1
Tree Check:
        Tree Height: 7
        Tree Size: 13 nodes
        No is not found 

Team Members: 1) Suchith Pinreddy: void print_tree (node_t *tree); = Modified
                                    int recur_print (node_t *tree, int level); = Modified
                                    node_t* create_node(char word[30]); = Implemented
                                    void inorder_trav(node_t* root, FILE *fp); = Implemented
                                    node_t* insert_leaf(node_t* node, char word[30]); = Modified
                                    node_t* search_leaf(node_t * root,char data[30]); = Modified
                                    int total_nodes(node_t *tree); = Implemented 
                                    void concordance_file_write(node_t *root); = Implemented
                                    void tree_check(node_t *root, char word[30]); = Implemented 
                I implemeted fuctions to count the toatal no. of nodes, to write the data in the concordance file, 
                tree check and the file traversing functions. The questions were answered by me and checked by Yash my other teammate.
            2) Yash Nikumb: void print_tree (node_t *tree); = Implemented
                                    int recur_print (node_t *tree, int level); = Implemeted
                                    node_t* create_node(char word[30]); = Implemented
                                    void inorder_trav(node_t* root, FILE *fp); = Implemented
                                    node_t* insert_leaf(node_t* node, char word[30]); = Designed
                                    node_t* search_leaf(node_t * root,char data[30]); = Designed
                                    int total_nodes(node_t *tree); = Modified
                                    void concordance_file_write(node_t *root); = Checked for errors/Modified
                                    void tree_check(node_t *root, char word[30]); = Check for logical errors 
                I designed the above functions to insert and search nodes in the Binary tree. I also debugged the program 
ii) Test Cases and Status
1. example text.txt – passed (text.txt)
----> Tree Check:
        Tree Height: 7
        Tree Size: 13 nodes
        in is found and as a frequency 1
      Tree Check:
        Tree Height: 7
        Tree Size: 13 nodes
        shut is not found
-------------------------------------------------------------------------------------------------------------------------------
2. text.txt with one word – passed (text2.txt)
----> Tree Check:
        Tree Height: 1
        Tree Size: 1 nodes
        in is found and as a frequency 1
      Tree Check:
        Tree Height: 1
        Tree Size: 1 nodes
        shut is not found
---------------------------------------------------------------------------------------------------------------------------------
3. empty text.txt – passed (text3.txt)
----> Tree Check:
        Tree Height: 0
        Tree Size: 0 nodes
        in is not found
      Tree Check:
        Tree Height: 0
        Tree Size: 0 nodes
        shut is not found
----------------------------------------------------------------------------------------------------------------------------------
4. text.txt with > 500 total words – passed (text4.txt)
-----> Tree Check:
        Tree Height: 9
        Tree Size: 217 nodes
        in is found and as a frequency 11
       Tree Check:
        Tree Height: 9
        Tree Size: 217 nodes
        shut is not found
-----------------------------------------------------------------------------------------------------------------------------------

iii). Binary Search Tree Analysis
1. Example of a best case for inserting n words into a binary search tree 
Ans. The best case scenario for BST is when inserting the root node for the Binary search tree. 
2. Big O of the best case for inserting n words into a binary search tree 
Ans. The best case scenario for Binary Search tree for n no. of words is when O(1).
3. Big O of the storage requirements for a binary search tree of size n
Ans. Big O of the storage requirements for size n BST is O(n+c) where c is a constant for all the variable that were used. 
4. For the example text.txt file, the tree height is 7. What would the minimum height be in
the best case? 
Ans. The minimum height of the tree will be Level zero means height will be one the root will be the best case scenario for the following example.
*/
