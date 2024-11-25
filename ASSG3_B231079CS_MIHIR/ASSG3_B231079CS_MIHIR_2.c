#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int key;
    struct node *nxt;
}hash;

int hashfun(int key,int n){
    return key%n;
}

hash *create(int key){
    hash *newh=(hash *)malloc(sizeof(hash));
    newh->key=key;
    newh->nxt=NULL;
    return newh;
}

void insert(hash **htable,int k,int n){
    hash *newh=create(k);
    int index=hashfun(k,n);
    hash *temp=htable[index];
    if(temp==NULL || temp->key>newh->key){
        
        newh->nxt=htable[index];
        htable[index]=newh;
    }
    else{
        if(temp->key==newh->key){
            printf("-1\n");
             return;
            }
        while(temp->nxt!=NULL && temp->nxt->key<newh->key){               
            temp=temp->nxt;
        }

        if(temp->nxt!=NULL && temp->nxt->key==newh->key){
            printf("-1\n");
            return;
        }
        newh->nxt=temp->nxt;
        temp->nxt=newh;
    }
}

void search(hash **htable,int k,int n){
    int c;
    for(int i=0;i<n;i++){
        c=0;
        hash *temp=htable[i];
        while(temp!=NULL){
            c++;
            if(temp->key==k){               
                printf("%d ",i);
                printf("%d \n",c);
                return;
            }
            temp=temp->nxt;
        }
    }
    printf("-1\n");
}

void delete(hash **htable,int k,int n){
    int c;
    for(int i=0;i<n;i++){
        c=0;
        hash *temp=htable[i];
        hash *p=NULL;
        while(temp!=NULL){
            c++;
            if(temp->key==k){
                if(p==NULL){
                    htable[i]=temp->nxt;
                }
                else{
                    p->nxt=temp->nxt;      
                }
                free(temp);         
                printf("%d ",i);
                printf("%d \n",c);
                return;
            }
            p=temp;
            temp=temp->nxt;
        }
        
    }
    printf("-1\n");
}

void update(hash **htable,int ok,int nk,int n){
    int check=0;
    for(int i=0;i<n;i++){
        hash *temp=htable[i];
        while(temp!=NULL){
            if(temp->key==ok){
                check=1;
                break;
            }
            temp=temp->nxt;
        }
        if(check){
            break;
        }
    }

    if(!check){
        printf("-1\n");
        return;
    }

    for(int i=0;i<n;i++){
        hash *temp=htable[i];
        while(temp!=NULL){
            if(temp->key==nk){
                printf("-1\n");
                return;
            }
            temp=temp->nxt;
        }       
    }
    delete(htable,ok,n);
    insert(htable,nk,n);
}

void print(hash **htable,int ind,int n){
    hash *temp=htable[ind];
    while(temp!=NULL){
        printf("%d ",temp->key);
        temp=temp->nxt;
    }
}

int main(){
    char c;
    int n;
    scanf("%d",&n);
    hash **htable=(hash **)malloc(n*sizeof(hash *));
    for(int i=0;i<n;i++){
        htable[i]=NULL;
    }
    int k1,k2,k3,ok,nk,ind;
    
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                scanf("%d",&k1);
                insert(htable,k1,n);
                break;
            case 'b':
                scanf("%d",&k2);
                search(htable,k2,n);
                break;
            case 'c':
                scanf("%d",&k3);
                delete(htable,k3,n);
                break;
            case 'd':
                scanf("%d",&ok);
                scanf("%d",&nk);
                update(htable,ok,nk,n);
                break;
            case 'e':
                scanf("%d",&ind);
                print(htable,ind,n);
                printf("\n");
                break;
            case 'f':
                break;

        }
    }while(c!='f');
    return 0;
}
