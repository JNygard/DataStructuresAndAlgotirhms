#include <stdio.h>
#include <stdlib.h>
#include "circ_list.h"
#include "circ_list.c"


int main(){
	circ_list coll;
	coll.head = 0;
	coll.tail = 0;
	int numPer,interval;

	printf("Give the number of persons -> ");
	scanf("%d",&numPer);

	printf("Give the removal interval -> ");
	scanf("%d",&interval);

	int i;

	for(i=1; i<=numPer; i++){
		list_insert(&coll,i);
	}

	print_removals(&coll,interval);


	return 0;
}
