#include <stdlib.h>
#include <time.h>
#include "csl210_lab1.h"
#include <stdio.h>

nodeQ_t* convertSparseMatrixToLinkedList(unsigned short** matrix, unsigned short rows, unsigned short columns){
    // It is assumed that the input will be valid.
    // So not performing any checks here.
    // Ideally, all checks must be implemented before processing the data

    nodeQ_t* llist = EMPTYNODE;
    nodeQ_t* curr = EMPTYNODE;

    for (int r = 0; r < rows; r++) {        
        for (int c = 0; c < columns; c++){
            if(0 != matrix[r][c]){
                nodeQ_t* ptr = (nodeQ_t*)malloc(sizeof(nodeQ_t));
                ptr->row = r;
                ptr->column = c;
                ptr->value = matrix[r][c];
                ptr->next = EMPTYNODE;
                
                if(EMPTYNODE == llist){   
                    curr = llist = ptr;
                }
                else{
                    curr->next = ptr;
                    curr = ptr;
                }
            }
       }
    }

    return llist;
}

void printList(nodeQ_t* head){
    if(EMPTYNODE == head) return;

    nodeQ_t* node = head;
    while(node){
        printf("%d | %d | %d | --> ", node->row, node->column, node->value);
        node = node->next;
    }
    printf("EMPTYNODE\n");
}

nodeQ_t* multiplySparseMatricesLinkedLists(nodeQ_t* matrix_llist_1, nodeQ_t* matrix_llist_2){
    // It is assumed that the lists input will be compatible for multiplication

    nodeQ_t* multList = EMPTYNODE;

    nodeQ_t* lst1 = matrix_llist_1;
    while(lst1){
        nodeQ_t* lst2 = matrix_llist_2;
       
        while(lst2){
             nodeQ_t* currMultList = multList;

            if(lst1->column == lst2->row){

                if(EMPTYNODE == multList){
                    multList = (nodeQ_t*)malloc(sizeof(nodeQ_t));
                    multList->row = lst1->row;
                    multList->column = lst2->column;
                    multList->value = lst1->value * lst2->value;
                    multList->next = EMPTYNODE;
                    currMultList = multList;
                    continue;
                }

                short found = 0;
                while(currMultList){
                    if(currMultList->row == lst1->row && currMultList->column == lst2->column){
                        currMultList->value = currMultList->value + (lst1->value * lst2->value);
                        found = 1;
                        break;
                    }

                    if(currMultList->next)
                        currMultList = currMultList->next;
                    else
                        break;
                }

                if(0 == found){
                    currMultList->next = (nodeQ_t*)malloc(sizeof(nodeQ_t));
                    currMultList = currMultList->next;
                    currMultList->row = lst1->row;
                    currMultList->column = lst2->column;
                    currMultList->value = lst1->value * lst2->value;
                    currMultList->next = EMPTYNODE;
                }
            }

            lst2 = lst2->next;
        }

        lst1 = lst1->next;
    }

    return multList;
}

void insertPriorityHashTable(priorityNodeQ_t* item){
    // assuming valid input. 
    // allowing duplicate values in the chain

    unsigned short idxTable = hashFuncLab1(item->value);

    if(0 == g_priorityHashTable[idxTable]){
        g_priorityHashTable[idxTable] = item;
    }
    else{
        priorityNodeQ_t* curr = g_priorityHashTable[idxTable];
        if(EMPTYNODE == curr) {
            return;
        }
        if(curr->priority >= item->priority){ // 1 is higher priority than 2 and so forth ...
            g_priorityHashTable[idxTable] = item;
            item->next = curr;
        }
        else{
            priorityNodeQ_t* prev = curr; 
            
            while(EMPTYNODE != curr && curr->priority < item->priority){
                prev = curr;
                curr = curr->next;
            }

            if(EMPTYNODE == curr){
                // inserting at the end
                prev->next = item;
                return;
            }

            // inserting in the middle
            item->next = prev->next;
            prev->next = item;
    
        }
    }
}

priorityNodeQ_t* dequeueFromPriorityHashTable(unsigned short key){
    // assuming valid input
    unsigned short idxTable = hashFuncLab1(key);
    priorityNodeQ_t* node = g_priorityHashTable[idxTable];

    if(key == node->value){
        g_priorityHashTable[idxTable] = node->next;
        return node;
    }

    if(EMPTYNODE != node){

        priorityNodeQ_t* prev = node;
        priorityNodeQ_t* curr = node->next;

        while(curr){

            if(key == curr->value){
                prev->next = curr->next;            
                return curr;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    return EMPTYNODE;
}

unsigned short** createRandomSparseMatrix(unsigned short rows, unsigned short columns){
    unsigned short **arr = (unsigned short **)malloc(rows * sizeof(unsigned short *));    
    
    for (int r = 0; r < rows; r++) {
        arr[r] = (unsigned short *)malloc(columns * sizeof(unsigned short));
        
        for (int c = 0; c < columns; c++){
            unsigned short v = rand() % 20;
            if (0 == v % 3)
                arr[r][c] = v;
            else
                arr[r][c] = 0;
        }
    }
    return arr;
}


int main(){
    srand(time(0));

    unsigned short numRow1 = 4 + rand() % 10;
    unsigned short numCol1 = 4 + rand() % 10;
    unsigned short numRow2 = numCol1;
    unsigned short numCol2 = 4 + rand() % 10;

    nodeQ_t* llist1 = convertSparseMatrixToLinkedList(createRandomSparseMatrix(numRow1, numCol1), numRow1, numCol1);
    printList(llist1);
    printf("\n\n");
    nodeQ_t* llist2 = convertSparseMatrixToLinkedList(createRandomSparseMatrix(numRow2, numCol2), numRow2, numCol2);
    printList(llist2);
    printf("\n\n");
    nodeQ_t* multList = multiplySparseMatricesLinkedLists(llist1, llist2);
    printList(multList);
    printf("\n\n");

    unsigned short inpArr[50] = {0};

    for(int itr=0; itr<50; itr++){
        priorityNodeQ_t* node = (priorityNodeQ_t*)malloc(sizeof(priorityNodeQ_t));
        node->next = EMPTYNODE;
        node->value = 1 + rand() % 100;
        inpArr[itr] = node->value;
        node->priority = 1 + rand() % 5;
        insertPriorityHashTable(node);
    }

    for(int itr=0; itr<SIZE_HASH_TABLE; itr++){
        priorityNodeQ_t* node = g_priorityHashTable[itr];
        while(node){
            printf("%d | %d | --> ", node->priority, node->value);
            node = node->next;
        }
        printf("EMPTYNODE\n\n");
    }

    {
        printf("\n\n");
        priorityNodeQ_t* node = dequeueFromPriorityHashTable(inpArr[34]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[20]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[2]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[5]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[27]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[13]);
        printf("%d || %d\n", node->priority, node->value);
        node = dequeueFromPriorityHashTable(inpArr[43]);
        printf("%d || %d\n", node->priority, node->value);
    }

    printf("\n\n\n\n");

    for(int itr=0; itr<SIZE_HASH_TABLE; itr++){
        priorityNodeQ_t* node = g_priorityHashTable[itr];
        while(node){
            printf("%d | %d | --> ", node->priority, node->value);
            node = node->next;
        }
        printf("EMPTYNODE\n\n");
    }

    return 0;
}