#ifndef SORTEDSET_H
#define SORTEDSET_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

struct SkipListNode
{
    double score;
    char *member;
    struct SkipListNode **forward; 

};

struct SkipList
{
    struct SkipListNode *head;
    int level;

};

struct SkipListNode *createSkipListNode(double ,char *, int ); 
struct SkipList *createSkipList();
int randomLevel();
void insertSkipList(struct SkipList *list,double score,char* member);

int getRank(struct SkipList*,char *);
double getScore(struct SkipList*,char *);
void freeSkipList(struct SkipList*);

void ZADD(struct SkipList*,double,char*);
int ZCARD(struct SkipList*);

#endif //SORTEDSET_H