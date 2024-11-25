#include<stdio.h>
#include<stdlib.h>

int minDistance(int dist[], int sptSet[],int n) {
    int min = 100, min_index;

    for (int v = 0; v < n; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[],int n) {
    
    for (int i = 0; i < n; i++)
        printf("%d ", dist[i]);
}

void dijkstra(int** graph, int src,int n) {
    int dist[n];
    int sptSet[n]; 

    for (int i = 0; i < n; i++)
        dist[i] = 100, sptSet[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, sptSet,n);

        sptSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != 100 && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printSolution(dist,n);
}

int main(){
    int n,s;
    scanf("%d",&n);
    int** a=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        a[i]=(int*)malloc(n*sizeof(int));
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=0;
        }
    }

    int node,adj;
    char op;
    for(int i=0;i<n;i++){
        scanf("%d%c",&node,&op);
        
            while (op!='\n') {
                scanf("%d%c",&adj,&op) ;
                a[node - 1][adj - 1] = 1;
                
                
        }

    }

    int dist;
    for(int i=0;i<n;i++){
        scanf("%d%c",&node,&op);
        
        while (op!='\n') {
            for(int h=0;h<n;h++){
                if(a[node-1][h]==1){
                    scanf("%d%c",&dist,&op) ;
                    a[node - 1][h] = dist;
                }
            }
        }
    }

    scanf("%d",&s);

    dijkstra(a,s-1,n);

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",a[i][j]);
    //     }
    //     printf("\n");
    // }




}