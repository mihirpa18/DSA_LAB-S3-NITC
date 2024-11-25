#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int ver;
    int weight;
    struct node *next;
}list;

typedef struct graph{
    list **adjlist;
}graph;

typedef struct edge{
    int u;
    int v;
    int wt;
}edge;

typedef struct set{
    int *parent;
    int *rank;
}set;

set *make_set(int n){
    set *news=malloc(sizeof(set));
    news->parent=(int *)malloc(n*sizeof(int));
    news->rank=(int *)malloc(n*sizeof(int));

    for(int i=0;i<n;i++){
        news->parent[i]=i;
        news->rank[i]=0;
    }

    return news;
}

int ultip(int x,set *s){
    if(x==s->parent[x]){
        return x;
    }
    return s->parent[x]=ultip(s->parent[x],s);
}

void unionedge(int u,int v,set *s){
    u=ultip(u,s);
    v=ultip(v,s);
    if(u==v){
        return;
    }
    if(s->rank[u]<s->rank[v]){
        s->parent[u]=v;
    }
    else if(s->rank[v]<s->rank[u]){
        s->parent[v]=u;
    }
    else{
        s->parent[u]=v;
        s->rank[v]++;
    }
}

list *createn(int ver,int wt){
    list *newn=malloc(sizeof(list));
    newn->ver=ver;
    newn->weight=wt;
    newn->next=NULL;
    return newn;
}

graph *createg(int n){
    graph *newg=malloc(sizeof(graph));
    newg->adjlist=malloc(n*sizeof(list *));

    for(int i=0;i<n;i++){
        newg->adjlist[i]=NULL;
    }

    return newg;
}


void add_edge(graph *g,int head,int tail,int wt){
    if(g->adjlist[head]==NULL){
        g->adjlist[head]=createn(tail,wt);
        return;
    }
    list *temp=g->adjlist[head];    
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=createn(tail,wt);
    return ;
}

void swap(edge *e1,edge *e2){
    edge temp=*e1;
    *e1=*e2;
    *e2=temp;
}

void sort(int n,edge e[]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(e[j].wt > e[j+1].wt){
                swap(&e[j],&e[j+1]);
            }
        }
    }
}

int kruskal(int n,edge e[],int ec){
    int total=0;
    set *s=make_set(n);
    sort(ec,e);
    for(int i=0;i<ec;i++){
        int u=e[i].u;
        int v=e[i].v;
        int wt=e[i].wt;
        if(ultip(u,s)!=ultip(v,s)){
            unionedge(u,v,s);
            total+=wt;
        }
    }
    return total;
}

int main(){
    int n;
    scanf("%d",&n);
    int tail;
    char c;
    graph *g=createg(n);
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        while(1){
            scanf("%c",&c);
            if(c=='\n'){
                break;
            }
            scanf("%d",&tail);
            add_edge(g,head,tail,0);
        }
    }
    int num=n*(n-1)/2;
    edge *e=malloc(num*sizeof(edge));
    int ec=0;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        list *temp=g->adjlist[head];
        while(temp!=NULL){
            scanf("%d",&temp->weight);
            if(head<temp->ver){
                e[ec].u=head;
                e[ec].v=temp->ver;
                e[ec].wt=temp->weight;
                ec++;
            }
            temp=temp->next;
        }
    }

    int tot=kruskal(n,e,ec);
    printf("%d\n",tot);
}
