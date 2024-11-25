#include<stdio.h>
#include<stdlib.h>

void set_init(int n,int *parent,int *size){
    for(int i=0;i<n;i++){
        parent[i]=i;
        size[i]=1;
    }
}

int ulti_parent(int ind,int *parent){
    if(ind==parent[ind]){
        return ind;
    }
    return parent[ind]=ulti_parent(parent[ind],parent);
}

void union_set(int u,int v,int *parent,int *size){
    u=ulti_parent(u,parent);
    v=ulti_parent(v,parent);
    if(u==v){
        return;
    }
    if(size[u]<size[v]){
        parent[u]=v;
        size[v]+=size[u];
    }
    else{
        parent[v]=u;
        size[u]+=size[v];
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int parent[n];
    int size[n];
    set_init(n,parent,size);
    union_set(1,2,parent,size);
    union_set(2,3,parent,size);
    union_set(4,5,parent,size);
    union_set(6,7,parent,size);
    union_set(5,6,parent,size);

    if(ulti_parent(1,parent)==ulti_parent(7,parent)){
        printf("Same set\n");
    }
    else{
        printf("Not same\n");
    }
    union_set(3,7,parent,size);
    if(ulti_parent(1,parent)==ulti_parent(7,parent)){
        printf("Same set\n");
    }
    else{
        printf("Not same\n");
    }
}