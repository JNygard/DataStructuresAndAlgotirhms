#ifndef CIRCLIST_H_INCLUDED
#define CIRCLIST_H_INCLUDED

// Defines data to store in list
typedef int data_type;

// Defines node and its pointer
typedef struct nd {
	data_type data;
	struct nd* next;
} node, *pnode; 

// Defines circular list
typedef struct clst {
	pnode head;
	pnode tail;
} circ_list; 

// Inserts key in the list
void list_insert(circ_list *li, data_type key);

// Searches key from the list
pnode list_search(circ_list li, data_type key);

// Removes key from the list
void list_remove(circ_list *li,data_type key);

// Prints the list
void print_list(circ_list li);

#endif