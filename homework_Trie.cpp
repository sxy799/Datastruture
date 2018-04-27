#include <bits/stdc++.h> using namespace std;

map<char,int>mp1; 
map<char,int>::iterator it1; 
map<char,string>mp2; 
map<char,string>::iterator it2;

typedef struct Node { char data; int freq; struct Node * lchild,*rchild; }Node;

#define swap(x,y){\
__typeof(x) __tmp = x;\
x = y;\
y = __tmp;\
}

Node *getNewNode() { 
    Node *p = (Node *)malloc(sizeof(Node)); 
    p->lchild = p->rchild = NULL;
     p->freq = p->data = 0; 
     return p; 
 }

Node * build(Node **huffman_node,int n) {
 #define hswap(x,y){
      swap(huffman_node[x],huffman_node[y]);
} 
    Node * root; 
    for (int i=0; i < n -1; i++) { 
    int ind1 = n - i - 1; 
    int ind2 = n - i - 2; 
    if (huffman_node[ind1]->freq > huffman_node[ind2]->freq) { 
    hswap(ind2,ind1);
     } 
     for (int j = 0; j < ind2; j++) { 
     if (huffman_node[j]->freq < huffman_node[ind1]->freq) { 
     hswap(j,ind1); 
     hswap(j,ind2); 
     } else if (huffman_node[j]->freq < huffman_node[ind2]->freq) { 
     hswap(j,ind2); 
     } 
     } 
     root = getNewNode(); root->data = 0; root->lchild = huffman_node[ind1]; root->rchild = huffman_node[ind2]; root->freq = huffman_node[ind1]->freq + huffman_node[ind2]->freq; huffman_node[ind2] = root; } #undef hswap return root; } void getEncode(Node *root,int k,char *str) { if (root == NULL) return ; if (root->lchild == NULL) { str[k] = '\0'; printf("%c->%s\n",root->data,str); //cout<

TrieNode *GetNewNode() { TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode)); p->flag = 0; for (int i = 0; i < 26; i++) { p->next[i] = NULL; } return p; }

void clear(Trie tree) { if (tree == NULL) return; for (int i = 0; i < 26; i++) { if (tree->next[i] == NULL) continue; clear(tree->next[i]); } free(tree); return ; }

int insert(Trie tree,const char * str1) { TrieNode *p = tree; while (str1[0]) {

    if (p->next[str1[0] - '0'] == NULL)
    {
        p->next[str1[0] - '0'] = GetNewNode();
    }
    p = p->next[str1[0] - '0'];
    str1++;
}
p->flag = 1;
return 1;
}

int search(Trie tree,const char * str1) { TrieNode * p = tree; while (str1[0] && p) { p = p->next[str1[0] - '0']; str1++; } return p && p->flag; }

char str[105][105]; int main(){ int n,m; mp1.clear(); mp2.clear(); cin>>n>>m; for (int i=0; i<n; i++){ cin>>str[i]; for (int j=0; j<strlen(str[i]); j++){ mp1[str[i][j]]; } } cout<<" ------------------ freq : ------------------ "<<endl; for (it1 = mp1.begin(); it1 != mp1.end(); it1){ cout<

 Node **huffman_node = (Node **)malloc(sizeof(Node *)* n);
 int i = 0;
 for (it1 = mp1.begin(); it1 != mp1.end(); it1++){
    huffman_node[i] = getNewNode();
    huffman_node[i]->data = it1->first;
    huffman_node[i]->freq = it1->second;
    i++;
}
Node *root = build(huffman_node,n);
char encode[100];
getEncode(root,0,encode);

cout<<" ------------------ huffmancode ------------------ "<<endl;
for (it2 = mp2.begin(); it2 != mp2.end(); it2++){
    string tmp = "2";
    it2->second += tmp;
    cout<<it2->first<<"   ** "<<it2->second<<endl;
}


Trie tree = GetNewNode();
for (int i=0; i<n; i++){
    string aft_str = "";
    for (int j=0; j<strlen(str[i]); j++){
        aft_str += mp2[str[i][j]];
    }
    aft_str += "3";
    insert(tree,aft_str.c_str());
}
for (int i=0; i<m; i++)
{
    char checked_str[105];
    cin>>checked_str;
    string checked = "";
    for (int j=0; j<strlen(checked_str); j++){
        if (mp2.find(checked_str[j]) != mp2.end()){
            checked += mp2[checked_str[j]];
        }
        else checked += "4";
    }
    checked += "3";
    cout<<" checked : "<<checked<<endl;
    printf("%s serach_result: %s \n",checked_str,search(tree,checked.c_str()) ? "YES" : "NO");
  }
  return 0;
}
 /*

3 3 aaa bbbbbbb cccccccc aaa bbb aaa

4 4 he hers his she

she hhhe he herr

4 4 he hers his 我我

she hhhe he 我我

*/