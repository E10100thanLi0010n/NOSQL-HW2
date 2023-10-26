#include"table.h"
#include"benchmark.h"


int  main()
{   
    srand(time(NULL));

    //function 1
      RedisTest();
      test();

    
    //function 2

    printf("the following results are for function2 \n");
     RedisTest_average_Create_Read();
    //  benchmark_create() ;
    //  benchmark_read();


    //function 3
    printf("the following results are for function3 \n");
    


    return 0;
}