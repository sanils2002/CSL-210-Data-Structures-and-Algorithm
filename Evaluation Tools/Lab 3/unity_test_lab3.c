#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "csl210_lab3.h"

#define MAX_TREE_HUFFMAN_INSTR 1 << 10

struct minHeap_instr {
  unsigned size;
  unsigned capacity;
  struct btNode **array;
};

struct btNode *createNode_instr(char item, unsigned freq) {
  struct btNode *temp = (struct btNode *)malloc(sizeof(struct btNode));

  temp->left = temp->right = NULL;
  temp->value = item;
  temp->frequency = freq;

  return temp;
}

struct minHeap_instr *createMinHeap_instr(unsigned capacity) {
  struct minHeap_instr *minHeap_instr = (struct minHeap_instr *)malloc(sizeof(struct minHeap_instr));

  minHeap_instr->size = 0;

  minHeap_instr->capacity = capacity;

  minHeap_instr->array = (struct btNode **)malloc(minHeap_instr->capacity * sizeof(struct btNode *));
  return minHeap_instr;
}

void swapMinHuffmanNode_instr(struct btNode **a, struct btNode **b) {
  struct btNode *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify_instr(struct minHeap_instr *minHeap_instr, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap_instr->size && minHeap_instr->array[left]->frequency < minHeap_instr->array[smallest]->frequency)
    smallest = left;

  if (right < minHeap_instr->size && minHeap_instr->array[right]->frequency < minHeap_instr->array[smallest]->frequency)
    smallest = right;

  if (smallest != idx) {
    swapMinHuffmanNode_instr(&minHeap_instr->array[smallest], &minHeap_instr->array[idx]);
    minHeapify_instr(minHeap_instr, smallest);
  }
}

int checkSizeOne_instr(struct minHeap_instr *minHeap_instr) {
  return (minHeap_instr->size == 1);
}

struct btNode *extractMin_instr(struct minHeap_instr *minHeap_instr) {
  struct btNode *temp = minHeap_instr->array[0];
  minHeap_instr->array[0] = minHeap_instr->array[minHeap_instr->size - 1];

  --minHeap_instr->size;
  minHeapify_instr(minHeap_instr, 0);

  return temp;
}

void insertMinHeap_instr(struct minHeap_instr *minHeap_instr, struct btNode *minHeapNode) {
  ++minHeap_instr->size;
  int i = minHeap_instr->size - 1;

  while (i && minHeapNode->frequency < minHeap_instr->array[(i - 1) / 2]->frequency) {
    minHeap_instr->array[i] = minHeap_instr->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap_instr->array[i] = minHeapNode;
}

void buildMinHeap_instr(struct minHeap_instr *minHeap_instr) {
  int n = minHeap_instr->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify_instr(minHeap_instr, i);
}

int isLeaf_instr(struct btNode *root) {
  return !(root->left) && !(root->right);
}

struct minHeap_instr *createAndBuildMinHeap_instr(char item[], int freq[], int size) {
  struct minHeap_instr *minHeap_instr = createMinHeap_instr(size);

  for (int i = 0; i < size; ++i)
    minHeap_instr->array[i] = createNode_instr(item[i], freq[i]);

  minHeap_instr->size = size;
  buildMinHeap_instr(minHeap_instr);

  return minHeap_instr;
}

struct btNode *buildHuffmanTree_instr(char item[], int freq[], int size) {
  struct btNode *left, *right, *top;
  struct minHeap_instr *minHeap_instr = createAndBuildMinHeap_instr(item, freq, size);

  while (!checkSizeOne_instr(minHeap_instr)) {
    left = extractMin_instr(minHeap_instr);
    right = extractMin_instr(minHeap_instr);

    top = createNode_instr('$', left->frequency + right->frequency);

    top->left = left;
    top->right = right;

    insertMinHeap_instr(minHeap_instr, top);
  }
  return extractMin_instr(minHeap_instr);
}

btNode_t* createHuffmanTree_instr(char input[], unsigned short sz)
{
    short frequency_table[26] = {0};
    for(short itr=0; itr < sz; itr++){
        //printf("input char = %c\n", input[itr]);
        frequency_table[ (short)(input[itr]) - 97]++;
    }

    char item[26] = {'\0'};
    int freq[26] = {0};
    unsigned short size = 0;

    for(short itr=0; itr < 26; itr++){
        //printf("char = %c, freq = %d\n\n", (char)(itr+97), frequency_table[itr]);
        if(frequency_table[itr] > 0){
            item[size] = (char)(itr+97);
            freq[size++] = frequency_table[itr];
        }
    }

    return buildHuffmanTree_instr(item, freq, size);
}

void unity_createHuffmanTree()
{   
    char input[] = "qwertyqqwfrtggggbryyyyyyyeeeeqqqqqqq";
    btNode_t* huffTree = createHuffmanTree(input, sizeof(input)/sizeof(char) - 1);
	btNode_t* huffTree_instr = createHuffmanTree_instr(input, sizeof(input)/sizeof(char) - 1);

	if(!huffTree)  TEST_ASSERT_EQUAL_INT16(0, 1);  

    TEST_ASSERT_EQUAL_INT16(huffTree->frequency, huffTree_instr->frequency);    
}

void setUp (void) {} 
void tearDown (void) {} 

int main(void){

		UNITY_BEGIN();

		RUN_TEST(unity_createHuffmanTree);
		
		UNITY_END();

		return 0;
}