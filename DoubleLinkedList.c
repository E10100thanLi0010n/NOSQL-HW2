#include"DoubleLinkedList.h"



struct DouLL* createDoubleLL(void)
{
    struct DouLL *dll=(struct DouLL*)malloc(sizeof(struct DouLL));

    if(!dll)
    {
        printf("double linked list allocated failed \n");
        return NULL;
    }

    dll->head=dll->tail=NULL;
    dll->length=0;
    return dll;
}


struct Node* createNode(char* key)
{
    struct Node *newnode=(struct Node*)malloc(sizeof(struct Node));
    size_t keylen=strlen(key);
    newnode->key=(char*)malloc(keylen+1);

    if(!newnode->key) 
    {
        printf("Memory allocation for key failed.\n");
        free(newnode);
        return NULL;
    }
    // strncpy(newnode->key,key,strlen(key));
    strncpy(newnode->key, key,sizeof(newnode->key)-1);
    //newnode->key[keylen- 1] = '\0';
    newnode->next=newnode->prev=NULL;
    return newnode;
}




void LPUSH(struct DouLL* dll,char* key)
{
    struct Node *node=createNode(key);
    if(!node)
    {
        printf("memory allocated failed \n");
        return;
    }

    node->next=dll->head;
    strncpy(node->key,key,strlen(key));
    node->prev=NULL;

    if(dll->head!=NULL)
        dll->head->prev=node;


    dll->head=node;
    if(dll->tail==NULL)
    dll->tail=node;

    dll->length++;
}


void RPUSH(struct DouLL* dll,char* key)
{

    struct Node *node=createNode(key);

    if(!node)
    {
        printf("memory allocated failed \n");
        return;
    }

    node->prev=dll->tail;
    strncpy(node->key,key,strlen(key));
    node->next=NULL;


    if(dll->tail!=NULL)
    {
        dll->tail->next=node;
    }

    dll->tail=node;

    if(dll->head==NULL)
    dll->head=node;


    dll->length++;
}



//removes and returns an element from the head of a list
char* LPOP(struct DouLL* dll)
{
    if(dll->head==NULL)
    {
        printf("there is no element in the list.\n");
        return NULL;
    }


    struct Node *temp=dll->head;
    char* key=(char*)malloc(sizeof(temp->key));
    strncpy(key,temp->key,sizeof(temp->key)-1);

    dll->head=temp->next;

    if(dll->head!=NULL)
    {

        dll->head->prev=NULL;
    }else
    {
        dll->tail=NULL;
    }


    free(temp->key);
    free(temp);
    dll->length--;
    return key;

}

// removes and returns an element from the tail of a list
char* RPOP(struct DouLL* dll)
{
    if(dll->tail==NULL)
    {
        printf("there is no element in the list.\n");
        return NULL;
    }

    struct Node *temp=dll->tail;
    char* key=(char*)malloc(sizeof(temp->key));
    strncpy(key,temp->key,sizeof(temp->key)-1);

    dll->tail=temp->prev;

    if(dll->tail!=NULL)
    {

        dll->tail->next=NULL;
    }else
    {
        dll->head=NULL;
    }


    free(temp->key);
    free(temp);
    dll->length--;
    return key;

}

//LLEN returns the length of a list.
int LLEN(struct DouLL* dll)
{
    if(!dll) return -1;

    return dll->length;
}

void showList(struct DouLL* dll)
{
    if(!dll)
    {
        printf("no list!\n");
        return;
    }

    struct Node* node=dll->head;
    int i=0;
    while(node!=NULL)
    {

        //printf("%d is : %s \n",i,node);
        printf("%d is : %s \n",i,node->key);
        node=node->next;
        i++;
    }
    printf("---------------------\n");
    
}

void freeDLL(struct DouLL *dll)
{
    //struct Node* temp=dll->head;
    while(dll->head!=NULL)
    {
        struct Node* temp=dll->head;
        dll->head=dll->head->next;
        free(temp->key);
        free(temp);

       // temp=temp->next;
    }

    free(dll);
}


void LRANGE(struct DouLL *dll,int start,int end)
{
    if(!dll)
    {
        printf("there is no such doublelinked list \n");
        return ;
    }

    
    //out of range
    if((start>=dll->length) &&(end>=dll->length))
    {
        printf("(empty list or set)\n");
        return;

    }

    

    while(start<0)
    {
        start=start+dll->length;
    }

    while(end<0)
    {
        end=end+dll->length;
    }

    while(start>=dll->length)
    {
        start-=dll->length;
    }

    printf("start: %d\n",start);

    while(end>=dll->length)
    {
        end-=dll->length;
    }
    printf("end: %d\n",end);

    if (start < 0 || start >=dll->length || end < 0 || end >=dll->length ) 
    {
        printf("Invalid range\n");
        return;
    }

    if(start>end)
    {
        int temp=start;
        start=end;
        end=temp;
    }

    struct Node *current =dll->head;
    int index = 0;

    while (current != NULL && index < start) 
    {
        current = current->next;
        index++;
    }

    printf("LRANGE result: ");
    while (current != NULL && index <= end) 
    {
        printf("%s ", current->key);
        current = current->next;
        index++;
    }

    printf("\n");
}