#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
   int id;
   int seve;
   char *name; 
}patient;

void swap(patient **a,patient **b){
    patient *temp=*a;
    *a=*b;
    *b=temp;
}

void minheapify(patient **pq,int i,int n){
    int min=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<n && pq[l]->seve<pq[min]->seve){
        min=l;
    }
    if(r<n && pq[r]->seve<pq[min]->seve){
        min=r;
    }
    if(min!=i){
        swap(&pq[i],&pq[min]);
        minheapify(pq,min,n);
    }
}

void heapup(patient **pq,int i){
    while(i>0 && pq[i]->seve < pq[(i-1)/2]->seve){
        swap(&pq[i],&pq[(i-1)/2]);
        i=(i-1)/2;
    }
}
void admit(patient **pq,int id,int sever,char name[],int *n){
    (*n)++;
    int i=*n-1;
    pq[i]=(patient *)malloc(sizeof(patient));
    pq[*n-1]->id=id;
    pq[*n-1]->seve=sever;
    pq[i]->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(pq[*n-1]->name,name);

    while(i>0 && pq[i]->seve < pq[(i-1)/2]->seve){
        swap(&pq[i],&pq[(i-1)/2]);
        i=(i-1)/2;
    }

    for(int j=0;j<*n;j++){
        printf("%d ",pq[j]->id);
    }
    printf("\n");
}

void treat(patient **pq,int *n){
    if(*n==0){
        printf("-1");
        return;
    }
    printf("%d %s",pq[0]->id,pq[0]->name);
    swap(&pq[0],&pq[*n-1]);
    (*n)--;
    minheapify(pq,0,*n);
}

void update(patient **pq,int id,int nsevere,int *n){
    int i;
    for(i=0;i<*n;i++){
        if(pq[i]->id==id){
        break;
        }
    }
    if(i==*n){
        printf("-1\n");
        return;
    }
    pq[i]->seve=nsevere;
    if(pq[i]->seve < pq[(i-1)/2]->seve){
        heapup(pq,i);
    }
    else{
        minheapify(pq,i,*n);
    }

    for(int j=0;j<*n;j++){
        printf("%d ",pq[j]->id);
    }
    printf("\n");
}

void query(patient **pq,int id,int *n){
    int i;
    for(i=0;i<*n;i++){
        if(pq[i]->id==id){
        break;
        }
    }
    if(i==*n){
        printf("-1\n");
        return;
    }
    printf("%s %d\n",pq[i]->name,pq[i]->seve);
}

void sort(patient **pq,int *n){
    for(int i=(*n/2)-1;i>=0;i--){
        minheapify(pq,i,*n);
    }
    for(int i=*n-1;i>=0;i--){
        swap(&pq[0],&pq[i]);
        minheapify(pq,0,i);
    }
}

void mostsevere(patient **pq,int *n){
    patient *arr[*n];
    if(*n==0){
        printf("-1\n");
        return;
    }
    for(int i=0;i<*n;i++){
        arr[i]=pq[i];
    }
    sort(arr,n);
    if(*n<3){
        for(int i=*n-1;i>=0;i--){
            printf("%d %s %d\n",arr[i]->id,arr[i]->name,arr[i]->seve);
        }
    }
    else{
        for(int i=*n-1;i>(*n-4);i--){
            printf("%d %s %d\n",arr[i]->id,arr[i]->name,arr[i]->seve);
        }
    }

}

int main(){
    char c;
    int id,severe,id2,nsev,id3;
    char name[50];
    int n=0;
    patient **pq=(patient **)malloc(1000*sizeof(patient *));
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                scanf("%d",&id);
                scanf("%d",&severe);
                scanf("%s",name);
                admit(pq,id,severe,name,&n);
                break;
            case 'b':
                treat(pq,&n);
                printf("\n");
                break;
            case 'c':
                scanf("%d",&id2);
                scanf("%d",&nsev);
                update(pq,id2,nsev,&n);
                break;
            case 'd':
                scanf("%d",&id3);
                query(pq,id3,&n);
                break;
            case 'e':
                mostsevere(pq,&n);
                break;
            case 'g':

                break;
        }
    }while(c!='g');
    return 0;
}