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

int lr=0,rr=0;

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
        rr++;
        return rightrotate(node);
    }
    
    //rr rotation
    if(bf<-1 && key>node->right->val){
        lr++;
        return leftrotate(node);
    }

    //lr rot
    if(bf>1 && key>node->left->val){
        lr++;
        node->left=leftrotate(node->left);
        rr++;
        return rightrotate(node);
    }

    //rl rot
    if(bf<-1 && key<node->right->val){
        rr++;
        node->right=rightrotate(node->right);
        lr++;
        return leftrotate(node);
    }

    return node;

}

void postOrder(avl *root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}

void vaulthelp(avl *root,int k,int lvl,int *arr,int *i){
    if(root==NULL){
        return;
    }
    if(lvl==k && root->val%2!=0){
        arr[(*i)++]=root->val;
    }
    vaulthelp(root->left,k,lvl+1,arr,i);
    vaulthelp(root->right,k,lvl+1,arr,i);
}

float vault(avl *root,int k,int *arr){
    int i=0;

    vaulthelp(root,k,0,arr,&i);
    if(i==0){
        return 0.0;
    }
    int sum=0;
    for(int j=0;j<i;j++){
        sum+=arr[j];
    }
    return (float)sum/i;  
}

int main(){
    char c;
    int n,k;
    float avg;
    avl *root=NULL;
    int arr[100];
    do{
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf("%d",&n);
                root=insert(root,n);
                break;
            case 'p':
                postOrder(root);
                printf("\n");
                break;
            case 'a':
                scanf("%d",&k);
                avg=vault(root,k,arr);
                printf("%.1f\n",avg);
                break;
            case 'e':
                
                break;
        }
    }while(c!='e');
}
