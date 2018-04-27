#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


#define swap(x,y){\
__typeof(x) tmp = x;\
 x = y;\
y = tmp;\
}

#define TEST(n,func){\
int *num = (int *) malloc(sizeof(int) * n);\
for(int i = 0; i < n; i++){\
num[i] = rand() % 100;\
}\
func;\
printf("%s : ",#func);\
for (int i = 0; i < n ;i++){\
printf("%d ",num[i]);\
   }\
printf("\n");\
  }


void bubble_sort(int *num,int n){
    int flag = 1;
    for (int i = 0; i < n - 1 && flag ; i++ ){
        flag = 0;
        for (int j = 0; j < n - 1 - i; j++){
            if (num[j+1] <  num[j]){
                swap(num[j+1],num[j]);
                flag ++;
            }
        }
    }
    return;
}

void insert_sort(int *num, int n){
    for (int i = 0; i < n; i++){
        for (int j = i - 1; j >= 0; j-- ){
            if (num[j + 1] < num[j]) { swap(num[j+1],num[j]);}
            else
              break;
        }
    }
    return ;
}

void insert_sort_op(int *num, int n){
    int ind = 0;
    for (int i = 1; i < n; i++){
        if (num[i] < num[ind]) ind = i;
    }
    while (ind){
        swap(num[ind],num[ind - 1]); 
        ind--;
    }
    for (int i = 0; i < n-1 ; i++){
        for (int j = i; num[j+1] < num[j]; j--){
            swap(num[j+1],num[j]);
        }
    }
    return ;
}


void Merge_sort(int *num,int l,int r){
    if (l == r) return ;
    int mid = (l + r) >> 1;
    Merge_sort(num,l,mid);
    Merge_sort(num,mid + 1,r);

    int *tmp = (int *) malloc(sizeof(int) * (r - l + 1));
    int ind1 = l;
    int ind2 = mid + 1;
    int k= 0;
    while (ind1 <=mid || ind2 <= r){
        if (ind2 > r || (num[ind1] <= num[ind2] && ind1 <= mid)){
            tmp[k++] = num[ind1++];
        }else {
            tmp[k++] = num[ind2++];
        }
    }
    memcpy(num+l,tmp,sizeof(int) * (r - l + 1));
    free(tmp);
}

void Merge_sort1(int *num, int n){
    for (int i = 2; i < n; i = i<<1){
         int len = i >> 1;
         for (int j = 0; j < n; j += i){
            int ind1 = j,r;
            int mid = j + len;
            int ind2 = j + len + 1;
            if (i + j > n) r = n;
            else  r = j + i;
            int k= 0;
            int *tmp = (int *) malloc(sizeof(int) * (i));
             printf("ind1 : %d, ind2 : %d, r : %d \n",ind1,ind2,r);
            while (ind1 <=mid || ind2 <= r){
                if (ind2 > r || (num[ind1] <= num[ind2] && ind1 <= mid)){
                 tmp[k++] = num[ind1++];
                }else {
                 tmp[k++] = num[ind2++];
                }
             }
             printf("tmp :");
             for (int c = 0; c < k; c++){
                 printf("%d ",tmp[c]);
             }
             printf("\n");
             k = 0;
       //       memcpy(num+j,tmp,sizeof(int) * (i));
             for (int ii = j; ii < j+i ; ii++){
                 num[ii] = tmp[k++];
             }
         free(tmp);
        }
    }
return ;
}

void select_sort(int *num,int n){
    int ind = 0;
    for (int i = 0; i < n; i++){
        ind = i;
        for (int j = i + 1 ; j < n; j++){
          if (num[j] < num[ind]) ind = j;
        }
        swap(num[i],num[ind]);
    }
    return ;
}

void quick_sort(int *num,int l,int r){
    if (l >= r) return;
    int x = l, y = r, z = num[l];
    while(x < y){
        while (x < y && num[y] >= z) y--;
        if (x < y) num[x] = num[y],x++;
        while(x < y && num[x] <= z) x++;
        if (x < y) num[y] = num[x],y--;
    }
    num[x] = z;
    quick_sort(num,l,x-1);
    quick_sort(num,x+1,r);
    return ;
}


void quick_sort_op(int *num,int l,int r){
    if (l >= r) return;
    int x = l, y = r, z = num[(l + r) >>  1];
    do{
        while (num[x] < z) x++;
        while (num[y] > z) y--;
        if (x < y){
            swap(num[x],num[y]);
            x++,y--;
        }
    }while (x < y);
    num[x] = z;
    quick_sort_op(num,l,x);
    quick_sort_op(num,x,r);
    return ;
}

void quick_sort_op2(int *num, int l,int r){
    if (l >= r) return ;
    while (l < r){
      int x = l, y = r, z = num[(l + r) << 1];
     do{
        while (num[x] < z) x++;
        while (num[y] > z) y--;
        if (x < y){
            swap(num[x],num[y]);
            x++,y--;
        }
      }while(x < y);
   
     num[x] = z  ;
     quick_sort_op2(num,l,x);
      r = y;
    }
}

void  radix_sort(int *num,int n){
    #define MAX_N  65536
    int *cnt = (int*) malloc(sizeof(int) * MAX_N);
    int *tmp = (int *)malloc(sizeof(int) *MAX_N);
    memset(cnt,0,sizeof(cnt));
    for (int i = 0; i < n; i++){
        cnt[(num[i] & 65535) + 1 ] += 1;
    }
    for (int i = 1; i < MAX_N; i++){
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i  < n; i++){
        tmp[cnt[num[i] & 65535]++] = num[i];
    }

    int *p = tmp;
    tmp = num;
    num = p;
    memset(cnt,0,sizeof(cnt));
    for (int i = 0; i < n; i++){
        cnt[((num[i]>>16) & 65535) + 1 ] += 1;
    }
    for (int i = 1; i < MAX_N; i++){
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i <  n; i++){
        tmp[cnt[(num[i] >> 16) & 65535]++] = num[i];
    }
    #undef  MAX_N
    return ;
}


int main(){
   srand(time(0));
    TEST(20,Merge_sort(num,0,19));
//    TEST(20,quick_sort_op(num,0,19));
    /*TEST(20,quick_sort_op2(num,0,19));*/
    TEST(20,insert_sort_op(num,20));
    TEST(20,Merge_sort1(num,20));
    return 1;
}
