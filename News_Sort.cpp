#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
#include<vector>
#include<iostream>
#include<sys/stat.h>
#include<map>
#include<direct.h>
#include<windows.h>
#include<io.h>
#include<fstream>
#include<cstdlib>
using namespace std;
const string m=".\\Model";
map<string,int> num;
map<string,map<string,int>> book;
ifstream FI;
ofstream FO;
void Print_Sort(){
    string file=m+"\\sort";
    FO.open(file,ios::out);
    for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
        FO<<iter->first<<" "<<iter->second<<endl;
    }
    FO.close();
}
void Print_Single(string file,string $){
    FO.open(file,ios::out);
    for(map<string,int>::iterator iter=book[$].begin();iter!=book[$].end();iter++){
        FO<<iter->first<<" "<<iter->second<<endl;
    }
    FO.close();
}
void Get_Output_Folder(string folder){
	if (_access(folder.c_str(),0)==-1) _mkdir(folder.c_str());	
}
inline bool Exists_Test(const string& name) {
    struct stat test;   
    return (stat(name.c_str(),&test)==0);
}
struct Word{
    string s;
    int ti;
    const bool operator <(const Word &b){
        return s<b.s;
    }
};
inline void File_Create(string file){
    FO.open(file,ios::out);
    FO.close();
}
void Previous_Read(string $){//Model data to book[$]
    string file=m+"\\"+$+".dat";
    if(!Exists_Test(file)) File_Create(file);
    FI.open(file,ios::in);
    string w;
    int tt;
    while(FI>>w>>tt) book[$][w]=tt;
    FI.close();
}
string rd[100000];int siz;
void File_To_rd(string file){//Data file to rd string
    string Command="python -u Divide.py "+file+" temp";
    system(Command.c_str());
    FI.open("temp",ios::in);
    siz=1;
    while(FI>>rd[siz]) siz++;
    siz--;
    FI.close();
    sort(rd+1,rd+1+siz);
    siz=unique(rd+1,rd+1+siz)-rd-1;
    remove(".\\temp");
}
void Update_Single_File(string file,string $){
    File_To_rd(file);
    num[$]++;
    for(int i=1;i<=siz;i++) book[$][rd[i]]++;
}
void getFileNames(string path, vector<string>& files)
{
    string command="python -u GetFileName.py "+path;
	system(command.c_str());
    string r;
    FI.open("temp",ios::in);
    while(FI>>r) files.push_back(path+"\\"+r);
    FI.close();
    remove(".\\temp");
}
void Update_Model(){
    puts("Enter the folder name.");
    string Folder;
    cin>>Folder;
    puts("Enter the folder sort.");
    string $;//A little joke.
    cin>>$;
    Previous_Read($);
    vector<string> names;
	getFileNames(Folder,names);
    for(const auto &ph:names) Update_Single_File(ph,$);
    Print_Sort();
    Print_Single(m+"\\"+$+".dat",$);
}
void Begin(){
    Get_Output_Folder(m);
    string file=m+"\\sort";
    if(!Exists_Test(file)) File_Create(file);
    FI.open(file,ios::in);
    string q;int e;
    while(FI>>q>>e) num[q]=e;
    FI.close();
}
void Check_Single(string file){
    File_To_rd(file);
    map<string,long double> p;
    for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++) p[iter->first]=1.0/num.size();
    for(int i=1;i<=siz;i++){
        double B=0.0;
        for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
            B+=(p[iter->first]*=(long double)(book[iter->first][rd[i]]+1)/(iter->second+2));
        }
        for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
            p[iter->first]/=B;
        }
    }
    map<string,int>::iterator ans=num.begin();
    for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
        if(p[iter->first]>p[ans->first]) ans=iter;
    }
    cout<<ans->first<<" "<<ans->second<<endl;
}
void Load_Model(){
    for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
        Previous_Read(iter->first);
    }
    puts("Enter the file name.");
    string A;
    cin>>A;
    Check_Single(A);
}
int main()
{
    Begin();
    puts("Enter 'U' to update model or 'L' to load model");
    char ch;
    cin>>ch;
    if(ch=='U') Update_Model();
    if(ch=='L') Load_Model();
    return 0;
}