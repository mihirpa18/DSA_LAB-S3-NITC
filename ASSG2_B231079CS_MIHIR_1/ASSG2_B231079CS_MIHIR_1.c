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

void countrotations(int lr,int rr){
    printf("%d %d\n",lr,rr);
}

void postorder(avl *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->val);
    }
}

avl *search(avl *root,int k){
    if(root==NULL){
        return root;
    }
    if( root->val==k){
        return root;
    }
    
    if(k<root->val){
        return search(root->left,k);
    }
    else if(k>root->val){
        return search(root->right,k);
    }

}
void find(avl *root,int k){
    if(root==NULL){
        return;
    }
    if( root->val==k){
        printf("%d ",root->val);
    }
    
    if(k<root->val){
        printf("%d ",root->val);
        find(root->left,k);
    }
    else if(k>root->val){
        printf("%d ",root->val);
        find(root->right,k);
    }

}

void pancestors(avl *root,int key){
    if(root==NULL){
        return;
    }
    if(root->val==key){
        printf("%d ",root->val);
        return;
    }
    if(key < root->val){
        pancestors(root->left,key);
        printf("%d ",root->val);

    }
    else if(key > root->val){
        pancestors(root->right,key);
        printf("%d ",root->val);
    }
}

avl *succ(avl *root,int key)
{
    avl *temp;
    if(root->right!=NULL){
        temp=root->right;
            while(temp->left!=NULL){
                temp=temp->left;
            }
    }
       
    return temp;
}

avl *Delete(avl *root,int k)
{

    if (root == NULL)
    {
        return NULL;
    }
    if (k<root->val)
    {
        root->left=Delete(root->left, k);
    }
    else if (k>root->val)
    {
        root->right=Delete(root->right, k);
    }

    else if (root->left==NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }

    else if (root->left == NULL)
    {
        avl *temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL)
    {
        avl *temp = root->left;
        free(root);
        return temp;
    }
    else
    {
        avl *suc = succ(root,k);
        root->val = suc->val;
        root->right=Delete(root->right, suc->val);
    }

    root->height = 1 + max(getheight(root->left), getheight(root->right));

    
    int balance = balancefac(root);


    // Left Left Case
    if (balance > 1 && balancefac(root->left) >= 0){
        rr++;
        return rightrotate(root);
    }
    // Left Right Case
    if (balance > 1 && balancefac(root->left) < 0)
    {
        lr++;
        root->left =  leftrotate(root->left);
        rr++;
        return rightrotate(root);
    }

    // Right Right Case
    if (balance < -1 && balancefac(root->right) <= 0){
        lr++;
        return leftrotate(root);
    }
    // Right Left Case
    if (balance < -1 && balancefac(root->right) > 0)
    {
        rr++;
        root->right = rightrotate(root->right);
        lr++;
        return leftrotate(root);
    }    
    return root;
}

int main(){
    char c;
    int n,n1,n2,n3;
    int bf;
    avl *root=NULL;
    do{
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf("%d",&n);
                root=insert(root,n);
                break;
            case 'f':
                scanf("%d",&n1);
                avl *s=search(root,n1);
                if(s==NULL){
                    printf("-1");
                }
                else{
                    find(root,n1);
                }
                printf("\n");
                break;
            case 'p':
                postorder(root);
                printf("\n");
                break;
            case 's':
                countrotations(lr,rr);
                break;
            case 'd':
                scanf("%d",&n3);
                avl *sea=search(root,n3);
                if(sea==NULL){
                    printf("-1");
                }
                else{
                    pancestors(root,n3);
                    root=Delete(root,n3);
                }
                
                printf("\n");
                break;
            case 'b':
                scanf("%d",&n2);
                avl *bfc=search(root,n2);
                if(bfc==NULL){
                    printf("-1");
                }
                else{
                    bf=balancefac(bfc);
                    printf("%d ",bf);
                }
                printf("\n");
                break;
            case 'e':
                break;
        }
    }while(c!='e');
    return 0;
}