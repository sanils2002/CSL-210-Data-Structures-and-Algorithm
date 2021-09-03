#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

struct keyval_item* dataBucket[SIZE] = {NULL}; 

int hashFunc(int key) {
   return key % SIZE;
}

struct keyval_item* search(int key) {
   //get the hash 
   int hashIndex = hashFunc(key);  
   struct keyval_item* head_item = dataBucket[hashIndex]; 

   while(NULL != head_item){
      if(head_item->key == key){
         return head_item;
      }
      head_item = head_item->next;
   }

   return NULL;
}

void insert(int key,int data) {
   struct keyval_item *item = (struct keyval_item*) malloc(sizeof(struct keyval_item));
   item->data = data;  
   item->key = key;

   //get the hash 
   int hashIndex = hashFunc(key);
   if(NULL != dataBucket[hashIndex]){
      // insert before the current and create a new head
      item->next = dataBucket[hashIndex];
   }  
   dataBucket[hashIndex] = item;
}

void delete(struct keyval_item* item) {
   int key = item->key;

   //get the hash 
   int hashIndex = hashFunc(key);
   free(dataBucket[hashIndex]);
   dataBucket[hashIndex] = NULL;    
}

void display() {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
      if(dataBucket[i] != NULL)
         printf(" (%d,%d) pair at index = %d\n",dataBucket[i]->key,dataBucket[i]->data, i);
   }
	
   printf("\n");
}

