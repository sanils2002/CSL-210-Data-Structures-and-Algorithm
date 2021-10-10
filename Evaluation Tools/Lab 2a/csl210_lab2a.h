
/**
 * Lab assignment 2a
 * CSL 210 2021
 * Deadline: Sunday Oct 10 11pm.
 * Submit the c implementation file for this header file
 * Filename should be of format YourEnrollmentNumber_lab2a.c (lower case); e.g., bt20cse999_lab2a.c
 *
 * 
 * Compilation error = 0
 * Late submission = 0
 * Presence of uncommented main function in the submission file = 0
 * Cheating/plagiarism = 0
 * */

#define EMPTYNODE 0

struct bstNode{
    short value;
    struct bstNode* left;
    struct bstNode* right;
};

typedef struct bstNode bstNode_t;

struct quadNode{
    short value;
    struct quadNode* child0; // leftmost
    struct quadNode* child1; // next to the leftmost
    struct quadNode* child2; // right of child1
    struct quadNode* child3; // rightmost

};

typedef struct quadNode quadNode_t;

typedef enum {
  INORDER = 0,
  PREORDER = 1,
  POSTORDER = 2
} traversal_t ; 

/**
 * Method to convert a BST to Quad Tree
 * A Quad tree is an ADT similar to BST
 * In a Quad Tree following properties hold
 *      each node has between 0 to 4 children
 *      values in the leftmost subtree are lesser than the values in subtree to its right
 *      and likewise until the rightmost subtree 
 * 
 * For this function there are two inputs
 *      i)  rootBST: root of a valid BST
 *      ii) order: order of traversal, i.e. inorder, preorder or postorder
 * 
 * The output of the traversal order of rootBST will be the sequence of input for creating the quad tree.
 * 
 * Return the root node of the quad tree created by your implementation.
 * The output will be compared using inorder traversal of quad tree (implemented by the instructor).
 * */
quadNode_t* convertBST2QuadTree(bstNode_t* rootBST, traversal_t order);

