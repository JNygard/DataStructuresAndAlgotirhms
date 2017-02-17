#include <stdio.h>
#include <stdlib.h>
#include "circ_list.h"

/*
	Allocates a node with data key
	and inserts it in the circular list
*/
void list_insert(circ_list *li, data_type key){
	node *n = (node *)malloc(sizeof(node));
	n->data = key;
	if(li->head == 0) {
		li->head = n;
		li->tail = n;
		n->next=li->head;
	}
	else {
		n->next=li->head;
		li->tail->next = n;
		li->tail = n;
	}
}

void print_removals(circ_list *li, int interval){
    pnode pNode = li->head;
    pnode pred = li->tail;
    int i;

    while(li->head != 0){
        for(i=1;i<interval;i++){
            pred = pNode;
            pNode = pNode->next;
        }

        printf("\nRemoving");
        print_node(pNode);

        if(pred==pNode){
            li->head = li->tail=0;
        }else{
            pred->next = pNode->next;

            if(pNode==li->tail)
                li->head = pNode->next;

            if(pNode == li->head)
                li->head = pNode->next;
        }

        free(pNode);
        pNode = pred->next;

    }

}

/*
	Searches a node according to key
	and returns a pointer to found node
*/
pnode list_search(circ_list li, data_type key){
	pnode pNode = li.head;

	if (pNode == 0)
		return 0;

	int found = 0;

	do {
		if(pNode->data == key){
			found = 1;
		}
		else {
			pNode = (pnode)pNode->next;
		}
	}while(pNode != li.head && found == 0);

	return pNode;
}

/*
	Searches a node according to key
	and removes it from the list
*/
void list_remove(circ_list *li,data_type key){
	pnode pNode = list_search(*li,key);

	if(pNode != 0){

		// Find predecessor, always exists because circular list
		pnode pred = li->head;

		while(pred->next != pNode){
			pred = pred->next;
		}

		// Only one node and it is deleted
		if(pred == pNode){
			li->head = li->tail = 0;
		}
		else {
			// Check if head or tail node deleted

			if(pNode == li->head){
				// Head deleted. New head will be next node
				li->head = pNode->next;
			}

			if(pNode == li->tail){
				// Tail deleted. New tail will be the predecessor
				li->tail = pred;
			}

			// Link the predecessor to next of deleted node
			pred->next = pNode->next;
		}

		free(pNode);
	}
}

// Prints a node
void print_node(pnode n){
	printf("%d",n->data);
}

// Prints the whole list
void print_list(circ_list li){
	if(li.head != 0){
		pnode pNode = li.head;
		do {
			print_node(pNode);
			printf(", ");
			pNode = (pnode)pNode->next;
		} while( pNode != li.head);
	}
}
