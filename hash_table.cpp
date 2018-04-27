#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';

typedef struct TrieNode {
    int is_terminal;
    struct TrieNode** childs;
} TrieNode, *Trie;

TrieNode* new_node() {
    TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode));
    p->childs = (TrieNode **)malloc(sizeof(TrieNode *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        p->childs[i] = NULL;
    }
    p->is_terminal = 0;
    return p;
}

void clear(TrieNode *p) {
    if (p != NULL) {
        for (int i = 0; i < SIZE; i++) {
            if (p->childs[i] != NULL) {
                clear(p->childs[i]);
            }
        }
        free(p->childs);
        free(p);
    }
}

void insert(Trie trie, char *pattern) {
    TrieNode *p = trie;
    for (int i = 0; i < strlen(pattern); i++){
       if(p->childs[pattern[i] - BASE] == NULL){
           p->childs[pattern[i] - BASE] = new_node();
       } 
        p=p->childs[pattern[i] - BASE];
    }
   p->is_terminal = 1;
}

int find(Trie trie, char *buffer) {
     TrieNode *p = trie;
    for (int i = 0; i < strlen(buffer); i++){
        if(p->childs[buffer[i] - BASE] == NULL){
           return 0;
       } 
         p=p->childs[buffer[i] - BASE];
    }
    return  p->is_terminal;
}

int main() {
    Trie root = new_node();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char pattern[100];
        scanf("%s", pattern);
        insert(root, pattern);
    }
    char buffer[100];
    scanf("%s", buffer);
    if (find(root, buffer)) {
        printf("String is found.\n");
    } else {
        printf("String is not found.\n");
    }
    clear(root);
    return 0;
}