#include<stdio.h>
#include<stdlib.h>

void path_sum(int x,int n,int mat[][n],int d,int *arr,int *c,int *wt){
    if(x==d){
        arr[(*c)++]=(*wt);
        return;
    }
    else{
        dfs(x,mat,)
    }
}
void dfs(int n,int matrix[][n],int *visited,int s,int d){
    visited[s]=0;
    for(int i=0;i<n;i++){
        if(!visited[i] && matrix[s][i]){
            dfs(n,matrix,visited,i,d);
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int adjmat[n][n];
    int fake[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adjmat[i][j]=0;
        }
    }
    int weight[n];
    int parent[n];
    char c;
    int tail;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        while(1){
            scanf("%c",&c);
            if(c=='\n'){
                break;
            }
            scanf("%d",&tail);
            adjmat[head][tail]=1;
        }
    }
    int wt;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        for(int j=0;j<n;j++){
            if(adjmat[i][j]==1){
                scanf("%d",&wt);
                adjmat[i][j]=wt;
            }
        }
    }
    int ans=prims_algo(n,adjmat,fake,parent,weight);
    printf("%d\n",ans);
}