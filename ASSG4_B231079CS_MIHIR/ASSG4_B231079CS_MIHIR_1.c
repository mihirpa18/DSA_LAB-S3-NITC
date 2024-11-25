#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void maxheapify(int arr[],int i,int n){
    int max=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<n && arr[l]>arr[max]){
        max=l;
    }
    if(r<n && arr[r]>arr[max]){
        max=r;
    }
    if(max!=i){
        swap(&arr[max],&arr[i]);
        maxheapify(arr,max,n);
    }
}


void insert(int *arr,int k,int *n){
    
    for(int j=0;j<*n;j++){
        if(arr[j]==k){
            return;
        }
    }
    (*n)++;
    int i=*n-1;
    arr[i]=k;

    while(i>0 && arr[i]>arr[(i-1)/2]){
        swap(&arr[i],&arr[(i-1)/2]);
        i=(i-1)/2;
        
    }   

}

int findmax(int *heap,int *n){
    if(*n==0){
        return -1;
    }
    return heap[0];
}

void extmax(int *heap,int *n){
    if(*n==0){
        printf("-1");
        return;
    }
    swap(&heap[0],&heap[*n-1]);
    (*n)--;
    maxheapify(heap,0,*n);    
}

void print(int *heap,int *n){
    for(int i=0;i<*n;i++){
        printf("%d ",heap[i]);
    }
}

void sort(int *heap,int *n){
    for(int i=(*n/2)-1;i>=0;i--){
        maxheapify(heap,i,*n);
    }
    for(int i=*n-1;i>=0;i--){
        swap(&heap[0],&heap[i]);
        maxheapify(heap,0,i);
    }
}

int klarge(int *heap,int k,int *n){
    if(k>*n){
        return -1;
    }
    int arr[*n];
    for(int i=0;i<*n;i++){
        arr[i]=heap[i];
    }
    sort(arr,n);
    return arr[*n-k];
}

void delkey(int *heap,int x,int *n){
    int i;
    for(i=0;i<*n;i++){
        if(heap[i]==x){
            break;
        }
    }
    if(i==*n){
        printf("-1");
        return;
    }

    if(*n==0){
        printf("0");
        return;
    }
    
    if(*n==1 && heap[0]==x){
        (*n)--;
        printf("0");
        return;
    }
    swap(&heap[i],&heap[*n-1]);
    (*n)--;
    maxheapify(heap,i,*n);

    print(heap,n);
}

void heapup(int *heap,int i){
    while(i>0 && heap[i]>heap[(i-1)/2]){
        swap(&heap[i],&heap[(i-1)/2]);
        i=(i-1)/2;
    }
}

void replace(int *heap,int oldv,int newv,int *n){
    int i;
    for(i=0;i<*n;i++){
        if(heap[i]==oldv){
            break;
        }
    }
    if(i==*n){
        int diff=abs(oldv-newv);
        printf("%d",diff);
        return;
    }
    heap[i]=newv;
    if(i>0 && heap[i]>heap[(i-1)/2]){
        heapup(heap,i);
    }
    else{
        maxheapify(heap,i,*n);
    }
    print(heap,n);
}

int main(){
    char c;
    int key,max,exmax,k,kele,x,oldv,newv;
    int n=0;
    int *heap=(int *)malloc(1000*sizeof(int));

    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                scanf("%d",&key);
                insert(heap,key,&n);
                break;
            case 'b':
                max=findmax(heap,&n);
                printf("%d\n",max);
                break;
            case 'c':
                if(n==0){
                    printf("-1");
                }
                else{
                    printf("%d ",heap[0]);
                    extmax(heap,&n);
                    print(heap,&n);
                }
                printf("\n");
                break;
            case 'd':
                scanf("%d",&k);
                kele=klarge(heap,k,&n);
                printf("%d\n",kele);
                break;
            case 'e':
                scanf("%d",&x);
                delkey(heap,x,&n);
                printf("\n");
                break;
            case 'f':
                scanf("%d",&oldv);
                scanf("%d",&newv);
                replace(heap,oldv,newv,&n);
                printf("\n");
                break;
            case 'g':
                
                break;
        }
    }while(c!='g');

    return 0;
}