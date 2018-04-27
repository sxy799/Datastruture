#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int Brute_Force(const char *str,const char *target){
	int len1 = strlen(str);
	int len2 = strlen(target);
	for (int i = 0; i <= len1 - len2; i++){
		int flag = 1;
		for (int j=0; j < len2 && flag; j++){
         flag = (str[i+j] == target[j]);
		}
		if (flag) return 1;
	}
	return 0;
}

int Kmp(const char *str, const char *target){
	int len1 = strlen(str);
	int len2 = strlen(target);
	int *next = (int *)malloc(sizeof(int) * len2);
    next[0] = -1;
    int j = -1,i;
    for (int i =1; i < len2; i++){
    	while (j != -1 && target[j+1] != target[i]){
    		j = next[j];
    	}
    	if (target[j+1] == target[i]){
    		j += 1;
    	}
    	next[i] = j;
    }
    j = -1,i = 0;
    while (i < len1){
       if (str[i] == target[j + 1]) j += 1, i += 1;
       else{
       	 while (str[i] != target[j+1] && j != -1){
       	 	j = next[j];
       	 }
       	 if (str[i] != target[j+1]){
       	 	i += 1;
       	 }
       }
       if (j + 1 == len2) break;
    }
	free(next);
	return (j+1 == len2);
}

int Sunday(const char *str, const char *target){
    int len1 = strlen(str);
    int len2 = strlen(target);
    int ch_ind[128] = {0};
    for (int i = 0; i < 128; i++){
    	ch_ind[i] = len2 + 1; //important
    }
    for (int i = 0; i < len2; i++){
    	ch_ind[target[i]] = len2 - i;
    }
    for (int i = 0; i<len1;){
    	int j = 0;
    	for (; j<len2 && str[i+j] == target[j]; j++);
    	if (j == len2) return 1;
        i += ch_ind[str[i + len2]];
    }
    return 0;
}

int Shift_And(const char* str, const char *target){
	int ch_code[128] = {0};
    int len2 = 0;
    for (len2; target[len2]; len2++){
       ch_code[target[len2]] |= (1<<len2);
    }
    int p = 0,limit = ((1 << (len2 - 1)) - 1);
    for (int i=0; str[i]; i++){
    	p = (p << 1 | 1) & ch_code[str[i]];
    	if (p > limit) return 1;
    }
    return 0;
}
int* p_leftadd(int *num,int n){
	for (int i = n-2; i >= 0; i--){
		num[i+1] = num[i];
	}
	num[0] = 1;
	/*printf("\n p_leftadd  \n");
	for (int i = 0; i<n; i++){
		printf(" num[%d]: %d   ",i,num[i] );
		if ((i+1) % 10 == 0) printf("\n");
	}*/
	return num;
}
int* p_and(int *p,int *ch_code,int n){
   for (int i = 0; i < n; i++){
      p[i] = p[i] * ch_code[i];
   }
   /*
   printf("\n p_and  \n");
	for (int i = 0; i<n; i++){
		printf(" num[%d]: %d   ",i,p[i] );
		if ((i+1) % 10 == 0) printf("\n");
	}*/
   return p;
}
int Shift_And_Improved(const char* str, const char *target){
	int len1 = strlen(str);
    int len2 = strlen(target);
    int ch_code[128][len2 + 5];
    for (int i = 0; i < 128; i++){
    	for (int j = 0; j < len2 + 5; j++){
    		ch_code[i][j] = 0;
    	}
    }
    for (int i = 0; i < len2; i++){
       ch_code[target[i]][i] = 1;
    }
    int *p = (int *)calloc(len2,sizeof(int));
    for (int i=0;str[i]; i++){
       p = p_leftadd(p,len2);
       p = p_and(p,ch_code[str[i]],len2);
       if (p[len2-1] == 1) return 1;
    }
    return 0;
}


#define TEST(func){\
	printf("%s = %d \n",#func,func);\
} 

int main(){
    char str1[100],str2[100];
    while (~scanf("%s%s",str1,str2)){
    	/*TEST(Brute_Force(str1,str2));
    	TEST(Kmp(str1,str2));
    	TEST(Sunday(str1,str2));*/
    	TEST(Shift_And(str1,str2));
    	TEST(Shift_And_Improved(str1,str2));
    }
	return 0;
}
/***
aabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa  bbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*/