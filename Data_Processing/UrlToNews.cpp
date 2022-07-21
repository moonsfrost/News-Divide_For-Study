#include<cstring>
#include<string>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<windows.h>
#include<io.h>
#include<direct.h>
#include<cstdio>
#include<ctime>
using namespace std;
string url[10010],file,folder;
void Get_File_Name(){
    puts("Please enter the url file name.(Do not beyond 10000 urls!!!)");
    cin>>file;
}
void Get_Output_Folder(){
    puts("Please enter the folder you want to save");
    cin>>folder;
	if (_access(folder.c_str(),0)==-1) _mkdir(folder.c_str());	
}
const string num[10]={"0","1","2","3","4","5","6","7","8","9"};
string Int_To_stirng(int a){
    string ans;
    for(int i=0;i<4;i++) ans=num[a%10]+ans,a/=10;
    return ans;
}
int main()
{
    Get_File_Name(),Get_Output_Folder();
    freopen(file.c_str(),"r",stdin);
    int n=1;
    while(cin>>url[n]) n++;
    n--;
    fclose(stdin);
    sort(url+1,url+1+n);
    n=unique(url+1,url+1+n)-url-1;
    double t=0;
    for(int i=0;i<n;i++){
        time_t bg=clock();
        string command="python -u GetNews.py "+url[1+i]+" "+folder+"\\"+Int_To_stirng(i);
        system(command.c_str());
        time_t ed=clock();
        t=t*i+(double)((double)ed-bg)/CLOCKS_PER_SEC;
        t/=(i+1);
        cout<<"-------Left time:"<<t*(n-i-1)<<"s-------\n";
    }
    return 0;
}