#include"table.h"
#include"benchmark.h"
#include"DoubleLinkedList.h"
#include"SortedSet.h"
#include"Hash.h"

int compare(const void* a,const void *b)
{
    return  strcmp(a,b);
}

int main()
{
 //double linked list
//    struct DouLL* myList = createDoubleLL();
//     RPUSH(myList, "1a");
//     RPUSH(myList, "2bb");
//     RPUSH(myList, "3c");
//     //RPUSH(myList, "4d");
//     //RPUSH(myList, "5e");
// showList(myList);
    // printf("len= %d\n",LLEN(myList));
    //char* popped1 = LPOP(myList);
    //printf("pop val is : %s\n",popped1);
    // showList(myList);
    // printf("len= %d\n",myList->length);
    // printf("\n\n");
    // LRANGE(myList,-100,100);
    // freeDLL(myList);

/*for void* obj */
    // char* words[]={"foo","zap","karsa"};
    // Zskiplist *sl=zslcreate(compare);

    // for(int i=0;words[i]!=NULL;i++)
    // {
    //     printf("insert %s: %p\n",words[i],zslinsert(sl,words[i]));

    // }



    
    //struct Zskiplist *list = zslcreate();

    // 插入元素
    //zslinsert(list, 1.0, "member1");
    //printf("%s \n",list->head->member);

    //zslinsert(list, 2.0, "member2");
    // zslinsert(list, 3.5, "member3");

    // ZADD(list, 1.0, "member1");
    // ZADD(list, 2.0, "member2");
    // ZADD(list, 3.5, "member3");
    
     //printf("Rank of member1: %d\n", zslgetRank(list, 1.0,"member1"));

    // printf("Score of member2: %f\n", zslgetScore(list, "member2"));

    // printf("zcard : %d\n",ZCARD(list));
     
    // printf("%d \n",skiplistLength(list));
    // double searchScore = 3.5;
    // char *searchMember = "member3";
    // if(zsldelete(list,1.0,"member1"))
    // {
    //     printf("%d \n",skiplistLength(list));
    // }


    // Zskiplistnode *foundNode = zslFind(list, searchScore, searchMember);

    // if (foundNode) 
    // {
    //     printf("Node found: Score=%.2f, Member=%s\n", foundNode->score, foundNode->member);
    // } else {
    //     printf("Node not found.\n");
    // }


    //釋放資源
    //zslfree(list);
  
    // char* str1 = "wang";
    // char* str2 = "ma";
    // char* str102 = "tian";
    // //printf("create a table \n");
    // struct Hash* table = create_table("table 1");

    // printf("ok, now you can create kv in your hash table \n");

    // HSET(table,"a" , str1);
    //HSET(table,"b", str2);
    //Hash_insert(table,"102", str102);


    //show_Hash(table);
   // printf("value for key :1 \n");

    // printf("value in key 1: %s \n", HGET(table,"a"));

    // printf("after delete 2 \n");
    // //delete_KV(table,"a");
    // //HDEL(table,"b");
    // EXPIRE(table,"a",3);
    // printf("\n");

   //printf("update data for key: 102 \n");
    //updateValue(table," 102");

    // show_Hash(table);

    // free_Hash(table);

    ZSet myZSet1, myZSet2, resultZSet;
    initZSet(&myZSet1);
    initZSet(&myZSet2);
    initZSet(&resultZSet);

    ZADD(&myZSet1, "member1", 10);
    ZADD(&myZSet1, "member2", 5);
    ZADD(&myZSet1, "member3", 20);

    ZADD(&myZSet2, "member1", 15);
    ZADD(&myZSet2, "member2", 8);
    ZADD(&myZSet2, "member4", 12);

    printf("ZRange 1:\n");
    Zrange(&myZSet1, 0, myZSet1.size - 1);

    printf("ZRange 2:\n");
    Zrange(&myZSet2, 0, myZSet2.size - 1);

    printf("ZINTERSTORE Result:\n");
    ZINTERSTORE(&resultZSet, &myZSet1, &myZSet2);
    Zrange(&resultZSet, 0, resultZSet.size - 1);

    printf("ZUNIONSTORE Result:\n");
    ZUNIONSTORE(&resultZSet, &myZSet1, &myZSet2);
    Zrange(&resultZSet, 0, resultZSet.size - 1);

    printf("ZCount: %d\n", ZCOUNT(&myZSet1, 5, 15));

    printf("ZRANGEBYSCORE:\n");
    ZRANGEBYSCORE(&myZSet1, 5, 15);

    printf("ZRANK: %d\n", ZRANK(&myZSet1, "member2"));

    printf("ZREMRANGEBYSCORE Result:\n");
    ZREMRANGEBYSCORE(&myZSet1, 5, 15);
    Zrange(&myZSet1, 0, myZSet1.size - 1);

    // 释放内存
    freeZSet(&myZSet1);
    freeZSet(&myZSet2);
    freeZSet(&resultZSet);

    return 0;
}

