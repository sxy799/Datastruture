#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(x,y){\
__typeof(x)tmp = x;\
x = y;\
y = tmp;\
}

void quick_sort(int *num,int l,int r){
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
    num[x] = z;
    quick_sort(num,l,x);
    quick_sort(num,x,r);
    return;
}
int main()
{
    int n;
    scanf("%d",&n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i=0; i<n; i++){
      scanf("%d",&arr[i]);
    }
    quick_sort(arr,0,n-1);

    for (int i=0; i<n; i++){
        if(i != 0) printf(" ");
        printf("%d",arr[i]);
    }
    printf("\n");
    return 0;
}