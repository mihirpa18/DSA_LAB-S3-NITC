#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    int val;
    struct tree *left;
    struct tree *right;
    int height;
}avl;

avl *create(int k){
    avl *newn=malloc(sizeof(avl));
    newn->val=k;
    newn->left=NULL;
    newn->right=NULL;
    newn->height=1;

    return newn;
}

int getheight(avl *n){
    if(n==NULL)
        return 0;
    
    return n->height;
}

int balancefac(avl *n){
    if(n==NULL)
        return 0;
    
    return getheight(n->left)-getheight(n->right);
}

int max(int a,int b){
    return a>b?a:b;
}

avl *rightrotate(avl *y){
    avl *x=y->left;
    avl *t2=x->right;

    x->right=y;
    y->left=t2;

    y->height= 1+ max(getheight(y->left),getheight(y->right));
    x->height= 1+ max(getheight(x->left),getheight(x->right));

    return x;
}

avl *leftrotate(avl *x){
    avl *y=x->right;
    avl *t2=y->left;

    y->left=x;
    x->right=t2;

    x->height= 1+ max(getheight(x->left),getheight(x->right));
    y->height= 1+ max(getheight(y->left),getheight(y->right));

    return y;
}

avl *insert(avl *node,int key){
    if (node == NULL)
        return  create(key);
 
    if (key < node->val)
        node->left  = insert(node->left, key);
    else if (key > node->val)
        node->right = insert(node->right, key);

    node->height=1+max(getheight(node->left),getheight(node->right));

    int bf=balancefac(node);

    //ll rotation
    if(bf>1 && key<node->left->val){
        return rightrotate(node);
    }
    
    //rr rotation
    if(bf<-1 && key>node->right->val){
        return leftrotate(node);
    }

    //lr rot
    if(bf>1 && key>node->left->val){
        node->left=leftrotate(node->left);
        return rightrotate(node);
    }

    //rl rot
    if(bf<-1 && key<node->right->val){
        node->right=rightrotate(node->right);
        return leftrotate(node);
    }

    return node;

}

void preOrder(avl *root)
{
    if(root != NULL)
    {
        printf("%d ", root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}
 
int main(){
    avl * root = NULL;
 
 
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);
    preOrder(root);
    return 0;
}