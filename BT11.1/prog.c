#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "io.h"
typedef struct hang_t{
    char *id;
    char *name;
    double price;
    int quantity;
}*hang;
int search(hang *list, int n, char *line){
    char *tmp = NULL;
    for(int i=0; i<n; i++){
        if(strstr(list[i]->id,line)) return i;
    }
    return -1;
}
void menu(){
    printf("Chuong trinh quan ly cua hang\n\n");
    printf("1. Xem thong tin mat hang\n");
    printf("2. Tao don hang\n");
    printf("3. Thoat\n");
}
void tail(){
    printf("%10s","Ma so");
    printf("%30s","Ten mat hang");
    printf("%30s","Gia tien");
    printf("%30s","So luong\n");
}
int main(){
    FILE *f = fopen("inp20k.txt", "r");
    int n, idx = 0, q, idx_bill = 0;
    double total = 0;
    char *line = NULL, *id, *name, *price, *quantity;
    cgetline(&line,0,f);
    n = atoi(line);
    hang *list = calloc(n,sizeof(hang));
    hang *list_bill = calloc(n,sizeof(hang));
    while(cgetline(&line,0,f)){
        id = strtok(line, " \n");
        name = strtok(NULL, " \n");
        price = strtok(NULL, " \n");
        quantity = strtok(NULL, " \n");
        list[idx] = malloc(sizeof(struct hang_t));
        list[idx]->id = strdup(id);
        list[idx]->name = strdup(name);
        list[idx]->price = atof(price);
        list[idx]->quantity = atoi(quantity);
        idx++;
    }
    int choice = -1;
    while(choice != 3){
        menu();
        printf("Nhap vao lua chon cua ban: ");
        scanf("%d", &choice);
        clear_stdin();
        if(choice == 1){
            printf("Nhap ma so mat hang: ");
            cgetline(&line,0,stdin);
            remove_tail_lf(line);
            idx = search(list,n,line);
            if(idx == -1) printf("Khong tim thay!\n");
            else{
                tail();
                printf("%10s",list[idx]->id);
                printf("%30s",list[idx]->name);
                printf("%30lf",list[idx]->price);
                printf("%30d\n",list[idx]->quantity);
            }
        }
        else if(choice == 2){
            while(strcmp(line,"STOP")){
                printf("Nhap ma so mat hang: ");
                cgetline(&line,0,stdin);
                remove_tail_lf(line);
                idx = search(list,n,line);
                if(idx == -1) printf("Khong tim thay!\n");
                else{
                    printf("Nhap so luong: ");
                    scanf("%d",&q);
                    clear_stdin();
                    if(list[idx]->quantity < q) printf("Khong du hang!\n");
                    else{
                        list_bill[idx_bill] = malloc(sizeof(struct hang_t));
                        list_bill[idx_bill] = list[idx];
                        list_bill[idx_bill]->quantity = q;
                        idx_bill++;
                    }
                }
            }
            printf("Cty ABC\n");
            printf("%30s\n","Don hang ban le");

            printf("%10s","STT");
            printf("%30s","Mat hang");
            printf("%30s","Don gia");
            printf("%30s","So luong");
            printf("%30s","Thanh tien\n");
            for(int i=0; i<idx_bill; i++){
                printf("%10d",i+1);
                printf("%30s",list_bill[i]->name);
                printf("%30lf",list_bill[i]->price);
                printf("%30d",list_bill[i]->quantity);
                total += list_bill[i]->quantity * list_bill[i]->price;
                printf("%30lf\n",list_bill[i]->quantity * list_bill[i]->price);
            }
            printf("----------------------------------------------------------------\n");
            printf("Tong tien: %lf",total);
        }
        printf("\n");
        printf("\n");
    }
    fclose(f);
}