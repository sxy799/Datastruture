#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    int flag,ind;
    struct TrieNode *next[26];
    struct TrieNode *fail;
    struct TrieNode *father;
} TrieNode, *Trie;

typedef struct DoubleArrayTrieNode {
    int n;
    int *base, *check;
} DoubleArrayTrieNode, *DATrie;

DATrie initDATrie(int n) {
    DATrie p = (DATrie)malloc(sizeof(DoubleArrayTrieNode) * 1);
    p->base = (int *)calloc(n, sizeof(int));
    p->check = (int *)calloc(n, sizeof(int));
    p->n = n;
    p->check[1] = -1;
    return p; 
}

TrieNode *getNewNode() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode) * 1);
    p->flag = 0;
    p->fail = NULL;
    for (int i = 0; i < 26; i++) {
        p->next[i] = NULL;
    }
    return p;
}

int insert(Trie tree, const char *str) {
    TrieNode *p = tree;
    int times = 0;
    while (str[0]) {
        if (p->next[str[0] - 'a'] == NULL) {
            p->next[str[0] - 'a'] = getNewNode();
            times += 1;
        }
        p = p->next[str[0] - 'a'];
        str++;
    }
    p->flag = 1;
    return times;
}

int search(Trie tree, const char *str) {
    TrieNode *p = tree;
    while (str[0] && p) {
        p = p->next[str[0] - 'a'];
        str++;
    }
    return p && p->flag;
}

int search_automatain(Trie ac_tree, const char *str) {
    int ret = 0;
    TrieNode *p = ac_tree,*q;
    while (str[0]) {
        while (p != NULL && p->next[str[0] - 'a'] == NULL) p = p->fail;
        if (p) p = p->next[str[0] - 'a'];
        else p = ac_tree;
        q = p;
        while (q) ret += q->flag,q = q->fail;
        str++;
    }
    return ret;
}

int transToDATrie(Trie ftree, int ind, DATrie ttree) {
    int val = 0, flag = 1, ret = ind;
    while (flag) {
        flag = 0;
        val += 1;
        for (int i = 0; i < 26; i++) {
            if (ftree->next[i] == NULL) continue;
            if (ttree->check[val + i] == 0) continue;
            flag = 1;
            break;
        }
    }
    if (ftree->flag) ttree->check[ind] = -ttree->check[ind];
    ttree->base[ind] = val;
    for (int i = 0; i < 26; i++) {
        if (ftree->next[i] == NULL) continue;
        ttree->check[val + i] = ind;
    }
    for (int i = 0; i < 26; i++) {
        if (ftree->next[i] == NULL) continue;
        int temp = transToDATrie(ftree->next[i], val + i, ttree);
        ret = (ret > temp ? ret : temp);
    }
    return ret;
}

void clear(Trie tree) {
    if (tree == NULL) return ;
    for (int i = 0; i < 26; i++) {
        if (tree->next[i] == NULL) continue;
        clear(tree->next[i]);
    }
    free(tree);
    return ;
}

void clearDATrie(DATrie tree) {
    if (tree == NULL) return ;
    free(tree->base);
    free(tree->check);
    free(tree);
    return ;
}

void build_automatain(Trie tree, int n) {
    if (tree == NULL) return ;
    tree->fail = NULL;
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode *) * (n+5));
    int head = 0, tail = 0;
    queue[tail++] = tree;
    while (head < tail) {
        TrieNode *p = queue[head++], *q;   
        for (int i = 0; i < 26; i++) {
            if (p->next[i] == NULL) continue;
            q = p->fail;
            while (q != NULL && q->next[i] == NULL) {//dont understand 
                q = q->fail;
            }
            if (q == NULL) q = tree;
            else q = q->next[i];
            p->next[i]->fail = q;
            queue[tail++] = p->next[i];
        }
    }
    free(queue);
    return ;
}
TrieNode* get_fail_pointer(TrieNode* node,int ind){
    if (node == NULL) return NULL;
    if (node->fail == NULL){
        node->fail = get_fail_pointer(node->father,node->ind);
    }
    if (node->fail == NULL) return  node;
    TrieNode *p = node->fail,*pre_p = node;
    while (p && p->next[ind] == NULL){
        if (p->fail == NULL){
            p->fail = get_fail_pointer(p->father,p->ind);
        }
    }
}
void build_automatain2(Trie tree){
  if (tree == NULL) return;
  for (int i = 0; i < 26; i++){
    if (tree->next[i] == NULL)continue;
    tree->next[i]->fail = get_fail_pointer(tree,i);
    build_automatain2(tree->next[i]);
  }
  return ;
}


int main(){
    int n, m, node_cnt = 0;
    char str[100];
    Trie tree = getNewNode();
    scanf("%d%d", &n, &m);
    while (n--) {
        scanf("%s", str);
        node_cnt += insert(tree, str);
    }
    printf("node_cnt : %d\n",node_cnt);
    build_automatain(tree, node_cnt);
    while (m--) {
        scanf("%s", str);
        printf("%d : %s\n", search_automatain(tree, str), str);
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