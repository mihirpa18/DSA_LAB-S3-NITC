#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int ver;
    struct node *nxt;
}node;

typedef struct graph{
    int numver;
    struct node **adjlist;
    int *visited;
}graph;

node *createn(int v){
    node *newn=(node *)malloc(sizeof(node));
    newn->ver=v;
    newn->nxt=NULL;

    return newn;
}

graph *createg(int num){
    graph *newg=(graph *)malloc(sizeof(graph));
    newg->numver=num;
    newg->adjlist=(node **)malloc(num*sizeof(node*));
    newg->visited=(int *)calloc(num,sizeof(int));

    for(int i=0;i<num;i++){
        newg->adjlist[i]=NULL;
    }

    return newg;

}

void add(graph *g,int k,int p){
    node *temp=createn(p);
    temp->nxt=g->adjlist[k];
    g->adjlist[k]=temp;
}

void print(graph *g){
    for(int i=0;i<g->numver;i++){
        node *temp=g->adjlist[i];
        while(temp!=NULL){
            printf("%d ",temp->ver);
            temp=temp->nxt;
        }
    }
}

void listToMatrix(int n,int adjmat[][n],graph *g){
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            adjmat[i][j]=0;
        }
    }
    for(int i=1;i<n;i++){
        node *temp=g->adjlist[i];
        while(temp!=NULL){
            int vertex=temp->ver;
            adjmat[i][vertex]=1;
            temp=temp->nxt;
        }
    }
}

int dfsCycle(int n,int ind,int adjmat[][n],int *visited,int *pathvisit){
    
    visited[ind]=1;
    pathvisit[ind]=1;
    for(int i=1;i<n;i++){
        if(adjmat[ind][i]==1){
            if(!visited[i]){
                if(dfsCycle(n,i,adjmat,visited,pathvisit)==1){
                    return 1;
                }
            }
            else if(pathvisit[i]==1){
                return 1;
            }
        }
    }
    pathvisit[ind]=0;
    return 0;
}

int checkCycle(int n,int adjmat[][n]){
    int *visited=(int *)calloc(n,sizeof(int));
    int *pathvisit=(int *)calloc(n,sizeof(int));

    for(int i=1;i<n;i++){
        if(!visited[i]){
            if(dfsCycle(n,i,adjmat,visited,pathvisit)==1){
                return 1;
            }
        }
    }
    return -1;
}

void dfsConnected(int ind,int n,int adjmat[][n],int *visited){
    visited[ind]=1;
    for(int j=1;j<n;j++){
        if(adjmat[ind][j]==1 && !visited[j]){
            dfsConnected(j,n,adjmat,visited);
        }
    }
}

int countStronglyConnected(int n,int adjmat[][n]){
    int count=0;
    int *visited=(int *)calloc(n,sizeof(int));
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            adjmat[i][j]=adjmat[j][i];
        }
    }
    for(int i=1;i<n;i++){
        if(!visited[i]){
            dfsConnected(i,n,adjmat,visited);
            count++;
        }
    }
    return count;
}

int main(){
    int n;
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    int adjmat[n+1][n+1];
    graph *g=createg(n+1);
   
    char c;
    char ch;
    int tail,head;
    for(int i=0;i<n;i++){
        scanf("%d",&head);
        while(1){
            scanf("%c",&ch);
            if(ch=='\n'){
                break;
            }
            scanf("%d",&tail);
            add(g,head,tail);
        }
    }
    
    // print(g);

    listToMatrix(n+1,adjmat,g);
    for(int i=1;i<n+1;i++){
        for(int j=1;j<n+1;j++){
            printf("%d ",adjmat[i][j]);
        }
        printf("\n");
    }
    int cycle,stconnect;
    do{
        scanf("%c",&c);
        switch (c){
        case 'a':
            cycle=checkCycle(n+1,adjmat);
            if(cycle==1){
                printf("-1\n");
            }
            else{
                printf("1\n");
            }
            break;
        case 'b':
            stconnect=countStronglyConnected(n+1,adjmat);
            printf("%d\n",stconnect);
            break;
        case 'x':

            break; 
        }
    }while(c!='x');
    
}