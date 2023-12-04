#include"table.h"
#include"benchmark.h"
#include"DoubleLinkedList.h"
#include"SortedSet.h"

int main()
{
 
//    struct DouLL* myList = createDoubleLL();

//     // 使用 lpush 在链表头部插入元素
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


    
    struct SkipList *list = createSkipList();

    // 插入元素
    insertSkipList(list, 1.0, "member1");
    insertSkipList(list, 2.0, "member2");
    insertSkipList(list, 3.5, "member3");

    //ZADD(list, 1.0, "member1");
   // ZADD(list, 2.0, "member2");
   // ZADD(list, 3.5, "member3");

    // 獲取排名和分數
    printf("Rank of member1: %d\n", getRank(list, "member3"));
    //printf("Score of member2: %f\n", getScore(list, "member2"));

    printf("zcard : %d\n",ZCARD(list));

    // 釋放資源
    freeSkipList(list);
  

    return 0;
}

