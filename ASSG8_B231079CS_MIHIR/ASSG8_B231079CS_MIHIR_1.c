#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void count_array(char t[],int lps[]){
    int i=0;
    int j=1;
    int n=strlen(t);
    lps[0]=0;
    while(j<n){
        if(t[i]==t[j]){
            i++;
            lps[j]=i;
            j++;
        }
        else{
            if(i!=0){
                i=lps[i-1];
            }
            else{
                lps[j]=0;
                j++;
            }
        }
    }
}

void kmp(char s[],char t[]){
    int n=strlen(s);
    int m=strlen(t);
    int lps[m];
    int *temp=(int *)malloc(n*sizeof(int));
    int c=0;
    int i=0,j=0;
    count_array(t,lps);
    while(i<n){
        if(s[i]==t[j]){
            i++;
            j++;
            if(j==m){
                temp[c++]=(i-j);
                j=lps[j-1];
            }
        }
        else{
            if(j!=0){
                j=lps[j-1];
            }
            else{
                i++;
            }
        }
    }
    int ans;
    if(c>0){
        ans=temp[c-1];
        printf("%d %d\n",ans,c);
    }
    else{
        printf("-1\n");
        return;
    }
}

int main(){
    char sh;
    int cs=0;
    char s[1000000];
    fgets(s,sizeof(s),stdin);
    s[strcspn(s, "\n")] = '\0';
    char t[1000000];
    fgets(t,sizeof(t),stdin);
    t[strcspn(t, "\n")] = '\0';
    
    // int n=strlen(s);
    // int m=strlen(t);
    // printf("%d %d\n",n,m);
    // printf("%s ",s);
    // printf("%s",t);


    kmp(s,t);
}