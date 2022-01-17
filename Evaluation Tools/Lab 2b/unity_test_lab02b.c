#include <stdlib.h>
#include <stdio.h>
#include "unity.h"
#include "csl210_lab2b.h"

btNode_t* arrBinTreeNodes_instr[4096] = {EMPTYNODE};
short currIdx_instr = 0;

// 1 is true, 0 is false
short isValidBST_instr(btNode_t* node)
{
		if (EMPTYNODE == node)
				return 1;

		if ((EMPTYNODE != node->left && node->left->value > node->value) ||  
						(EMPTYNODE != node->right && node->right->value < node->value))
				return 0;

		if (0 == isValidBST_instr(node->left) || 0 == isValidBST_instr(node->right))
				return 0;

		return 1;
}

void traverseTree_instr(btNode_t* node){
	if(!node) 
		return;

	arrBinTreeNodes_instr[currIdx_instr++] = node;
	traverseTree_instr(node->left); // left
	traverseTree_instr(node->right); // right
}

btNode_t* getBSTSubtree_instr(btNode_t* rootNode){
	traverseTree_instr(rootNode);

	btNode_t** nodePtr = &arrBinTreeNodes_instr[0];
	while(EMPTYNODE != *nodePtr){
		if ((EMPTYNODE != (*nodePtr)->left || EMPTYNODE != (*nodePtr)->right) && isValidBST_instr(*nodePtr))
			return *nodePtr;
		nodePtr++;
	}

	return EMPTYNODE;
}

btNode_t* createNode_instr(short data){
	btNode_t* node = (btNode_t*)malloc(sizeof(btNode_t));
	node->value = data;
	node->left = EMPTYNODE;
	node->right = EMPTYNODE;
	return node;
}

btNode_t* getParentNodeBST_instr(btNode_t* node, short val){

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

void insertNodeInBST_instr(btNode_t* root, btNode_t* newNode){

	if(EMPTYNODE == root || EMPTYNODE == newNode)
		return;

	btNode_t* parent = getParentNodeBST_instr(root, newNode->value);
	if(EMPTYNODE == parent)
		return;

	if(newNode->value > parent->value)
		parent->right = newNode;
	if(newNode->value < parent->value)
		parent->left = newNode;
}


void unity_getBSTSubtree()
{   
    {
	    btNode_t* nd = createNode_instr(5);
	    nd->left = createNode_instr(23);
	    nd->left->left = createNode_instr(141);
	    nd->left->right = createNode_instr(31);
	    btNode_t* subT_instr = getBSTSubtree_instr(nd);
        btNode_t* subT = getBSTSubtree(nd);
	
        if(subT) TEST_ASSERT_EQUAL_INT16(0,1);
    }

    {
	    btNode_t* nd = createNode_instr(100);
	    nd->left = createNode_instr(23);
        nd->right = createNode_instr(104);
	    nd->left->left = createNode_instr(3);
	    nd->left->right = createNode_instr(31);
	    btNode_t* subT_instr = getBSTSubtree_instr(nd);
        btNode_t* subT = getBSTSubtree(nd);
	
        if(!subT) TEST_ASSERT_EQUAL_INT16(0,1);

        TEST_ASSERT_EQUAL_INT16(subT_instr->value, subT->value);
    }    
}

void setUp (void) {} 
void tearDown (void) {} 

int main(void){

		srand(time(0));

		UNITY_BEGIN();

		RUN_TEST(unity_getBSTSubtree);
		
		UNITY_END();

		return 0;
}