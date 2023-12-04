#include"SortedSet.h"


struct SkipListNode *createSkipListNode(double score,char *member, int level)
{
    struct SkipListNode *node=(struct SkipListNode*)malloc(sizeof(struct SkipListNode));
    size_t mem_len=strlen(member);
    node->member=(char*)malloc(mem_len+1);
    
    
    if (!node) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        //exit(EXIT_FAILURE);
        free(node);
        return NULL;
    }

    node->score =score;
    strncpy(node->member,member,sizeof(node->member)-1);
    node->forward = (struct SkipListNode **)malloc((level + 1) * sizeof(struct SkipListNode *));
    if (!node->forward) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        //exit(EXIT_FAILURE);
        free(node);
        return NULL; 
    }

    return node;
}

struct SkipList *createSkipList()
{
    struct SkipList *list=(struct SkipList*)malloc(sizeof(struct SkipList));

    if(!list) 
    {
        printf("memory allocation failed.\n");
        free(list);
        return NULL;

    }

    list->head=createSkipListNode(0,"",0);
    list->level=0;

    return list;
}

int randomLevel() 
{
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < INT_MAX - 1) {
        level++;
    }
    return level;
}


void insertSkipList(struct SkipList *list,double score,char* member)
{
    if(!list) 
    {
        printf("no this list,sorry~\n");
        return ;
    }

    struct  SkipListNode *update[list->level+1];  
    struct  SkipListNode *current=list->head;

    for(int i=list->level;i>=0;i--)
    {
        while(current->forward[i]!=NULL && current->forward[i]->score<score)
        {
            current=current->forward[i];
        }

        update[i]=current;
    }

    int newlevel=randomLevel();
    if(newlevel > list->level)
    {
        for(int i=list->level+1;i<=newlevel;i++)
        update[i]=list->head;

        list->level=newlevel;
    }

    struct SkipListNode *node=createSkipListNode(score,member,newlevel);

    for(int i=0;i<=newlevel;i++)
    {
        node->forward[i]=update[i]->forward[i];
        update[i]->forward[i]=node;

    }

}

int getRank(struct SkipList *list,char *member) 
{
    struct SkipListNode *current = list->head;
    int rank = 0;

    for (int i = list->level; i >= 0; i--) 
    {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->member, member) < 0) 
        {
            rank += 1 << i;
            current = current->forward[i];
        }
    }

    return rank;
}

// 獲取元素的分數
double getScore(struct SkipList *list,char *member) 
{
    struct SkipListNode *current = list->head;

    for (int i = list->level; i >= 0; i--) 
    {
        while (current->forward[i] != NULL && strcmp(current->forward[i]->member, member) < 0) 
        {
            current = current->forward[i];
        }
    }

    if (current->forward[0] != NULL && strcmp(current->forward[0]->member, member) == 0) 
    {
        return current->forward[0]->score;
    } else 
    {
        return -1.0; // member not found!
    }
}






void freeSkipList(struct SkipList *list)
{
    struct SkipListNode *current=list->head,*next;

    while(current!=NULL)
    {
        next=current->forward[0];
        free(current->forward);
        free(current);
        current=next;
    }

    free(list);

    printf("you have free the list.\n");
}


void ZADD(struct SkipList *list,double score,char* member)
{
    
    int rank=getRank(list,member);

    if(rank!=-1)//member exists, then update score
    {
        struct SkipListNode *current=list->head->forward[0];
        for(int i=0;i<rank;i++)
        current=current->forward[i];

        current->score=score;
        return;
    }
    
    //not exist
    insertSkipList(list,score,member);

}




int ZCARD(struct SkipList *list)
{
    if(!list)   
    {
        printf("no such skiplist.\n");
        return -1;
    }

    return list->head->forward[0]==NULL ? 0 : getRank(list,"")+1;


}
