#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_L 256

typedef struct sanpham{
	int n;
	char ma_so[MAX_L];
    char ten[MAX_L];
    float gia_tien;
    int so_luong;
} sanpham;
sanpham *don_hang;
sanpham mua_hang[MAX_L];

int max;

void docFile(FILE *f)
{
	int i;
	fscanf(f, "%d", &max);
	don_hang = (sanpham*)malloc(max * sizeof(sanpham));
	for(i = 0;i<max;i++)
	{
		fscanf(f, "%s %s %f %d", &don_hang[i].ma_so, &don_hang[i].ten, &don_hang[i].gia_tien, &don_hang[i].so_luong);
		//printf("%-30s%-30s%-30f%-30d\n", don_hang[i].ma_so, don_hang[i].ten, don_hang[i].gia_tien, don_hang[i].so_luong);
	}
}

int timkiem(char maso[])
{
	int i;
	for(i = 0;i<max;i++)
	{
		if(strcmp(maso, don_hang[i].ma_so)==0) 
		{
			return i;
		}	
	}
	return -1;
}

void xemtt()
{
	char maso[20];
	printf("Nhap ma so hang:");
	scanf("%s", maso);
	int vitri = timkiem(maso);
	if(vitri != -1)
	{
		printf("%-30s%-30s%-30.2f%-30d\n", don_hang[vitri].ma_so, don_hang[vitri].ten, don_hang[vitri].gia_tien, don_hang[vitri].so_luong);
	}
	else
	{
		printf("Khong tim thay don hang\n");
	}
}

void themdonhang()
{
	char maso[20];
	int soluong, count = 0;
	double tong = 0;
	int i;
	while(strcmp(maso, "STOP") != 0)
	{
		printf("Nhap ma so don hang:");
		scanf("%s", maso);
		if(strcmp(maso, "STOP") == 0)
		{
			break;
		}
		int vitri = timkiem(maso);
		if(vitri != -1)
		{
			printf("Nhap vao so luong don hang: ");
			fflush(stdin);
			scanf("%d", &soluong);
			fflush(stdin);
			if(soluong <= don_hang[vitri].so_luong)
			{
				//mua_hang = (sanpham*)malloc(sizeof(sanpham));
				mua_hang[count] = don_hang[vitri];
				mua_hang[count].so_luong = soluong;
				count++;
			}
			else
			{
				printf("Vuot qua so luong hien co\n");
			}
		}
		else
		{
			printf("Khong tim thay mat hang\n");
		}
	}
	printf("%-20s%-50s%-20s%-20s%-20s\n", "STT", "Mat hang", "Don gia", "So luong", "Thanh tien");
	for(i = 0;i<count;i++)
	{
		printf("%-20d%-50s%-20.2f%-20d%-20.2f\n", i+1, mua_hang[i].ten, mua_hang[i].gia_tien, mua_hang[i].so_luong, mua_hang[i].gia_tien*mua_hang[i].so_luong);
		tong += mua_hang[i].gia_tien*mua_hang[i].so_luong;
	}
	printf("\n---------------------------------------\n");
	printf("Tong tien: %.2lf\n", tong);
}

int main(int argc, char *argv[])
{
	FILE *f;
	f = fopen(argv[1], "r");
	docFile(f);
	int choice = 0;
	while(choice != 3)
	{
		printf("1. Xem thong tin mat hang\n");
		printf("2. Tao don hang\n");
		printf("3. Thoat\n");
		printf("Nhap: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				xemtt();break;
			case 2:
				themdonhang();break;
			default:
				break;
		}		
	}
	return 0;
}



