#include<stdio.h>

int min(int a,int b){
    return (a<b)?a:b;
}

void floydAlgo(int n,int adjmat[][n]){
    for(int mid=0;mid<n;mid++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adjmat[i][j]=min(adjmat[i][j],(adjmat[i][mid]+adjmat[mid][j]));
            }
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int adjmat[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&adjmat[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjmat[i][j]==-1){
                adjmat[i][j]=1e9;
            }
        }
    }

    floydAlgo(n,adjmat);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",adjmat[i][j]);
        }
        printf("\n");
    }
}