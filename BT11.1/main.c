#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cgetline.c"

typedef struct hang_t{
    char *maso;
    char *ten;
    char *giatien;
    char *soluong;
    int x;
}*hang;


void Menu(){
    printf("Chuong trinh \n");
    printf("1. Xem thong tin mat hang\n");
    printf("2. Tao don hang\n");
    printf("3. Thoat\n");
}
void Headline(){
    printf(" %25s", "Ma so");
    printf(" %25s","Ten hang");
    printf(" %25s","Gia tien");
    printf(" %25s\n\n","So luong trong kho");
}    
void clear(void){
    while(getchar() != '\n');
}
void Add(hang a, char *maso, char *ten, char *giatien, char *soluong, int q){
    a->maso = strdup(maso);
    a->ten = strdup(ten);
    a->giatien = strdup(giatien);
    a->soluong = strdup(soluong);
    a->x = q;
}
void print(hang a){
    printf("%25s", a->maso);
    printf("%25s",a->ten);
    printf("%25s",a->giatien);
    printf("%25s\n",a->soluong);

}
void printlist(hang *a, int count){
    int idx = 0;
    for(int i=0; i<count; i++){
        if(a[i]->x){
            printf("%d  ",idx+1);
            print(a[i]);
            idx++;
        }
    }
}
void process(char *line, hang a, int q){
    char *maso;
    char *ten;
    char *giatien;
    char *soluong;
    maso = strtok(line," \n");
    ten = strtok(NULL," \n");
    giatien = strtok(NULL," \n");
    soluong = strtok(NULL," \n");
    Add(a, maso, ten, giatien, soluong, q);
}
void Search_maso(hang *a, char *p, int n){
    hang *find = calloc(n, sizeof(hang));
    int f = 0;
    char *tmp;
    for(int i=0; i<n; i++){
        tmp = strdup(a[i]->maso);
        if(strstr(tmp,p)){
            find[f] = a[i];
            f++;
        }
    }
    if(f==0) printf("Khong tim thay mat hang!");
    Headline();
    printlist(find,f);
    free(find);
} 

typedef struct hang_t{
    char *maso;
    char *ten;
    char *giatien;
    char *soluong;
    int x;
}*hang;

int main(int argc, char *argv[])
{
     if(argc != 2){
        return 1;
    }
    FILE *f = fopen(argv[1], "r"); 
    if(!f){
        printf("Loi mo tep %s \n",argv[1]);
        return 1;
    }
    int count = 0;
    char *line = NULL;
    hang *list = calloc(count, sizeof(hang));
    while(cgetline(&line,1,f)){
        count++;
        list = (hang*)realloc(list,count*sizeof(hang));
        list[count-1] = malloc(sizeof(struct hang_t));
        process(line,list[count-1],1);
    }
    fclose(f);
    int choice = 0;
    char str[1000];
    for(;;){
        printf("\n");
        Menu();
        printf("Nhap vao lua chon cua ban [1, 2, 3, 4, 5]: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Nhap ma so mat hang can tim: ");
                scanf("%s",str);
                Search_maso(list,str,count);
                break;
            
            case 2:
            break;
            case 3:
            clear();
            printf("\nBan da chon thoat chuong trinh!");
            free(list);
            return 0;


        }
    }
}
