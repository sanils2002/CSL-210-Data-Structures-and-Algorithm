
/**
 * Lab assignment 2b
 * CSL 210 2021
 * Deadline: Sunday Oct 10 11pm.
 * Submit the c implementation file for this header file
 * Filename should be of format YourEnrollmentNumber_lab2b.c (lower case); e.g., bt20cse999_lab2b.c
 *
 * 
 * Compilation error = 0
 * Late submission = 0
 * Presence of uncommented main function in the submission file = 0
 * Cheating/plagiarism = 0
 * */

#define EMPTYNODE 0

struct btNode{
    short value;
    struct btNode* left;
    struct btNode* right;
};

typedef struct btNode btNode_t;

/**
 * Method to find if a subtree in a binary tree is a BST 
 * 
 * For this function there is only one input
 *      i)  rootNode: root of a binary tree
 * 
 * Conditions:
 *      i) There will exactly 0 or 1 BST subtree in the input binary tree 
 *      ii) The number of nodes in the BST subtree will be greater than 2.
 *      iii) The BST subtree will be a proper subtree, i.e. it will not contain only internal nodes
 * 
 * Return the root node of the subtree that is a BST. Return EMPTYNODE if no BST is a subtree.
 * */
btNode_t* getBSTSubtree(btNode_t* rootNode);

