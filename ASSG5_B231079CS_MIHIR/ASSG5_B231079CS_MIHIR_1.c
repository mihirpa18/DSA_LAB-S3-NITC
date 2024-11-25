#include <stdio.h>
#include <stdlib.h>

void dfs(int ind, int n, int adjmat[][n], int visited[])
{
    visited[ind] = 1;
    for (int i = 0; i < n; i++)
    {
        if (adjmat[ind][i] == 1 && !visited[i])
        {
            dfs(i, n, adjmat, visited);
        }
    }
}

int count(int ind, int n, int adjmat[][n])
{
    int c = 0;
    int *visited = (int *)calloc(n, sizeof(int));
    for (ind = 0; ind < n; ind++)
    {
        if (!visited[ind])
        {
            dfs(ind, n, adjmat, visited);
            c++;
        }
    }
    return c;
}

void sizehelp(int ind, int n, int adjmat[][n], int visited[], int *size)
{
    visited[ind] = 1;
    for (int i = 0; i < n; i++)
    {
        if (adjmat[ind][i] == 1 && !visited[i])
        {
            (*size)++;
            sizehelp(i, n, adjmat, visited, size);
        }
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sizeofcomp(int ind, int n, int adjmat[][n])
{
    int *visited = (int *)calloc(n, sizeof(int));
    int *arr = (int *)malloc(n * sizeof(int));
    int i = 0;
    for (ind = n - 1; ind >= 0; ind--)
    {
        if (!visited[ind])
        {
            int size = 1;
            sizehelp(ind, n, adjmat, visited, &size);
            arr[(i)++] = size;
        }
    }

    bubbleSort(arr, i);
    for (int j = 0; j < i; j++)
    {
        printf("%d ", arr[j]);
    }
}

void bridgehelp(int ind,int n,int adjmat[][n],int *parent,int *visited,int tin[],int low[],int *timer,int *countbr){

    visited[ind]=1;
    tin[ind]=low[ind]=++(*timer);
    for(int j=0;j<n;j++){
        if(adjmat[ind][j]==1){
            if(!visited[j]){
                parent[j]=ind;
                bridgehelp(j,n,adjmat,parent,visited,tin,low,timer,countbr);

                low[ind]=(low[ind]<low[j])?low[ind]:low[j];

                if(low[j]>tin[ind]){
                    (*countbr)++;
                }
            }
            else{
                if(j!=parent[ind]){
                    low[ind]=(low[ind]<tin[j])?low[ind]:tin[j];
                }
            }
        }
    }
}

int bridge(int n,int adjmat[][n]){
    int c=0,t=0;
    int *visited=(int *)calloc(n,sizeof(int));
    int *parent=(int *)malloc(n*sizeof(int));
    int *tin=(int *)malloc(n*sizeof(int));
    int *low=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        parent[i]=-1;
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            bridgehelp(i,n,adjmat,parent,visited,tin,low,&t,&c);
        }
    }

    return c;
}

void articuhelp(int ind,int n,int adjmat[][n],int visited[],int parent[],int tin[],int low[],int *artico,int *timer){
    visited[ind]=1;
    tin[ind]=low[ind]=++(*timer);
    int child=0;
    for(int i=0;i<n;i++){
        if(adjmat[ind][i]==1){
            if(!visited[i]){
                parent[i]=ind;
                child++;
                articuhelp(i,n,adjmat,visited,parent,tin,low,artico,timer);

                low[ind]=(low[ind]<low[i])?low[ind]:low[i];

                if(parent[ind]==-1 && child>1){
                    (*artico)++;
                }
                if(parent[ind]!=-1 && low[i]>=low[ind]){
                    (*artico)++;
                }
            }
            else{
                if(i!=parent[ind]){
                    low[ind]=(low[ind]<tin[i])?low[ind]:tin[i];
                }
            }
        }        
    }
}

int articulation(int n,int adjmat[][n]){
    int artico=0,timer=0;
    int *visited=(int *)calloc(n,sizeof(int));
    int *tin=(int *)malloc(n*sizeof(int));
    int *low=(int *)malloc(n*sizeof(int));
    int *parent=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        parent[i]=-1;
    }

    for(int i=0;i<n;i++){
        if(!visited[i]){
            articuhelp(i,n,adjmat,visited,parent,tin,low,&artico,&timer);
        }
    }
    return artico;
}
int main()
{
    int n;
    scanf("%d", &n);
    int adjmat[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &adjmat[i][j]);
        }
    }

    int ind;
    char c;
    int co, si = 0;
    int *arr = (int *)malloc(sizeof(int));
    int bridgeco;
    int artico;
    do
    {
        scanf("%c", &c);
        switch (c)
        {
        case 'a':
            co = count(ind, n, adjmat);
            printf("%d\n", co);
            break;
        case 'b':
            sizeofcomp(ind, n, adjmat);
            printf("\n");
            break;

        case 'c':
            bridgeco=bridge(n,adjmat);
            printf("%d\n",bridgeco);
            break;
        case 'd':
            artico=articulation(n,adjmat);
            printf("%d\n",artico);
            break;
        case 'x':

            break;
        }
    } while (c != 'x');

    return 0;
}