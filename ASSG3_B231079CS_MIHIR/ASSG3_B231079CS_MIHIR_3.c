#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int hashfun(int key,int n){
    return (key)%n;
}

int isprime(int num){
    if(num<2){
        return 0;
    }
    for(int i=2;i<num;i++){
        if(num%i==0)
            return 0;
    }
    return 1;
}

int megaprime(int n){
    for(int i=n-1;i>1;i--){
        if(isprime(i)){
            return i;
        }
    }
    return -1;
}

int hashfun2(int key,int n){
    int prime=megaprime(n);
    return prime-(key%prime);  
}

void initialize(int *htable,int n){
    for(int i=0;i<n;i++){
        htable[i]=-1;
    }
}

void linearprob(int htable[],int key[],int n,int m){
    int c=0;
    initialize(htable,n);
    for(int i=0;i<m;i++){
        int j=0;
        int hash=hashfun(key[i],n);
        while(htable[(hash + j)%n]!=-1){
                j++;
                c++;
        }
        hash=(hash + j)%n;
        htable[hash]=key[i];
        printf("%d ",hash);
    }
    printf("\n%d\n",c);
}

void quadraticprob(int htable[],int key[],int n,int m){
    int c=0;
    initialize(htable,n);
    for(int j=0;j<m;j++){
        int i=0;
        int hash=hashfun(key[j],n);
        while(htable[(hash + (i*i))%n]!=-1){
            i++;
            c++;
        }
        hash=(hash+(i*i))%n;
        htable[hash]=key[j];
        printf("%d ",hash);
    }
    printf("\n%d\n",c);
}

void doublehash(int htable[],int key[],int n,int m){
    int c=0;
    initialize(htable,n);
    for(int j=0;j<m;j++){
        int i=0;
        int hash;
        int hash1=hashfun(key[j],n);
        int hash2=hashfun2(key[j],n);

        while(htable[(hash1 + i*hash2)%n]!=-1){
            i++;
            c++;
        }
        hash=(hash1+ i*hash2)%n;
        htable[hash]=key[j];
        printf("%d ",hash);
    }
    printf("\n%d\n",c);
}



int main(){
    char c;
    int n;
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    int arr[m];
    for(int i=0;i<m;i++){
        scanf("%d",&arr[i]);
    }
    int htable[n];
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                linearprob(htable,arr,n,m);
                break;
            case 'b':
                quadraticprob(htable,arr,n,m);
                break;
            case 'c':
                doublehash(htable,arr,n,m);
                break;
            case 'd':
                break;
        }
    }while(c!='d');
    return 0;
}