#include <stdio.h>
#include <stdlib.h>
/**  this PriorQueue's index is 1 start   */
#define swap(a,b){\
__typeof(a) tmp = a;\
a = b;\
b = tmp;\
}

typedef struct PriorityQueue{
    int *data;
    int n,size;
}PriorityQueue;

PriorityQueue* init(int n){
    PriorityQueue *p = (PriorityQueue *)malloc(sizeof(PriorityQueue*)*1);
    p->n = 0;
    p->size = n+1;
    p->data = (int *)malloc(sizeof(int) * (n+1));
    return p;
}

void clear(PriorityQueue * p){
    if (p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}
int push(PriorityQueue *p, int val){
    if (p->n + 1 >= p->size) {
        return 0;
    }
    p->n += 1;
    p->data[p->n] = val;
    int ind = p->n;
    //maintain
    while (ind > 1 && p->data[ind >> 1] < p->data[ind]){
        swap(p->data[ind >> 1],p->data[ind]);
        ind = ind >> 1;
    }
    return 1;
}
int empty(PriorityQueue *p){
    return p->n == 0;
}

int pop(PriorityQueue *p){
   if (empty(p)){
    return 0;
   }
   p->data[1] = p->data[p->n];
   p->n -= 1;
   //maintain
   int ind = 1;
   while (ind << 2 <= p->n){
      int ind1 = ind * 2;
      int ind2 = ind * 2 + 1;
      int max_ind = ind;//denote symbol of break ind2 <= p->n && 
      if ( p->data[ind1] > p->data[ind]) max_ind = ind1;
      if (ind2 <= p->n && p->data[ind2] > p->data[ind]) max_ind = ind2;
      if (max_ind == ind) break;
      swap(p->data[ind],p->data[max_ind]);
      ind = max_ind;
   }
   return 1;
}

int front(PriorityQueue *p){
    return  p->data[1];
}
int main()
{
   int n;
   scanf("%d",&n);
   PriorityQueue *p = init(n);
   for (int i=0; i<n; i++){
    int num;
    scanf("%d",&num);
    push(p,num);
    printf("the front of PriorityQueue :%d \n",front(p));
   }
   while (!empty(p)){
    printf("element of PriorityQueue : %d \n",front(p));
    pop(p);
   }
   return 0;
}