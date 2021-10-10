/**
 * Lab assignment 1
 * CSL 210 2021
 * Deadline: Saturday September 4 by 6am.
 * Submit the c implementation file for this header file
 * Filename should be of format YourEnrollmentNumber_lab1.c (lower case); e.g., bt20cse999.c
 * 
 * Implement all the functions even if the solution is imperfect. If you dont implement all functions,
 * it will result in a compilation error
 *
 * 
 * Compilation error = 0
 * Late submission = 0
 * Presence of uncommented main function in the submission file = 0
 * Cheating/plagiarism = 0
 * */

#define EMPTYNODE 0
#define SIZE_HASH_TABLE 5

struct nodeQ{
    unsigned short row;
    unsigned short column;
    short value;
    struct nodeQ* next;
};

typedef struct nodeQ nodeQ_t;

struct priorityNodeQ{
    unsigned short value;
    unsigned short priority;
    struct priorityNodeQ* next;
};

typedef struct priorityNodeQ priorityNodeQ_t;

priorityNodeQ_t* g_priorityHashTable[SIZE_HASH_TABLE] = {0};

/**
 * Method to convert sparse matrix to linked list
 * Input -
 *      matrix: is a 2d array with values pre-populated 
 *      rows: number of rows in a 2d array
 *      columns: number of columns in a 2d array
 * Output - 
 *      Linked list that represents the input matrix
 *      The memory for ouput linked list must be allocated inside the function
 *      The caller will take care of freeing the memory
 * */
nodeQ_t* convertSparseMatrixToLinkedList(unsigned short** matrix, unsigned short rows, unsigned short columns);

/**
 * Multiply two sparse matrices that are represented as linked list
 * Input -
 *      matrix_llist_1: linked list output using convertSparseMatrixToLinkedList function
 *      matrix_llist_2: linked list output using convertSparseMatrixToLinkedList function
 * Output - 
 *      Linked list that represents the input matrix
 *      The memory for ouput linked list must be allocated inside the function
 *      The caller will take care of freeing the memory
 * */
nodeQ_t* multiplySparseMatricesLinkedLists(nodeQ_t* matrix_llist_1, nodeQ_t* matrix_llist_2);


/**
 * DO NOT DELETE OR REIMPLEMENT THIS FUNCTION
 * */
unsigned short hashFuncLab1(unsigned short key){
    return key % SIZE_HASH_TABLE;
}

/**
 * Insert elements in g_priorityHashTable (defined above)
 * The function must use the implementation of hashFuncLab1 defined above
 * The input hashFuncLab1 is the "value" member of priorityNodeQ_t
 * In case of collision, separate chaining must be used.
 * Every chain (linked list) in the hash table must be a priority queue
 * The priority value will be in the range 1 - 5, 1 being the highest. 
 * The head node in the chain must be the node with highest priority and tail with the lowest
 * Basic implementation for hash table available at 
 * https://github.com/aniket-acad/data_structures/blob/main/adt/hash_table.c
 * Input -
 *      item will be instatiated in memory before passing it in
 * */
void insertPriorityHashTable(priorityNodeQ_t* item);

/**
 * Function to remove/dequeue the element from g_priorityHashTable with the highest priority for the input key
 * The element with highest priority is the head node in the chain
 * Output - 
 *      The element with the highest priority (1 on the scale of 1-5) for the input key must be dequeued and returned
 * */
priorityNodeQ_t* dequeueFromPriorityHashTable(unsigned short key);