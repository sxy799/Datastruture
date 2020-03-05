#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define swap(x,y){\
__typeof(x)tmp = x;\
x = y;\
y = tmp;\
}

void insert_sort(int *num,int n){
   for (int i = 1; i < n; i++){
   	for (int j = i-1; j >= 0; j--){
   		if (num[j+1] < num[j]) {
   			swap(num[j],num[j+1]); // yidong
   		}
   		else break;
   	}
   }
   return ;
}

void insert_sort_op(int *num,int n){/// error
	int ind = 0;
	for (int i = 1; i < n; i++){
		if (num[i] < num[ind]) ind = i;
	}
	while(ind){
		swap(num[ind],num[ind-1]);
		--ind;
	}
  for (int i = 2; i < n; i++){
   	 for (int j = i; num[j] < num[j-1]; j--){
   			swap(num[j-1],num[j]); // yidong
   	  }
  }
  //return ;
}

void bubble_sort(int *num,int n){
	int times ;
    for (int i = 0; i < n-1 && times; i++){
    	times = 0;
    	for (int j = 0; j < n - i - 1; j++){
    		if (num[j] > num[j+1]){
    			swap(num[j],num[j+1])
    			times ++;
    		}
    	}
    }
	return ;
}

void Merge_sort(int *num,int l,int r){
     if (l == r) return ;
     int mid = (l + r) >> 1;
     Merge_sort(num,l,mid);
     Merge_sort(num,mid+1,r);

     int *tmp = (int *)malloc(sizeof(int) *(r - l +1));
     int ind1 = l;
     int ind2 = mid+1;
     int k =0;
     while (ind1 <= mid || ind2 <= r){
     	if (ind2 > r || (ind1 <= mid && num[ind1] <= num[ind2])){
     		tmp[k++] = num[ind1++];
     	}else {
     		tmp[k++] = num[ind2++];
     	}
     }
    memcpy(num+l,tmp,sizeof(r - l + 1));
    free(tmp);
}

void select_sort(int *num,int n){
	for (int i=0; i<n-1; i++){
		int ind = i;
		for (int j = i+1; j < n; j++){
			if (num[j] < num[ind]) ind = j;
		}
		swap(num[i],num[ind]);
	}
}
void quick_sort(int *num,int l,int r){///3n+3m+2
	if (l >= r) return ;
	int x = l,y = r,z = num[l];
	 while (x < y){
      while(x < y && num[y] >= z) y--;
      if(x < y) num[x] = num[y],x++;
      while (x < y && num[x] <= z) x++;
      if (x < y)num[y] = num[x],y--;
	}
	num[x] = z;
	quick_sort(num,l,x-1);
	quick_sort(num,x+1,r);
	return;
}
void quick_sort_op(int *num,int l,int r){///n+m+1
    if (l >= r) return ;
    int x = l,y = r,z = num[(l+r)>>1];
    do{
      while (num[x] < z) ++x;
      while (num[y] > z) --y;
      if (x <= y){
        swap(num[x],num[y]);
        ++x,--y;
      }
    }while (x <= y);
    //num[x] = z;
    quick_sort_op(num,l,y);
    quick_sort_op(num,x,r);
    return;
}

void quick_sort_op2(int *num,int l,int r){///n+m+1
    while (l < r ){
      int x = l,y = r,z = num[(l+r)>>1];
      do{
        while (num[x] < z) ++x;
        while (num[y] > z) --y;
        if (x <= y){
          swap(num[x],num[y]);
          ++x,--y;
        }
      }while (x <= y);
      quick_sort_op2(num,x,r);
      r = y;
    }
    return;
}
void count_sort(int *num,int n){
	#define MAX_N 1000
	int *temp = (int *)calloc(MAX_N + 1 ,sizeof(int));
	for (int i = 0; i < n; i++){
       temp[num[i]]++;
	}
	for (int i = 0; i <= MAX_N; i++){
		if (temp[i] == 0) continue;
		while (temp[i]--){
			printf("%d ", i);
		}
	}
	printf("\n");
	free(temp);
	#undef MAX_N
	return ;
}
void radix_sort(int *num,int n){
	#define MAX_N 65536
	int* cnt = (int *)calloc(MAX_N + 1, sizeof(int));
	int *temp = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
    	cnt[(num[i] & 65535)+1] += 1; 
    }
    for (int i = 1; i <= 65535; i++){
    	cnt[i] += cnt[i-1];
    }
    for (int i = 0; i<n; i++){
    	temp[cnt[num[i] & 65535]++] = num[i];///important 
    }
    int *p = temp;
    temp = num;
    num = p;
    memset(cnt,0,sizeof(cnt));
    for (int i = 0; i < n; i++){
    	cnt[((num[i]>>16) & 65535)+1] += 1; 
    }
    for (int i = 1; i <= 65535; i++){
    	cnt[i] += cnt[i-1];
    }
    for (int i = 0; i<n; i++){
    	temp[cnt[(num[i]>>16) & 65535]++] = num[i];///important 
    }
    #undef MAX_N
    return ;
}

int *num = (int *)malloc(sizeof(int) * 20);

void OutPut(){
    for (int i = 0; i < 20 ; i++){
        printf("%d ",num[i]);
    }
    printf("\n");
}

#define TEST(n,func){\
	for (int i = 0; i < n; i++){\
		num[i] = rand()%100 + 1;\
	}\
    OutPut();\
	func;\
	printf("%s : ", #func);\
	for (int i = 0; i < n; i++){\
		printf("%d ",num[i]);\
	}\
	printf("\n");\
}

int main(){
    srand(time(0));
    
  /*  TEST(20,bubble_sort(num,20));
    TEST(20,Merge_sort(num,0,19));
    TEST(20,select_sort(num,20));*/
    TEST(20,quick_sort(num,0,19));
    TEST(20,quick_sort_op(num,0,19));
    TEST(20,quick_sort_op2(num,0,19));
    /*TEST(20,insert_sort(num,20));
    TEST(20,insert_sort(num,20));
    TEST(20,count_sort(num,20));
    TEST(20,radix_sort(num,20));
    TEST(20,insert_sort_op(num,20));*/
	return 0;
}
