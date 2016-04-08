﻿#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "aktie.h"

using namespace std;


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

void loadHash(string aname[],string akuerz[])
{
    ifstream f;  // Datei-Handle
    //string s;
    int i=0;
    string s;
    size_t pos,pos1;
    f.open("hash.txt", ios::in); // Öffne Datei aus Parameter
    while (!f.eof())          // Solange noch Daten vorliegen
    {
        getline(f, s);     // Lese eine Zeile
        if(s.length()>1)
        {
            pos=s.find(",");
            //string to integger
            istringstream(s.substr(0,pos))>>i;

            pos1=s.find(",",pos+1);
            aname[i]=s.substr(pos+1,(pos1-pos-1));

            akuerz[i]=s.substr(pos1+1);

        }
    }
    f.close();
}

void saveHash(string aname[],string akuerz[])
{
    fstream f("hash.txt", ios::out);
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

void import(string s, string kurz)
{

    ifstream f;  // Datei-Handle
    //string s;
    int laenge=1;
    f.open("msft.csv", ios::in); // Öffne Datei aus Parameter
    while (!f.eof()&&laenge<31)          // Solange noch Daten vorliegen
    {
        getline(f, s);     // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        laenge++;
    }
    f.close();


}

void search(string eingabe,string aname[],string akuerz[])
{
    int hname=hashd(eingabe.c_str())%1499;
    int hkuerz=hashd(eingabe.c_str())%1499;
    string werte="";

    if(aname[hname] == eingabe){
        cout<< "TEst"<<endl;
    }else{
        while(aname[hname] != eingabe){
            werte += hname + ",";
            hname = (hname*hname) % 1499;
            if(werte.find(hname) != -1){
                break;
            }
        }
    }
    if(akuerz[hkuerz] == eingabe){
        cout<< "TEst"<<endl;
    }else{
        while(akuerz[hkuerz] != eingabe){
            werte += hkuerz + ",";
            hkuerz = (hkuerz*hkuerz) % 1499;
            if(werte.find(hkuerz) != -1){
                break;
            }
        }
    }
}
/*
void search(string eingabe,string aname[],string akuerz[])
{
    size_t found, found2;
    for(int i = 0; i<1499; i++)
    {
        found = aname[i].find(eingabe);
        found2 = akuerz[i].find(eingabe);
        if(found != -1)
        {
            cout<< "Name gefunden"<<endl;
            cout<< i <<endl;
        }
        if(found2 != -1)
        {
            cout<< "Kuerzel gefunden"<<endl;
            cout<< i <<endl;
        }
    }
}
*/
void deletefunc(string eingabe,string aname[],string akuerz[])
{
    size_t found, found2;
    for(int i = 0; i<1499; i++)
    {
        found = aname[i].find(eingabe);
        found2 = akuerz[i].find(eingabe);
        if(found != -1)
        {
            cout<< "Name gefunden"<<endl;
            cout<< i <<endl;
            cout<< aname[i] << "wird gelöscht" <<endl;
            aname[i] = "NULL";
        }
        if(found2 != -1)
        {
            cout<< "Kuerzel gefunden"<<endl;
            cout<< i <<endl;
            cout<< akuerz[i] << "wird gelöscht" <<endl;
            akuerz[i] = "NULL";
        }
    }
}
int main()
{
    string aname[1499]="NULL";
    string akuerz[1499]="NULL";

    loadHash(aname,akuerz);
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
            search(eingabe,aname,akuerz);
            //search(eingabe)
        }
        if(eingabe =="delete")
        {
            cout<<"Was möchten Sie löschen?"<<endl;
            cin>>eingabe;
            deletefunc(eingabe,aname,akuerz);
        }
        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }
    while(eingabe != "quit");
    saveHash(aname,akuerz);

    return 0;
}


