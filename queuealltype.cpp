#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define init(T) __init(sizeof(T),10)
#define push(q,val) (__push(q,&val))
#define front(q,T) (*((T*) __front(q)))

typedef struct Queue{
    void *data;
    int data_size;
    int head,tail,length;
} Queue;

int expand(Queue*);
Queue *__init(int,int);
int __push(Queue *,void *);
void pop(Queue*);
int empty(Queue*);
void clear(Queue*);
void * __front(Queue *);


int main(){
	Queue *queue = init(int);
	int op,val;
	while (~scanf("%d",&op)){
		switch(op){
			case 1 : 
			  scanf("%d",&val);
			  push(queue,val);
			  break;
			case 2 :
			  pop(queue);
			  break;
			case 3:
			  printf("front value : %d\n",front(queue,int));
			  break;
			default :
			  fprintf(stderr,"operater error !");
			  break;
		}

	}
	return 0;
}

int expand(Queue *q){
	void *temp = (int *) realloc (q->data,q->data_size * 2 * q->length);
	if (temp == NULL) return 0;
	  q->data = temp;
	  return 1;
}
Queue *__init(int data_size,int n){
    Queue *q = (Queue *)malloc(sizeof(Queue) * 1);
    q->data = malloc(data_size * n);/// moren  void *
    q->length = n;
    q->tail = 0;
    q->head = 0;
    q->data_size = data_size;
    return q;
}

int __push(Queue *q ,void *val_p){
   if (q->tail == q->length){
   	   if (expand(q) == 0){
   	   	  return 0;
   	   }
   }
   char *data = (char *)(q->data);
   memcpy(data + q->tail * q->data_size , val_p,q->data_size);
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
    if (empty(q)) {
    	return ;
    }
    free(q->data);///malloc he free neibushixian  malloc calloc 
	free(q);
}
void * __front(Queue *q){
    if (q == NULL) return NULL;
    return (char *)(q->data) + q->head * q->data_size;
}