#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <bits/stdc++.h>
using namespace std;


typedef struct Node{
	char data;
    struct Node* father;
    struct Node* child;
    struct Node* brother;
}Node;

typedef struct Tree{
    char *data;
    int amt;
    int child_pos;
}Tree;

queue<Node*>q;

Node* GetNewNode(){
	Node *p = (Node*)malloc(sizeof(Node));
	p->father = (Node*)malloc(sizeof(Node));
	p->child = (Node*)malloc(sizeof(Node));
	p->brother = (Node*)malloc(sizeof(Node));
	p->brother = p->father = p->child = NULL;
	return p;
}
Node* build_Tree(Node *node ,char* str){
	for (int i = 0; i < strlen(str); i++){
      if(node->child != NULL){
   	       Node* tmp = node->child;
   	       int found = 1;
   	       while (tmp->data != str[i]){
   	  	     tmp = tmp->brother;
   	  	     if(tmp == NULL) {
   	  	 	 found = 0;
   	  	 	 break;
   	  	   }
   	   } 
   	   if(found == 0){
   	  	 printf("not found \n");
         Node *p = GetNewNode();
         p->data = str[i];
         p->father = node;
         tmp->brother = p;
   	   }
   	   else if(found == 1){
   	     printf("found \n");
         node = node->child;
   	   }
    }else{
      printf("null \n");
      Node *p = GetNewNode();
      p->data = str[0];
      p->father = node;
      node->child = p;	
    }
  }
  return node;
}

void BFS(Node *node){
	while (!q.empty()){
		Node* fir = q.front();
		q.pop();
        printf("%c ",fir->data);
	    while (fir->child){
          printf("%c ",fir->child->data);
          q.push(fir->child);
          Node *tmp = fir->child->brother;
          while (tmp){
       	    printf("%c ",tmp->data);
       	    q.push(tmp);
         	tmp = tmp->brother;
          }
      } 
	}
}

int main(){
    int n,m;
    Node* node = GetNewNode();
    node->data = '0';
    scanf("%d %d",&n,&m);
    while (n--){
    	char str[50];
    	scanf("%s",str);
    	printf("you input : %s \n", str);
    	node = build_Tree(node,str);
    }
    q.push(node);
    BFS(node);
    
	return 0;
}
/*
4 4 
her
he
she
shrs

hers
he
ssss
she

*/