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


//check time  betewwn HW and Hiredis
double measExecuTime(int (*function)())
{
    clock_t start,end;
    double cpu_time;

    start=clock();
    function();
    end=clock();

    cpu_time=((double)(end-start))/CLOCKS_PER_SEC;
    return cpu_time;
}
/*
size_t measMemUse(int (*function)())
{
    size_t memUseBefore,memUseAfter;

    FILE *statfile=fopen("/proc/self/statm", "r");
    fscanf(statfile,"%s %lu",&memUseBefore);
    fclose(statfile);

    function();

    FILE *statfile=fopen("/proc/self/statm", "r");
    fscanf(statfile,"%s %lu",&memUseAfter);
    fclose(statfile);
    

    return (memUseAfter-memUseBefore)*(size_t)getpagesize();


}
*/
void analysisTable_regenData(struct HashTable *ht)
{





}

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


}

void test(struct HashTable *ht)
{   
    
    int length=10;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644); // 打开或创建文件

    if (fd == -1) {
        perror("open");
        exit(1);
    }


    for(int i=0;i<100000;i++)
    {   
        char* key=generate_random_string(length);
        char* value=generate_random_string(length);
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

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Insertion time: %.6f seconds\n", elapsed);

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