#include<stdio.h>
#include<stdlib.h>

int hascycle(int ind,int n,int mat[][n],int *visited,int *pathvis,int check[]){
    visited[ind]=1;
    pathvis[ind]=1;
    check[ind]=0;
    for(int i=0;i<n;i++){
        if(mat[ind][i]==1){
            if(!visited[i]){
                if(hascycle(i,n,mat,visited,pathvis,check)==1){
                    check[i]=0;
                    return 1;
                }
            }
            else if(pathvis[i]==1){
                check[i]=0;
                return 1;
            }
        }
    }
    check[ind]=1;
    pathvis[ind]=0;
    return 0;
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
    int visited[n];
    int pathvis[n];
    int check[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
        pathvis[i]=0;
        check[i]=0;
    }

    for(int i=0;i<n;i++){
        if(!visited[i]){
            hascycle(i,n,mat,visited,pathvis,check);
        }
    }
    int arr[n];
    int c=0;
    for(int i=0;i<n;i++){
        if(check[i]==1){
            arr[c++]=i;
        }
    }
    for(int i=0;i<c;i++){
        printf("%d ",arr[i]);
    }
}