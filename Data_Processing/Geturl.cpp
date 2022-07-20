#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
string input,output;
char p[2][1001];
int nex[2][1001];
void gnex(){
    for(int o=0;o<2;o++){
        #define fs p[o]
        #define fnex nex[o]
        int len=strlen(fs+1);
        for(int i=2;i<=len;i++){
            int now=i-1;
            while(fs[fnex[now]+1]!=fs[i]&&now) now=fnex[now];
            if(fs[fnex[now]+1]==fs[i]) fnex[i]=fnex[now]+1;
        }
        #undef fs
        #undef fnex
    }
}
vector<int> pos[2];
int main()
{
    puts("Please enter the input name,the output name,previous and last string you want to find.");
    puts("Warning:Do not");
    cin>>input>>output;
    scanf("%s %s",p[0]+1,p[1]+1);
    gnex();
    freopen(input.c_str(),"r",stdin);
    freopen(output.c_str(),"w",stdout);
    char s[1000010];
    while(~scanf("%s",s+1)){
        pos[0].clear(),pos[1].clear();
        int n=strlen(s+1);
        for(int o=0;o<2;o++){
            #define fs p[o]
            #define fnex nex[o]
            int m=strlen(fs+1),now=0;
            for(int i=1;i<=n;i++){
                while(now&&s[i]!=fs[now+1]) now=fnex[now];
                if(s[i]==fs[now+1]) now++;
                if(now==m) pos[o].push_back(i),now=0;
            }
            #undef fs
            #undef fnex
        }
        if(pos[0].size()!=pos[1].size()) puts("ERROR");
        else for(int i=0;i<pos[0].size();i++){
            printf("%s",p[0]+1);
            for(int j=pos[0][i]+1;j<=pos[1][i];j++) putchar(s[j]);
            putchar('\n');
        }
    }
    return 0;
}