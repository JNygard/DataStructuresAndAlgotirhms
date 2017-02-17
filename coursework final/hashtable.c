#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct entry{
    char *key;
    char *value;
    struct entry *next;
};
struct hashtable{
    int size;
    struct entry **table;
};

typedef struct entry entry;
typedef struct hashtable hashtable;

//Create new HT
hashtable *new_hashtable(){
    int size = 65536;
    hashtable *ht = NULL;
    ht = malloc(sizeof(ht));
    ht->table=malloc(sizeof(entry*)*size);
    ht->size = size;
    return ht;
}

//Hash
int hash(hashtable *ht, char *key){
    unsigned long int x;
    int i = 0;
    while(x<ULONG_LONG_MAX&&i<strlen(key)){
        x = x<<8;
        x+=key[i];
        i++;
    }
    return x%ht->size;
}

//Make key value pair
entry *ht_newpair(char *key, char *value){
    entry *pair;
    if((pair = malloc(sizeof(entry)))==NULL){
        return NULL;
    }else if((pair->key=strdup(key))==NULL){
        return NULL;
    }else if((pair->value=strdup(value))==NULL){
        return NULL;
    }else{
        pair->next=NULL;
        return pair;
    }
}

//Insert key&value
void hashtable_put(hashtable *ht, char *key, char *value){
    entry *newpair = NULL;
    entry *next = NULL;
    entry *last = NULL;
    int bin = hash(ht, key);
    next = ht->table[bin];
    while(next!=NULL&&next->key!=NULL&&strcmp(key,next->key)>0){
        last = next;
        next = next->next;
    }
    if(next!=NULL&&next->key!=NULL&&strcmp(key,next->key)==0){
        free(next->value);
        next->value=strdup(value);
    }else{
        newpair = ht_newpair(key,value);
        if(next==ht->table[bin]){
            newpair->next=next;
            ht->table[bin] = newpair;
        }else if(next==NULL){
            last->next=newpair;
        }else{
            newpair->next = next;
            last->next = newpair;
        }
    }
}

//Get value
char *hashtable_get(hashtable *hashtable, char *key){
    entry *pair;
    pair = hashtable->table[hash(hashtable,key)];
    while(pair!=NULL&&pair->key!=NULL&&strcmp(key,pair->key)>0){
        pair = pair->next;
    }
    if(pair==NULL||pair->key==NULL||strcmp(key,pair->key)!=0){
        return NULL;
    }else{
        return pair->value;
    }
}







