#ifndef HASH_H
#define HASH_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h> //uint32_t
#include<stdbool.h>

#include<stddef.h>


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

struct Key_Value
{
    char key[LENGTH+1];
    char value[LENGTH+1];
    struct Key_Value* next;

};

struct Hash
{
    struct Key_Value** KVPairs;
    int count;
    char ListName[LISTNAME_MAX];
    int capacity;
    //struct  LinkedList** overflow_buckets;
};

unsigned int HashFunction(char* key);
// hash function
//unsigned int hash_function(char* key);
//uint16_t MurmurHash3_x86_32( void *key, int len, uint32_t seed) ;
// struct LinkedList** create_overbuck(struct Hash* hm);
// struct LinkedList* allocate_List();
// struct LinkedList* insert_LinkedList(struct LinkedList* list, struct Key_Value* kv);

struct Hash* create_table(char* );

struct Key_Value* create_HashKV(char* key, char* value);

// handling_cllision()
//void handle_collision(struct Hash* hm, struct Key_Value* kv, unsigned int index);
//insert
void Hash_insert(struct Hash* hm,char* key, char* value);

//search
struct Key_Value* search_KV(struct Hash* hm,char* key);
//find the value of the key
char* ValueforKey(struct Hash* hm,char* key);
//update
void updateHashValue(struct Hash* hm,char* key);
void delete_KV(struct Hash* hm,char* key);
//void free_list(struct LinkedList* list);
//void free_overbuck(struct Hash* hm);
void free_KV(struct Key_Value* kv);
void free_Hash(struct Hash* hm);
void show_Hash(struct Hash* hm);

char* HGET(struct Hash* hm,char* key);
void HSET(struct Hash* hm,char* key,char*);
void HDEL(struct Hash* hm,char* key);

void EXPIRE(struct Hash* hm,char* key);

#endif
