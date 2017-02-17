#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Needed because RAND_MAX may be < 35000
*/
unsigned int bigRandom(){
	unsigned int random =
  		(((unsigned int) rand() <<  0) & 0x0000FFFF) |
  		(((unsigned int) rand() << 16) & 0x00000000FFFF0000);

  	return random;
}

int randperm(int n,int* A){
	int i,x,randnumber;
	for(i=0; i < n; i++){
		A[i] = i+1;
	}

	for(i=0; i < n; i++){
		randnumber = bigRandom()%n;
		x = A[i];
		A[i] = A[randnumber];
		A[randnumber] = x;
	}
}

int partition(int* a, int p, int r){
    int x = a[r];
    int i = p-1;
    int j = p;
    while(j<r){
        if(a[j]<=x){
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        j++;
    }
    int temp2 = a[i+1];
    a[i+1] = a[r];
    a[r] = temp2;
    return i+1;
}

void quicksort(int* A, int p, int r){
    if(p<r){

        int q=partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

void insertionsort(int* A, int n){
    int j = 1;
    while(j<n){
        int k = A[j];
        int i = j-1;
        while(i>=0 && A[i]>k){
            A[i+1] = A[i];
            i = i-1;
        }
        A[i+1] = k;
        j++;
    }

}

int main(){
	clock_t start,end;

	// Reserve one large array
	int *array = (int *)malloc(80000000*sizeof(int));

	double totaltime;
	int size;

	printf("Input array size > ");
	scanf("%d",&size);

	randperm(size,array);

   int i = 0;
 /*    for(i=0; i < size; i++)
        printf("%d, ", array[i]);
*/
    printf("\n");

	start = clock();
	quicksort(array, 0, size-1);
	end = clock();
	totaltime = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Quicksort of %d variables: %f seconds\n", size,totaltime);

    printf("\n");



    printf("\n");

    *array = (int *)malloc(80000000*sizeof(int));
    randperm(size,array);

     /*  i = 0;
        for(i=0; i < size; i++)
            printf("%d, ", array[i]);
    */

	start = clock();
	insertionsort(array, size);
	end = clock();
	totaltime = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Insertion sort of %d variables: %f seconds\n", size,totaltime);

 /*  i = 0;
    for(i=0; i < size; i++)
        printf("%d, ", array[i]);
*/
	return 0;
}
