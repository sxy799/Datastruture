#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

double calc(const char *str,int l,int r)
{
    printf("calc  l = %d  r = %d\n",l,r);
    int min_pos = -1, pri = INF,temp_pri = 0;
    for (int i=l; i < r; i++)
    {
        int cur_pri = INF + 1;
        switch(str[i])
        {
        case '(' :temp_pri += 100;break;
        case ')' :temp_pri -= 100;break;
        case '+' :
        case '-' :cur_pri = temp_pri + 1;break;
        case '*' :
        case '/' :cur_pri = temp_pri + 2;break;
        }
        if (cur_pri <= pri)
        {
            min_pos = i;
            pri = cur_pri;
        }
    }
   // printf(" ******* min_pos = %d \n",min_pos);
    if (min_pos == -1)
    {
        //printf(" num judge \n");
        double num = 0;
        while (str[l] == ' ' || str[l] == '(') l++;
        sscanf(str+l,"%lf",&num);
        //printf(" num  %lf \n",num);
        return num;
    }
    else
    {
        double a = calc(str,l,min_pos);
        double b = calc(str,min_pos+1,r);
        switch(str[min_pos])
        {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
        }
    }
    return 0.0;
}
int main()
{
    char str[500];
    int n;
    while (scanf("%s",str) != EOF)
    {
        getchar();
        printf("%.2lf\n",calc(str,0,strlen(str)));
    }
    return 0;
}
