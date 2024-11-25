#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int node;
    struct node *nxt;
}list;

typedef struct graph{
    list **adjlist;

}graph;

list *createn(int node){
    list *newn=malloc(sizeof(list));
    newn->node=node;
    newn->nxt=NULL;

    return newn;
}

graph *createg(int n){
    graph *newg=malloc(sizeof(graph));
    newg->adjlist=malloc(n*sizeof(list *));
    for(int i=1;i<=n;i++){
        newg->adjlist[i]=NULL;
    }

    return newg;
}

void add(graph *g,int head,int tail){
    if(g->adjlist[head]==NULL){
        g->adjlist[head]=createn(tail);
    }
    else{
        list *temp=g->adjlist[head];
        while(temp->nxt!=NULL){
            temp=temp->nxt;
        }
        temp->nxt=createn(tail);
    }
}

void list_to_matrix(int n,int adjmat[][n],graph *g){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adjmat[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        list *temp=g->adjlist[i];
        while(temp!=NULL){
            adjmat[i][temp->node]=1;
            temp=temp->nxt;
        }
    }
}

void stack_help(int n,int ind,int adjmat[][n],int visited[],int *stack,int *k){
    visited[ind]=1;
    for(int i=1;i<n;i++){
        if(adjmat[ind][i]==1 && !visited[i]){
            stack_help(n,i,adjmat,visited,stack,k);
        }
    }
    stack[(*k)++]=ind;
}

void count_help(int n,int ind,int adjmat[][n],int visited[]){
    visited[ind]=1;
    for(int i=1;i<n;i++){
        if(adjmat[ind][i]==1 && !visited[i]){
            count_help(n,i,adjmat,visited);
        }
    }
}


int scc(int n,int adjmat[][n]){
    int c=0;
    int *visited=(int *)calloc(n,sizeof(int));
    int *stack=(int *)calloc(n,sizeof(int));
    int k=0;
    int trans[n][n];
    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            trans[i][j]=adjmat[j][i];
        }
    }
    for(int i=1;i<n;i++){
        if(!visited[i]){
            stack_help(n,i,adjmat,visited,stack,&k);
        }
    }

    for(int i=1;i<n;i++){
        visited[i]=0;
    }

    for(int i=k-1;i>=0;i--){
        if(!visited[stack[i]]){
            count_help(n,stack[i],adjmat,visited);
            c++;
        }
    }
    return c;

}

int main(){
    int n,m;
    scanf("%d",&n);
    scanf("%d",&m);
    graph *g=createg(n+1);
    int adjmat[n+1][n+1];
    char ch;
    int tail;
    for(int i=0;i<n;i++){
        int head;
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

    for(int i=1;i<=n;i++){
        list *temp=g->adjlist[i];
        printf("%d ",i);
        while(temp!=NULL){
            printf("%d ",temp->node);
            temp=temp->nxt;
        }
        printf("\n");
    }

    list_to_matrix(n+1,adjmat,g);
     for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d ",adjmat[i][j]);
        }
        printf("\n");
    }

    int sccc=scc(n+1,adjmat);
    printf("%d\n",sccc);
}