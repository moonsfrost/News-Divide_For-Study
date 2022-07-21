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
#include<cstdlib>
using namespace std;
const string m=".\\Model";
map<string,int> num;
map<string,map<string,int>> book;
void Print_Sort(){
    string file=m+"\\sort";
    freopen(file.c_str(),"w",stdout);
    for(map<string,int>::iterator iter=num.begin();iter!=num.end();iter++){
        cout<<iter->first<<" "<<iter->second<<endl;
    }
    fclose(stdout);
}
void Print_Single(string file,string $){
    freopen(file.c_str(),"w",stdout);
    for(map<string,int>::iterator iter=book[$].begin();iter!=book[$].end();iter++){
        cout<<iter->first<<" "<<iter->second<<endl;
    }
    fclose(stdout);
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
    freopen(file.c_str(),"w",stdout);
    fclose(stdout);
}
void Previous_Read(string $){
    string file=m+"\\"+$+".dat";
    if(!Exists_Test(file)) File_Create(file);
    freopen(file.c_str(),"r",stdin);
    string w;
    int tt;
    while(cin>>w>>tt) book[$][w]=tt;
    fclose(stdin);
}
string rd[100000];int siz;
void File_To_rd(string file){
    string Command="python -u Divide.py "+file+" temp";
    system(Command.c_str());
    freopen("temp","r",stdin);
    siz=1;
    while(cin>>rd[siz]) siz++;
    siz--;
    sort(rd+1,rd+1+siz);
    siz=unique(rd+1,rd+1+siz)-rd-1;
    fclose(stdin);
}
void Update_Single_File(string file,string $){
    File_To_rd(file);
    num[$]++;
    for(int i=1;i<=siz;i++) book[$][rd[i]]++;
}
void getFileNames(string path, vector<string>& files)
{
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile=_findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1){
		do{
			if ((fileinfo.attrib & _A_SUBDIR)){
				if (strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!= 0)
					getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		}while(_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
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
    freopen(file.c_str(),"r",stdin);
    string q;int e;
    while(cin>>q>>e) num[q]=e;
    fclose(stdin);
}
int main()
{
    Begin();
    char ch;
    puts("Enter 'U' to update model or 'L' to load model");
    cin>>ch;
    if(ch=='U') Update_Model();
    return 0;
}