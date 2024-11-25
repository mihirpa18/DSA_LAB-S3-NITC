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

avl *rr(avl *y){
    avl *x=y->left;
    avl *t2=x->right;

    x->right=y;
    y->left=t2;

    y->height=1+ max(getheight(y->left),getheight(y->right));
    x->height=1+ max(getheight(x->left),getheight(x->right));

    return x;
}
avl *lr(avl *x){
    avl *y=x->right;
    avl *t2=y->left;

    y->left=x;
    x->right=t2;

    x->height= 1 + max(getheight(x->left),getheight(x->right));
    y->height= 1+ max(getheight(y->left),getheight(y->right));

    return y;
}

avl *insert(avl *root,int k){
    if(root==NULL){
        return create(k);
    }
    if(k < root->val){
        root->left=insert(root->left,k);
    }
    else if(k > root->val){
        root->right=insert(root->right,k);
    }

    root->height= 1 + max(getheight(root->left),getheight(root->right));

    int bf=balancefac(root);

    if(bf>1 && k < root->left->val){
        return rr(root);
    }
    if(bf<-1 && k > root->right->val){
        return lr(root);
    }
    if(bf>1 && k > root->left->val){
        root->left=lr(root->left);
        return rr(root);
    }
    if(bf<-1 && k < root->right->val){
        root->right=rr(root->right);
        return lr(root);
    }
    return root;
}

avl *isuc(avl *root,int k){
    avl *temp;
    if(root->right!=NULL){
        temp=root->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
    }
    return temp;
}
avl *delete(avl *root,int k){
    if(root==NULL){
        return;
    }
    if(k<root->left){
        root->left=delete(root->left,k);
    }
    else if(k>root->left){
        root->right=delete(root->right,k);
    }
    else if(root->left==NULL && root->right==NULL){
        free(root);
        return NULL;
    }
    else if(root->left==NULL){
        avl *temp=root->right;
        free(root);
        return temp;
    }
    else if(root->right==NULL){
        avl *temp=root->left;
        free(root);
        return temp;
    }
    else{
        avl *suc=isuc(root,k);
        root->val=suc->val;
        root->right=delete(root->right,suc->val);
    }

    root->height= 1 + max(getheight(root->left),getheight(root->right));
    int bf=balancefac(root);

    if(bf>1 && balancefac(root->left)>=0){
        return rr(root);
    }
    if(bf<-1 && balancefac(root->right)<=0){
        return lr(root);
    }
    if(bf>1 && balancefac(root->left)<0){
        root->left=lr(root->left);
        return rr(root);
    }
    if(bf<-1 && balancefac(root->right)>0){
        root->left=rr(root->right);
        return lr(root);
    }
    return root;
}
void postorder(avl *T){
    if(T==NULL){
        return;
    }
        postorder(T->left);
        postorder(T->right);
        printf("%d ",T->val);
    
}

int main(){
    char c;
    avl *root=NULL;
    int n;
    do{
        scanf(" %c",&c);
        switch(c){
            case 'i':
                scanf("%d",&n);
                root=insert(root,n);
                break;
            case 'p':
                postorder(root);
                printf("\n");
                break;
             case 's':
                // if(root==NULL || root->height==1 || (root->left==NULL || root->right==NULL)){
                //     printf("-1\n");
                // }
                // else{
                //     sm=secondmax(root,arr);
                //     printf("%d\n",sm);
                // }
                break;
            case 'e':
            
                break;
        }
    }while(c!='e');
    return 0;
}
