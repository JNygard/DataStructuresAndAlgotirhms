#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.c"
#include "bst.h"

int main(){

	// Empty linked list
	bst coll;
	coll.root=0;

	// seed random generator
	srand((unsigned int)time(NULL));

	int i;


	// Insert random numbers into the tree
	for(i=0; i<100; i++){
		bst_insert(&coll,rand());
	}

	printf("Original tree:\n");
	print_tree_inorder(coll);
	printf("\n Root was: ");
	print_node(coll.root);

	int limit = 10000;
	printf("\n\nIndices less than %d:\n",limit);

	for(i=0; i < limit; i++){
		print_node(bst_search(coll,i));
	}

	printf("\n\nRemoving indices less than %d\n",limit);
	for(i=0; i < limit; i++){
		bst_remove(&coll,i);
	}
	printf("Tree after removing: \n");
	print_tree_inorder(coll);

	bst_delete(coll.root);
	coll.root=0;

	return 0;
}
