#include<stdio.h>
#include<stdlib.h>

int minind(int n,int visited[],int wt[]){
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



void prims_algo(int n,int adjmat[][n],int *parent,int *weight,int s,int store[][3]){
    int visited[n];
    int k=0;
    for(int i=0;i<n;i++){
        visited[i]=0;
        weight[i]=1e9;
    }

    weight[s]=0;
    parent[s]=-1;

    for(int i=0;i<n;i++){
        int min=minind(n,visited,weight);
        visited[min]=1;
        for(int j=0;j<n;j++){
            if(!visited[j] && adjmat[min][j] && adjmat[min][j]<weight[j]){
                parent[j]=min;
                weight[j]=adjmat[min][j];
            }
        }
        if(parent[min]!=-1){
            store[k][0]=parent[min];
            store[k][1]=min;
            store[k][2]=weight[min];
            k++;
        }
    }

    for(int i=0;i<k;i++){
        printf("%d %d (%d) ",store[i][0],store[i][1],store[i][2]);
    }
    
} 

int total_weight(int n,int *weight){
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=weight[i];
    }
    return sum;
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
    int weight[n];
    int parent[n];
    int store[n][3];
    int tweight,s;
    char c;
    do{
        scanf("%c",&c);
        switch(c){
            case 's':
                scanf("%d",&s);
                prims_algo(n,adjmat,parent,weight,s,store);
                printf("\n");
                break;
            case 'b':
                tweight=total_weight(n,weight);
                printf("%d\n",tweight);
                break;
            case 'e':

                break;
        }
    }while(c!='e');

}