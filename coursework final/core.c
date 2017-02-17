
void askFileName(char name[]);
void splitPharse(char line[], char pharse[], char associatedPhrases[]);
void arrayToUpper(char arr[100]);
char* concat(const char *s1, const char *s2);


char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void arrayToUpper(char arr[100]){
    int i;
    for(i=0;i<100;i++){
        if(islower(arr[i])){
            arr[i] = toupper(arr[i]);
        }
    }
}


void splitPharse(char line[], char pharse[], char associatedPhrases[]){
        strncpy(pharse, strtok(line, ":"), 100);
        strncpy(associatedPhrases, strtok(NULL, ":"), 100);
}

void askFileName(char name[]){
    bool found = false;
    do{
        printf("Give textfile name: ");
        scanf("%s", name);
        if(access(name, F_OK)!= -1){
            printf("%s", "File found \n");
            found = true;
        }else{
            printf("%s", "File does not exists. Try again \n");
        }
    }while(found==false);
}
