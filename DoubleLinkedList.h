#ifndef DLL_H
#define DLL_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include<time.h>

struct Node{
    char* key;
    //int value;
    struct Node *prev,*next;
};

struct DouLL{
    struct Node *head,*tail;
    int length;
};

struct DouLL* createDoubleLL(void);
struct Node* createNode(char* key);
void LPUSH(struct DouLL* dll,char* key);
void RPUSH(struct DouLL* dll,char* key);
char* LPOP(struct DouLL* dll);
char* RPOP(struct DouLL* dll);
int LLEN(struct DouLL* dll);
void showList(struct DouLL* dll);
void freeDLL(struct DouLL *dll);
void LRANGE(struct DouLL *dll,int ,int );



#endif 