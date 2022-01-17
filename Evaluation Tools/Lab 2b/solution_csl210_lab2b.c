#include "csl210_lab2b.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

btNode_t* arrBinTreeNodes[4096] = {EMPTYNODE};
short currIdx = 0;

// 1 is true, 0 is false
short isValidBST(btNode_t* node)
{
		if (EMPTYNODE == node)
				return 1;

		if ((EMPTYNODE != node->left && node->left->value > node->value) ||  
						(EMPTYNODE != node->right && node->right->value < node->value))
				return 0;

		if (0 == isValidBST(node->left) || 0 == isValidBST(node->right))
				return 0;

		return 1;
}

void traverseTree(btNode_t* node){
	if(!node) 
		return;

	arrBinTreeNodes[currIdx++] = node;
	traverseTree(node->left); // left
	traverseTree(node->right); // right
}

btNode_t* getBSTSubtree(btNode_t* rootNode){
	traverseTree(rootNode);

	btNode_t** nodePtr = &arrBinTreeNodes[0];
	while(EMPTYNODE != *nodePtr){
		if ((EMPTYNODE != (*nodePtr)->left || EMPTYNODE != (*nodePtr)->right) && isValidBST(*nodePtr))
			return *nodePtr;
		nodePtr++;
	}

	return EMPTYNODE;
}

btNode_t* createNode(short data){
	btNode_t* node = (btNode_t*)malloc(sizeof(btNode_t));
	node->value = data;
	node->left = EMPTYNODE;
	node->right = EMPTYNODE;
	return node;
}

btNode_t* getParentNodeBST(btNode_t* node, short val){

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

void insertNodeInBST(btNode_t* root, btNode_t* newNode){

	if(EMPTYNODE == root || EMPTYNODE == newNode)
		return;

	btNode_t* parent = getParentNodeBST(root, newNode->value);
	if(EMPTYNODE == parent)
		return;

	if(newNode->value > parent->value)
		parent->right = newNode;
	if(newNode->value < parent->value)
		parent->left = newNode;
}


int main(){

	srand(time(0));
	btNode_t* bst = createNode(100);
	for(int itr=0; itr<8; itr++){
		insertNodeInBST(bst, createNode(100 + rand() % 1024));
	}

	btNode_t* nd = createNode(5);
	nd->left = createNode(23);
	nd->left->left = createNode(141);
	nd->left->right = createNode(31);
	btNode_t* subT = getBSTSubtree(nd);
	if(subT) printf("%d\n", subT->value);

	nd->left->left->right = bst;
	subT = getBSTSubtree(nd);
	if(subT) printf("%d\n", subT->value);

	subT = getBSTSubtree(bst);
	if(subT) printf("%d\n", subT->value);

	return 0;
}