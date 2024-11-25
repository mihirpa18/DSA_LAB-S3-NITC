#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

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

avl *search(avl *root,int k){
	if(root==NULL){
		return root;
	}
	
	if(root->val>k){
		return search(root->left,k);
	}
	else{
		return search(root->right,k);
	}
}

int delsearch(avl *root,int k){
    if(root==NULL){
		return 0;
	}
	while(root!=NULL){
        if(root->val>k){
            root=root->left;
        }
        else if(k>root->val){
            root=root->right;
        }
        else{
            return 1;
        }
    }
    return 0;
}

int getheight(avl *node){
    if(node==NULL){
        return 0;
    }

    return node->height;
}

int balancefac(avl *node){
    if(node==NULL){
        return 0;
    }

    return getheight(node->left)-getheight(node->right);
}

int max(int a,int b){
    return a>b?a:b;
}

avl *rightrotate(avl *y){
    avl *x=y->left;
    avl *t2=x->right;

    x->right=y;
    y->left=t2;

    y->height=1+max(getheight(y->left),getheight(y->right));
    x->height=1+max(getheight(x->left),getheight(x->right));

    return x;
}

avl *leftrotate(avl *x){
    avl *y=x->right;
    avl *t2=y->left;

    y->left=x;
    x->right=t2;

    x->height=1+max(getheight(x->left),getheight(x->right));
    y->height=1+max(getheight(y->left),getheight(y->right));

    return y;
}

avl *insert(avl *root,int k){
    if(root==NULL){
        return create(k);
    }
    if(k<root->val){
        root->left=insert(root->left,k);
    }
    else{
        root->right=insert(root->right,k);
    }

    root->height=1+max(getheight(root->left),getheight(root->right));

    int bf=balancefac(root);

    if(bf>1 && k<root->left->val){
        return rightrotate(root);
    }
    if(bf<-1 && k>root->right->val){
        return leftrotate(root);
    }
    if(bf>1 && k>root->left->val){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    if(bf<-1 && k<root->right->val){
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}

int numcreator(char *str,int *i){
    int num=0;
    while(str[*i]>='0' && str[*i]<='9'){
        num = num*10 + (str[*i]-'0');
        (*i)++;
    }
    return num;
}

avl *build(char *str,int *i){
    if(str[*i]=='\0'){
        return NULL;
    }
    while(str[*i]==' '){
        (*i)++;
    }
    if(str[*i]==')'){
        (*i)++;
        return NULL;
    }

    int num=numcreator(str,i);

    avl *node=create(num);
    while(str[*i]==' '){
        (*i)++;
    }
    if(str[*i]=='('){
        (*i)++;
        node->left=build(str,i);
        (*i)++;
    }
    while(str[*i]==' '){
        (*i)++;
    }
    if(str[*i]=='('){
        (*i)++;
        node->right=build(str,i);
        (*i)++;
    }
    while(str[*i]==' '){
        (*i)++;
    }
    return node;
    
}

void treetos(avl *root){

    if(root==NULL){
        printf("( ) ");
        return;
    }
    
    printf("( %d ",root->val);
    if(root->left==NULL && root->right==NULL){
        printf(") ");
        return;
    }
    treetos(root->left);
    treetos(root->right);
    printf(") ");
}

void builds(avl *root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->val);
    treetos(root->left);
    treetos(root->right);
}

void preorder(avl *root){
    if(root!=NULL){
        printf("%d ",root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

avl *succ(avl *root){
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
        return NULL;
    }
    if(k<root->val){
        root->left=delete(root->left,k);
    }
    else if(k>root->val){
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
        avl *suc=succ(root);
        root->val=suc->val;
        root->right=delete(root->right,suc->val);
    }

    root->height=1+max(getheight(root->left),getheight(root->right));

    int balance=balancefac(root);
    if(balance>1 && balancefac(root->left)>=0){
        return rightrotate(root);
    }
    if(balance>1 && balancefac(root->left)<0){
        root->left=leftrotate(root->left);
        return rightrotate(root);
    }
    if(balance<-1 && balancefac(root->right)<=0){
        return leftrotate(root);
    }
    if(balance<-1 && balancefac(root->right)<0){
        root->right=rightrotate(root->right);
        return leftrotate(root);
    }
    return root;
}

avl *mini(avl *root){
	avl *min=NULL;
	while(root->left!=NULL){
		root=root->left;
	}
	min=root;
	return min;
}

avl *avl_succ(avl *root,int n){
    avl *sea=search(root,n);
    if(sea==NULL){
        return NULL;
    }
    if(sea->right!=NULL){
        return mini(sea->right);
    }
    else{
        avl *temp=root;
        avl *suc=NULL;
        while(temp->val!=sea->val){
            if(temp->val>sea->val){
                suc=temp;
                temp=temp->left;
            }
            else{
                temp=temp->right;
            }
        }
        return suc;
    }
}
avl *pred(avl *root,int k){
	avl *temp=search(root,k);
	avl *pre=NULL;

	while(root!=NULL){
		if(root->val<temp->val){
			pre=root;
			root=root->right;
		}
		else{
			root=root->left;
		}
	}
	return pre;
}


void printpath(avl *root,int k){
    if(root==NULL){
        return;
    }
   

    if(root->val==k){
        printf("%d ",root->val);
        return ;
    }
     printf("%d ",root->val);
    if(k<root->val){
         printpath(root->left,k);
    }
    else{
         printpath(root->right,k);
    }
}

void succpath(avl *root,int n){
    avl *sea=search(root,n);
    if(sea==NULL){
        printf("%d\n",getheight(root)-1);
        return;
    }

    avl *suc=avl_succ(root,n);

    if(suc==NULL){
        printf("%d ",getheight(root)-1);

    }
    else{
        printpath(root,suc->val);
    }
    printf("\n");
}

void subtreesum(avl *root,int n,int *sum){
    if(root!=NULL){
        subtreesum(root->left,n,sum);
        (*sum)+=root->val;
        subtreesum(root->right,n,sum);
    }
}

int avlclosest(avl *root,int n){
    if(root==NULL){
        printf("-1");
        exit(1);
    }
    avl *suc=avl_succ(root,n);
    
    avl *pre=pred(root,n);
    if(suc==NULL){
        return pre->val;
    }
    else if(pre==NULL){
        return suc->val;
    }
    else{
        int suc_dif=abs(suc->val-n);
        int pre_dif=abs(pre->val-n);

        if(suc_dif<pre_dif){
            return suc->val;
        }
        else if(suc_dif>pre_dif){
            return pre->val;
        }
        else if(suc_dif==pre_dif){
            return pre->val;
        }
    }
}

int main(){
    avl *root=NULL;
    char c;
    char s[1000];
    int i=0,j=0,n1,n2,n3,n5;
    fgets(s,sizeof(s),stdin);
    root=build(s,&i);
    int temp,n4,sum=0;
    char ch;
    do{
        scanf(" %c",&c);
        switch(c){
            case 'a': 
                while(1){
                    scanf("%c",&ch);
                    if(ch=='\n'){
                        break;
                    }
                    scanf("%d",&temp);
                    root=insert(root,temp);
                }
                builds(root);
                printf("\n");
                break;
            case 'b':
                scanf("%d",&n1);
                scanf("%d",&n2);
                int c=0;

                for(int k=n1;k<=n2;k++){
                    if(delsearch(root,k)){
                        c++;
                        root=delete(root,k);
                    }
                    
                }
                if(c==0){
                    printf("-1\n");
                    continue;
                }
                    printf("%d ",c);
                    preorder(root);
                    printf("\n");
                
                break;
            case 'c':
                scanf("%d",&n3);
                succpath(root,n3);
                break;
            case 'd':
                scanf("%d",&n4);
                avl *dum=search(root,n4);
                if(dum==NULL){
                    printf("-1\n");
                }
                else{
                    subtreesum(dum,n4,&sum);
                    printf("%d ",sum);
                    builds(dum);
                    printf("\n");
                }
                break;
            case 'e':
                scanf("%d",&n5);
                avl *pseudo=search(root,n5);
                if(pseudo==NULL){
                    printf("-1\n");
                }
                else{
                    int close=avlclosest(root,n5);
                    printf("%d\n",close);
                }
                break;
            case 'g':
                break;
        }
    }while(c!='g');

    return 0;
}