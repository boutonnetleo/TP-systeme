#include <stdlib.h>
#include <stdio.h>
typedef struct linked_list
{
    int value;
    struct linked_list *next;
} linked_list;

linked_list first_n_whole_number(int n){
    linked_list* next= NULL;
    linked_list start;
    for(int i=n-1;i>0;i=i-1){
        linked_list* current = malloc(sizeof(linked_list));
        current->next=next;
        current->value=i;
        next=current;
    }
    start.value=0;
    start.next=next;
    return start;
}

int size_linked_list(linked_list head){
    int size=1;
    for(linked_list curr= head;curr.next!=NULL;curr=*curr.next){
        size=size+1;
    }
    return size;
}

void print_each_element(linked_list head){
    for(linked_list curr= head;curr.next!=NULL;curr=*curr.next){
    printf("address : %p , value : %d \n",&curr,curr.value);
    }

}

int main()
{
    linked_list a =first_n_whole_number(5);
    printf("%d \n",a.next->next->next->next->value);
    printf("%d \n",size_linked_list(a));
    print_each_element(a);
}