#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
	char data;
	int freq;
	struct Node *lchild,*rchild;
}Node;

#define hswap(x,y){\
Node* p = (Node *)malloc(sizeof(Node));\
p = huffman_node[x];\
huffman_node[x] = huffman_node[y];\
huffman_node[y] = p;\
}


Node* GetNewNode(){
	Node* p = (Node*)malloc(sizeof(Node));
	p->freq = p->data = 0;
	p->lchild = p->rchild = 0;
	return p;
}
Node* BuildTree(Node ** huffman_node,int n){
	Node* root;
	for (int i=0;i < n; i++){
		int ind1 = n - i - 1;
		int ind2 = n - i - 2;
		if (huffman_node[ind1] > huffman_node[ind2]){
			hswap(ind1,ind2);
		}
		for (int j=0; j < ind2; j++){
             if (huffman_node[j] < huffman_node[ind2]){
             	hswap(j,ind2);
             }
             if (huffman_node[ind2] < huffman_node[ind1]){
             	hswap(ind1,ind2);
             }
		}
		root = GetNewNode();
		root->freq = huffman_node[ind1]->freq + huffman_node[ind2]->freq;
		root->lchild = huffman_node[ind1];
		root->rchild = huffman_node[ind2];
	}
	return root;
}

void Encode(Node* root,int k,char *str){
	if (root == NULL) return ;
	if (root->lchild == NULL){
		str[k] = '\0';
		printf("letter:%c huffmancode: %s\n",root->data,str);
		return ;
	}
	str[k] = '0';
	Encode(root,k+1,str);
	str[k] = '1';
	Encode(root,k+1,str);
}

int main(){
	int n,freq;
	char data[10];
	scanf("%d",&n);
	printf("n = %d\n",n );
	Node ** huffman_node = (Node**)malloc(sizeof(Node*) * n);
	 huffman_node[0]->freq = n;
	/*for (int i = 0; i < n; i++){
		scanf("%s%d",data,&freq);
		printf("data = %s freq = %d\n",data,freq);
        huffman_node[i]->freq = freq;
        printf("data = %s freq = %d\n",data,freq);
	}
    /*
	Node* root = BuildTree(huffman_node,n);
	char encode[100];
	Encode(root,0,encode);*/
	return 0;
}

