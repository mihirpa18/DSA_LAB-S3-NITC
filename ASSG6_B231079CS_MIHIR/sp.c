#include<stdlib.h>
#include<stdio.h>

int minind(int n,int visited[],int dist[]){
    int min=1000000;
    int ind;
    for(int i=1;i<n;i++){
        if(!visited[i] && dist[i]<min){
            min=dist[i];
            ind=i;
        }
    }
    return ind;
}

void print_sp(int x,int parent[]){
    if(parent[x]==-1){
        printf("%d ",x);
        return;
    }
    print_sp(parent[x],parent);
    printf("%d ",x);

}

void djk(int n,int mat[][n],int s,int d){
    int visited[n];
    int dist[n];
    int parent[n];
    for(int i=1;i<n;i++){
        visited[i]=0;
        dist[i]=1e9;
        parent[i]=-1;
    }
    dist[s]=0;
    parent[s]=-1;
    for(int i=1;i<n;i++){
        int min=minind(n,visited,dist);
        visited[min]=1;
        for(int j=1;j<=n;j++){
            if(mat[min][j] && !visited[j] && dist[min]+mat[min][j]<dist[j]){
                dist[j]=mat[min][j]+dist[min];
                parent[j]=min;
            }
        }
    }

    printf("%d ",dist[d]);
    printf("\n");
    print_sp(d,parent);
}

void print(int n,int mat[][n]){
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int tail;
    char c;
    int mat[n+1][n+1];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mat[i][j]=0;
        }
    }

    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        while(1){
            scanf("%c",&c);
            if(c=='\n'){
                break;
            }
            scanf("%d",&tail);
            mat[head][tail]=1;
        }
    }

    int wt;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        for(int j=1;j<=n;j++){
            if(mat[head][j]==1){
                scanf("%d",&wt);
                mat[head][j]=wt;
            }
        }
    }

    int s,d;
    scanf("%d",&s);
    scanf("%d",&d);
    print(n+1,mat);
    printf("\n");

    djk(n+1,mat,s,d);
    
}