#include<stdio.h>
#include<stdlib.h>

int minind(int n,int *visited,int *wt){
    int min=1e9;
    int minind;
    for(int i=0;i<n;i++){
        if(!visited[i] && wt[i]<min){
            min=wt[i];
            minind=i;
        }
    }
    return minind;
}

void sp(int x,int *parent,int *arr,int *c){
    if(parent[x]==-1){
        arr[(*c)++]=x;
        return;
    }
    sp(parent[x],parent,arr,c);
    arr[(*c)++]=x;
}

int djk(int n,int matrix[][n],int s,int d){
    int visited[n];
    int secmin[n];
    int weight[n];
    int parent[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
        parent[i]=-1;
        weight[i]=1e9;
        secmin[i]=1e9;
    }
    weight[s]=0;

    for(int i=0;i<n;i++){
        int min=minind(n,visited,weight);
        visited[min]=1;
        for(int j=0;j<n;j++){
            if(!visited[j] && matrix[min][j]){
                int minwt=matrix[min][j]+weight[min];
                if(minwt<weight[j]){
                    parent[j]=min;
                    secmin[j]=weight[j];
                    weight[j]=matrix[min][j]+weight[min];
                }
            
                else if(minwt>weight[j] && secmin[j]>min){
                    secmin[j]=weight[j];
                }
            }
        }
        
    }
    return secmin[d]-weight[d];
}

// int abs_diff(int n,int matrix[][n],int s,int d){
//     int parent[n];
//     int min1=djk(n,matrix,s,d,parent);
//     int arr[n];
//     int c=0;
//     sp(d,parent,arr,&c);
//     for(int i=0;i<n;i++){
//         for(int j=0;j<n;j++){
//             for(int k=0;k<n;k++){
//                 if(arr[i]==matrix[j][k]){
//                     matrix[j][k]=100000000;
//                 }
//             }
//         }
//     }
//     int min2=djk(n,matrix,s,d,parent);

//     return abs(min1-min2);
// }

int main(){
    int n;
    scanf("%d",&n);
    int mat[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }

    int s;
    int d;
    scanf("%d",&s);
    scanf("%d",&d);
    int ans=djk(n,mat,s,d);
    printf("%d\n",ans);

}