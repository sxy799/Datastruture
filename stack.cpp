#include <stdio.h>
#include <stdlib.h>

typedef struct  Stack{
    int *data;
    int size;
    int top;
}Stack;

Stack* init(int );
int push(Stack *,int );
int pop(Stack *);
int top(Stack *);
int expand(Stack *s);
int empty(Stack *);
void clear(Stack *);


int main(){
	Stack *s = init(4);
	int op,val;
	while (~scanf("%d",&op)){
		switch(op){
			case 1 : 
               scanf("%d",&val);
			   push(s,val);
			   printf("%d  push Stack \n",val);
			   break;
            case 2 :
               pop(s);
              break;
            case 3:
               printf("top %d\n",top(s));
               break;
            default:
              fprintf(stderr,"operater error !\n");
			  break;

		}
	}
	return 0;
}

Stack* init(int n){
  Stack *s  = (Stack *)malloc(sizeof(Stack) * 1);
  s->data = (int *)malloc(sizeof(int ) * n);
  s->top = -1;
  s->size = n;
  return s;
}

int expand(Stack *s){
	int *temp = (int *) realloc (s->data,s->size * 2 * sizeof(int));
	if (temp == NULL) return 0;
	  s->data = temp;
	  //printf("expand \n");
	  return 1;
}

int push(Stack *s,int val){
   if (s->top == s->size -1 ) {
   	if (expand(s) == 0) return 0;
   }
   s->top += 1;
   s->data[s->top] = val;
   return 1;
}

int pop(Stack *s){
    if (empty(s) ) return 0;
    s->top -= 1;
    return 1;
}

int top(Stack *s){
	if (empty(s) ) return 0;
    return s->data[s->top];
}
int empty(Stack *s){
	return s->top == -1;
}
void clear(Stack *s){
   if (s== NULL) return ;
   free(s->data);
   free(s);
   return ;
}

