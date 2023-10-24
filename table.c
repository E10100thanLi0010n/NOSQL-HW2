#include"table.h"

unsigned int LEFT_KEY=0;
//DataBase index[INDEX_LENGTH];

// hash function for database->index[]
unsigned int main_hash_function(char* key) //
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) 
    {
        hash = (hash * 31) + key[i];
    }
    return hash % INDEX_LENGTH;
}

//multihash for table->Key-Value
uint16_t MurmurHash3_x86_32( void *key, int len, uint32_t seed) 
{
    uint8_t *data = ( uint8_t *)key;
    const int nblocks = len / 4;

    uint32_t h1 = seed;
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;

    uint32_t *blocks = ( uint32_t *)(data + nblocks * 4);

    for (int i = -nblocks; i; i++)
    {
        uint32_t k1 = blocks[i];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> 17);
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> 19);
        h1 = h1 * 5 + 0xe6546b64;
    }

    uint8_t *tail = ( uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3)
    {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
                k1 *= c1;
                k1 = (k1 << 15) | (k1 >> 17);
                k1 *= c2;
                h1 ^= k1;
    }

    h1 ^= len;
    h1 ^= (h1 >> 16);
    h1 *= 0x85ebca6b;
    h1 ^= (h1 >> 13);
    h1 *= 0xc2b2ae35;
    h1 ^= (h1 >> 16);

    return (uint16_t)h1;
}
/*
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
*/

// struct KeyValue* create_KV(void)
// {
//     struct KeyValue* newkv = (struct KeyValue*)malloc(sizeof(struct KeyValue));
//     newkv->key = (char*)malloc(11);
//     newkv->value = (char*)malloc(11);
//     //newkv->key=strdup(key);
//     //newkv->value=strdup(value);

//     if (newkv->key == NULL || newkv->value == NULL)
//     {
//         if (newkv->key != NULL) free(newkv->key);
//         if (newkv->value != NULL) free(newkv->value);
//         free(newkv);
//         return NULL;
//     }

//     //strncpy(newkv->key,key,10);
//     //strncpy(newkv->value, value,10);
//     newkv->isDeleted=0;
//     return newkv;
// }

struct KeyValue* create_KV(char* key, char* value)
{
    struct KeyValue* newkv = (struct KeyValue*)malloc(sizeof(struct KeyValue));
    //newkv->key = (char*)malloc(strlen(key)+1);
    //newkv->value = (char*)malloc(strlen(value)+1);
    //newkv->key=strdup(key);
    //newkv->value=strdup(value);

    // if (newkv->key == NULL || newkv->value == NULL)
    // {
    //     if (newkv->key != NULL) free(newkv->key);
    //     if (newkv->value != NULL) free(newkv->value);
    //     free(newkv);
    //     return NULL;
    // }

    
    if(newkv)
    {
        strncpy(newkv->key, key, sizeof(newkv->key) - 1); // 避免溢出
        strncpy(newkv->value, value, sizeof(newkv->value) - 1); // 避免溢出
    }

    //strncpy(newkv->key,key,10);
    //strncpy(newkv->value, value,10);
    newkv->isDeleted=0;
    return newkv;
}

//create
struct HashTable* initHashTable(void)
{
    struct HashTable *ht=(struct HashTable*)malloc(sizeof(struct HashTable));


    if(ht==NULL) return NULL;


    ht->tablesize=INITIAL_TABLE_SIZE;
    ht->table=(KeyValue**)calloc(INITIAL_TABLE_SIZE,sizeof(struct KeyValue*));
    //ht->table=(KeyValue*)calloc(INITIAL_TABLE_SIZE,sizeof(struct KeyValue));
    if(ht->table==NULL) 
    {
        free(ht->table);
        printf("create table failed. \n");
        return NULL;
    }
        //ht->table[1000] = (char*)malloc(2);
    for (int i = 0; i < ht->tablesize; i++)
    {
        ht->table[i]=(struct KeyValue*)malloc(sizeof(struct KeyValue));
        ht->table[i]->isDeleted=0;

        // if (ht->table[i] != NULL) 
        // {
        // *(ht->table[1000]) =create_KV(NULL,NULL);
        // } else {
        // printf("ggwp \n");
        // }
        // ht->table[i]->isDeleted=0;
        //ht->table[i]->key=NULL;
        //ht->table[i]->value=NULL;
        //ht->table[i] = create_KV(NULL,NULL);
        if (ht->table[i] == NULL) 
        {
            for (int j = 0; j < i; j++) 
            {
                free(ht->table[j]);
            }
            free(ht->table);
            free(ht);
            return NULL;
        }

    }
    ht->size =0;
    return ht;
}


//resize size when rehashing
void resize(struct HashTable* ht) 
{

    int newSize =ht->tablesize* 2;
    struct KeyValue** newTable = (struct KeyValue**)malloc(sizeof(struct KeyValue*) * newSize);
    //struct KeyValue* newTable = (struct KeyValue*)malloc(sizeof(struct KeyValue) * newSize);
    if(!newTable) return;

      for (int i = 0; i < newSize; i++) 
      {
        //newTable[i] = (struct KeyValue*)malloc(sizeof(struct KeyValue));
        newTable[i]=create_KV(NULL,NULL);
        if (newTable[i] == NULL) 
        {
            for (int j = 0; j < i; j++) 
            {
                free(newTable[j]);
            }
            free(newTable);
            return;
        }
        // newTable[i]->key = NULL;
        strcpy(newTable[i]->key, "");
        newTable[i]->isDeleted = 0;
    }


    //transfer
    for (int i = 0; i < ht->tablesize; i++)
    {

        if(ht->table[i]->key!=NULL && !ht->table[i]->isDeleted)
        {
            int index=MurmurHash3_x86_32(ht->table[i]->key,newSize,SEED);

            while(newTable[index]->key!=NULL)
                index=(index+1)%newSize;

            strncpy(newTable[index]->key,ht->table[i]->key,10);
            strncpy(newTable[index]->value,ht->table[i]->value,10);
        }

    }
    printf("now current size is : %d\n",newSize);
    
    free(ht->table);
    ht->tablesize=newSize;
    ht->table=newTable;
    
    //return ;

}






//insert new key-value pairs
void insert(HashTable* ht, char* key,char* value)
{
    //struct HashTable *ht = &mainHashtables[mainHash].subtables[subHash];
    int index = MurmurHash3_x86_32(key,10,SEED)%(ht->tablesize); //KEY LENGTH=10
    struct KeyValue *newKV = create_KV(key, value);
    int deleteindex=-1;
    int initindex=index;

    while(ht->table[index]->key!=NULL) //there is a keyvalue in corresponding position.
    {
        if(ht->table[index]->isDeleted && deleteindex==-1)
            deleteindex=index;

        index=(index+1)%(ht->tablesize);

        //table is full
        if(index==initindex) 
        {
            printf("this table is full\n");
            LEFT_KEY++; //store non-stored key
            free(newKV);
            return; 

        }

    }
 
    if (deleteindex != -1)
    {
        index = deleteindex;
        ht->table[index]->isDeleted = 0;
    }
    ht->table[index]=newKV;
    // ht->table[index]->key=strdup(key);
    // ht->table[index]->value=strdup(value);
    strncpy(ht->table[index]->key, key, sizeof(newKV->key) - 1); // 避免溢出
    strncpy(ht->table[index]->value, value, sizeof(newKV->value) - 1); // 避免溢出
    ht->size++;
    if((float)ht->size/ht->tablesize> LOAD_FACTOR)
    resize(ht);
    free(newKV);
}



//get data from table
char* get(HashTable* ht, char* key)
{
    int index = MurmurHash3_x86_32(key,10,SEED)%(ht->tablesize); //KEY LENGTH=10
    int initindex=index;

    while (ht->table[index]->key != NULL)
    {
        //key found
        if (!ht->table[index]->isDeleted && strcmp(ht->table[index]->key, key) == 0)
        {
            return ht->table[index]->value;
        }

        index = (index + 1) % ht->tablesize;

        if (index == initindex)
        {
            // Key not found
            printf("your key: %s is not found \n",key);
            return NULL;
        }
    }


    return NULL;
}

//update
void updateValue(struct HashTable* ht,char* key)
{

    if (ht == NULL)
    {
        printf("there is no data in data table.\n");
        return;
    }

    char* newstr = NULL;
    int newstr_len = 10; //FIXME
    newstr = (char*)malloc(sizeof(char) * newstr_len);

    if (newstr == NULL)
    {
        perror("memory allocation failed. \n");
        return;
    }

    struct KeyValue* currKV = ht->table[MurmurHash3_x86_32(key,10,SEED)];//FIXME 

    if (currKV != NULL)
    {
        printf("enter your new value: ");
        if (fgets(newstr, newstr_len - 1, stdin) != NULL)
        {
            //len= the actul length of newstr
            size_t len = strlen(newstr);

            if (len > 0 && newstr[len - 1] == '\n') newstr[len - 1] = '\0';
            //put newstr into kvpairs[i].value
            if (strlen(newstr) < newstr_len)
            {
                strcpy(currKV->value, newstr);
                printf("updated data at index %s is : %s\n", key, currKV->value);
            }
            else
            {
                printf("your input value is too long to be stored in data table. \n");
            }
            free(newstr);
            return;
        }
        else
        {
            printf("input read failed.\n");
        }
    }


    for (int i = 0; i < ht->tablesize; i++)
    {
        if (strcmp(ht->table[i]->key,key)==0)
        {
            printf("enter your new value\n");
            //redesign the length of newstr
            if (fgets(newstr, newstr_len - 1, stdin) != NULL)
            {
                //len= the actul length of newstr
                size_t len = strlen(newstr);

                if (len > 0 && newstr[len - 1] == '\n') newstr[len - 1] = '\0';
                //put newstr into kvpairs[i].value
                if (strlen(newstr) < newstr_len)
                {
                    strcpy(ht->table[i]->value, newstr);
                    printf("updated data at index %s is : %s\n", key,ht->table[i]->value);
                }
                else
                {
                    printf("your input value is too long to be stored in data table. \n");
                }

                free(newstr);
                return;
            }
            else
            {
                perror("input read failed. \n");
            }

        }
    }

    printf("key : %s not found in the hash table.\n", key);
    free(newstr);
}

//delete
void freeKV(struct KeyValue* kv)
{
    // if (kv != NULL)
    // {

    //     if (kv->value != NULL)
    //     {
    //         free(kv->value);
    //         free(kv->key);
    //         kv->value = NULL;
    //         kv->key=NULL;
    //     }

    // }

    //free(kv->value);
    free(kv);
    



}


void freetable(struct HashTable* ht)
{

    if(!ht)
    {
        printf("hash table doesn't exist \n");
        return;
    }

    for (int i = 0; i < ht->tablesize; i++)
    {
        struct KeyValue* kv = ht->table[i];
        if(kv!=NULL)
        {
            freeKV(ht->table[i]);
            ht->table[i] = NULL;
        }
    }


    free(ht);
    printf("your hash table now is deleted. \n");   
}


//delete
void deleteKV(HashTable *ht,char* key)
{




}



/*
int main() {
    HashTable ht;
    initHashTable(&ht);

    clock_t start_time=clock();




    insert(&ht, "one", 1);
    insert(&ht, "two", 2);
    insert(&ht, "four", 4);
    insert(&ht, "three", 3);
    insert(&ht, "five", 5);
    insert(&ht, "six", 6);
    insert(&ht, "seven", 7);
    insert(&ht, "eight", 8);


    clock_t end_time=clock();


    double execution_time=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    //double execution_time=difftime;

    printf("Execution time: %f seconds\n", execution_time);
    printf("Value for 'one': %d\n", get(&ht, "one"));
    printf("Value for 'two': %d\n", get(&ht, "two"));
    printf("Value for 'four': %d\n", get(&ht, "four"));




    
    srand(time(NULL));
    int length=rand()%(10-5+1)+5;  //length=5~10
    for(int i=0;i<10^5;i++)
    insert(&ht,generate_random_string(length),genRanVal());




    
    return 0;
}

*/