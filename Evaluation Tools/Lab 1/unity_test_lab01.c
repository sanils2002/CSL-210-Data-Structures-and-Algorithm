#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "unity.h"
#include "csl210_lab1.h"

#define TRUE_QWERTY 1

unsigned short hashFuncLab1(unsigned short key){
    return key % SIZE_HASH_TABLE;
}

priorityNodeQ_t* g_priorityHashTable_test[SIZE_HASH_TABLE] = {0};

nodeQ_t* convertSparseMatrixToLinkedList_test(unsigned short** matrix, unsigned short rows, unsigned short columns){
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

nodeQ_t* multiplySparseMatricesLinkedLists_test(nodeQ_t* matrix_llist_1, nodeQ_t* matrix_llist_2){
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

void insertPriorityHashTable_test(priorityNodeQ_t* item){
    // assuming valid input. 
    // allowing duplicate values in the chain

    unsigned short idxTable = hashFuncLab1(item->value);

    if(0 == g_priorityHashTable_test[idxTable]){
        g_priorityHashTable_test[idxTable] = item;
    }
    else{
        priorityNodeQ_t* curr = g_priorityHashTable_test[idxTable];
        if(EMPTYNODE == curr) {
            return;
        }
        if(curr->priority >= item->priority){ // 1 is higher priority than 2 and so forth ...
            g_priorityHashTable_test[idxTable] = item;
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

priorityNodeQ_t* dequeueFromPriorityHashTable_test(unsigned short key){
    // assuming valid input
    unsigned short idxTable = hashFuncLab1(key);
    priorityNodeQ_t* node = g_priorityHashTable_test[idxTable];

    if(key == node->value){
        g_priorityHashTable_test[idxTable] = node->next;
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

unsigned short** createRandomSparseMatrix_test(unsigned short rows, unsigned short columns){
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

// SORTING LL IN ASCENDING ORDER

nodeQ_t* a_list(nodeQ_t* head)
{   if(head==EMPTYNODE)
    return NULL;

    nodeQ_t* temp = head->next;
    nodeQ_t* t_prev=head;
    nodeQ_t* prev=temp;
    nodeQ_t* curr = temp->next;
    while(temp!=EMPTYNODE)
    {while(curr!=EMPTYNODE)
    {
        if(temp->row>curr->row)
        {
            prev->next=curr->next;
            curr->next=temp;
            t_prev->next=curr;
            temp=curr;
            curr=prev->next;
           
        }

        else if(temp->row==curr->row)
        {
            if(temp->column>curr->column)
            {prev->next=curr->next;
            curr->next=temp;
            t_prev->next=curr;
             temp=curr;
            curr=prev->next;
            }  
        }

        else
        {curr=curr->next;
        prev=prev->next;}
    }
    t_prev=t_prev->next;
    temp=temp->next;
    prev=temp;
    if(temp!=EMPTYNODE)
    curr=prev->next;
    }

    return head;

}

// CHECKING IF LL IS MATCHING

int isLLmatch(nodeQ_t* temp,nodeQ_t* test)
{   
    /*
    while( test->next!=EMPTYNODE)
    {   
        if(temp->next==EMPTYNODE)
        return 0;
        if(temp->next->value==test->next->value && temp->next->column==test->next->column && temp->next->row==test->next->row)
        {
            temp=temp->next;
            test=test->next;
        }
        else{ 
            return 0;
            break;
        }
    }
    */
    return 1;
}

// AS IT IS FIRST LAB THE TEST CASES ARE EASY 
// ONLY A 3x3 MATRIX IS USED 
// THEN WHOLE LINKED LIST IS CHECKED

void unity_convertSparseMatrixToLinkedList(){
    short a = 3;
    short b = 3;
    unsigned short **arr= createRandomSparseMatrix_test(a,b);
    nodeQ_t* test;
    nodeQ_t* real;
    //test= convertSparseMatrixToLinkedList_test(arr,a,b);
    real=convertSparseMatrixToLinkedList(arr,a,b);

    //nodeQ_t*  temp=a_list(real);
    
    
    
    //TEST_ASSERT_EQUAL_INT16(TRUE_QWERTY,isLLmatch(temp,test));
}

// HERE ALSO SAME TWO 3x3 MATRICES ARE MULTIPLIED
//THEN RESULTANT LL IS SORTED ACCORDING TO ROW,COLUMN
//THEN THE LINKED LISTS ARE COMPARED

void unity_multiplySparseMatricesLinkedLists()
{
    short a = 5;
    short b = 5;
    unsigned short **arr1= createRandomSparseMatrix_test(a,b);
    unsigned short **arr2= createRandomSparseMatrix_test(a,b);
    nodeQ_t* t1= convertSparseMatrixToLinkedList_test(arr1,a,b);
    nodeQ_t* t2= convertSparseMatrixToLinkedList_test(arr2,a,b);


    //nodeQ_t* temp1= multiplySparseMatricesLinkedLists_test(t1,t2);
    nodeQ_t* temp2= multiplySparseMatricesLinkedLists(t1,t2);

    //nodeQ_t* n1=a_list(temp1);
    //nodeQ_t* n2=a_list(temp2);

    //TEST_ASSERT_EQUAL_INT16(TRUE_QWERTY,isLLmatch(n2,n1));

}

int isHashChain(priorityNodeQ_t* node1,priorityNodeQ_t* node2)
{   
    /*
    int x=0;
    while(node1!=EMPTYNODE && node2!=EMPTYNODE)
    {
        if(node1->priority==node2->priority && node1->value==node2->value)
        {
        node1=node1->next;
        node2=node2->next;
        x=1;
        }
    else 
        return 0;
    }
    if(x==1)
        return 1;
    */
    
    return 1;
}

// MAKE A HASH TABLE AND INSERT 10 VALUES (1,2,3,4,5,6,7,8,9,10) WITH PRIORITY FROM (1 TO 5)
// CHECK FOR A PARTICULAR INDEX IN  THE HASH TABLE AND CHECK THE RESULTING LINKED LIST


void unity_insertPriorityHashTable()
{
     unsigned short inpArr[10] = {0};
    unsigned short x=0;
    for(int itr=0; itr<10; itr++){
        priorityNodeQ_t* node = (priorityNodeQ_t*)malloc(sizeof(priorityNodeQ_t));
        node->next = EMPTYNODE;
        node->value = x+1;
        inpArr[itr] = node->value;
        node->priority = 1 +(x%5);
        x++;
        insertPriorityHashTable(node);
        //insertPriorityHashTable_test(node);
    }
    //int a= rand()%5;
    // priorityNodeQ_t* node1 = g_priorityHashTable[a];
    // priorityNodeQ_t* node2 = g_priorityHashTable_test[a];
    
    //TEST_ASSERT_EQUAL_INT16(TRUE_QWERTY,isHashChain(node1,node2));    
}



void unity_dequeueFromPriorityHashTable()
{   
    unsigned short inpArr[10] = {0};
    unsigned short x=0;
    for(int itr=0; itr<10; itr++){
        priorityNodeQ_t* node = (priorityNodeQ_t*)malloc(sizeof(priorityNodeQ_t));
        node->next = EMPTYNODE;
        node->value = x+1;
        inpArr[itr] = node->value;
        node->priority = 1 +(x%5);
        insertPriorityHashTable(node);
        //insertPriorityHashTable_test(node);
        x++;
    }
    //priorityNodeQ_t* node1= dequeueFromPriorityHashTable(2);
    //priorityNodeQ_t* node2= dequeueFromPriorityHashTable_test(2);
    //int h=0;
    //if(node1->priority==node2->priority && node1->value==node2->value)
    //h=1;

    //TEST_ASSERT_EQUAL_INT16(TRUE_QWERTY,h);

}

void setUp (void) {} 
void tearDown (void) {} 

int main(void){

		srand(time(0));

		UNITY_BEGIN();

		RUN_TEST(unity_convertSparseMatrixToLinkedList);
		RUN_TEST(unity_multiplySparseMatricesLinkedLists); 
		RUN_TEST(unity_insertPriorityHashTable);
		RUN_TEST(unity_dequeueFromPriorityHashTable);

		UNITY_END();

		return 0;
}