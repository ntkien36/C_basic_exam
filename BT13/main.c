#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "io.h"
typedef struct mhang_t{
    char *id1;
    char *id2;
}*mhang;

int cmp1(const void *a, const void *b){
    char *p1 = (*(mhang*)a)->id2;
    char *p2 = (*(mhang*)b)->id2;
    return strcmp(p1,p2);
}
int cmp2(const void *a, const void *b){
    char *p1 = (*(mhang*)a)->id1;
    char *p2 = (*(mhang*)b)->id1;
    return strcmp(p1,p2);
}

int findmhang(mhang *hang, char *p, int l, int r){
    if(l<=r){
        int m = (l + r) / 2;
        if(strcmp(hang[m]->id2,p) == 0) printf("%s",hang[m]->id1);
        else if(strcmp(hang[m]->id2,p) > 0) return findmhang(hang,p,l,m-1);
        else return findmhang(hang,p,m+1,r);
    }
    return 0;
}

int findcompany(mhang *hang, char *p, int l, int r){
    if(l<=r){
        int m = (l + r) / 2;
        if(strcmp(hang[m]->id1,p) == 0) printf("%s",hang[m]->id2);
        else if(strcmp(hang[m]->id1,p) > 0) return findcompany(hang,p,l,m-1);
        else return findcompany(hang,p,m+1,r);
    }
    return 0;
}
int main(int argc, char *argv[]){
    clock_t start = clock();
    char mode[2];
    strcpy(mode,argv[1]);
    FILE *f = fopen(argv[3], "r");
    int n, idx = 0;
    char *line = NULL, *id1, *id2, *tmp;
    cgetline(&line,0,f);
    n = atoi(line);
    mhang *hang = calloc(n,sizeof(mhang));
    while(cgetline(&line,0,f)){
        hang[idx] = malloc(sizeof(struct mhang_t));
        id1 = strtok(line, " \n");
        id2 = strtok(NULL, " \n");
        hang[idx]->id1 = strdup(id1);
        hang[idx]->id2 = strdup(id2);
        idx++;
    }
    //printf("%s",mode);
    if(strcmp(mode,"f1")==0){
        tmp = argv[2];
        qsort(hang,n,sizeof(hang),cmp1);
        findmhang(hang,tmp,0,n-1);
    }
    else if(strcmp(mode,"f2")==0){
        tmp = argv[2];
        qsort(hang,n,sizeof(hang),cmp2);
        findcompany(hang,tmp,0,n-1);
    }
    fclose(f);
    return 0;
}
