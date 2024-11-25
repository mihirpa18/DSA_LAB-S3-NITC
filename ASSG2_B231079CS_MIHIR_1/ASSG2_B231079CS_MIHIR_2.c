#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
    int val;
    int key;
    struct tree *left;
    struct tree *right;
    int height;
}avl;

avl *create(int k,int v){
    avl *newn=malloc(sizeof(avl));
    newn->val=v;
    newn->key=k;
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


avl *insert(avl *node,int k,int v){
    
    if (node == NULL){
        return  create(k,v);
    }
    
    if(k==node->key){
        node->val=v;
        return node;
    }
    if (k < node->key)
        node->left  = insert(node->left, k,v);
    else if (k > node->key)
        node->right = insert(node->right, k,v);
    
    node->height=1+max(getheight(node->left),getheight(node->right));

    int bf=balancefac(node);

    //ll rotation
    if(bf>1 && k<node->left->key){
        return rightrotate(node);
    }
    
    //rr rotation
    if(bf<-1 && k>node->right->key){
        return leftrotate(node);
    }

    //lr rot
    if(bf>1 && k>node->left->key){
        node->left=leftrotate(node->left);
        return rightrotate(node);
    }

    //rl rot
    if(bf<-1 && k<node->right->key){
        node->right=rightrotate(node->right);
        return leftrotate(node);
    }

    return node;

}

avl *upperbound(avl *root,int k){
    avl *temp=root;
    avl *ub=NULL;
    while(temp!=NULL){
        if(k<=temp->key){
            ub=temp;
            temp=temp->left;
        }
        else{
            temp=temp->right;
        }
    } 
    return ub;
}

void displayElements(avl *root){
    if(root!=NULL){
        displayElements(root->right);
        printf("%d ",root->key);
        displayElements(root->left);
    }
}



avl *find(avl *root,int k){
    if(root==NULL){
        return root;
    }
    if( root->key==k){
        return root;
    }
    
    if(k<root->key){
        
        return find(root->left,k);
    }
    else if(k>root->key){
       return find(root->right,k);
    }

}

void size(avl *root,int *s){
    if(root!=NULL){
        (*s)++;
        size(root->left,s);
        size(root->right,s);
    }
}

int empty(avl *root){
    return root==NULL;
}

int main(){
    char c;
    int k,v,k2,k3;
    int bf;
    avl *root=NULL;
    int sz,em;
    do{
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf("%d",&k);
                scanf("%d",&v);
                root=insert(root,k,v);
                break;
            case 'f':
                scanf("%d",&k2);
                avl *s=find(root,k2);
                if(s==NULL){
                    printf("-1");
                }
                else{
                    printf("%d %d",s->key,s->val);
                }
                printf("\n");
                break;
            case 's':
                sz=0;
                size(root,&sz);
                printf("%d\n",sz);
                break;
            case 'd':
                displayElements(root);
                printf("\n");
                break;
            case 'u':
            scanf("%d",&k3);
                avl *ub=upperbound(root,k3);
                if(ub==NULL){
                    printf("-1\n");
                }
                else{
                    printf("%d %d\n",ub->key,ub->val);
                }
                break;
            case 'e':
                em=empty(root);
                printf("%d\n",em);
                break;
            case 't':
                break;
        }
    }while(c!='t');
    return 0;
}