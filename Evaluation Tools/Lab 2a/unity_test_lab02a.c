#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "csl210_lab2a.h"
#include <time.h>

short inputSequenceToQuadTree_instr[1 << 16] = {0}; // 65536
// this is very large array. 
// can use linked list instead. didn't want to make the code too complicated, so chose array.
unsigned short countNodesInBST_instr = 0;
bstNode_t* root_instr = EMPTYNODE;

void printInorderQuadTree_instr(quadNode_t* node){
    if(!node) 
        return;

    printInorderQuadTree_instr(node->child0); // left
	printInorderQuadTree_instr(node->child1); // left
    printf("%d, ", node->value); // root
    printInorderQuadTree_instr(node->child2); // right
	printInorderQuadTree_instr(node->child3); // right

}

quadNode_t* getParentNodeQuadTree(quadNode_t* node, short data){

	//There are 4 children per node. You can call them L1, L2, R1, R2.
	//L1 < Root. L2 < Root. L1 < L2.
	//R1 > Root, R2 > Root. R2 > R1. 

	while(EMPTYNODE != node){
		if (data > node->value) {
			if(EMPTYNODE != node->child2 && EMPTYNODE != node->child3){
				if (data > node->child3->value)
					node = node->child3;
				else
					node = node->child2;

				continue;
			}

			if((EMPTYNODE != node->child2 && EMPTYNODE == node->child3)){
				if (data < node->child2->value)
					node = node->child2;
				else
					break;

				continue;
			}

			if((EMPTYNODE == node->child2 && EMPTYNODE == node->child3))
				break;
		}

		if(data < node->value){
			if((EMPTYNODE != node->child0) && (EMPTYNODE != node->child1)){
				if (data > node->child1->value)
					node = node->child1;
				else
					node = node->child0;

				continue;
			}

			if((EMPTYNODE != node->child0) && (EMPTYNODE == node->child1)){
				if (data < node->child0->value)
					node = node->child0;
				else
					break;

				continue;
			}

			if((EMPTYNODE == node->child0) && (EMPTYNODE == node->child1))
				break;
		}
	}

	return node;
}

void insertNodeInQuadTree_instr(quadNode_t* root, quadNode_t* newNode){

	//There are 4 children per node. You can call them L1, L2, R1, R2.
	//L1 < Root. L2 < Root. L1 < L2.
	//R1 > Root, R2 > Root. R2 > R1. 

	if(EMPTYNODE == root || EMPTYNODE == newNode)
		return;

	quadNode_t* parent = getParentNodeQuadTree(root, newNode->value);
	if(EMPTYNODE == parent)
		return;

	if(newNode->value > parent->value){
		if(EMPTYNODE == parent->child2) 
			parent->child2 = newNode;

		else if(EMPTYNODE == parent->child3) 
			parent->child3 = newNode;
	}

	if(newNode->value < parent->value){
		if(EMPTYNODE == parent->child0) 
			parent->child0 = newNode;

		else if(EMPTYNODE == parent->child1) 
			parent->child1 = newNode;
	}
}

quadNode_t* createQuadNode_instr(short data){
	quadNode_t* node = (quadNode_t*)malloc(sizeof(quadNode_t));
	node->value = data;

	node->child0 = EMPTYNODE;
	node->child1 = EMPTYNODE;
	node->child2 = EMPTYNODE;
	node->child3 = EMPTYNODE;

	return node;
}

void insertInorder_instr(bstNode_t* node){
	if(!node) 
		return;

	insertInorder_instr(node->left); // left
	// following statement is dangerous if countNodesInBST_instr becomes greater than size of inputSequenceToQuadTree_instr
	// however, we have a very large array and our environment is controlled
	inputSequenceToQuadTree_instr[countNodesInBST_instr++] = node->value; 
	insertInorder_instr(node->right); // right
}

void insertPreorder_instr(bstNode_t* node){
	if(!node) 
		return;

	// following statement is dangerous if countNodesInBST_instr becomes greater than size of inputSequenceToQuadTree_instr
	// however, we have a very large array and our environment is controlled
	inputSequenceToQuadTree_instr[countNodesInBST_instr++] = node->value; 
	insertPreorder_instr(node->left); // left
	insertPreorder_instr(node->right); // right

}

void insertPostorder_instr(bstNode_t* node){
	if(!node) 
		return;

	insertPostorder_instr(node->left); // left
	insertPostorder_instr(node->right); // right
	// following statement is dangerous if countNodesInBST_instr becomes greater than size of inputSequenceToQuadTree_instr
	// however, we have a very large array and our environment is controlled
	inputSequenceToQuadTree_instr[countNodesInBST_instr++] = node->value; 
}

quadNode_t* convertBST2QuadTree_instr(bstNode_t* rootBST, traversal_t order){

	countNodesInBST_instr = 0;

	if(INORDER == order)
		insertInorder_instr(rootBST);
	else if(PREORDER == order)
		insertPreorder_instr(rootBST);
	else
		insertPostorder_instr(rootBST);

	/*for(int i = 0; i < countNodesInBST_instr; i++)
	  printf("%d, ", inputSequenceToQuadTree_instr[i]);

	  printf("\n\n");*/

	quadNode_t* rootQuad = createQuadNode_instr(inputSequenceToQuadTree_instr[0]);
	for(int i = 1; i < countNodesInBST_instr; i++){
		insertNodeInQuadTree_instr(rootQuad, createQuadNode_instr(inputSequenceToQuadTree_instr[i]));
	}

	return rootQuad;
}

bstNode_t* createBSTNode_instr(short data){
	bstNode_t* node = (bstNode_t*)malloc(sizeof(bstNode_t));
	node->value = data;

	node->left = EMPTYNODE;
	node->right = EMPTYNODE;
	return node;
}

bstNode_t* getParentNodeBST_instr(bstNode_t* node, short val){

	while(EMPTYNODE != node){
		if ((val > node->value) && (node->right != EMPTYNODE))     
			node = node->right;
		else if ((val > node->value) && (node->right == EMPTYNODE))
			return node;
		else if ((val < node->value) && (node->left != EMPTYNODE))    
			node = node->left;
		else if ((val < node->value) && (node->left == EMPTYNODE))
			return node;
		else
			return EMPTYNODE;
	}

	return EMPTYNODE;
}

void insertNodeInBST_instr(bstNode_t* root, bstNode_t* newNode){

	if(EMPTYNODE == root || EMPTYNODE == newNode)
		return;

	bstNode_t* parent = getParentNodeBST_instr(root, newNode->value);
	if(EMPTYNODE == parent)
		return;

	if(newNode->value > parent->value)
		parent->right = newNode;
	if(newNode->value < parent->value)
		parent->left = newNode;
}

void unity_convertBST2QuadTree_inorder()
{   
	quadNode_t* rootQuad = EMPTYNODE;
	rootQuad = convertBST2QuadTree_instr(root_instr, INORDER);
	if(!rootQuad) TEST_ASSERT_EQUAL_INT16(0,1);
   
}

void unity_convertBST2QuadTree_preorder()
{   
	quadNode_t* rootQuad = EMPTYNODE;
	rootQuad = convertBST2QuadTree_instr(root_instr, PREORDER);
	if(!rootQuad) TEST_ASSERT_EQUAL_INT16(0,1);
   
}

void unity_convertBST2QuadTree_postorder()
{   
	quadNode_t* rootQuad = EMPTYNODE;
	rootQuad = convertBST2QuadTree_instr(root_instr, POSTORDER);
	if(!rootQuad) TEST_ASSERT_EQUAL_INT16(0,1);
   
}


void setUp (void) {} 
void tearDown (void) {} 

int main(void){

		srand(time(0));

		root_instr = createBSTNode_instr(100);
		for(int itr=0; itr<50; itr++)
			insertNodeInBST_instr(root_instr, createBSTNode_instr(1 + rand() % 4096)); 

		UNITY_BEGIN();

		RUN_TEST(unity_convertBST2QuadTree_inorder);
		RUN_TEST(unity_convertBST2QuadTree_preorder);
		RUN_TEST(unity_convertBST2QuadTree_postorder);
		
		UNITY_END();

		return 0;
}