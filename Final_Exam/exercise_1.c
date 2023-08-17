#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#define NAME_LEN 101 // 100 symbols and '\0'
#define CURRENCY_LEN 5 // 4 symbols and '\0'
#define ITEMS_COUNT 10

typedef struct BankAccount{
    uint16_t number;
    char name[NAME_LEN];
    float availability;
    char currency[CURRENCY_LEN];
}BankAccount;

typedef struct Node{
    BankAccount account;
    struct Node* next;
}Node;

double totalBalance(Node* head){
    if(head == NULL) return -1;
    // make unsigned to prevent overflow
    double balance = 0.00;
    while(head != NULL){
        balance += head->account.availability;
        head = head->next;
    }
    return balance;
}

Node* maxBalance(Node* head){
    if(head == NULL) return NULL;
    // make unsigned to prevent overflow
    double max_balance = head->account.availability;
    Node* max_node = head;
    head = head->next;
    while(head != NULL){
        if(head->account.availability > max_balance){
            max_balance = head->account.availability;
            max_node = head;
        }
        head = head->next;
    }
    return max_node;
}

void push_front(Node** head, BankAccount account){
    Node *new_node = malloc(sizeof(Node));
    new_node->account = account;
    new_node->next = *head;
    *head = new_node;
}

void print_info(Node *head){
    while(head != NULL){
        printf("%d %s %.2f %s\n", head->account.number, head->account.name,
             head->account.availability, head->account.currency);
        head = head->next;
    }
}

int is_unique(Node *head, uint16_t unique_number){
    while(head != NULL){
        if(head->account.number == unique_number){
            return 0;
        }
        head = head->next;
    }
    return 1;
}

void delete(Node** head){
    while(*head != NULL){
        Node* temp = (*head);
        *head = (*head)->next;
        free(temp);
        temp = NULL;
    }
    printf("\n");
}

Node* init(){
    srand(time(NULL));
    Node* head = NULL;
    char *currency[] = {"leva", "euro"};

    for(int i = 0; i < ITEMS_COUNT; i++){
        BankAccount account;

        // Unique number
        uint16_t unique_number;
        do{
            unique_number = rand() % (0xffff + 1); // Max 16 bit number
        }while(!is_unique(head, unique_number));
        account.number = unique_number;

        // 2 to 5 words
        // 0 to 2 + (0 to 1 + 2 = 2 or 3)
        uint8_t words_count = (rand() % (5 - 2)) + (rand() % 2 + 2);
        
        uint8_t name_cnt = 0;
        for(int i = 0; i < words_count; i++){
            // check if spaces because 5 * 20 + 4 spaces > 100
            // 1 to 20 symbols + '\0'
            uint8_t name_len =  ((rand() % 20) + 1) + 1;
            for(int j = 0; j < name_len; j++){
                if(j == 0){
                    account.name[name_cnt++] = (rand() % ('Z' - 'A' + 1)) + 'A';
                }else{
                    account.name[name_cnt++] = (rand() % ('z' - 'a' + 1)) + 'a';
                }
            }
            if( i + 1 < words_count){
                account.name[name_cnt++] = ' ';
            }
        }
        account.name[name_cnt] = '\0';

        // 0.00 to 100 000.00
        account.availability = (rand() % 10000001) / 100.;

        // currency either leva or euro
        strcpy(account.currency, currency[rand() % 2]);

        push_front(&head, account);
    }
    return head;
}

int main(void){
    Node* head = init();
    print_info(head);
    printf("%.2lf\n", totalBalance(head));
    Node* max = maxBalance(head);
    printf("%.2f\n", max->account.availability);
    // check max how to free it without deleting the head
    // free(max);
    delete(&head);
    return 0;
}
