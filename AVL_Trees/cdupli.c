#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    int val;
    struct tree *left;
    struct tree *right;
    int height;
    int count;
}avl;

avl *create(int k){
    avl *newn=(avl *)malloc(sizeof(avl));
    newn->val=k;
    newn->left=NULL;
    newn->right=NULL;
    newn->height=1;
    newn->count=1;
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

    if(node->val == key){
        (node->count)++;
        return node;
    }

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

void preorder(avl *root){
    if(root==NULL){
        return;
    }
    printf("%d(%d) ",root->val,root->count);
    preorder(root->left);
    preorder(root->right);
}

void hminnodes(avl *root,int h,int *numnode){
    if(root==NULL){
        return;
    }
    if(root->height==h){
        (*numnode)++;
    }
    hminnodes(root->left,h,numnode);
    hminnodes(root->right,h,numnode);
}

void seclarge(avl *root,int sl[],int *i){
    if(root==NULL){
        return;
    }

    seclarge(root->left,sl,i);
    if(root->left==NULL && root->right==NULL){
        sl[(*i++)]=root->val;
        return;
    }   
    seclarge(root->right,sl,i);
}

int main(){
    avl* root = NULL;
    int num=0,i=0;
    int arr[100];
    // for(int j=0;j<100;j++){
    //     arr[i]=-1;
    // }
    /* Constructing tree given in the above figure */
    root = insert(root, 35);
    root = insert(root, 45);
    root = insert(root, 55);
    root = insert(root, 47);
    root = insert(root, 50);
    root = insert(root, 52);
    root = insert(root, 60);
    root = insert(root, 65);
 
    printf("Pre order traversal of the constructed AVL tree is \n");
    preorder(root);
    printf("\n");

    // int h;
    // scanf("%d",&h);
    // hminnodes(root,h,&num);
    // printf("%d\n",num);
    seclarge(root,arr,&i);
    printf("%d\n",arr[i-2]);
 
    return 0;
}