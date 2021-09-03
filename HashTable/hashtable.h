#define SIZE 255

struct keyval_item {
   int data;   
   int key;
   struct keyval_item* next;
};