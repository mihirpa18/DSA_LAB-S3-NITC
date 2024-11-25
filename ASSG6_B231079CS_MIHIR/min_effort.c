#include<stdlib.h>
#include<stdio.h>

int min(int n,int visited[],int dist[]){
    int min=1e9;
    int minind;
    for(int i=1;i<n;i++){
        if(!visited[i] && dist[i]<min){
            min=dist[i];
            minind=i;
        }
    }
    return minind;
}

void djk(int n,int mat[][n],int s,int d){
    int visited[n*n];
    int dist[n*n];
    for(int i=0;i<n*n;i++){
        dist[i]=1e9;
        visited[i]=0;
    }
    dist[s]=0;

    for(int i=0;i<n*n;i++){
        int u=min(n,visited,dist);
        visited[u]=1;

        int x=u/n;
        int y=u%n;
        int dx={1,-1,0,0};
        int dy={0,0,1,-1};
        for(int j=0;j<4;j++){
            int nx=x+dx;
            int ny=y+dy;
            if(nx>=0 && nx<n && ny>=0 && ny<n){
                int neigbr=nx*n + ny;

            }
        }
    }
}