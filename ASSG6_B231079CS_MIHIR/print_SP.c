#include<stdio.h>
#include<stdlib.h>

int min(int n,int visited[],int dist[]){
    int min=1e9;
    int minind;
    for(int i=0;i<n;i++){
        if(!visited[i] && dist[i]<min){
            min=dist[i];
            minind=i;
        }
    }
    return minind;
}

void printpath(int parent[],int ind){
    if(parent[ind]==-1){
        printf("%d ",ind);
        return;
    }
    printpath(parent,parent[ind]);
    printf("%d ",ind);
}

void print_SP(int n,int mat[][n],int s,int d){
    int visited[n];
    int dist[n];
    int parent[n];

    for(int i=1;i<n;i++){
        visited[i]=0;
        dist[i]=1e9;
        parent[i]=-1;
    }

    dist[s]=0;
    for(int i=1;i<n;i++){
        int u=min(n,visited,dist);
        visited[u]=1;
        for(int j=1;j<n;j++){
            if(!visited[j] && mat[u][j] && (dist[j]>dist[u]+mat[u][j])){
                dist[j]=dist[u]+mat[u][j];
                parent[j]=u;
            }
        }
    }
    printf("%d ",dist[d]);
    printpath(parent,d);
}
int main(){
    int n;
    scanf("%d",&n);
    int matrix[n+1][n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    int s,d;
    scanf("%d",&s);
    scanf("%d",&d);
    print_SP(n+1,matrix,s,d);
}