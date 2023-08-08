#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int get_list_size(Node *cll){
    int count = 0;
    if(cll == NULL){
        return count;
    }
    Node* temp = cll;
    do{
        cll = cll->next;
        count++;
    }while(cll != temp);
    return count;
}

void print_list(struct Node *cll){
    if(cll == NULL){
        perror("Invalid node");
        exit(-1);
    }
    Node* temp = cll;
    do{
        printf("%d ", cll->data);
        cll = cll->next;
    }while(cll != temp);
    printf("\n");
}

void push_back(Node** head, int data){
    if(head == NULL){
        perror("Invalid head");
        exit(-1);
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    if(*head == NULL){
        new_node->next = new_node;
        *head = new_node;
        return;
    }
    new_node->next = (*head);
    Node *temp = *head;

    for(;temp->next != *head; temp = temp->next);
    temp->next = new_node;
}

void delete_list(struct Node **cll){
    if(cll == NULL){
        perror("Invalid node");
        exit(-1);
    }
    if(*cll == NULL) return;

    Node* start = *cll;
    Node* temp;
    for(int i = 0; i < get_list_size(*cll); i++){
        temp = *cll;
        (*cll) = (*cll)->next;
        free(temp);
    }
}

struct Node* insertAfter(struct Node *cll, int skipCount, int newElem){
    if(cll == NULL || skipCount == 0){
        perror("Invalid node or skip count/ cannot change head");
        exit(-1);
    }
    if((skipCount > get_list_size(cll) + 1) || (skipCount < 0)){
        perror("Invalid skip count");
        exit(-1);
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->data = newElem;

    for(int i = 1; i < skipCount; cll = cll->next, i++);
    new_node->next = cll->next;
    cll->next = new_node;
    return new_node;
}

int main(void){
    int numbers_count;

    do{
        printf("Enter number count: ");
        scanf("%d", &numbers_count);
    }while(numbers_count <= 0);

    Node* list = NULL;
    int number;
    for(int i = 0; i < numbers_count; i++){
        scanf("%d", &number);
        push_back(&list, number);
    }

    insertAfter(list, 2, 5);
    insertAfter(list, 2, 8);
    
    printf("%d\n", get_list_size(list));

    return 0;
}