# include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binary_search1(int *num,int n,int x){
	int head = 0,tail = n -1, mid;
	while (head <= tail){
		mid = (head + tail) >> 1;
		if (num[mid] == x) return mid;
		if (num[mid] < x) head = mid+1;
		else tail = mid -1;
	}
	return -1;
}

int binary_search2(int *num,int n){
   int head = -1 ,tail = n-1,mid;
   while (head < tail){
   	  mid = (head + tail + 1) >> 1;
   	  if (num[mid] == 0) tail = mid - 1;
   	  else head = mid;
   }
   return head;
}

int binary_search3(int* num,int n){
	int head = 0,tail = n,mid;
	while (head < tail){
		mid = (head + tail ) >> 1;
		if (num[mid] == 0) head = mid + 1;
		else tail = mid;
	}
	if (head == n) return -1;
	return head;
} 

double f(double x){
  static int  a = 3.0,b = 2.0,c = 9.0;
  return a * x * x + b *x + c;
   
}

double ternary_search(double (*func)(double)){
	#define EPSLON 1e-7
  double L = -1000, R = 1000, m1,m2;
  while (fabs(L - R) > EPSLON){
  	m1 = (R - L)/3.0 + L;
  	m2 = L + 2*(R - L)/3.0;
  	if (func(m1) > func(m2)) L = m1;
  	else R = m2;
  }
  return L;
  #undef EPSLON
}

int main(){
     
     int num1[] = {1,2,3,4,5};
     printf("binary_search1(4) : %d \n",binary_search1(num1,5,4));

     int num2[] = {0,0,0,0,0,0,0,0,0,0};
     printf("binary_search2():%d\n",binary_search2(num2,10));

     int num3[] = {0,0,0,0,0,0,0,0,0,0};
     printf("binary_search3():%d\n",binary_search3(num3,10));

    printf("ternary_search() : %lf\n",ternary_search(f));
	return -1;
}
