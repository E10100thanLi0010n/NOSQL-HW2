#include"SortedSet.h"

int ZSKIPLIST_MAXLEVEL=32;

Zskiplistnode *zslcreateNode(int level,double score,char* member)
{
    if(level <=0 || member==NULL)
    {
        printf("Invalid arguments.\n");
        return NULL;
    }

    struct Zskiplistnode *node=(struct Zskiplistnode*)malloc(sizeof(struct Zskiplistnode)+level*sizeof(struct Zskiplistlevel));
    
    size_t mem_len=strlen(member);
    node->member = (char *)malloc(mem_len + 1);
    if (node->member == NULL) 
    {
        printf("Memory allocation failed for member.\n");
        free(node);
        return NULL;
    }

    strncpy(node->member, member, mem_len);
    node->member[mem_len] = '\0'; 


    node->score =score;
    //strcpy(node->member, member);
    //strncpy(node->member,member,sizeof(node->member)-1);
   // node->forward = (struct SkipListNode **)malloc((level + 1) * sizeof(struct SkipListNode *));
    // if (!node->forward) 
    // {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     //exit(EXIT_FAILURE);
    //     free(node);
    //     return NULL; 
    // }

    return node;
}

struct Zskiplist *zslcreate()
{
    struct Zskiplist* list=(struct Zskiplist*)malloc(sizeof(struct Zskiplist));

    // if(!list) 
    // {
    //     printf("memory allocation failed.\n");
    //     free(list);
    //     return NULL;
    // }

    list->length=0;
    list->level=1;
    list->head=zslcreateNode(ZSKIPLIST_MAXLEVEL,0,"");
    
    

    for (int i = 0; i < ZSKIPLIST_MAXLEVEL;i++) 
    {
        list->head->level[i].forward = NULL;
        list->head->level[i].span = 0;
    }

    list->head->backward=NULL;
    list->tail=NULL;


    return list;
}

int zslrandomLevel() 
{
    int level =1;
    while (rand() < RAND_MAX / 2 && level < INT_MAX - 1) {
        level++;
    }
    return (level<ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL ;
}


struct Zskiplistnode* zslinsert(struct Zskiplist *list,double score,char* member)
{
    if(!list) 
    {
        printf("no this list,sorry~\n");
        return NULL;
    }

    //struct  Zskiplistnode *update[list->level+1];  
    struct Zskiplistnode *update[ZSKIPLIST_MAXLEVEL],*x;
    unsigned int rank[ZSKIPLIST_MAXLEVEL];
    int level;
    //struct  Zskiplistnode *current=list->head;

    x=list->head;
    for(int i=list->level-1;i>=0;i--)
    {
        rank[i]=(i == (list->level-1)) ? 0: rank[i+1];

        while(x->level[i].forward && 
        (x->level[i].forward->score < score ||(x->level[i].forward->score == score &&
                                        strcmp(x->level[i].forward->member,member) < 0)))
        {
            rank[i] += x->level[i].span;
            x = x->level[i].forward;
        }


        update[i] = x;

    }

    level=zslrandomLevel();

    if(level > list->level)  //newnode's level bigger than old other 
    {
        for(int i=list->level;i<level;i++)
        {
            rank[i]=0;
            update[i] = list->head;
            update[i]->level[i].span = list->length;

        }
        list->level=level;
    }
    
    x=zslcreateNode(level,score,member);
    for(int i=0;i<level;i++)
    {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }

    /* increment span for untouched levels */
    for (int i = level; i <list->level; i++) {
        update[i]->level[i].span++;
    }

    x->backward = (update[0] == list->head) ? NULL : update[0];
    if (x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        list->tail = x;
    
    list->length++;
    
    return x;

   

    // for(int i=list->level;i>=0;i--)
    // {
    //     while(current->forward[i]!=NULL && current->forward[i]->score<score)
    //     {
    //         current=current->forward[i];
    //     }

    //     update[i]=current;
    // }

    // int newlevel=randomLevel();
    // if(newlevel > list->level)
    // {
    //     for(int i=list->level+1;i<=newlevel;i++)
    //     update[i]=list->head;

    //     list->level=newlevel;
    // }

    // struct Zskiplistnode *node=createSkipListNode(newlevel,score,member);

    // for(int i=0;i<=newlevel;i++)
    // {
    //     node->forward[i]=update[i]->forward[i];
    //     update[i]->forward[i]=node;

    // }

}

int  zslgetRank(struct Zskiplist* list,double score,char *member)
{
    struct Zskiplistnode *current = list->head;
    int rank = 0;

    for(int i=list->level-1;i>=0;i--)
    {
        while(current->level[i].forward &&(current->level[i].forward->score < score ||
            (current->level[i].forward->score == score &&
            strcmp(current->level[i].forward->member,member) <= 0))) 
            {
                rank += current->level[i].span;
                current = current->level[i].forward;
            }

        if (current->member && strcmp(current->member,member) == 0) return rank;

    }

    return 0;
}

// 獲取元素的分數
double zslgetScore(struct Zskiplist *list,char *member) 
{
    if(list==NULL || member ==NULL) return -1.0;


    struct Zskiplistnode *current = list->head;

    while (current) {
        int cmp = strcmp(member, current->member);
        if (cmp == 0) {
            //found it
            return current->score;
        } else if (cmp < 0 || (cmp == 0 && current->backward == NULL)) {
            // error
            return -1.0;
        } else {
            // move to next node in down level
            current = current->backward;
        }
    }

    // not found it
    return -1.0;


}

int zslrandomlevel(void)
{
    int level=1;

   while((rand()&0xFFFF) < (ZSKIPLIST_P * 0xFFFF))
        level += 1;
    return (level<ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL;
}





void zslfreeNode(struct Zskiplistnode *node)
{
    if(!node)
    {
        printf("memory allocation failed\n");
        return;
    }

    free(node->member);
    free(node->backward);

    struct Zskiplistlevel *level = node->level;
    while(level)
    {
        struct Zskiplistlevel *next = level->forward ? level->forward->level : NULL;
        free(level);
        level = next;
    }

        
    free(node);


}

void zslfree(struct Zskiplist *list)
{
    struct  Zskiplistnode *node=list->head->level[0].forward,*next;

    //free(list->head);
    zslfreeNode(list->head);
    zslfreeNode(list->tail);
    while(node)
    {   
        next=node->level[0].forward;
        zslfreeNode(node);
        node=next;

    }

    //free(list);
}


void zsldeleteNode(struct Zskiplist* list,struct Zskiplistnode *node,struct Zskiplistnode** update)
{

    for(int i=0;i<list->level;i++)
    {
        if(update[i]->level[i].forward==node)
        {
            update[i]->level[i].span+=node->level[i].span-1;
            update[i]->level[i].forward=node->level[i].forward;

        }else
        {
            update[i]->level[i].span-=1;

        }

    }

    if(node->level[0].forward)
    {
        node->level[0].forward->backward=node->backward;
    }else
    {
        list->tail=node->backward;
    }

    while(list->level>1 &&list->head->level[list->level-1].forward==NULL)
    list->level--;

    list->length--;

}

int zsldelete(struct Zskiplist *list,double score,char* member,struct Zskiplistnode**node)
{
    struct Zskiplistnode *current=list->head,*next,*update[ZSKIPLIST_MAXLEVEL];

    // while(current!=NULL)
    // {
    //     next=current->forward[0];
    //     free(current->forward);
    //     free(current);
    //     current=next;
    // }


    for(int i=list->level-1;i>=0;i++)
    {
         while (current->level[i].forward &&
                (current->level[i].forward->score < score ||
                    (current->level[i].forward->score == score &&
                     strcmp(current->level[i].forward->member,member) < 0)))
        {
            current= current->level[i].forward;
        }
        update[i] = current;



    }

    current=current->level[0].forward;

    if(current && score==current->score && strcmp(current->member,member)==0)
    {
        zsldeleteNode(list,current,update);

        if(!node) zslfreeNode(current);
        else *node=current;
        
        return 1;

    }



    //free(list);

    printf("you have free the list.\n");
    return 0;
}


void ZADD(struct Zskiplist *list,double score,char* member)
{
    
    int rank=zslgetRank(list,score,member);

    // if(rank!=-1)//member exists, then update score
    // {
    //     struct Zskiplistnode *current=list->head->forward[0];
    //     for(int i=0;i<rank;i++)
    //     current=current->forward[i];

    //     current->score=score;
    //     return;
    // }
    
    //not exist
    zslinsert(list,score,member);

}




int ZCARD(struct Zskiplist *list)
{
    if(!list)   
    {
        printf("no such skiplist.\n");
        return -1;
    }

    return (list->head->level[0].span==NULL) ? 0 : zslgetRank(list,1,"")+1;

    
}

/**************DICT****************/

void DictInit(struct Dict *dict,size_t initcapa)
{
    //dict->entries;


}