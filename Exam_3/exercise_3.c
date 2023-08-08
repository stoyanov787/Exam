#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define LEN 19
#define REL_TOL 0.01

typedef struct Product
{
     double old_price;
     double new_price;
     unsigned int id;
     char product_type;
     char product_name[LEN];
}Product;

int contains_id(Product* products, int len, int id){
    for(int i = 0; i < len; i++){
        if(products[i].id == id) return 1;
    }
    return 0;
}

Product* create_products(int len){
    Product* products = malloc(sizeof(Product) * len);
    char names[][4] = {"aaa", "bbb", "ccc"}; // 3 chars for letters and 1 for '\0'
    srand(time(NULL));
    for(int i = 0; i < len; i++){
        products[i].old_price = (499 + (rand() % (10045 - 499 + 1))) / 100.00;
        products[i].new_price = (499 + (rand() % (10045 - 499 + 1))) / 100.00;
        products[i].product_type = (rand() % (('D' - 'A') + 1)) + 'A';
        strcpy(products[i].product_name, names[rand() % 3]);
        int id = rand();
        while(contains_id(products, i + 1, id) || id == 0){
            id = rand();
        }
        products[i].id = id;
    }
    return products;
}

void print_products(Product* products, int len){
    for(int i = 0; i < len; i++){
        printf("%.2lf %.2lf %u %c %s\n", products[i].old_price, products[i].new_price,
                 products[i].id, products[i].product_type, products[i].product_name);
    }
}

int compare_product(const void *a, const void *b){
    int price1 = ((Product*)a)->new_price - ((Product*)a)->old_price;
    int price2 = ((Product*)b)->new_price - ((Product*)b)->old_price;
    if(abs(price1 - price2) < REL_TOL){
        if(((Product*)a)->product_type == ((Product*)b)->product_type){
            if(!strcmp(((Product*)a)->product_name, ((Product*)b)->product_name)){
                if(((Product*)a)->id > ((Product*)b)->id){
                    return -1;
                }
            }else if(strcmp(((Product*)a)->product_name, ((Product*)b)->product_name) > 1){
                return -1;
            }
        }else if(((Product*)a)->product_type > ((Product*)b)->product_type){
            return -1;
        }
    }else if(price1 > price2) return -1;
    return 1;

}


int main(void){
    Product* products = create_products(40);
    
    print_products(products, 40);
    qsort(products, sizeof(Product), 40, compare_product);
    printf("\n");
    print_products(products, 40);

    FILE* file;
    file = fopen("products.bin", "w+");

    if(file == NULL){
        perror("Unable to open file");
        exit(-1);
    }

    free(products);
    fclose(file);
    return 0;
}