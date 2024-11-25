#include<stdio.h>
#include<stdlib.h>

int hashfun(int key,int n){
    return key%n;
}

void prob(int hash[],int n,int key){
    int i=0;
    int h=hashfun(key,n);
    while(hash[(h + (i*i))%n]!=-1){
        i++;
    }
    h=(h+(i*i))%n;
    hash[h]=key;
}

void rehash(int hash[],int arr[],int oldn,int newn,int count){
    
    for(int i=0;i<newn;i++){
        hash[i]=-1;
    }
    for(int i=0;i<count;i++){
        prob(hash,newn,arr[i]);
    }
}

int main(){
    char c;
    int n;
    scanf("%d",&n);
    int count=0;
    int key,oldn;
    int hash[1000];
    int arr[1000];
    for(int i=0;i<n;i++){
        hash[i]=-1;
    }
    do{
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf("%d",&key);
                arr[count]=key;
                count++;
                
                if(count>0.75*n){
                    oldn=n;
                    n*=2;
                    rehash(hash,arr,oldn,n,count);
                }
                else{
                    prob(hash,n,key);
                }

                break;
            case 'd':
                for(int i=0;i<n;i++){
                    printf("%d ",hash[i]);
                }
                printf("\n");
                break;
            case 'e':

                break;
        }
    }while(c!='e');
    return 0;
}