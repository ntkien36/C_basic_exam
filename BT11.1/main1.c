#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "cgetline.c"
void clear(void){
    while(getchar() != '\n');
}
typedef struct hang_t{
    char *id;
    char *name;
    char *price;
    char *quantity;
}*hang;

void Menu(){
    printf("Don hang ban le\n");
    printf("%s", "STT");
    printf(" %30s","Mat hang");
    printf(" %30s","Don gia");
    printf(" %30s","So luong");
    printf(" %30s\n\n","Thanh tien");
}
void function(){
    printf("1. Xem thong tin mat hang\n");
    printf("2. Tao don hang\n");
    printf("3. Thoat\n");
}

void add(char *line, hang a){
    char *id;
    char *name;
    char *price;
    char *quantity;
    id = strtok(line, " \n");
    name = strtok(NULL, " \n");
    price = strtok(NULL, " \n");
    quantity = strtok(NULL, " \n");
    a->id = strdup(id);
    a->name = strdup(name);
    a->price = strdup(price);
    a->quantity = strdup(quantity);
}
/*
char strlwr(char s){
    char* tmp = s;
    for (;*tmp;++tmp){
        *tmp = tolower((unsigned char) *tmp);
    }
    return s;
}*/
void search(hang *a, char *p, int count){
    hang *find = calloc(count+1, sizeof(hang));
    int f = 0;
    char *tmp;
    for(int i = 0; i<=count; i++){
        tmp = strdup(a[i]->id);
        printf("%s\n",tmp);
        char *sub = strstr(p,tmp);
        printf("%s\n",sub);
        if(strstr(tmp,p)){
            find[f] = a[i];
            f++;
        }
    }
    if(f == 0)printf("Khong ton tai mat hang!\n");
    else{
        for(int i=0; i<=count; i++){
            printf(" %s",find[i]->id);
            printf(" %30s",find[i]->name);
            printf(" %30s",find[i]->price);
            printf(" %30s\n",find[i]->quantity);
        }
    }
}
int check(hang *a, char *p, int count){
    char *tmp = NULL;
    for(int i = 0; i<=count; i++){
        tmp = strdup(a[i]->id);
        printf("%s\n",tmp);
        char *sub = strstr(p,tmp);
        printf("%s\n",sub);
        if(strstr(tmp,p)){
            return 1+i;
        }
    }
    return 0;
}
int main(int argc, char *argv[]){
    FILE *f_c = fopen(argv[1], "r");
    char c;
    int count = 1;
    while(!fscanf(f_c, "%c", &c)){
        if(c == '\n') count ++;
    }
    fclose(f_c);
    hang *list = calloc(count, sizeof(hang));
    FILE *f = fopen(argv[1], "r");
    char *line = NULL;
    int idx = 0;
    while(cgetline(&line,0,f)){
        list[idx] = malloc(sizeof(struct hang_t));
        add(line,list[idx]);
        idx++;
    }
    int choice = -1;
    while(choice != 3){
        function();
        printf("Nhap vao lua chon cua ban [1, 2, 3]: ");
        scanf("%d",&choice);
        if(choice == 1){
            printf("Ma so don hang: ");
            clear();
            line = NULL;
            cgetline(&line,0,stdin);
            search(list,line,count);
        }
        else if(choice == 2){
            char *id_tmp = NULL;
            printf("Nhap vao ma so mat hang: ");
            cgetline(&id_tmp,0,stdin);
            int po = check(list,id_tmp,count);
            int pq = 0;
            int quan;
            sscanf(list[po-1]->quantity, "%d", &quan);
            if(po){
                printf("Nhap vao so luong: ");
                scanf("%d",&pq);
                if(pq > quan) printf("Khong du");
                else{
                    Menu();
                    float a;
                    int b;
                    sscanf(list[po-1]->price,"%f", &a);
                    sscanf(list[po-1]->quantity,"%d", &b);
                    printf(" %30s",list[po-1]->name);
                    printf(" %30s",list[po-1]->price);
                    printf(" %30s",list[po-1]->quantity);
                    printf(" %30f\n",a*b);
                }
            }
        }
    }
    fclose(f);
}