#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}tree;

typedef struct lvl{
    tree *q[100];
    int r;
    int f;
}que;

tree *create(int k){
    tree *newn=malloc(sizeof(tree));
    newn->val=k;
    newn->left=NULL;
    newn->right=NULL;

    return newn;
}

que *createq(){
    que *news=(que *)malloc(sizeof(que));
    news->r=news->f=-1;

    return news;
}

void push(que *qu,tree *root){
    qu->q[++qu->r]=root;
}

tree *pop(que *qu){
    return qu->q[++qu->f];
}

int isempty(que *qu){
    return qu->f==qu->r;
}

tree *search(tree *root,int k){
    if(root==NULL || root->val==k){
        return root;
    }
    if(k < root->val){
        return search(root->left,k);
    }
    else{
        return search(root->right,k);
    }
}

tree *insert(tree *root,int k){
    if(root==NULL){
        return create(k);
    }
    if(root->val >k){
        root->left=insert(root->left,k);
    }
    else if(k > root->val){
        root->right=insert(root->right,k);
    }

    return root;
}

int mininlvl(tree *root,int l){
    que *temp=createq();
    push(temp,root);
    int lvl=0,min=10000;
    while(!isempty(temp)){
        int size=temp->r-temp->f;
        lvl++;
        
        
        if(lvl==l){
            for(int i=0;i<size;i++){
                tree *fake=pop(temp);
                if(fake->val < min){
                    min=fake->val;
                }
            }
            return min;
        }
        for(int i=0;i<size;i++){
            tree *dum=pop(temp);
            if(dum->left!=NULL){
                push(temp,dum->left);
            }
            if(dum->right!=NULL){
                push(temp,dum->right);
            }
        }
    }
    return min;
        
}

void postorder(tree *root){
    if(root==NULL){
        return ;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->val);
}

int main()
{
    char c;
    int k,l,min;
    tree *root =NULL;

    do
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'i':
            scanf("%d",&k);
            root=insert(root,k);
            printf("\n");
            break;

        case 'z':
            // zigzag(root);
            // printf("\n");
             break;

        case 'm':
            scanf("%d",&l);
            min=mininlvl(root,l);
            printf("%d",min);
            break;

        case 'd':
            // d=diameter(root);
            // printf("%d\n",d);
            break;

        case 's':
            // rsum=rightleafsum(root);
            // printf("%d\n",rsum);
            break;

        case 'e':
            break;
        }

    } while (c != 'e');

    return 0;
}