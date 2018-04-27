#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode;

BSTNode *getNewNode(int key) {
    BSTNode *p = (BSTNode *)malloc(sizeof(BSTNode));
    p->lchild = p->rchild = NULL;
    p->key = key;
    return p;
}

BSTNode *insert(BSTNode *tree, int key) {
    if (tree == NULL) {
        return getNewNode(key);
    }
    if (tree->key == key) return tree;
    if (key < tree->key) tree->lchild = insert(tree->lchild, key);
    else tree->rchild = insert(tree->rchild, key);
    return tree;
}

BSTNode *predecessor(BSTNode *tree) {
    BSTNode *temp = tree->lchild;
    while (temp->rchild) {
        temp = temp->rchild;
    }
    return temp;
}

BSTNode *delete_node(BSTNode *tree, int key) {
    if (tree == NULL) return NULL;
    if (key < tree->key) {
        tree->lchild = delete_node(tree->lchild, key);
    } else if (key > tree->key) {
        tree->rchild = delete_node(tree->rchild, key);
    } else {
        if (tree->lchild == NULL && tree->rchild == NULL) {
            free(tree);
            return NULL;
        } else if (tree->lchild == NULL || tree->rchild == NULL) {
            BSTNode *ret_tree = (tree->lchild ? tree->lchild : tree->rchild);
            free(tree);
            return ret_tree;
        } else {
            BSTNode *p = predecessor(tree);
            tree->key = p->key;
            tree->lchild = delete_node(tree->lchild, p->key);
        }
    }
    return tree;
}

int search(BSTNode *tree, int key) {
    if (tree == NULL) return 0;
    if (key == tree->key) return 1;
    if (key < tree->key) return search(tree->lchild, key);
    return search(tree->rchild, key);
}

void clear(BSTNode *tree) {
    if (tree == NULL) return ;
    clear(tree->lchild);
    clear(tree->rchild);
    free(tree);
    return ;
}

void inorder(BSTNode *tree) {
    if (tree == NULL) return ;
    inorder(tree->lchild);
    printf("%d ", tree->key);
    inorder(tree->rchild);
    return ;
}

Node * findSmall(Node * root, int  val){
    if (root = NULL) return n;
    Node* tmp = root->data,*ret = tmp;
    while (1){
        if (tmp->data <= val){
            tmp = tmp->rchild;
            if (tmp->data > ret->data)  ret = tmp;
        }else {
            tmp = tmp->lchild;
        }
    }
     return ret;
}

int main() {
    int op, value;
    BSTNode *tree = NULL;
    while (~scanf("%d%d", &op, &value)) {
        switch (op) {
            case 1: tree = insert(tree, value); break;
            case 2: tree = delete_node(tree, value); break;
            case 3: printf("search(%d) = %d\n", value, search(tree, value)); break;
            case 4: inorder(tree); printf("\n"); break;
        }
    }
    return 0;
}