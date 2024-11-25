#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} tree;

typedef struct stack
{
    tree *s[100];
    int top;
} stack;

typedef struct queue{
    tree *q[100];
    int r;
    int f;
}que;

struct node *create(int k)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = k;
    temp->left = temp->right = NULL;
    return temp;
}

struct node *searchKey(struct node *root, int num)
{
    if (root == NULL || root->data == num)
    {
        return root;
    }
    if (root->data < num)
    {
        return (searchKey(root->right, num));
    }
    else
    {
        return (searchKey(root->left, num));
    }
}

tree *contree(int *inorder, int *preorder, int n, int instart, int inend, int prestart, int preend)
{
    if (prestart > preend || instart > inend)
    {
        return NULL;
    }

    int head = preorder[prestart];

    int index = 0;

    for (index = instart; index < inend; index++)
    {
        if (inorder[index] == head)
        {
            break;
        }
    }

    tree *newnode = create(head);

    int leftspace = (index - instart);

    newnode->left = contree(inorder, preorder, n, instart, (index - 1), prestart + 1, prestart + leftspace);
    newnode->right = contree(inorder, preorder, n, index + 1, inend, prestart + leftspace + 1, preend);

    return newnode;
}

void postorder(tree *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

stack *createstack()
{
    stack *new = (stack *)malloc(sizeof(stack));
    new->top = -1;
    return new;
}

int isempty(stack *s)
{
    return s->top == -1;
}

void push(stack *sk, tree *root)
{
    sk->s[++sk->top] = root;
}

tree *pop(stack *sk)
{
    return sk->s[sk->top--];
}

void zigzag(tree *root)
{
    if (root == NULL)
    {
        return;
    }
    stack *curr = createstack();
    stack *nxt = createstack();
    int check = 1;
    push(curr,root);
    while (!isempty(curr))
    {
        tree *dummy = pop(curr);
        printf("%d ", dummy->data);
        if (check)
        {
            if (dummy->right != NULL)
            {
                push(nxt, dummy->right);
            }
            if (dummy->left != NULL)
            {
                push(nxt, dummy->left);
            }
            
        }
        else
        {
            if (dummy->left != NULL)
            {
                push(nxt, dummy->left);
            }
            if (dummy->right != NULL)
            {
                push(nxt, dummy->right);
            }
        }
        if (isempty(curr))
        {
            check=0;
            stack *temp = curr;
            curr = nxt;
            nxt = temp;
        }
    }
}

que *createq(){
    que *newq=(que *)malloc(sizeof(que));
    newq->r=newq->f=-1;
    return newq;
}

void enque(que *qu,tree *root){
    qu->q[++qu->r]=root;
}

int isemptyq(que *q){
    return q->r==q->f;
}

tree *deque(que *qu){
    return qu->q[++qu->f];
}

int max(int a,int b){
    int m=0;
    if(a>b){
        m=a;
    }
    else{
        m=b;
    }
    return m;
}

void levelmax(tree *root){
    if(root==NULL){
        return;
    }

    int *maxarr=(int *)malloc(100*sizeof(int));
    int index=0;
    maxarr[index++]=root->data; 
    que *q=createq();
    enque(q,root);
  
    while(!isemptyq(q)){
        int size=q->r-q->f;
        int lvlmax=0;
        for(int i=0;i<size;i++){
        tree *temp=deque(q);
        if(temp->left!=NULL){
            enque(q,temp->left);
            lvlmax=max(lvlmax,temp->left->data);
        }
        if(temp->right!=NULL){
            enque(q,temp->right);
            lvlmax=max(lvlmax,temp->right->data);
        }
        }
        if(lvlmax!=0){
            maxarr[index++]=lvlmax;
        }
    }
    for(int i=0;i<index;i++){
        printf("%d ",maxarr[i]);
    }
    printf("\n");
}

int height(tree *root,int *diam){
    if(root==NULL){
        return 0;
    }
    
    int lh=height(root->left,diam);
    int rh=height(root->right,diam);

    *diam=max(*diam,(lh+rh));

    return 1+max(lh,rh);
}
int diameter(tree *root){
    
    int diam=0;
    int h=height(root,&diam);
    return diam+1;

}

void rootsum(tree *root,int *rsum){
    if(root==NULL){
        return;
    }
    if(root->right!=NULL && root->right->left==NULL && root->right->right==NULL){
         (*rsum)+=root->right->data;
    }

    rootsum(root->left,rsum);
    rootsum(root->right,rsum);
}

int rightleafsum(tree *root){
    int rsum=0;
    rootsum(root,&rsum);
    return rsum;
}

int main()
{
    char c;
    int n;
    int d,rsum;
    scanf("%d", &n);

    int inorder[n];
    int preorder[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &inorder[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &preorder[i]);
    }

    tree *root = contree(inorder, preorder, n, 0, n - 1, 0, n - 1);

    do
    {
        scanf(" %c", &c);
        switch (c)
        {
        case 'p':
            postorder(root);
            printf("\n");
            break;

        case 'z':
            zigzag(root);
            printf("\n");
            break;

        case 'm':
            levelmax(root);
            break;

        case 'd':
            d=diameter(root);
            printf("%d\n",d);
            break;

        case 's':
            rsum=rightleafsum(root);
            printf("%d\n",rsum);
            break;

        case 'e':
            break;
        }

    } while (c != 'e');

    return 0;
}