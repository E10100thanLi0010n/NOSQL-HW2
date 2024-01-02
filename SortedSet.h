#ifndef SORTEDSET_H
#define SORTEDSET_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

//int ZSKIPLIST_MAXLEVEL;
#define ZSKIPLIST_P 0.25
#define SKIPLIST_MAXLEVEL 32

typedef struct Zskiplistnode
{
    double score;
    char *member;
    //void *obj;
    struct Zskiplistnode *backward; 

    struct Zskiplistlevel
    {
        struct Zskiplistnode *forward;
        unsigned long span;

    } level[];

}Zskiplistnode;

typedef struct Zskiplist
{
    struct Zskiplistnode *head,*tail;
    int level;
    unsigned long length;
}Zskiplist;


struct Dict
{
    struct Entry
    {
        char *key;
        void *value;

    }*entries;

    size_t size;
    size_t capa;//capacity

} ;





struct ZSet
{
    struct Zskiplist *zsl;
    //struct dict *dict; 

};

//function

//skiplist =zsl

struct Zskiplistnode* zslcreateNode(int  ,double ,char*  ); 
struct Zskiplist *zslcreate();
int randomLevel();
struct Zskiplistnode* zslinsert(struct Zskiplist *list,double score,char* member);

int zslgetRank(struct Zskiplist*,double,char *);
double getScore(struct Zskiplist*,char *);

int zslrandomlevel(void);



void zslfreeNode(struct Zskiplistnode *);
void zslfree(struct Zskiplist *);
int zsldelete(struct Zskiplist *list,double score,char* member,struct Zskiplistnode**node);
void zsldeleteNode(struct Zskiplist* ,struct Zskiplistnode *,struct Zskiplistnode** );

void ZADD(struct Zskiplist*,double,char*);
int ZCARD(struct Zskiplist*);

//dict
void DictInit(struct Dict *dict,size_t initcapa);




#endif //SORTEDSET_H