#include<stdio.h>
#include<stdlib.h>


typedef struct queue{
    int qu[100];
    int f;
    int r;
}que;

que *createq(){
    que *newq=(que*)malloc(sizeof(que));
    newq->f=newq->r=-1;

    return newq;
}

void enque(que *q,int k){
    q->qu[++q->r]=k;
}

int deque(que *q){
    return q->qu[++q->f];
}

int isemptyq(que *q){
    return q->r==q->f;
}

int isbipartite(int ind,int n,int adjmat[][n]){
    int *visited=(int *)calloc(n,sizeof(int));
    int *color=(int *)calloc(n,sizeof(int)); //0-no color , 1-red ,2-blue
    visited[ind]=1;
    color[ind]=1;
    que *q=createq();
    enque(q,ind);
    
    while(!isemptyq(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(adjmat[d][i]==1){
                if(color[i]==color[d]){
                    return -1;
                }
                if(!visited[i]){
                    visited[i]=1;
                    color[i]=(color[d]==1)?2:1;
                    enque(q,i);
                }
            }
        }
    }
    return 1;
}

int hascycle(int ind,int n,int adjmat[][n]){
    int *visited=(int *)calloc(n,sizeof(int));
    int *parent=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        parent[i]=-1;
    }
    visited[ind]=1;
    que *q=createq();
    enque(q,ind);
    while(!isemptyq(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(adjmat[d][i]==1){
                if(!visited[i]){
                    enque(q,i);
                    parent[i]=d;
                    visited[i]=1;
                }
                else if(parent[d]!=i){
                    return 1;
                }
            }
            
        }
    }
    return -1;
}

int istree(int ind,int n,int adjmat[][n]){
    if(hascycle(ind,n,adjmat)==1){
        return -1;
    }
    int edge=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjmat[i][j]==1){
                edge++;
            }
        }
    }
    edge/=2;
    if(edge!=(n-1)){
        return -1;
    }

    int *visited=(int *)calloc(n,sizeof(int));
    que *q=createq();
    enque(q,ind);
    visited[ind]=1;
    while(!isemptyq(q)){
        int d=deque(q);
        for(int i=0;i<n;i++){
            if(adjmat[d][i]==1 && !visited[i]){
                visited[i]=1;
                enque(q,i);
            }
        }
    }
    for(int i=0;i<n;i++){
        if(!visited[i]){
            return -1;
        }
    }    
    return 1;
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

    char c;
    int bp;
    int hc;
    int tree;
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                bp=isbipartite(0,n,adjmat);
                if(bp==1){
                    printf("1\n");
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'b':
                hc=hascycle(0,n,adjmat);
                if(hc==1){
                    printf("1\n");
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'c':
                tree=istree(0,n,adjmat);
                if(tree==1){
                    printf("1\n");
                }
                else{
                    printf("-1\n");
                }
                break;
            case 'x':

                break;
        }
    }while(c!='x');
    
}