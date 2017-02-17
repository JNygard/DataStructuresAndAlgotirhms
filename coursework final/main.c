#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "hashtable.c"
#include "bst.c"
#include "core.c"

void runIt();
void fileOptions(hashtable *pharseTable);

void organize(hashtable *pharseTable, hashtable *countTable,FILE *file);
void countTimesDetected(int *countCountTable,hashtable *countTable);
void countBorders(int *countCountTable,int *biggest, int *smallest);
void listTopHundred(hashtable *countTable, int smallest);
void finalTopSort(char *topPharses,int biggest, int smallest, int *countCountTable, hashtable *countTable);


int main(){
    int option;
    while(option != 0){
        printf("0: Quit \n1: Start \n>");
        scanf("%d", &option);
        printf("\n");
        if(option==0){
            exit(0);
        }else if(option==1){
            runIt();
        }else{
            printf("Invalid input. Try again. \n");
        }
    }
    return 0;
}

void fileOptions(hashtable *pharseTable){
    int option = 1;
    while(option !=0){
        printf("0: Exit this file \n1: Find associated phrases\n>");
        scanf("%d", &option);
        printf("\n");
        if(option==0){
            break;
        }
        //If user wants to find the associated pharses
        else if(option==1){
            char pharse[100];
            printf("Find pharse: ");
            scanf("%s", pharse);
            arrayToUpper(pharse);
            char* associatedPhrases = hashtable_get(pharseTable,pharse);
            if(associatedPhrases!=NULL)
                printf("\nFound: \n%s\n", associatedPhrases);
            else
                printf("Not found\n");
        }
        else{
            printf("Invalid input\n");
        }
    }
}

//Start
void runIt(){
    //Remove old files
    remove("top100.txt");
    remove("unordered_top_pharses.txt");

    //Get file name and open it for reading
    char fname[100];
    FILE *file;
    askFileName(fname);
    file = fopen(fname,"r");

    //Create hashtables for pharses AND for counting the times each pharse has been detected
    hashtable *pharseTable = new_hashtable();
    hashtable *countTable = new_hashtable();
    int countCountTable[300] = {0};
    int biggest=0, smallest = 0;

    //Take time
    clock_t start,end;
    double totaltime;
    start = clock();

    organize(pharseTable,countTable, file);
    countTimesDetected(countCountTable,countTable);
    countBorders(countCountTable, &biggest, &smallest);
    listTopHundred(countTable, smallest);
    finalTopSort("unordered_top_pharses.txt",biggest,smallest,countCountTable,countTable);

    end = clock();
    totaltime = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Total time: %f \n", totaltime);
    printf("See top 100 pharses listed in top100.txt file\n");
    printf("\n");

    //Remove help files
    remove("uniquePharses.txt");
    remove("unordered_top_pharses.txt");

    fileOptions(pharseTable);
}



//calculate the times each pharse is detected to countTable
//set all associated pharses of a pharse to pharsaTable value
//list unique pharses to own temporary file
void organize(hashtable *pharseTable, hashtable *countTable,FILE *file){
    int count = 0, uniquePharsesCount = 0, interval = 100000, reset = 0;
    char line[256];
    FILE *uniquePharsesList = fopen("uniquePharses.txt", "w");
    while(fgets(line, sizeof(line),file)){
        char pharse[100], associatedPhrases[100];
        splitPharse(line, pharse, associatedPhrases);
        arrayToUpper(pharse);
        if(reset>=interval){
            printf("So far readen %dK lines..\n", count/1000);
            reset = 0;
        }
        reset++;
        count++;
        char* oldassociatedPhrases = hashtable_get(pharseTable,pharse);
        if( oldassociatedPhrases == NULL){
            uniquePharsesCount++;
            hashtable_put( pharseTable, pharse, associatedPhrases );
            hashtable_put(countTable, pharse, "1");

            fprintf(uniquePharsesList, "%s\n", pharse);
        }else{
            int pcount;sscanf(hashtable_get(countTable,pharse), "%d", &pcount);
            pcount++;char str[15];sprintf(str, "%d", pcount);

            hashtable_put(countTable, pharse, str);
            char* newassociatedPhrases = concat(oldassociatedPhrases, associatedPhrases);
            hashtable_put( pharseTable, pharse, newassociatedPhrases );
            //fprintf(topPharses, "%s : %s\n", pharse,hashtable_get(countTable,pharse));
        }
    }
    printf("\nTotal %dK lines\n", count/1000);
    fclose(file);
    fclose(uniquePharsesList);
}

//Count how many times different pharses has detected the same amount of times
void countTimesDetected(int *countCountTable,hashtable *countTable){
    FILE *uniquePharsesList2 = fopen("uniquePharses.txt", "r");
    bst coll;
	coll.root=0;
    char pharseline[256];
    int ccount = 0;
    while(fgets(pharseline, sizeof(pharseline),uniquePharsesList2)){
        strtok(pharseline, "\n");
        if(hashtable_get(countTable,pharseline)!= NULL){
            int pInt;sscanf(hashtable_get(countTable,pharseline), "%d", &pInt);
            countCountTable[pInt]++;
            bst_insert(&coll,pInt);
            ccount++;
        }
    }
    fclose(uniquePharsesList2);
}

//Count the limit for top pharses
void countBorders(int *countCountTable,int *biggest, int *smallest){
   int i=299, xcount = 0;
    while(i>0 && xcount<100){
        if(xcount==0)
            *biggest = i;
        xcount+= countCountTable[i];
        //printf("%d : %d \n", i, countCountTable[i]);
        i--;
        *smallest = i+1;
    }
}



//List the top pharses to file
void listTopHundred(hashtable *countTable, int smallest){
    FILE *topPharses = fopen("unordered_top_pharses.txt", "w");
    FILE *uniquePharsesList3 = fopen("uniquePharses.txt", "r");
    char pharseline[256];
    while(fgets(pharseline, sizeof(pharseline),uniquePharsesList3)){
            strtok(pharseline, "\n");

            if(hashtable_get(countTable,pharseline)!=NULL){
                int pcount;sscanf(hashtable_get(countTable,pharseline), "%d", &pcount);
                if(pcount>=smallest){
                    fprintf(topPharses, "%s\n", pharseline);
                }
            }
    }
    fclose(topPharses);
    fclose(uniquePharsesList3);
}

//Sort the top pharses and print the final result to top100.txt file
void finalTopSort(char *tops,int biggest, int smallest, int *countCountTable, hashtable *countTable){
    //printf("%s : %d : %d \n\n", tops,biggest,smallest);
    FILE *finalTopPharses = fopen("top100.txt", "a");
    char pharseline[256];
    int count = biggest, cutt = 100;
    while(count>=smallest){
        int amount = countCountTable[count];
        if(amount>0){
            FILE *topPharses = fopen(tops, "r");
            while(fgets(pharseline, sizeof(pharseline),topPharses)){
                strtok(pharseline, "\n");
                int pcount;sscanf(hashtable_get(countTable,pharseline), "%d", &pcount);
                if(pcount==count){
                    fprintf(finalTopPharses, "%s %s\n", pharseline, hashtable_get(countTable,pharseline));
                    amount--;
                    cutt--;
                }
                if(amount==0||cutt==0)
                    break;
            }
            if(cutt==100)
                break;
        }
        count--;
    }
    fclose(finalTopPharses);
}










