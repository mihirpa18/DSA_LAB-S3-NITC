#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
    int id;
    int p;
}job;

void swap(job **a,job **b){
    job *temp=*a;
    *a=*b;
    *b=temp;
}

void minheapify(job *que[],int i,int n){
    int min=i;
    int l=2*i+1;
    int r=2*i+2;

    if(l<n && que[l]->p<que[min]->p){
        min=l;
    }
    if(r<n && que[r]->p<que[min]->p){
        min=r;
    }
    if(min!=i){
        swap(&que[i],&que[min]);
        minheapify(que,min,n);
    }
}

void heapup(job *que[],int i){
    while(i>0 && que[i]->p < que[(i-1)/2]->p){
        swap(&que[i],&que[(i-1)/2]);
        i=(i-1)/2;
    }
}

void add(job *que[],int id,int p,int *n){
    job *nj=(job *)malloc(sizeof(job));
    nj->id=id;
    nj->p=p;
    (*n)++;
    int i=*n-1;
    que[i]=nj;

    while(i>0 && que[i]->p < que[(i-1)/2]->p){
        swap(&que[i],&que[(i-1)/2]);
        i=(i-1)/2;
    }
}

void schedule(job *que[],int *n){
    if(*n==0){
        printf("-1\n");
        return;
    }
    printf("%d\n",que[0]->id);
    swap(&que[0],&que[*n-1]);
    (*n)--;
    minheapify(que,0,*n);
}

void nxtjob(job *que[],int *n){
    if(*n==0){
        printf("-1\n");
        return;
    }
    printf("%d\n",que[0]->id);
}

void replace(job *que[],int id,int np,int *n){
    int i;
    for(i=0;i<*n;i++){
        if(que[i]->id==id){
        break;
        }
    }
    if(i==*n){
        printf("-1\n");
        return;
    }
    que[i]->p=np;
    if(que[i]->p < que[(i-1)/2]->p){
        heapup(que,i);
    }
    else{
        minheapify(que,i,*n);
    }
}

void print(job *que[],int *n){
    if(*n==0){
        printf("-1\n");
        return;
    }
    for(int i=0;i<*n;i++){
        printf("%d %d\n",que[i]->id,que[i]->p);
    }
}

int main(){
    char c;
    int id,p,id2,np;
    job *que[1000];
    int n=0;
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                scanf("%d",&id);
                scanf("%d",&p);
                add(que,id,p,&n);
                break;
            case 'b':
                schedule(que,&n);
                break;
            case 'c':
                nxtjob(que,&n);
                break;
            case 'd':
                scanf("%d",&id2);
                scanf("%d",&np);
                replace(que,id2,np,&n);
                break;
            case 'e':
                print(que,&n);
                break;
            case 'g':

                break;
        }
    }while(c!='g');
    return 0;
}