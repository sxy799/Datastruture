#include <stdio.h>
#include <stdlib.h>

#define MC(T,n)(T*)malloc(sizeof(T) * n)
#define CC(T,n)calloc(n,sizeof(T));


typedef struct TrieNode{
	 int flag;
   struct  TrieNode *next[256];
}TrieNode,*Trie;

TrieNode *GetNewNode(){
   TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode));
   p->flag = 0;
   for (int i = 0; i < 26; i++){
   	p->next[i] = NULL;
   }
   return p;
}

void clear(Trie tree){
	if (tree == NULL) return;
	for (int i = 0; i < 26; i++){
		if (tree->next[i] == NULL) continue;
		clear(tree->next[i]);
	}
	free(tree);
	return ;
}

int insert(Trie tree,const char * str){
	TrieNode *p = tree;
	int times = 0;
	while (str[0]){
		if (p->next[str[0] - '0'] == NULL){
			p->next[str[0] - '0'] = GetNewNode();
			times++;
		}
		p = p->next[str[0] - '0'];
		str++;
	}
	p->flag = 1;
	return times;
}

int search(Trie tree,const char * str){
	TrieNode * p = tree;
	while (str[0] && p){
		p = p->next[str[0] - '0'];
		str++;
	}
    return p && p->flag;
}


int main(){
    int n,m,node_ct;;
    char str[100];
    Trie tree = GetNewNode();
    scanf("%d %d",&n,&m);
    while (n--){
    	scanf("%s",str);
    	node_ct += insert(tree,str);
    }
    while (m--){
    	scanf("%s",str);
    	printf("%d : %s \n", search(tree,str),str);
    }
	return 0;
}
/*
3 1
a
aa
aaa
aaaaa
*/