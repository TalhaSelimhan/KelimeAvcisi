#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;
bool buyukMu(string x,string y){
    return x.length()>y.length();
}

bool gidildiMi(int x,int y,const bool (&gidilenler)[4][4]){
    return gidilenler[x][y];
}
//rdenvbegroydiahc
void bulucu(int x,int y, map <string,int> &kelimeler, string &tutulan,vector <string> &bulunanlar,const char (&harfler)[4][4],bool (&konumlar)[4][4]){
    tutulan.push_back(harfler[x][y]);
    konumlar[x][y]=true;
    int uzunluk=tutulan.length();
    if(kelimeler[tutulan]==1)bulunanlar.push_back(tutulan);
    
    if(x!=0 && uzunluk<10){
        if(!gidildiMi(x-1,y,konumlar))bulucu(x-1,y,kelimeler,tutulan,bulunanlar,harfler,konumlar);
        if(y!=0 && !gidildiMi(x-1,y-1,konumlar)) bulucu(x-1,y-1,kelimeler,tutulan,bulunanlar,harfler,konumlar);
        if(y!=3 && !gidildiMi(x-1,y+1,konumlar)) bulucu(x-1,y+1,kelimeler,tutulan,bulunanlar,harfler,konumlar);
    }
    if(x!=3 && uzunluk<10){
        if(!gidildiMi(x+1,y,konumlar))bulucu(x+1,y,kelimeler,tutulan,bulunanlar,harfler,konumlar);
        if(y!=0 && !gidildiMi(x+1,y-1,konumlar)) bulucu(x+1,y-1,kelimeler,tutulan,bulunanlar,harfler,konumlar);
        if(y!=3 && !gidildiMi(x,y,konumlar)) bulucu(x+1,y+1,kelimeler,tutulan,bulunanlar,harfler,konumlar);
    }
    if(y!=0 && !gidildiMi(x,y-1,konumlar)&& uzunluk<10) bulucu(x,y-1,kelimeler,tutulan,bulunanlar,harfler,konumlar);
    if(y!=3 && !gidildiMi(x,y+1,konumlar)&& uzunluk<10) bulucu(x,y+1,kelimeler,tutulan,bulunanlar,harfler,konumlar);   
    tutulan.pop_back();
    konumlar[x][y]=false;
}

int main(){
    ifstream sozluk;
    sozluk.open("kelimeler.txt");
    string line,s;
    char harfler[4][4];
    map <string,int> kelimeler;
    vector <string> bulunanlar;
    bulunanlar.reserve(5000);
    bool konumlar[4][4]={false};
    if(sozluk.is_open()){
        while ( getline (sozluk,line)){
            kelimeler[line]=1;
        }
        sozluk.close();
    }
    else{
        cout<<"dosya acilamadi"<<endl;
        return 1;
    }
    
    cin >> s;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            harfler[i][j]=s[i*4+j];
        }
    }
    string tutulan;
    tutulan.clear();
    for(int i =0;i<16;i++){
        bulucu(i/4,i%4,kelimeler,tutulan,bulunanlar,harfler,konumlar);
    }
    sort(bulunanlar.begin(),bulunanlar.end(),buyukMu);
    for(string item:bulunanlar){
        cout<<item<<endl;
    }
    return 0;
}