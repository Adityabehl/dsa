#include <bits/stdc++.h>
using namespace std;

struct AVL {
    int val, h;
    AVL *l,*r;
    AVL(int v): val(v), h(1), l(nullptr), r(nullptr) {}
};

int height(AVL* n){ return n ? n->h : 0; }
void update(AVL* n){ if(n) n->h = 1 + max(height(n->l), height(n->r)); }

AVL* rotateRight(AVL* y){
    AVL* x = y->l; AVL* T2 = x->r;
    x->r = y; y->l = T2;
    update(y); update(x);
    return x;
}

AVL* rotateLeft(AVL* x){
    AVL* y = x->r; AVL* T2 = y->l;
    y->l = x; x->r = T2;
    update(x); update(y);
    return y;
}

int balance(AVL* n){ return n ? height(n->l) - height(n->r) : 0; }

AVL* avlInsert(AVL* root, int key){
    if(!root) return new AVL(key);
    if(key < root->val) root->l = avlInsert(root->l, key);
    else if(key > root->val) root->r = avlInsert(root->r, key);
    else return root;
    update(root);
    int b = balance(root);
    if(b > 1 && key < root->l->val) return rotateRight(root);
    if(b < -1 && key > root->r->val) return rotateLeft(root);
    if(b > 1 && key > root->l->val){ root->l = rotateLeft(root->l); return rotateRight(root); }
    if(b < -1 && key < root->r->val){ root->r = rotateRight(root->r); return rotateLeft(root); }
    return root;
}

AVL* avlSearch(AVL* root, int key){
    while(root){
        if(key == root->val) return root;
        root = key < root->val ? root->l : root->r;
    }
    return nullptr;
}

void inorderAVL(AVL* r){ if(!r) return; inorderAVL(r->l); cout<<r->val<<" "; inorderAVL(r->r); }

int main(){
    AVL* root = nullptr;
    int vals[] = {10,20,30,40,50,25};
    for(int v: vals) root = avlInsert(root, v);
    cout<<"AVL inorder: "; inorderAVL(root); cout<<"\n";
    auto p = avlSearch(root, 25);
    cout<<(p ? "Found 25\n" : "25 not found\n");
    return 0;
}
