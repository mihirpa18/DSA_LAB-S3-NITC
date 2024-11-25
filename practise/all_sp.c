#include<stdlib.h>
#include<stdio.h>

int minind(int n,int visited[],int dist[]){
    int min=1e9;
    int minind;
    for(int i=0;i<n;i++){
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
    int ways[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
        dist[i]=1e9;
        ways[i]=1;
    }
    dist[src]=0;
    ways[src]=1;
    
    for(int i=0;i<n;i++){
        int min=minind(n,visited,dist);
        visited[min]=1;
        for(int j=0;j<n;j++){
            if(!visited[j] && mat[min][j] ){
                if((dist[min]+mat[min][j])<dist[j]){
                    ways[j]=ways[min];
                    dist[j]=dist[min]+mat[min][j];
                }
                else if((dist[min]+mat[min][j])==dist[j]){
                    ways[j]+=ways[min];
                }
            }
        }
    }
    // for(int i=0;i<n;i++){
    //     printf("%d ",ways[i]);
    // }
    // printf("\n");
    printf("%d\n",ways[d]);
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

    int src,d;
    scanf("%d",&src);
    scanf("%d",&d);
    
    djk(n,mat,src,d);
}