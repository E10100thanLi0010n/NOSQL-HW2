#include"SortedSet.h"

int ZSKIPLIST_MAXLEVEL=32;

// int compare(const void* a,const void *b)
// {
//     return  strcmp(a,b);
// }


Zskiplistnode *zslcreateNode(int level,double score,char* member)
//Zskiplistnode *zslcreateNode(int level,void *obj)
{
    if(level <=0 || member==NULL)
    {
        printf("Invalid arguments.\n");
        return NULL;
    }

    Zskiplistnode *node=(Zskiplistnode*)malloc(sizeof(Zskiplistnode)+level*sizeof(struct Zskiplistlevel));
    
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
    // node->obj=obj;
    return node;
}

//Zskiplist *zslcreate(int (*compare)(const void*,const void*))
Zskiplist *zslcreate()
{
    Zskiplist* list=(Zskiplist*)malloc(sizeof(Zskiplist));
    if(!list) 
    {
        printf("memory allocation failed.\n");
        free(list);
        return NULL;
    }

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
    /* void* obj */
    // int j;
    // Zskiplist *sl;
    // sl=malloc(sizeof(*sl));
    // sl->level=1;
    // sl->length=0;
    // sl->head=zslcreateNode(ZSKIPLIST_MAXLEVEL,NULL);

    // for(int j=0;j<ZSKIPLIST_MAXLEVEL;j++)
    // {
    //     sl->head->level[j].forward=NULL;
    //     sl->head->level[j].span=0;
    // }

    // sl->head->backward=NULL;
    // sl->tail=NULL;
    // sl->compare=compare;

    // return sl;

}

void zslfreeNode(struct Zskiplistnode *node)
{
    if(!node)
    {
        printf("memory allocation failed\n");
        return;
    }

    free(node->member);
    //free(node->obj);
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

void zslfree(Zskiplist *list)
{
     if (!list) {
        printf("Skip list is NULL\n");
        return;
    }

    Zskiplistnode *current=list->head->level[0].forward,*next;
    while(!current)
    {
        next=current->level[0].forward;
        zslfreeNode(current);
        current=next;
    }

    free(list);
}


int zslrandomLevel() 
{
    int level =1;
    // while (rand() < RAND_MAX / 2 && level < INT_MAX - 1) {
    //     level++;
    // }
    while((rand() & 0xFFFF)<(SKIPLIST_P * 0xFFFF)) level++;
    return (level<ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL ;
}


Zskiplistnode* zslinsert(struct Zskiplist *list,double score,char* member)
//Zskiplistnode* zslinsert(Zskiplist *list,void *obj)
{
    if(!list) 
    {
        printf("no this list,sorry~\n");
        return NULL;
    }

    //struct  Zskiplistnode *update[list->level+1];  
    Zskiplistnode *update[ZSKIPLIST_MAXLEVEL],*x;
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



    // //reach insert position
    // for(int i=list->level-1;i>=0;i--)
    // {
    //     rank[i]=i==(list->level-1)? 0 : rank[i+1];
    //     while(x->level[i].forward && list->compare(x->level[i].forward->obj,obj)<0)
    //     {
    //         rank[i]+=x->level[i].span;
    //         x=x->level[i].forward;
    //     }

    //     update[i]=x;
    // }


    // //if elemet is already inside ,return NULL
    // if(x->level[0].forward && list->compare(x->level[0].forward->obj,obj)==0)
    //     return NULL;

    // //add new node with random level
    // level=zslrandomLevel();

    // if(level> list->level)
    // {
    //     for(int i=0;i<list->level;i++)
    //     {
    //         rank[i]=0;
    //         update[i]=list->head;
    //         update[i]->level[i].span=list->length;
    //     }
    //     list->level=level;
    // }

    // x=zslcreateNode(level,obj);
    // for(int i=0;i<level;i++)
    // {   
    //     x->level[i].forward=update[i]->level[i].forward;
    //     update[i]->level[i].forward=x;

    //     x->level[i].span=update[i]->level[i].span -(rank[0]-rank[i]);
    //     update[i]->level[i].span=(rank[0]-rank[i])+1;

    // }

    // //increment span for untouched levels

    // for(int i=level;i<list->level;i++)
    // {
    //     update[i]->level[i].span++;

    // }

    // x->backward=(update[0] ==list->head)? NULL: update[0];
    // if(x->level[0].forward)
    //     x->level[0].forward->backward=x;
    // else
    //     list->tail=x;
    

    // list->length++;
    // return x;


    
   

    
}

// int  zslgetRank(struct Zskiplist* list,double score,char *member)
// {
//     struct Zskiplistnode *current = list->head;
//     int rank = 0;

//     for(int i=list->level-1;i>=0;i--)
//     {
//         while(current->level[i].forward &&(current->level[i].forward->score < score ||
//             (current->level[i].forward->score == score &&
//             strcmp(current->level[i].forward->member,member) <= 0))) 
//             {
//                 rank += current->level[i].span;
//                 current = current->level[i].forward;
//             }

//         if (current->member && strcmp(current->member,member) == 0) return rank;

//     }

//     return 0;
// }

// // 獲取元素的分數
// double zslgetScore(struct Zskiplist *list,char *member) 
// {
//     if(list==NULL || member ==NULL) return -1.0;


//     struct Zskiplistnode *current = list->head;

//     while (current) {
//         int cmp = strcmp(member, current->member);
//         if (cmp == 0) {
//             //found it
//             return current->score;
//         } else if (cmp < 0 || (cmp == 0 && current->backward == NULL)) {
//             // error
//             return -1.0;
//         } else {
//             // move to next node in down level
//             current = current->backward;
//         }
//     }

//     // not found it
//     return -1.0;


// }

//Internal function used by skiplistDelete
void zsldeleteNode(Zskiplist* list,Zskiplistnode *node,Zskiplistnode** update)
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

// Delete an element from the skiplist
int zsldelete(Zskiplist *list,double score,char* member)
{
    Zskiplistnode *current=list->head,*next,*update[ZSKIPLIST_MAXLEVEL];

    // while(current!=NULL)
    // {
    //     next=current->forward[0];
    //     free(current->forward);
    //     free(current);
    //     current=next;
    // }


    for(int i=list->level-1;i>=0;i--)
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
        zslfreeNode(current);
        return 1;
    }
    return 0;
}



Zskiplistnode *zslFind(Zskiplist *list,double score,char *member) 
{
    Zskiplistnode *current=list->head;

    for (int i = list->level-1; i >= 0; i--) 
    {
        while (current->level[i].forward &&
               (score < current->level[i].forward->score ||
                (score == current->level[i].forward->score && 
                strcmp(current->level[i].forward->member, member) < 0)))
        {
            current =current->level[i].forward;
        }
    }
    //current=current->level[0].forward;
    if (current->level[0].forward && score == current->level[0].forward->score 
        && strcmp(current->level[0].forward->member, member) == 0) 
    {
        return current->level[0].forward;
    } else {
        return NULL;
    }
}


Zskiplistnode* skiplistPopHead(Zskiplist *list) 
{
    Zskiplistnode *current = list->head->level[0].forward;

    if (!current) return NULL;

    double score =current->score;
    char *member = strdup(current->member);  // Assuming member is a string

    zsldelete(list, score, member);

    size_t levelSize = 0;
    for (int i = 0; i < current->level; i++) 
    {
        levelSize += sizeof(struct Zskiplistlevel);
    }
    // Assuming the Zskiplistnode is dynamically allocated, otherwise, you might not need to free it.
    Zskiplistnode *popNode = malloc(sizeof(Zskiplistnode) + levelSize);
    popNode->score = score;
    popNode->member = member;
    popNode->backward = NULL;

    // Copy the level information if needed
    for (int i = 0; i < current->level; i++) {
        popNode->level[i].forward = current->level[i].forward;
        popNode->level[i].span =current->level[i].span;
    }

    // Assuming that x->level[0].forward is NULL after zsldelete
    popNode->level[0].forward = NULL;

    return popNode;
}

/* If the skip list is empty, NULL is returned, otherwise the element
 * at tail is removed and its pointed object returned. */
Zskiplistnode* zslPopTail(Zskiplist *list) 
{
    Zskiplistnode *current = list->tail;
    if (!current) return NULL;

    char *member = strdup(current->member);  // Assuming member is a string
    double score = current->score;

    zsldelete(list, score, member);

    size_t levelSize = 0;
    for (int i = 0; i < current->level; i++) 
    {
        levelSize += sizeof(struct Zskiplistlevel);
    }
    // Assuming the Zskiplistnode is dynamically allocated, otherwise, you might not need to free it.
    Zskiplistnode *popNode = malloc(sizeof(Zskiplistnode) + levelSize);
    popNode->score = score;
    popNode->member = member;
    popNode->backward = NULL;

    // Copy the level information if needed
    for (int i = 0; i < current->level; i++) {
        popNode->level[i].forward = current->level[i].forward;
        popNode->level[i].span = current->level[i].span;
    }

    // Assuming that current->level[0].forward is NULL after zsldelete
    popNode->level[0].forward = NULL;

    return popNode;
}

unsigned long skiplistLength(Zskiplist *list) 
{
    return list->length;
}


// void ZADD(struct Zskiplist *list,double score,char* member)
// {
    
//     int rank=zslgetRank(list,score,member);

//     // if(rank!=-1)//member exists, then update score
//     // {
//     //     struct Zskiplistnode *current=list->head->forward[0];
//     //     for(int i=0;i<rank;i++)
//     //     current=current->forward[i];

//     //     current->score=score;
//     //     return;
//     // }
    
//     //not exist
//     zslinsert(list,score,member);

// }




// int ZCARD(struct Zskiplist *list)
// {
//     if(!list)   
//     {
//         printf("no such skiplist.\n");
//         return -1;
//     }

//     return (list->head->level[0].span==NULL) ? 0 : zslgetRank(list,1,"")+1;

    
// }

// /**************DICT****************/

// void DictInit(struct Dict *dict,size_t initcapa)
// {
//     //dict->entries;


// }