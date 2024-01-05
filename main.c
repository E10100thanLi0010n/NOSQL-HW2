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


    char* words[]={"foo","zap","karsa"};
    Zskiplist *sl=zslcreate(compare);

    for(int i=0;words[i]!=NULL;i++)
    {
        printf("insert %s: %p\n",words[i],zslinsert(sl,words[i]));

    }



    
    // struct Zskiplist *list = zslcreate();

    // // 插入元素
    // zslinsert(list, 1.0, "member1");
    // zslinsert(list, 2.0, "member2");
    // zslinsert(list, 3.5, "member3");

    //ZADD(list, 1.0, "member1");
   // ZADD(list, 2.0, "member2");
   // ZADD(list, 3.5, "member3");

    // 獲取排名和分數
    // printf("Rank of member1: %d\n", zslgetRank(list, 1.0,"member1"));

    // printf("Score of member2: %f\n", zslgetScore(list, "member2"));

    //printf("zcard : %d\n",ZCARD(list));

    // 釋放資源
    //zslfree(list);
  
    // char* str1 = "wang";
    // char* str2 = "ma";
    // char* str102 = "tian";
    // //printf("create a table \n");
    // struct Hash* table = create_table("table 1");

    // printf("ok, now you can create kv in your hash table \n");

    // Hash_insert(table,"a" , str1);
    // Hash_insert(table,"a", str2);
    //Hash_insert(table, 102, str102);


    //show_Hash(table);
    // printf("valuefor key :1 \n");

    // printf("value in key 1: %s \n", ValueforKey(table,"a"));

     //printf("after delete 2 \n");
     //delete_KV(table,"a");
    // printf("\n");

    // printf("update data for key: 102 \n");
    // updateValue(table, 102);

     //show_Hash(table);

    //free_Hash(table);

   

    return 0;
}

