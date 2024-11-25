#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int k;
    int weight;
    struct node *nxt;
}list;

typedef struct graph{
    list **adjlist;
    int *visited;
}graph;

typedef struct heap{
    int dist;
    int node;
}heap;

void swap(heap **a,heap **b){
    heap *temp=*a;
    *a=*b;
    *b=temp;
}

void minheap(int i,int *n,heap *h[]){
    int l=2*i+1;
    int r=2*i+2;
    int min=i;
    if(l<*n && h[l]->dist < h[min]->dist){
        min=l;
    }
    if(r<*n && h[r]->dist < h[min]->dist){
        min=r;
    }
    if(min!=i){
        swap(&h[i],&h[min]);
        minheap(min,n,h);
    }
}

int isempty(heap *h[],int *n){
    return (*n==0);
}

int extractmin(heap *h[],int *n){
    int min=h[0]->node;
    swap(&h[0],&h[*n-1]);
    *n=(*n-1);
    minheap(0,n,h);
     return min;
}

void heapup(heap *h[],int i){
    while(i>0 && h[i]->dist < h[(i-1)/2]->dist){
        swap(&h[i],&h[(i-1)/2]);
        i=(i-1)/2;
    }
}

void addpq(heap *h[],int k,int wt,int *n){
    (*n)++;
    h[(*n-1)]=malloc(sizeof(heap));
    h[(*n-1)]->node=k;
    h[(*n-1)]->dist=wt;
    int i=*n-1;
    heapup(h,i);
}

void updatepq(heap *h[],int *n,int node,int wt){
    for(int i=0;i<*n;i++){
        if(h[i]->node==node){
            if(h[i]->dist > wt){
                h[i]->dist=wt;
                heapup(h,i);
            }
            else if(h[i]->dist < wt){
                h[i]->dist=wt;
                minheap(i,n,h);
            }
        }
    }
}

list *createn(int k,int wt){
    list *newn=malloc(sizeof(list));
    newn->k=k;
    newn->weight=wt;
    newn->nxt=NULL;
    return newn;
}

graph *createg(int num){
    graph *newg=malloc(sizeof(graph));
    newg->adjlist=malloc(num*sizeof(list*));
    newg->visited=calloc(num,sizeof(int));

    for(int i=1;i<=num;i++){
        newg->adjlist[i]=NULL;
    }

    return newg;
}

void addg(graph *g,int head,int tail,int wt){
    list *temp=createn(tail,wt);
    temp->nxt=g->adjlist[head];
    g->adjlist[head]=temp;
}

void reverseAdjList(list **adjlist, int vertex) {
    list *prev = NULL;
    list *current = adjlist[vertex];
    list *next = NULL;

    while (current != NULL) {
        next = current->nxt; 
        current->nxt = prev; 
        prev = current;      
        current = next;      
    }
    adjlist[vertex] = prev; 
}



void dijkstrasAlgo(graph *g,heap *h[],int s,int n){
    int distance[n+1];
    int hsize=0;
    for(int i=1;i<=n;i++){
        distance[i]=1000000;
    }
    distance[s]=0;

    for(int i=1;i<=n;i++){
        addpq(h,i,distance[i],&hsize);
    }

    while(!isempty(h,&hsize)){
        int ind=extractmin(h,&hsize);
        list *dummy=g->adjlist[ind];
        while (dummy!=NULL){
            int k=dummy->k;
            if(distance[ind]+dummy->weight < distance[k]){
                distance[k]=distance[ind]+dummy->weight;
                updatepq(h,&hsize,k,distance[k]);
            }
            dummy=dummy->nxt;
        }
    }

    for(int i=1;i<=n;i++){
        printf("%d ",distance[i]);
    }

}

int main(){
    int n;
    scanf("%d",&n);
    graph *g=createg(n+1);
    heap *h[n];
    char c;
    int tail,wt;
    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        while(1){
            scanf("%c",&c);
            if(c=='\n'){
                break;
            }
            scanf("%d",&tail);
            addg(g,head,tail,0);         
        }
    }

    for (int i = 1; i <= n; i++) {
        reverseAdjList(g->adjlist, i); 
    }

    for(int i=0;i<n;i++){
        int head;
        scanf("%d",&head);
        list *temp=g->adjlist[head];
        while(temp!=NULL){
            scanf("%d",&(temp->weight));
            temp=temp->nxt;
        }
    }

    int s;
    scanf("%d",&s);
    dijkstrasAlgo(g,h,s,n);

}