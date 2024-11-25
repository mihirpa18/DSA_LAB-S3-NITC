#include<stdlib.h>
#include<stdio.h>

int minind(int n,int visited[],int dist[]){
    int min=1e9;
    int minind;
    for(int i=1;i<=n;i++){
        if(!visited[i] && dist[i]<=min){
            min=dist[i];
            minind=i;
        }
    }
    return minind;
}


void djk(int n,int mat[][n],int src,int d){
    int visited[n];
    int dist[n];
    for(int i=1;i<n;i++){
        visited[i]=0;
        dist[i]=1e9;
    }
    dist[src]=0;
    for(int i=1;i<n;i++){
        int min=minind(n,visited,dist);
        visited[min]=1;
        for(int j=1;j<n;j++){
            if(!visited[j] && mat[min][j] && (dist[min]+mat[min][j])<dist[j]){
                dist[j]=dist[min]+mat[min][j];
            }
        }
    }
    for(int i=1;i<n;i++){
        printf("%d ",dist[i]);
    }
    printf("\n");
    printf("%d\n",dist[d]);
}
int main(){
    int n;
    scanf("%d",&n);
    int mat[n+1][n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    int src,d;
    scanf("%d",&src);
    scanf("%d",&d);
    
    djk(n+1,mat,src,d);
}