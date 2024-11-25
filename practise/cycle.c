#include<stdio.h>
#include<stdlib.h>

typedef struct queue{
    int r;
    int f;
    int q[100];
}que;

que *createq(){
    que *newq=malloc(sizeof(que));
    newq->f=newq->r=-1;

    return newq;
}

void enque(que *qu,int k){
    qu->q[++qu->r]=k;
}

int deque(que *qu){
    return qu->q[++qu->f];
}

int isempty(que *qu){
    return qu->f==qu->r;
}

int isbipartite(int ind,int n,int mat[][n]){
    int *visited=(int *)calloc(n,sizeof(int));
    int *color=(int *)malloc(n*sizeof(int)); //0-no color,1-b,2-r
    que *q=createq();
    enque(q,ind);
    visited[ind]=1;
    color[ind]=1;
    while(!isempty(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(mat[d][i]==1){
                if(color[i]==color[d]){
                    return -1;
                }
                if(!visited[i]){
                    visited[i]=1;
                    color[i]=(color[i]==1)?2:1;
                    enque(q,i);
                }
            }
        }
    }

    return 1;
}

int hascycle(int ind,int n,int matrix[][n]){
    int *visited=(int *)calloc(n,sizeof(int));
    int *parent=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        parent[i]=-1;
    }
    visited[ind]=1;
    que *q=createq();
    enque(q,ind);
    while(!isempty(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(matrix[d][i]){
                if(!visited[i]){
                    visited[i]=1;
                    parent[i]=d;
                    enque(q,i);
                }
                else if(i!=parent[d]){
                    return 1;
                }
            }
        }
    }
    return -1;
}

int main(){
    int n;
    scanf("%d",&n);
    int mat[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }

}