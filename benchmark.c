//hw2 benchwork

#include"benchmark.h"

unsigned int LEFT=0;


//generate random string 
char* generate_random_string(int length) 
{
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* random_string = (char*)malloc(length + 1);

    if (random_string) 
    {
        for (int i = 0; i < length; i++) 
        {
            int index = rand() % (sizeof(charset) - 1);
            random_string[i] = charset[index];
        }
        random_string[length] = '\0';
    }

    return random_string;
}




//function 1 :redis
void RedisTest(void)
{
    //hiredis test
    redisContext *context=redisConnect("127.0.0.1",6379);

    if(context!=NULL && context->err)
    {   
        redisFree(context);
        printf("connect redis server err:%s \n",context->errstr);
        return;
    }else
    {
        printf("connect redisserver success \n");
    }

    const char* cmd="SET my key value";

    redisReply *reply=(redisReply *)redisCommand(context,cmd);

    if(!reply)
    {
        printf("command execute fail \n");
        redisFree(context);
        return;
    }

  

    //freeReplyObject(reply);

    //clock_t start,end;
    printf("this is redis for 100000 data insert\n");
    printf("------------------------------------\n");

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for(int i=0;i<100000;i++)
    {
        char hkey[LENGTH];
        char hvalue[LENGTH];
        snprintf(hkey, sizeof(hkey), "hkey%d", i);
        snprintf(hvalue, sizeof(hvalue), "hvalue%d", i);
    
        redisReply *reply = (redisReply *)redisCommand(context, "SET %s %s", hkey, hvalue);
        freeReplyObject(reply);
    }


    gettimeofday(&end, NULL);

    
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Insertion time: %.6f seconds\n", elapsed);

    
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        long memory_usage = usage.ru_maxrss; // in kilobytes
        printf("Memory usage: %ld KB\n", memory_usage);
    } else {
        printf("Unable to determine memory usage\n");
    }


    redisFree(context);

    printf("------------------------------------\n");
    printf("this is the end of redis for 100000 data insert\n\n");
    

}

//funtion1 : my hash table 
void test(void)
{   
    struct HashTable *ht=initHashTable();
    printf("this is my hash table for 100000 data insert\n");
    printf("------------------------------------\n");

    //int length=10,num_records=100000;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644); // 打开或创建文件

    if (fd == -1) {
        perror("open");
        exit(1);
    }


    for(int i=0;i<100000;i++)
    {   
        char* key=generate_random_string(LENGTH);
        char* value=generate_random_string(LENGTH);
        //unsigned int main_hash_function(char* key)
        insert(ht,key,value);
        
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "Key: %s, Value: %s\n", key, value);
        int bytes_written = write(fd, buffer, strlen(buffer));

        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }
    }
    
    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 100000.0;
    printf("Insertion time: %.6f seconds\n", elapsed);

    // double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    // printf("Create operation for %d records took %f seconds\n", num_records, elapsed_time);

    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) 
    {
        long memory_usage = usage.ru_maxrss; // in kilobytes
        printf("Memory usage: %ld KB\n", memory_usage);
    } else 
    {
        printf("Unable to determine memory usage\n");
    }

    freetable(ht);
    close(fd);

    printf("------------------------------------\n");
    printf("this is the end of my hash table for 100000 data insert\n\n");



}
//funtion 2: Redis average_Create_Read
void RedisTest_average_Create_Read(void)
{
    redisContext *context = redisConnect("localhost", 6379); // 连接到Redis服务器
    if(context!=NULL && context->err)
    {   
        redisFree(context);
        printf("connect redis server err:%s \n",context->errstr);
        return;
    }else
    {
        printf("connect redisserver success \n");
    }

    
    char key[LENGTH];
    char value[LENGTH];
    struct timeval start, end;
    double elapsed_time;

    int num_records = 100000; 

    
    gettimeofday(&start, NULL);

    printf("this is redis for average time for data create and read\n");
    printf("------------------------------------\n");

    for (int i = 0; i < num_records; i++) 
    {
        snprintf(key, sizeof(key), "key%d", i);
        snprintf(value, sizeof(value), "value%d", i);
        redisReply *reply = redisCommand(context, "SET %s %s", key, value);
        freeReplyObject(reply);
    }
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Create (SET) operation took %f seconds\n", elapsed_time);

    // 测试随机读取（Read）操作
    gettimeofday(&start, NULL);
    for (int i = 0; i < num_records; i++) 
    {
        snprintf(key, sizeof(key), "key%d", rand() % num_records);
        redisReply *reply = redisCommand(context, "GET %s", key);
        freeReplyObject(reply);
    }
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Random Read (GET) operation took %f seconds\n", elapsed_time);

    redisFree(context); // 断开与Redis的连接

    printf("------------------------------------\n");
    printf("this is the end of redis for average time for data create and read\n");
    


}

//function 2 : my hash table for average create delay
void benchmark_create(void) 
{
    struct HashTable *ht=initHashTable();
    int num_records=10000;

    struct timeval start, end;
    double elapsed_time;

    printf("this is my hash table for average time for data random create \n");
    printf("------------------------------------\n");

    gettimeofday(&start, NULL);
    for (int i = 0; i < num_records; i++) {
        char key[15];
        char value[15];
        snprintf(key, sizeof(key), "key%d", i);
        snprintf(value, sizeof(value), "value%d", i);
        insert(ht, key, value);
    }
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Create operation for %d records took %f seconds\n", num_records, elapsed_time);

    printf("------------------------------------\n");
    printf("this is the end of my hash table for average time for data random create\n");

    freetable(ht);
}

//random read
void benchmark_read(void) 
{
    srand(time(NULL));
    struct HashTable *ht=initHashTable();
    int num_records=100000;
    //CREATE
    struct timeval Cstart, Cend;
    double Celapsed_time;
    //READ
    struct timeval Rstart, Rend;
    double Relapsed_time;


    printf("this is my hash table for average time for data random create \n");
    printf("------------------------------------\n");

    gettimeofday(&Cstart, NULL);
    for (int i = 0; i < num_records; i++) {
        // char key[LENGTH];
        // char value[LENGTH];
        // snprintf(key, sizeof(key), "key%d", i);
        // snprintf(value, sizeof(value), "value%d", i);
        char* key=generate_random_string(LENGTH);
        char* value=generate_random_string(LENGTH);

        insert(ht, key, value);
    }
    gettimeofday(&Cend, NULL);
    Celapsed_time = (Cend.tv_sec - Cstart.tv_sec) + (Cend.tv_usec - Cstart.tv_usec) / 1000000.0;
    printf("Create operation for %d records took %f seconds\n", num_records, Celapsed_time);

    printf("------------------------------------\n");
    printf("this is the end of my hash table for average time for data random create\n");
/////
    // printf("this is my hash table for average time for data random read \n");
    // printf("------------------------------------\n");

    // gettimeofday(&Rstart, NULL);
    // for (int i = 0; i < num_records; i++) 
    // {
    //     //char key[LENGTH];
    //     //snprintf(key, sizeof(key), "key%d", rand() % num_records);
    //     int index=rand()%ht->tablesize;
    //     char* value = get(ht, ht->table[index]->key);
        
    //     if (value != NULL) 
    //     {
    //         printf("Read: Key = %s, Value=%s\n", ht->table[index]->key, value);
    //     }
    // }
    // gettimeofday(&Rend, NULL);
    // Relapsed_time = (Rend.tv_sec - Rstart.tv_sec) + (Rend.tv_usec - Rstart.tv_usec) / 100000.0;
    // printf("Random Read operation for %d records took %f seconds\n", num_records, Relapsed_time);

    // printf("------------------------------------\n");
    // printf("this is the end of my hash table for average time for random data read\n");

    freetable(ht);

}

/*
void test(struct DataBase *db)
{   
    
    int length=10;
    //input 10^5(10w) data
    // for(int i=0;i<100;i++)
    // {
    //     //insert 1000 data
    //     for(int i=0;i<1000;i++) //insert(MainHash(db,key),generate_random_string(),generate_random_string());
    //     {
    //         //char* generate_random_string(int length) 
            
    //         char* key=generate_random_string(length);
    //         //unsigned int main_hash_function(char* key)
    //         insert(db->index[main_hash_function(key)],key,generate_random_string(length));
    //     }
    //     //then, check deleted key-value and regenerate.
        
    //     while(LEFT!=0)
    //     {
    //         char* key=generate_random_string(length);
    //         //insert_LEFT_KEY(db->index[main_hash_function(key)],key,generate_random_string(length));
            


    //     }
        

    //     //give feedback to databse so that next round avoids happening data skew.

    // }


///////////////
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int arr[]={0};
    int tableindex=0;

    for(int i=0;i<100;i++)
    {   
        for(int i=0;i<1000;i++)
        {
            
            char* key=generate_random_string(length);
            //unsigned int main_hash_function(char* key)
            insert(db->index[main_hash_function(key)],key,generate_random_string(length));

            for(int i=0;i<50;i++)
            {
                if(LOAD_FACTOR-0.5 <= db->index[i]->size && db->index[i]->size < LOAD_FACTOR)
                {   
                    arr[tableindex]=i;
                    tableindex++;
                }
            }

            while(LEFT)
            {

                LEFT--;
            }


        }
    
    }

    
    gettimeofday(&end, NULL);

    
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Insertion time: %.6f seconds\n", elapsed);

    
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        long memory_usage = usage.ru_maxrss; // in kilobytes
        printf("Memory usage: %ld KB\n", memory_usage);
    } else {
        printf("Unable to determine memory usage\n");
    }



}
*/