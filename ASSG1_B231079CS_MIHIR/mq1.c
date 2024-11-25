#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int lvl;
}tree;

typedef struct queue{
    tree *q[1000];
    int r;
    int f;
}que;

tree *create(int k){
    tree *newt=malloc(sizeof(tree));
    newt->val=k;
    newt->lvl=1;
    newt->left=NULL;
    newt->right=NULL;
    newt->parent=NULL;
    return newt;
}

tree *add(tree *root,int k){
    if(root==NULL){
        root=create(k);
        return root;
    }
    if(root->val>k){
        root->left=add(root->left,k);
    }
    else{
        root->right=add(root->right,k);
    }
    return root;
}

tree *build(int *in,int *pre,int n,int ins,int ine,int pres,int pree){
    if(ins>ine || pres>pree){
        return NULL;
    };
    int dum=pre[pres];
    int index;
    
    for(index=0;index<n;index++){
        if(in[index]==dum){
            break;
        }
    }
    
    tree *root=create(dum);
    int lgap=(index-ins);
    
    root->left=build(in,pre,n,ins,index-1,pres+1,(pres+lgap+1));
    root->right=build(in,pre,n,index+1,ine,(pres+lgap+1),pree);
    
    return root;
}





void postorder(tree *root){
    if(root!=NULL){
        
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->val);
    }
}

que *createq(){
    que *newq=(que *)malloc(sizeof(que));
    newq->r=newq->f=-1;
    return newq;
}
void enque(que *qu,tree *root){
    qu->q[qu->r++]=root;
}

int isemptyq(que *qu){
    return qu->f==qu->r;
}

tree *deque(que *qu){
    return qu->q[++qu->f];
}

int height(tree *root,tree *a,int h){
    if(root->val==a->val){
        return h;
    }
    int lh,rh;
    if(a->val<root->val){
       
         lh+=height(root->left,a,h);
    }
    else{
         rh+=height(root->right,a,h);
    }
    return lh+rh;
}
void cousins(tree *root,tree *a,tree *b){
    if(root==NULL){
        return;
    }
    
    que *qu=createq();
    while(!isemptyq(qu)){
        int size=qu->r-qu->f;
        
        for(int i=0;i<size;i++){
            tree *temp=deque(qu);
            if(temp->left!=NULL){
                enque(qu,temp->left);
                a->parent=temp;
            }
            if(temp->right!=NULL){
                enque(qu,temp->right);
                b->parent=temp;
            }
        }
        
    }
    int ah=height(root,a,0);
    int bh=height(root,b,0);
    if(a->parent!=b->parent && ah==bh){
        printf("yes");
    }
    else{
        printf("no");
    }
    
}

int main(){
    int n;
    scanf("%d",&n);
    int inorder[n];
    int pre[n];
    tree *dummyt=NULL;
    for(int i=0;i<n;i++){
        scanf("%d",&pre[i]);
    }
    for(int i=0;i<n;i++){
        dummyt=add(dummyt,pre[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&inorder[i]);
    }
    
    char c;
    tree *root=build(inorder,pre,n,0,n-1,0,n-1);
    tree *a=malloc(sizeof(tree));
    tree *b=malloc(sizeof(tree));
    
    do{
        scanf("%c",&c);
        switch(c){
            case 'p':
                postorder(root);
                printf("\n");
                break;
            case 'c':
                scanf("%d",&a->val);
                scanf("%d",&b->val);
                cousins(dummyt,a,b);
                break;
            case 'e':
                break;
        }
    }while(c!='e');
    return 0;
}

