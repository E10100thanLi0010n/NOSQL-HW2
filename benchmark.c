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

void test(struct DataBase *db)
{   
    int length=10;
    //input 10^5(10w) data
    for(int i=0;i<100;i++)
    {
        //insert 1000 data
        for(int i=0;i<1000;i++) //insert(MainHash(db,key),generate_random_string(),generate_random_string());
        {
            //char* generate_random_string(int length) 
            
            char* key=generate_random_string(length);
            //unsigned int main_hash_function(char* key)
            insert(db->index[main_hash_function(key)],key,generate_random_string(length));
        }
        //then, check deleted key-value and regenerate.
        /*
        while(LEFT!=0)
        {
            char* key=generate_random_string(length);
            //insert_LEFT_KEY(db->index[main_hash_function(key)],key,generate_random_string(length));
            


        }
        */

        //give feedback to databse so that next round avoids happening data skew.


    }



}