#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a,int b){
    return (a>b)?a:b;
}

void badchar_table(char *t,int m,int table[]){
    int ts=256;
        for(int i=0;i<ts;i++){
            table[i]=-1;
        }
        for(int i=0;i<m;i++){
            table[(int)t[i]]=i;
        }
}

void boyer(char *s,char *t){
    int n=strlen(s);
    int m=strlen(t);
    int ts=256;
    
    int table[ts];
    badchar_table(t,m,table);
    int x=0;
    int check=0;
    
    while(x<=(n-m)){
        int j=m-1;
        while(j>=0 && t[j]==s[x+j]){
            j--;
        }
        if(j<0){
            printf("%d\n",x);
            check=1;
            x+=(x+m < n)?m-table[(int)s[x+m]]:1;
        }
        else{
            x+=max(1,j-table[(int)s[x+j]]);
        }
    }
    if(!check){
        printf("-1\n");
    }
    
}
int main()
{
    char s[1000000];
    fgets(s,sizeof(s),stdin);
    s[strcspn(s, "\n")] = '\0';
    char t[1000000];
    fgets(t,sizeof(t),stdin);
    t[strcspn(t, "\n")] = '\0'; 
    // printf("%s",s);
    // printf("%s",t);
    
    boyer(s,t); 
    return 0;
}