#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// Minimum value of the tree
pbstnode bst_min(pbstnode rt){
	pbstnode x = rt;

	if(x == 0)
		return 0;

	while( x->left != 0)
		x = x->left;

	return x;
}

// Maximum value of the tree
pbstnode bst_max(pbstnode rt){
	pbstnode x = rt;

	if(x == 0)
		return 0;

	while( x->right != 0)
		x = x->right;

	return x;
}

/*
	Searches a node according to key
	and returns a pointer to found node
*/
pbstnode bst_search(bst bt, data_type key){
	pbstnode pNode = bt.root;

	while(pNode != 0 && pNode->data != key){
		if(pNode->data < key){
			pNode = pNode->right;
		}
		else {
			pNode = pNode->left;
		}
	}

	return pNode;
}

// Prints a node
void print_node(pbstnode n){
	if(n != 0)
		printf(" %d ",n->data);
}

void print_inorder(pbstnode pnode){
	if (pnode != 0) {
		print_inorder(pnode->left);
		print_node(pnode);
		print_inorder(pnode->right);
	}
}

// Prints the whole tree inorder
void print_tree_inorder(bst bt){
	print_inorder(bt.root);
}

/*
	Allocates a node with data key
	and inserts it in the tree
*/
void bst_insert(bst *bt, data_type key){
	bstnode *n = (bstnode *)malloc(sizeof(bstnode));
	n->data = key;
	n->parent=n->right=n->left=0;
	pbstnode x = bt->root;
	pbstnode y=0;
	while(x!=0){
		y=x;
		if(key < x->data)
			x = x->left;
		else if( key > x->data)
			x = x->right;
		else
			return;
	}

	n->parent = y;
	if( y == 0)
		bt->root = n;
	else if( key < y->data)
		y->left = n;
	else
		y->right = n;
}

/*
	Subroutine for removing
*/
void bst_transplant(bst *bt, pbstnode u, pbstnode v){
	if( u->parent == 0)
		bt->root = v;
	else if( u == (u->parent)->left )
		(u->parent)->left = v;
	else
 		(u->parent)->right = v;

 	if( v != 0)
 		v->parent = u->parent;
}

/*
	Searches a node according to key
	and removes it from the tree
*/
int bst_remove(bst *bt,data_type key) {
	pbstnode x = bst_search(*bt,key);

	if(x==0)
		return 0;

	if(x->left == 0) {
		bst_transplant(bt, x, x->right);
	}
	else if( x->right == 0){
		bst_transplant(bt, x, x->left);
	}
	else {
		pbstnode y = bst_min(x->right);

		if( y->parent != x){
			bst_transplant(bt,y,y->right);
			y->right = x->right;
			(y->right)->parent = y;
		}

		bst_transplant(bt,x,y);
		y->left = x->left;
		(y->left)->parent = y;
	}

	free(x);

	return 1;
}

// Delete the whole tree
void bst_delete(pbstnode node){
	if(node != 0) {
		bst_delete(node->left);
		bst_delete(node->right);
		free(node);
	}
}
