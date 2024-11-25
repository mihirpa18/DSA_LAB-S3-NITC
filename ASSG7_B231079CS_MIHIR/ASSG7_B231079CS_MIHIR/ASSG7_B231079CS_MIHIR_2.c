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

typedef struct union_edge{
    int u;
    int v;
    int weight;
}edge;

typedef struct make_set{
    int *parent;
    int *rank;
}set;

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

set *set_init(int n){
    set *news=malloc(sizeof(set));
    news->parent=(int *)malloc(n*sizeof(int));
    news->rank=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        news->parent[i]=i;
        news->rank[i]=0;
    }
    return news;
}

int ulti_parent(set *s,int x){
    if(x==s->parent[x]){
        return x;
    }
    return s->parent[x]=ulti_parent(s,s->parent[x]);
}

void union_set(int u,int v,set *s){
    u=ulti_parent(s,u);
    v=ulti_parent(s,v);
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
    edge t=*e1;
    *e1=*e2;
    *e2=t;
}

void sort(int n,edge e[]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(e[j].weight>e[j+1].weight){
                swap(&e[j],&e[j+1]);
            }
        }
    }
}

int kurskal_algo(int n,int edge_c,edge e[]){
    sort(edge_c,e);
    int total_wt=0;
    set *s=set_init(n);
    for(int i=0;i<edge_c;i++){
        int u=e[i].u;
        int v=e[i].v;
        int wt=e[i].weight;

        if(ulti_parent(s,u)!=ulti_parent(s,v)){
            union_set(u,v,s);
            total_wt+=wt;
        }
    }
    return total_wt;
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
    int edge_c=0;

    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        list *dummy=g->adjlist[head];
        while(dummy!=NULL){
            scanf("%d",&(dummy->weight));
            if(head<dummy->ver){
                e[edge_c].u=head;
                e[edge_c].v=dummy->ver;
                e[edge_c].weight=dummy->weight;
                edge_c++;

            }
            dummy=dummy->next;
        }
    }


    int weight=kurskal_algo(n,edge_c,e);
    printf("%d\n",weight);

}