#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* lchild;
    struct Node*  rchild;
}Node , *Tree;

Node *init(int val){
   Node *p = (Node *) malloc(sizeof(Node)*1);
   p->data = val;
   p->lchild  = p->rchild  = NULL;
   return p;
}

int preorder(Tree tree){
	if (tree == NULL) return 0;
	printf("%d ",tree->data);
	tree->lchild && preorder(tree->lchild);
	tree->rchild && preorder(tree->rchild);
	return 1;
}

int inorder(Tree tree ){
	if (tree == NULL) return 0;
	tree->lchild && inorder(tree->lchild);
	printf("%d ",tree->data);
	tree->rchild && inorder(tree->rchild);
	return 1;
}
int postorder(Tree tree){
	if (tree == NULL) return 0;
	tree->lchild && postorder(tree->lchild);
	tree->rchild && postorder(tree->rchild);
	printf("%d ",tree->data);
	return 1;
}


void clear(Tree tree){
	if (tree == NULL) return ;
	clear(tree->lchild);
	clear(tree->rchild);
	free(tree);
	return ;
}
Tree build_tree(){
	Tree tree = init(7);
	tree->lchild = init(5);
	tree->rchild = init(10);
	tree->lchild->lchild = init(3);
	tree->lchild->rchild = init(6);
	tree->rchild->lchild = init(9);
	tree->rchild->rchild = init(13);
	return tree;
}
int main(){
   
    Tree tree = init(1);
    tree->lchild = init(2);
    tree->rchild = init(3);
    tree->lchild->rchild = init(4);
    tree->rchild->lchild = init(5);
    	 preorder(tree),printf("\n");
    	 inorder(tree),printf("\n");
         postorder(tree),printf("\n");

    tree = build_tree();
    inorder(tree),printf("\n");
    clear(tree);
	return 0;
}