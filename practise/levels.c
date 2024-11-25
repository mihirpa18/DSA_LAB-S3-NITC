#include<stdio.h>
#include<stdlib.h>

typedef struct queue{
    int f;
    int r;
    int q[100];
}que;

typedef struct node{
    int node;
    struct node *next;
}list;

typedef struct graph{
    list **adjlist;
}graph;

que *createq(){
    que *newq=malloc(sizeof(que));
    newq->f=newq->r=-1;

    return newq;
}

list *createn(int node){
    list *newn=malloc(sizeof(list));
    newn->node=node;
    newn->next=NULL;

    return newn;
}

graph *createg(int n){
    graph *newg=malloc(sizeof(graph));
    newg->adjlist=malloc(n*sizeof(list *));

    for(int i=0;i<n;i++){
        newg->adjlist[i]=NULL;
    }
    return newg;
}

void enque(que *qu,int k){
    qu->q[++qu->r]=k;
}

int deque(que *qu){
    return qu->q[++qu->f];
}

int isempty(que *q){
    return q->f==q->r;
}

int level(int ind,int n,int matrix[][n],int x){
    int *visited=(int *)calloc(n,sizeof(int));
    que *q=createq();
    enque(q,ind);
    int lvl=0;
    while(!isempty(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(matrix[ind][i]==1){
                if(d==x){
                    return lvl;
                }
                if(!visited[i]){
                    visited[i]=1;
                    enque(q,i);
                }
            }
        }
        lvl++;
    }
    return lvl;
}

int main(){
    int n;
    scanf("%d",&n);
    graph *g=createg(n);

    int matrix[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i][j]=0;
        }
    }

    int tail;
    char c;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        while(1){
            scanf("%c",&c);
            if(c=='\n'){
                break;
            }
            scanf("%d",&tail);
            matrix[head][tail]=1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }

    int lvl=level(0,n,matrix,2);
    printf("%d\n",lvl);
}