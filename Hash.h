#ifndef HASH_H
#define HASH_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h> //uint32_t
#include<stdbool.h>

#include<stddef.h>
#include<unistd.h>

#define VALUE_MAX 100
#define HASH_MAX 1000
#define LISTNAME_MAX 20
#define LOAD_FACTOR 0.8 
//#define INDEX_LENGTH 50 
//#define ROTL32(x, y) (((x) << (y)) | ((x) >> (32 - (y)))
//#define SEED 40
#define LENGTH 10
#define INDEX_LEN 10
#define INITIAL_CAPACITY 10

typedef struct Key_Value
{
    char key[LENGTH+1];
    char value[LENGTH+1];
    struct Key_Value* next;

}Key_Value;

typedef struct Hash
{
    struct Key_Value** KVPairs;
    int count;
    char ListName[LISTNAME_MAX];
    int capacity;
    //struct  LinkedList** overflow_buckets;
}Hash;

unsigned int HashFunction(char* key);
// hash function
//unsigned int hash_function(char* key);
//uint16_t MurmurHash3_x86_32( void *key, int len, uint32_t seed) ;
// struct LinkedList** create_overbuck(struct Hash* hm);
// struct LinkedList* allocate_List();
// struct LinkedList* insert_LinkedList(struct LinkedList* list, struct Key_Value* kv);

Hash* create_table(char* );

Key_Value* create_HashKV(char* key, char* value);

// handling_cllision()
//void handle_collision(struct Hash* hm, struct Key_Value* kv, unsigned int index);
//insert
void Hash_insert(Hash* hm,char* key, char* value);

//search
Key_Value* search_KV(Hash* hm,char* key);
//find the value of the key
char* ValueforKey(Hash* hm,char* key);
//update
void updateHashValue(Hash* hm,char* key);
void delete_KV(Hash* hm,char* key);
//void free_list(struct LinkedList* list);
//void free_overbuck(struct Hash* hm);
void free_KV(Key_Value* kv);
void free_Hash(Hash* hm);
void show_Hash(Hash* hm);

char* HGET(Hash* hm,char* key);
void HSET(Hash* hm,char* key,char*);
void HDEL(Hash* hm,char* key);

void EXPIRE(Hash* ,char* ,int );

#endif
