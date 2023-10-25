#include"table.h"
#include"benchmark.h"


int  main()
{
    /*
    //int numbers_of_keys = 10;
    char* str1 = "wang";
    char* str2 = "ma";
    char* str102 = "tian";
    printf("create a table \n");
    struct Hash* table = create_table(100);

    printf("ok, now you can create kv in your hash table \n");

    Hash_insert(table, 1, str1);
    Hash_insert(table, 2, str2);
    Hash_insert(table, 102, str102);


    show_Hash(table);



    printf("valuefor key :1 \n");

    printf("value in key 1: %s \n", ValueforKey(table, 1));

    printf("after delete 2 \n");
    delete_KV(table, 2);
    printf("\n");

    printf("update data for key: 102 \n");
    updateValue(table,102);

    show_Hash(table);

    free_Hash(table);
    */
   
   struct HashTable* ht=initHashTable();
    char* str1="9487948712";
    char* str2="5566aa5566";
    char* str3="9487948712";
    char* str4="8787878787";


    // for(int i=0;i<1000;i++)
    // insert(ht,generate_random_string(10),generate_random_string(10));
    //printf("answer : %s is %s \n",str1,get(ht,str1));
     //insert(ht,str1,str2);
     //insert(ht,str4,str3);
     //printf("str1 is: %s\n",get(ht,str1));
     //showTable(ht);
    // deleteKV(ht,str4);
    // showTable(ht);
     printf("\n");

    //RedisTest();
    test(ht);
    //showTable(ht);

   /*
    double exectime=measExecuTime(main);
    printf("perform time : %f s \n",exectime);


    size_t memUse= measMemUse(main);
    printf("memory usage ：%lu pages\n",memUse);
    */


    /*
    struct DataBase* db=(struct DataBase*)malloc(sizeof(struct DataBase));
    test();
    
    
    */


    return 0;
}