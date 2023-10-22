#ifndef TABLE_H
#define TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdint.h>

#define INITIAL_TABLE_SIZE 10 
#define LOAD_FACTOR 0.8 
#define INDEX_LENGTH 50 //
#define ROTL32(x, y) (((x) << (y)) | ((x) >> (32 - (y)))
#define SEED 40



typedef struct KeyValue {
    char* key;
    char* value;
    int isDeleted;
} KeyValue;

typedef struct HashTable {
    KeyValue **table; //FIXME : or *table??
    int size;
    int tablesize;

} HashTable;


typedef struct DataBase{
    HashTable* index[62];



}DataBase;

//DataBase index[INDEX_LENGTH];
unsigned int LEFT_KEY=0;




//function name
unsigned int main_hash_function(char* key);

//char* generate_random_string(int length);
uint16_t MurmurHash3_x86_32( void *key, int len, uint32_t seed) ; 
struct HashTable* initHashTable(void);
void resize(HashTable* ht);
void insert(HashTable* ht, char* key,char* value); 
char* get(HashTable* ht, char* key);
void freetable(HashTable* ht);
void free_KV(struct KeyValue* kv);
void deleteKV(HashTable *ht,char* key);
struct KeyValue* create_KV(char* key, char* value);
void updateValue(struct HashTable* ht, char* key);






#endif