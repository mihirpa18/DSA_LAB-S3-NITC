#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node{
    char *name;
    char *rnum;
    int age;
    struct node *next;
}student;

student *create(char *name,char *rnum,int age){
    student *nst=(student *)malloc(sizeof(student));
    nst->name = (char *)malloc(strlen(name) + 1);
    strcpy(nst->name,name);
    nst->rnum = (char *)malloc(strlen(rnum) + 1);
    strcpy(nst->rnum,rnum);
    nst->age=age;
    nst->next=NULL;
    return nst;
}


int hashfun(char *name,int age){
    int s=0;
    int h;
    for(int i=0;i<strlen(name);i++){
        s+=name[i];
    }

    h=(s+age)%4;

    return h;
}

void insert(student **htable,char *name,char *rnum,int age){
    student *nst=create(name,rnum,age);
    int h=hashfun(name,age);
    student *temp=htable[h];

    if(temp==NULL || strcmp(temp->name,nst->name)>0){
            nst->next=htable[h];
            htable[h]=nst;
    }
    else{
            while(temp->next!=NULL && strcmp(temp->next->name,nst->name)<0){
                temp=temp->next;
            }
            nst->next=temp->next;
            temp->next=nst;
        }
    
}

int grpindex(char *name,student **htable){
    for(int i=0;i<4;i++){
        student *dum=htable[i];
        while(dum!=NULL){
            if(strcmp(dum->name,name)==0){
                int ind=hashfun(dum->name,dum->age);
                return ind;
            }
            dum=dum->next;
        }
    }
    return -1;
}

void sort(student **htable,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(strcmp(htable[j]->name,htable[j+1]->name)>0){
                student *temp=htable[j];
                htable[j]=htable[j+1];
                htable[j+1]=temp;
            }
        }
    }
}
void grp_co_list(student **htable,int k){
    student *arr[100];
    int j=0;
    int c=0;
    if(k<0 || k>3){
        printf("-1");
        return;
    }
    student *temp=htable[k];
    if(temp==NULL){
        printf("0");
        return;
    }
    while(temp!=NULL){
        c++;
        temp=temp->next;
    }
    printf("%d ",c);
    student *dummy=htable[k];
    while(dummy!=NULL){
        arr[j++]=dummy;
        dummy=dummy->next;
    }
    sort(arr,j);
    for(int i=0;i<j;i++){
        printf("%s ",arr[i]->name);
    }

}

void grp_br_list(student **htable,int m,char *br){
    if(m<0 || m>3){
        return;
    }
    student *temp=htable[m];
    int c=0;
    while(temp!=NULL){
        int n=strlen(temp->rnum);
        if(toupper(temp->rnum[n-2])==toupper(br[0]) && toupper(temp->rnum[n-1])==toupper(br[1])){
            c++;
            printf("%s ",temp->name);
            temp=temp->next;
        }
        else{
            temp=temp->next;
        }
    }
    if(c==0){
        printf("-1");
    }
    
}

void details(student **htable,char *rnum){
    for(int i=0;i<4;i++){
        student *temp=htable[i];
        while(temp!=NULL){
            if(strcmp(temp->rnum,rnum)==0){
                printf("%s %d %s\n",temp->name,temp->age,temp->rnum+strlen(temp->rnum)-2);
                return;
            }
            else{
                temp=temp->next;
            }
        }
    }
    printf("-1\n");
}



int grp_tfr_br(student **htable,int s,int t,char br[]){
    if(s<0 || s>3 || t<0 ||t>3 || s==t){
        return -1;
    }
    student *arr[100];
    int c=0,j=0;
    student *temp=htable[s];
    student *old=NULL;
    while(temp!=NULL){
        int n = strlen(temp->rnum);
        if (toupper(temp->rnum[n - 2]) == toupper(br[0]) && toupper(temp->rnum[n - 1]) == toupper(br[1])) {
            student *nxt=temp->next;
            if(old==NULL){
                htable[s]=nxt;
            }
            else{
                old->next=nxt;
            }

            temp->next=htable[t];
            htable[t]=temp;
            
            temp=nxt;
            c++;
        }
        else{
            old=temp;
            temp=temp->next;
        }
    
    }
    
    return c;
}

int main(){
    char c;
    int n;
    scanf("%d",&n);
    char name[100];
    char rnum[20];
    int age;

    student **htable=(student **)malloc(4*sizeof(student *));
    for(int i=0;i<4;i++){
        htable[i]=NULL;
    }

    for(int i=0;i<n;i++){
        scanf("%s",name);
        scanf("%s",rnum);
        scanf("%d",&age);
        insert(htable,name,rnum,age);
    }
    char n1[500],br[2],rolln[50],br2[50];
    int ind,k,m,s,t;
    
    do{
        scanf("%c",&c);
        switch(c){
            case 'a':
                scanf("%s",n1);
                ind=grpindex(n1,htable);
                printf("%d\n",ind);
                break;
            case 'b':
                scanf("%d",&k);
                grp_co_list(htable,k);
                printf("\n");
                break;
            case 'c':
                scanf("%d",&m);
                scanf("%s",br);
                grp_br_list(htable,m,br);
                printf("\n");
                break;
            case 'd':
                scanf("%s",rolln);
                details(htable,rolln);
                break;
            case 'e':
                scanf("%d",&s);
                scanf("%d",&t);
                scanf("%s",br2);
                int co=grp_tfr_br(htable,s,t,br2);
                printf("%d\n",co);
                break;
            case 'f':
                break;
        }
    }while(c!='f');
    return 0;
}