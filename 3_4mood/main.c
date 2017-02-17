#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int bigRandom(){
	unsigned int random =
  		(((unsigned int) rand() <<  0) & 0x0000FFFF) |
  		(((unsigned int) rand() << 16) & 0x00000000FFFF0000);

  	return random;
}
int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}
int randGenerator(int n,int* A){
	int i,x,randnumber;
	for(i=0; i < n; i++){
		A[i] = rand() % 10;
	}
}

int mood(int a[],int size){
    int curcombo = 0;
    int topcombo = 0;

    int top = 0;


    int m = 0;
    qsort( a, size, sizeof(int), compare );
    int i = 0;
    for(i; i < size; i++){
        //printf("%d", a[i]);
      if(a[i]==a[i-1]){
        curcombo++;
        if(curcombo>=topcombo){
            topcombo = curcombo;
            top = a[i];
        }
      }else{
        curcombo = 0;
      }

    }

    return top;
}



int main(){
    clock_t start,end;
    double totaltime;
    int *array = (int *)malloc(40000000*sizeof(int));

    int size;

    srand((int)time(NULL));
    printf("Input array size > ");
    scanf("%d",&size);

    randGenerator(size,array);

  /*  printf("Listassa [");
    int i = 0;
    for(i=0; i < size; i++)
        printf("%d, ", array[i]);
*/
    start = clock();
    printf("] useiten esiintyy numero %d \n", mood(array, size));
    end = clock();
    totaltime = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Operaation suoritukseen kulunut aika: %lf", totaltime);

    return 0;
}


