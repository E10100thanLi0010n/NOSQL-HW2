#include"table.h"
#include"benchmark.h"
#include"DoubleLinkedList.h"

int  main()
{
 
   struct DouLL* myList = createDoubleLL();

    // 使用 lpush 在链表头部插入元素
    RPUSH(myList, "1a");
    RPUSH(myList, "2bb");
    RPUSH(myList, "3c");
    //RPUSH(myList, "4d");
    //RPUSH(myList, "5e");


    // showList(myList);
    // printf("len= %d\n",LLEN(myList));

    
    
    //char* popped1 = LPOP(myList);
    //printf("pop val is : %s\n",popped1);
    showList(myList);
    printf("len= %d\n",myList->length);
    printf("\n\n");
    LRANGE(myList,-100,100);
    freeDLL(myList);


    

  

    return 0;
}