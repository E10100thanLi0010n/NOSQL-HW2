#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<fcntl.h>
#include<unistd.h>
#include <hiredis/hiredis.h>
#include"table.h"
#include <sys/time.h>
#include <sys/resource.h>


//generate random key(char*)-value(int) pairs
char* generate_random_string(int length); 
//int genRanVal(void);

//check time
double measExecuTime(int (*function)());
size_t measMemUse(int (*function)());

void RedisTest(void);
//void test(struct DataBase*);
void test(struct HashTable*);


#endif