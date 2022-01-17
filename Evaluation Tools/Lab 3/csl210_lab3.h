
/**
 * Lab assignment 3
 * CSL 210 2021
 * Deadline: Friday Oct 29 11pm.
 * Submit the c implementation file for this header file
 * Filename should be of format YourEnrollmentNumber_lab3.c (lower case); e.g., bt20cse999_lab3.c
 *
 * 
 * Compilation error = 0
 * Late submission = 0
 * Presence of uncommented main function in the submission file = 0
 * Cheating/plagiarism = 0
 * */

#define EMPTYNODE 0

struct btNode{
    unsigned short frequency;
    char value;
    struct btNode* left;
    struct btNode* right;
};

typedef struct btNode btNode_t;

/**
 * Method to create binary tree for huffman coding from the given input character sequence 
 * 
 * Video lecture: https://drive.google.com/file/d/19vsla2J6E_s3hUOhSSg2p1TVBroUC8bl/view 
 * 
 * Input will be an array of characters. Size of the input array is the second parameter.
 * The input will consist of lower case letters from the English alphabet.
 *    
 * Your function will calculate frequency of individual characters in the input array.
 * 
 * For example 'qwertyqqwfrtggggbryyyyyyyeeeeqqqqqqq' will be the input array.
 * Your implementation will calculate the frequency of occurrence of individual characters ('q', 'w', 'e', 'r' etc.). 
 * Based on the frequency of individual characters, you will build the binary tree for huffman coding.
 * 
 * Return the root node of the huffman tree
 * */
btNode_t* createHuffmanTree(char input[], unsigned short sz);