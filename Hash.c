#include"Hash.h"


unsigned int HashFunction(char* key) //
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) 
    {
        hash = (hash * 31) + key[i];
    }
    return hash % INDEX_LEN;
}


struct Key_Value* create_HashKV(char* key, char* value)
{
    struct Key_Value* newkv = (struct Key_Value*)malloc(sizeof(struct Key_Value));
    if(newkv==NULL)
    {
        printf("allocated failed \n");
        free(newkv);
        return NULL;
    }
    
    strncpy(newkv->key, key, sizeof(newkv->key) -1); // 避免溢出
    strncpy(newkv->value, value, sizeof(newkv->value)-1); // 避免溢出
    newkv->next==NULL;
    return newkv;
}


struct Hash* create_table(char* name)
{
    struct Hash* hm = (struct Hash*)malloc(sizeof(struct Hash));
    if (hm == NULL)
    {
        printf("create_table: allocated failed\n");
        return NULL;
    }

    hm->count = 0;
    hm->capacity = INITIAL_CAPACITY;
    hm->KVPairs = (struct Key_Value**)calloc(INITIAL_CAPACITY, sizeof(struct Key_Value*));

    // for (int i = 0; i < hm->capacity; i++)
    //     hm->KVPairs[i] = NULL;
    //hm->overflow_buckets = create_overbuck(hm);
    if(hm->KVPairs==NULL) 
    {
        free(hm);
        printf("create table failed. \n");
        return NULL;
    }
    for (int i = 0; i < hm->capacity; i++)
    {
        hm->KVPairs[i] = create_HashKV("", "");
        //hm->KVPairs[i]->isDeleted=0;
    }


    strncpy(hm->ListName,name, sizeof(hm->ListName) -1);
    printf("create table called %s \n",hm->ListName);
    return hm;
}

/*
struct Key_Value* Remove_From_Linkedlist(struct LinkedList* list)
{
    //no kv in the list
    if(!list) return NULL;

    //if(!list->next) return NULL;


    struct LinkedList* temp=list;
    struct LinkedList* newnode=list->next;
    temp->next=NULL;

    list=newnode;
    struct Key_Value *kv=NULL;
    memcpy(temp->node,kv,sizeof(struct Key_Value));
    free(temp->node->value);
    free(temp->node);
    free(temp);
    return kv;
}
*/

// // handling_cllision()
// void handle_collision(struct Hash* hm, struct Key_Value* kv, unsigned int index)
// {
//     struct LinkedList* head = hm->overflow_buckets[index];

//     if (head == NULL)
//     {
//         head = allocate_List();
//         head->node = kv;
//         head->next = NULL;
//         return;

//     }
//     else
//     {
//         hm->overflow_buckets[index] = insert_LinkedList(head, kv);
//         return;
//     }

// }



//insert
void Hash_insert(struct Hash* hm,char* key, char* value)
{
    int index = HashFunction(key);
    struct Key_Value* newKV=create_HashKV(key, value);

    if (hm->KVPairs[index] == NULL) //no KV in index
    {
        hm->KVPairs[index] = newKV;
    }
    else
    {
        struct Key_Value* current = hm->KVPairs[index];
        while (current->next != NULL) 
        current = current->next;

        current->next = newKV;
    }
   
    // if (hm->count > (hm->size / 2)) {
    //     rehash(hm);
    // }
    // }
    hm->count++;
}



//search
struct Key_Value* search_KV(struct Hash* hm,char* key)
{
    int index = HashFunction(key);
    struct Key_Value* current = hm->KVPairs[index];


    while(current!= NULL)
    {
        if (strcmp(current->key,key)==0) return current;
        /*
        if(head==NULL) return NULL;
        currKV=head->node;
        head=head->next;

        */
        current=current->next;
    }

   
    printf("there is no such Key_Value in this Hash table. \n");
    return NULL;
}


//find the value of the key
char* ValueforKey(struct Hash* hm,char* key)
{
    int index =HashFunction(key);
    struct Key_Value* current=search_KV(hm, key);
    if (current!= NULL) return current->value;

    /*
    for (size_t i = 0; i < hm->capacity; i++)
    {
        if (hm->KVPairs[i]->key == key)
        {
            // value = strdup(hm->KVPairs[i]->value);
             //return value;
            return hm->KVPairs[i]->value;
        }
    }
    */
    printf("(nil) \n");
    printf("Sorry, there is no such Key_Value in the hash table.\n");
    return NULL;
}


//update
void updateHashValue(struct Hash* hm,char* key)
{
    if (hm == NULL)
    {
        printf("there is no data in data table.\n");
        return;
    }

    char* newstr = NULL;
    int newstr_len = 100;
    newstr = (char*)malloc(sizeof(char) * newstr_len);

    if (newstr == NULL)
    {
        perror("memory allocation failed. \n");
        return;
    }

    struct Key_Value* current= search_KV(hm, key);

    if (current!= NULL)
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
                strcpy(current->value, newstr);
                printf("updated data at index %d is : %s\n", key, current->value);
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


    for (int i = 0; i < hm->capacity; i++)
    {
        if (hm->KVPairs[i]->key == key)
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
                    strcpy(hm->KVPairs[i]->value, newstr);
                    printf("updated data at index %d is : %s\n", key, hm->KVPairs[i]->value);
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


void delete_KV(struct Hash* hm,char* key)
{
    int index =HashFunction(key);
    struct Key_Value* kv =search_KV(hm,key);

    /*
    struct Key_Value* currKV = search_KV(hm, key);

    if (currKV != NULL && currKV->key == key) //found in the search_KV
    {
        free(currKV->value);
        free(currKV);
        hm->KVPairs[index] = NULL;
        hm->count--;
        printf("deleted key_value with key %d from KVPairs", key);
        return;


    }
    */

    if (kv != NULL && strcmp(kv->key,key)==0) //found in KVPairs[index]
    {
        free_KV(kv);
        hm->KVPairs[index] = NULL; //FIXME:what about the leftover of overflow_buckets[index]
        hm->count--;
        printf("deleted key_value with key %s from KVPairs", key);
        return;
    }


    

    printf("Key %s not found in the hash table.\n", key);
}


//delete
void free_KV(struct Key_Value* kv)
{
    // if (kv != NULL)
    // {

    //     if (kv->value != NULL)
    //     {
    //         //kv->value = NULL;
    //         free(kv->value);
    //     }
    //     if()

    // }

    //free(kv->value);
    free(kv);
}


void free_Hash(struct Hash* hm)
{

    if (hm == NULL) return;

    for (int i = 0; i < hm->capacity; i++)
    {
        struct Key_Value* current= hm->KVPairs[i];
        // if (kv != NULL)
        // {
        //     free_KV(hm->KVPairs[i]);
        //     hm->KVPairs[i] = NULL;
        // }

        while(current !=NULL)
        {
            struct  Key_Value* tmp;
            tmp=current;
            current=current->next;
            free_KV(tmp);

        }
        
    }

    
    free(hm->KVPairs);
    hm->KVPairs = NULL;
    free(hm);
    hm = NULL;
    printf("you have cleared all the data table \n");
}




void show_Hash(struct Hash* hm)
{
    printf("\nHash Table\n--------------------------\n");

    for (int i = 0; i < hm->capacity; i++)
    {
        struct Key_Value* current= hm->KVPairs[i];
        
        // if (currKV != NULL)
        // {
        //     printf("index: %d, key: %d, value: %s\n", i, currKV->key, currKV->value);
        // }

        while(current !=NULL )
        {
          printf("index: %d, key: %s, value: %s\n", i, current->key, current->value);      
            current=current->next;
        }
        printf("\n");
        // while (head != NULL)
        // {
        //     printf("index: %d, key: %d, value: %s\n", i, head->node->key, head->node->value);
        //     head = head->next;
        // }

    }

    printf("this Hash table is over \n");
    printf("-------------\n");
}

char* HGET(struct Hash* hm,char* key)
{
    ValueforKey(hm,key);



}


void HSET(struct Hash* hm,char* key,char* value)
{

    int index = HashFunction(key);
    struct Key_Value* current = hm->KVPairs[index];
    int findflag=0;

    while(current!= NULL)
    {
        if (strcmp(current->key,key)==0) //same key
        {
            strncpy(current->value, value, sizeof(current->value)-1);
            //findflag=1;
            printf("update it's new key %s , val: %s\n",current->key,current->value);
            printf("0 \n");
            break;
        }
        current=current->next;
    }

    if(!findflag)
    {
        Hash_insert(hm,key,value);
    }

}


void HDEL(struct Hash* hm,char* key)
{

    delete_KV(hm,key);


}

void EXPIRE(struct Hash* hm,char* key)
{




}