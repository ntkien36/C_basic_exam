#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "io.h"

typedef struct hang_t{
    char *id;
    int price;
}*hang;

typedef struct mhang_t{
    char *id_mhang1;
    int number;
}*mhang;

typedef struct dhang_t{
    char *id_dhang;
    int k;
    mhang *mh;
}*dhang;

int searchprice(hang *mathang, char *p, int n){
    for(int i=0; i<n; i++){
        if(strstr(mathang[i]->id,p)) return mathang[i]->price;
    }
    return 0;
}

int main(int argc, char *argv[])
{
     if(argc != 3){
        return 1;
    }
    clock_t start = clock();
    FILE *f = fopen(argv[1], "r"); 
    if(!f){
        printf("Loi mo tep %s \n",argv[1]);
        return 1;
    }
    int n, m, idx = 0, q, idx_bill = 0;
    char *line = NULL, *id, *tmp, *price,*number;
    cgetline(&line,0,f);
    n = atoi(line);
    hang *list = calloc(n,sizeof(hang));
    while(cgetline(&line,0,f)){
        id = strtok(line, " \n");
        price = strtok(NULL, " \n");
        list[idx] = malloc(sizeof(struct hang_t));
        list[idx]->id = strdup(id);
        list[idx]->price = atoi(price);
        idx++;
    }
    fclose(f);

    FILE *f1 = fopen(argv[2], "r"); 
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
        donhang[idx]->mh = calloc(donhang[idx]->k,sizeof(mhang));
        for(int i=0; i<donhang[idx]->k; i++){
            donhang[idx]->mh[i] = malloc(sizeof(struct mhang_t));
            id = strtok(NULL, " \n");
            donhang[idx]->mh[i]->id_mhang1 = strdup(id);
            number = strtok(NULL, " \n");
            donhang[idx]->mh[i]->number = atoi(number);
        }
        idx++;
    }
    fclose(f1);
    //printf("%s",donhang[2]->mh[1]->id_mhang1);

    int total[m];
    for(int i=0; i<m; i++){
        total[i] = 0;
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<donhang[i]->k; j++){
            total[i] += searchprice(list,donhang[i]->mh[j]->id_mhang1,n) * (donhang[i]->mh[j]->number);
        }
    }
    int first = 0, second = 0, third = 0;
    int idx1 = -1, idx2 = -1, idx3 = -1;
    for(int i=0; i<m; i++){
        if (total[i] > first)
        {
            third = second;
            second = first;
            first = total[i];
            idx3 = idx2;
            idx2 = idx1;
            idx1 = i;
        }
        else if (total[i] > second)
        {
            third = second;
            second = total[i];
            idx3 = idx2;
            idx2 = i;
        }
        else if (total[i] > third)
            third = total[i];
    }
    printf("%s %d\n", donhang[idx1]->id_dhang,first);
    printf("%s %d\n", donhang[idx2]->id_dhang,second);
    printf("%s %d\n", donhang[idx3]->id_dhang,third);

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Thoi gian chay: %lf\n", cpu_time_used);
    return 0;
}



