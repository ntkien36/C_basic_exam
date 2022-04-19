#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "io.h"
typedef struct mhang_t{
    char *id_mhang;
    int price;
}*mhang;
typedef struct mhang_t1{
    char *id_mhang1;
    int number;
}*mhang1;
typedef struct dhang_t{
    char *id_dhang;
    int k;
    mhang1 *cap;
}*dhang;
int cmp(const void *a, const void *b){
    char *p1 = (*(mhang*)a)->id_mhang;
    char *p2 = (*(mhang*)b)->id_mhang;
    return strcmp(p1,p2);
}
int findprice(mhang *mathang, char *p, int l, int r){
    if(l<=r){
        int m = (l + r) / 2;
        if(strcmp(mathang[m]->id_mhang,p) == 0) return mathang[m]->price;
        else if(strcmp(mathang[m]->id_mhang,p) > 0) return findprice(mathang,p,l,m-1);
        else return findprice(mathang,p,m+1,r);
    }
    return 0;
}
int main(int argc, char *argv[]){
    clock_t start = clock();
    FILE *f = fopen(argv[1], "r");
    int n, idx = 0;
    char *line = NULL, *id, *price, *number;
    cgetline(&line,0,f);
    n = atoi(line);
    mhang *mathang = calloc(n,sizeof(mhang));
    while(cgetline(&line,0,f)){
        mathang[idx] = malloc(sizeof(struct mhang_t));
        id = strtok(line, " \n");
        price = strtok(NULL, " \n");
        mathang[idx]->id_mhang = strdup(id);
        mathang[idx]->price = atoi(price);
        idx++;
    }
    qsort(mathang,n,sizeof(mathang),cmp);
    fclose(f);
    FILE *f1 = fopen(argv[2], "r");
    int m;
    cgetline(&line,0,f1);
    m = atoi(line);
    idx = 0;
    dhang *donhang = calloc(m,sizeof(dhang));
    while(cgetline(&line,0,f1)){
        donhang[idx] = malloc(sizeof(struct dhang_t));
        id = strtok(line, " \n");
        number = strtok(NULL, " \n");
        donhang[idx]->id_dhang = strdup(id);
        donhang[idx]->k = atoi(number);
        donhang[idx]->cap = calloc(donhang[idx]->k,sizeof(mhang1));
        for(int i=0; i<donhang[idx]->k; i++){
            donhang[idx]->cap[i] = malloc(sizeof(struct mhang_t1));
            id = strtok(NULL, " \n");
            donhang[idx]->cap[i]->id_mhang1 = strdup(id);
            number = strtok(NULL, " \n");
            donhang[idx]->cap[i]->number = atoi(number);
        }
        idx++;
    }
    fclose(f1);
    int price_bill[m];
    for(int i=0; i<m; i++){
        price_bill[i] = 0;
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<donhang[i]->k; j++){
            price_bill[i] += findprice(mathang,donhang[i]->cap[j]->id_mhang1,0,n-1) * (donhang[i]->cap[j]->number);
        }
    }
    int first = 0, second = 0, third = 0;
    int idx1 = -1, idx2 = -1, idx3 = -1;
    for(int i=0; i<m; i++){
        if (price_bill[i] > first)
        {
            third = second;
            second = first;
            first = price_bill[i];
            idx3 = idx2;
            idx2 = idx1;
            idx1 = i;
        }
        else if (price_bill[i] > second)
        {
            third = second;
            second = price_bill[i];
            idx3 = idx2;
            idx2 = i;
        }
 
        else if (price_bill[i] > third)
            third = price_bill[i];
            idx3 = i;
    }
    printf("%s %d\n", donhang[idx1]->id_dhang,first);
    printf("%s %d\n", donhang[idx2]->id_dhang,second);
    printf("%s %d\n", donhang[idx3]->id_dhang,third);
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thoi gian chay: %lf\n", cpu_time_used);
    return 0;
}