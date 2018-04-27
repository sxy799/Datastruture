#include <stdio.h>
#include <stdlib.h>

#define DEFVALUE(n, defval) ((#n[0] ? n : defval))
#define init(n) __init(DEFVALUE(n, 10))

typedef struct Queue{
    int *data;
    int head,tail,length;
} Queue;

int expand(Queue*);
Queue *__init(int);
int push(Queue *,int);
void pop(Queue*);
int empty(Queue*);
void clear(Queue*);
void output(Queue *);


int main(){
	Queue *queue = init();
	int op,val;
	while (~scanf("%d",&op)){
		switch(op){
			case 1 : 
			  scanf("%d",&val);
			  printf("push return value : %d \n " ,push(queue,val));
			  break;

			case 2 :
			  pop(queue);
			  break;
			default :
			  fprintf(stderr,"operater error !");
			  break;
		}
		output(queue);
	}
	return 0;
}

int expand(Queue *q){
	int *temp = (int *) realloc (q->data,sizeof(int )*2*q->length);
	if (temp == NULL) return 0;
	  q->data = temp;
	  return 1;
}
Queue *__init(int n){
    Queue *q = (Queue *)malloc(sizeof(Queue) * 1);
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->tail = 0;
    q->head = 0;
    return q;
}

int push(Queue *q ,int val){
   if (q->tail == q->length){
   	   if (expand(q) == 0){
   	   	  return 0;
   	   }
   }
   q->data[q->tail] = val;
   q->tail++;
   return 1;
}
void pop(Queue *q){
	if (empty(q)){
		return ;
	}
	q->head++;
	return ;
}
int empty(Queue *q){
	return q->head == q->tail;
}
void clear(Queue *q){
    if (q == NULL) {
    	return ;
    }
    free(q->data);
	free(q);
}

void output(Queue *q)
{
	for (int i = q->head; i < q->tail; i++){
		printf("%d ",q->data[i]);
	}
	printf("\n");
}


