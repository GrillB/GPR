#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "aktie.h"

using namespace std;

struct aktie
{
    string name;
    string kuerz;
};

unsigned int hashd(const char* s)
{
    unsigned int seed = 0;
    unsigned int hashs = seed;
    while (*s)
    {
        hashs = hashs * 101  +  *s++;
    }
    return hashs;
}

int recHashname(int hashw,string aname[])
{

      if(aname[hashw]!="NULL")
    {
        hashw=(hashw*hashw)%1499;
        hashw=recHashname(hashw,aname);
    }
    return hashw;
}

int recHashkuerz(int hashw,string akuerz[])
{
    if(akuerz[hashw]!="NULL")
    {
        hashw=(hashw*hashw)%1499;
        hashw=recHashkuerz(hashw,akuerz);
    }
    return hashw;
}

void add(string name, string kuerz,string aname[],string akuerz[])
{
    int hname=hashd(name.c_str())%1499;
    int hkuerz=hashd(kuerz.c_str())%1499;
    aname[recHashname(hname,aname)]=name;
    akuerz[recHashkuerz(hkuerz,akuerz)]=kuerz;
}

void loadHash(string eingabe,string aname[],string akuerz[])
{
    ifstream f;  // Datei-Handle
    //string s;
    int i=0;
    string zeile;
    f.open(eingabe+".txt", ios::in);// Öffne Datei aus Parameter
    if(f){
    while (!f.eof())          // Solange noch Daten vorliegen
    {
        getline(f, zeile);     // Lese eine Zeile
        if(zeile.length()>1)
        {
            /*pos=s.find(",");
            //string to integger
            istringstream(s.substr(0,pos))>>i;
            pos1=s.find(",",pos+1);
            aname[i]=s.substr(pos+1,(pos1-pos-1));
            akuerz[i]=s.substr(pos1+1);*/
            stringstream ss(zeile);
            string cc;
            getline(ss,cc,',');
            istringstream(cc)>>i;
            getline(ss,cc,',');
            aname[i]=cc;
            getline(ss,cc,',');
            akuerz[i]=cc;



        }
    }
    }else{
    cout<<"Datei existiert nicht!"<<endl;

    }
    f.close();
}

void saveHash(string eingabe,string aname[],string akuerz[])
{
    fstream f(eingabe+".txt", ios::out);
    int i=0;
    string s;
    while(i<1499)
    {
        if(aname[i]!="NULL"||akuerz[i]!="NULL")
            f<<i<<","<< aname[i] <<","<< akuerz[i]<<endl;
        i++;
    }
    f.close();
}

void import(string eingabe,string kurz)
{

    ifstream f;  // Datei-Handle
    string s;
    int laenge=1;
    f.open("msft.csv", ios::in); // Öffne Datei aus Parameter
    while (!f.eof()&&laenge<31)          // Solange noch Daten vorliegen
    {
        getline(f, s);    // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        laenge++;
    }
    f.close();
}

int search(string eingabe,string aname[],string akuerz[])
{
    int hname=hashd(eingabe.c_str())%1499;
    int hkuerz=hashd(eingabe.c_str())%1499;
    int werte[1499]={0};

    //string werte="";

    if(aname[hname] == eingabe){
        return 1;
    }else{
        while(aname[hname] != eingabe){
         //   werte += hname + ",";
            werte[hname]=1;
            hname = (hname*hname) % 1499;
           // if(werte.find(hname) != -1){
           if(werte[hkuerz]){
                break;
            }
        }
    }
    if(akuerz[hkuerz] == eingabe){
        return 1;
    }else{
        while(akuerz[hkuerz] != eingabe){
           // werte += hkuerz + ",";
           werte[hkuerz]=1;
            hkuerz = (hkuerz*hkuerz) % 1499;
           // if(werte.find(hkuerz) != -1){
           if(werte[hkuerz]){
                break;
            }
        }
        return 0;
    }

}

void deletefunc(string eingabe,string aname[],string akuerz[])
{
//    size_t found, found2;
//    int hashw= search(eingabe, aname, akuerz);
//    if(hashw){
//
//
//            cout<< "Name gefunden"<<endl;
//            cout<< hashw <<endl;
//            cout<< aname[i] << "wird gelöscht" <<endl;
//            aname[i] = "NULL";
//
//            cout<< "Kuerzel gefunden"<<endl;
//            cout<< i <<endl;
//            cout<< akuerz[i] << "wird gelöscht" <<endl;
//            akuerz[i] = "NULL";
//
//    }
}
int main()
{
    string aname[1499]="NULL";
    string akuerz[1499]="NULL";

//    loadHash(aname,akuerz);
    string eingabe="";
    string name, kurz;


    do
    {



        if(eingabe == "add")
        {
            cout<<"Name: ";
            cin>>name;
            cout<<"Kürzel: ";
            cin>>kurz;
            add(name,kurz,aname,akuerz);
        }
        if(eingabe =="search")
        {
            cout<<"Was suchen Sie?"<<endl;
            cin>>eingabe;
            if(search(eingabe,aname,akuerz))
            {
                cout<<"Gesuchte Inhalt wurde gefunden!"<<endl;
            }
            else
            {
                cout<<"Gesuchte Inhalt wurde NICHT gefunden!"<<endl;
            }
            //search(eingabe)
        }
        if(eingabe =="delete")
        {
            cout<<"Was möchten Sie löschen?"<<endl;
            cin>>eingabe;
            deletefunc(eingabe,aname,akuerz);
        }if(eingabe =="save")
        {
            cout<<"Speichern der Hashtable \"FILENAME\": ";
            cin>>eingabe;
            saveHash(eingabe,aname,akuerz);
        }if(eingabe=="load")
        {
            cout<<"Laden der Hashtable \"FILENAME\": ";
            cin>>eingabe;
            loadHash(eingabe,aname,akuerz);
        }

        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }
    while(eingabe != "quit");


    return 0;
}


