#include <bits/stdc++.h>
using namespace std;

struct BST {
    int val;
    BST *l,*r;
    BST(int v): val(v), l(nullptr), r(nullptr) {}
};

BST* bstInsert(BST* root, int x){
    if(!root) return new BST(x);
    if(x < root->val) root->l = bstInsert(root->l, x);
    else if(x > root->val) root->r = bstInsert(root->r, x);
    return root;
}

BST* findMin(BST* root){ while(root && root->l) root = root->l; return root; }

BST* bstDelete(BST* root, int x){
    if(!root) return nullptr;
    if(x < root->val) root->l = bstDelete(root->l, x);
    else if(x > root->val) root->r = bstDelete(root->r, x);
    else {
        if(!root->l){ BST* t = root->r; delete root; return t; }
        if(!root->r){ BST* t = root->l; delete root; return t; }
        BST* succ = findMin(root->r);
        root->val = succ->val;
        root->r = bstDelete(root->r, succ->val);
    }
    return root;
}

BST* bstSearch(BST* root, int x){
    while(root){
        if(x==root->val) return root;
        root = (x < root->val) ? root->l : root->r;
    }
    return nullptr;
}

void preorder(BST* r){ if(!r) return; cout<<r->val<<" "; preorder(r->l); preorder(r->r); }
void inorder(BST* r){ if(!r) return; inorder(r->l); cout<<r->val<<" "; inorder(r->r); }
void postorder(BST* r){ if(!r) return; postorder(r->l); postorder(r->r); cout<<r->val<<" "; }

int main(){
    BST* root = nullptr;
    int arr[] = {50,30,70,20,40,60,80};
    for(int v: arr) root = bstInsert(root, v);
    cout<<"Inorder: "; inorder(root); cout<<"\n";
    cout<<"Preorder: "; preorder(root); cout<<"\n";
    cout<<"Postorder: "; postorder(root); cout<<"\n";
    root = bstDelete(root, 50);
    cout<<"After deleting 50, inorder: "; inorder(root); cout<<"\n";
    auto p = bstSearch(root, 60);
    cout<<(p ? "Found 60\n" : "60 not found\n");
    return 0;
}
