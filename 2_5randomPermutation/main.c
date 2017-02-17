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
	int i,j;
	int x;
	for(i=0; i < n; i++){
		int newNumber = 0;
		while(newNumber == 0){
			newNumber = 1;
			x = (bigRandom()%n) + 1;
			for(j=0; j < i; j++){
				if( A[j] == x )
					newNumber = 0;
			}
		}
		A[i] = x;
	}
}
int randperm2(int n,int* A, int* used){
	int i,j,usedNumber;
	unsigned int x;

	for(i=0; i <= n; i++){
		used[i] = 0;
	}

	for(i=0; i < n; i++){
		int usedNumber = 1;
		while(usedNumber == 1){
			x = (bigRandom()%n) + 1;
			usedNumber = used[x];
		}
		A[i] = x;
		used[x] = 1;
	}
}
int randperm3(int n,int* A){
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

int main(){
	clock_t start,end;

    int cont = 1;

	while(cont){
        int alg = 0;
        printf("Select algorithm 1, 2, 3 > ");
        scanf("%d",&alg);

        int *array = (int *)malloc(40000000*sizeof(int));
        int *helper = (int *)malloc(40000000*sizeof(int));

        // Aray for permutation
        double totaltime;
        int size;

        srand((int)time(NULL));
        printf("Input array size > ");
        scanf("%d",&size);

        start = clock();

        if(alg==1){
            randperm(size,array);
        }else if(alg==2){
            randperm2(size,array,helper);
        }else if(alg==3){
            randperm3(size,array);
        }






        end = clock();
        totaltime = (double)(end-start)/CLOCKS_PER_SEC;

        printf("Time is %f seconds\n", totaltime);

        //Printing the table to test permutation:
        /*
        int i;
        for(i=0; i < size; i++)
            printf("%d ", array[i]);
        */
        printf("Continue 1, 0 ? > ");
        scanf("%d",&cont);
	}

	return 0;
}
