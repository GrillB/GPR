﻿#include <iostream>
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

int recHashname(int hashw,aktie aname[])
{

    if(aname[hashw].name!="")
    {
        hashw=(hashw*hashw)%1499;
        hashw=recHashname(hashw,aname);
    }
    return hashw;
}

int recHashkuerz(int hashw,aktie akuerz[])
{
    if(akuerz[hashw].kuerz!="")
    {
        hashw=(hashw*hashw)%1499;
        hashw=recHashkuerz(hashw,akuerz);
    }
    return hashw;
}

void add(string name, string kuerz,aktie aname[],aktie akuerz[])
{
    int hname=hashd(name.c_str())%1499;
    int hkuerz=hashd(kuerz.c_str())%1499;

    hname=recHashname(hname,aname);
    hkuerz=recHashkuerz(hkuerz,akuerz);

    aname[hname].name=name;
    akuerz[hkuerz].kuerz=kuerz;

    aname[hname].kuerz=akuerz[hkuerz].kuerz;
    akuerz[hkuerz].name=aname[hname].name;

}

void loadHash(string eingabe,aktie aname[],aktie akuerz[])
{
    ifstream f;  // Datei-Handle
    //string s;
    int i=0;
    string zeile;
    f.open(eingabe+".txt", ios::in);// Öffne Datei aus Parameter
    if(f)
    {
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
                // f<<i<<","<< aname[i].name <<","<< aname[i].kuerz<<","<< akuerz[i].name <<","<< aname[i].kuerz<<endl;
                stringstream ss(zeile);
                string cc;
                getline(ss,cc,',');
                istringstream(cc)>>i;

                getline(ss,cc,',');
                aname[i].name=cc;
                getline(ss,cc,',');
                aname[i].kuerz=cc;

                getline(ss,cc,',');
                akuerz[i].name=cc;
                getline(ss,cc,',');
                akuerz[i].kuerz=cc;

                cout<<aname[i].name<<" : "<<aname[i].kuerz<<endl;
                cout<<akuerz[i].name<<" : "<<akuerz[i].kuerz<<endl;



            }
        }
    }
    else
    {
        cout<<"Datei existiert nicht!"<<endl;

    }
    f.close();
}

void saveHash(string eingabe,aktie aname[],aktie akuerz[])
{
    fstream f(eingabe+".txt", ios::out);
    int i=0;

    while(i<1499)
    {
        if(aname[i].name!=""||akuerz[i].kuerz!="")
        {
            //f<<i<<","<< aname[i].name <<","<< akuerz[i].kuerz<<endl;
            f<<i<<","<< aname[i].name <<","<< aname[i].kuerz<<","<< akuerz[i].name <<","<< akuerz[i].kuerz<<endl;
        }
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

int search(string eingabe,aktie aname[],aktie akuerz[])
{
    int hname=hashd(eingabe.c_str())%1499;
    int hkuerz=hashd(eingabe.c_str())%1499;
    int werte[1499]= {0};

    //string werte="";

    if(aname[hname].name == eingabe)
    {

        return hname*10;
    }
    else
    {
        while(aname[hname].name != eingabe)
        {
            //   werte += hname + ",";
            werte[hname]=1;
            hname = (hname*hname) % 1499;
            // if(werte.find(hname) != -1){
            if(aname[hname].name == eingabe)
                return hname*10;
            if(werte[hkuerz])
            {
                break;
            }
        }
    }

    if(akuerz[hkuerz].kuerz == eingabe)
    {
        return hkuerz*10+1;
    }
    else
    {
        while(akuerz[hkuerz].kuerz != eingabe)
        {
            // werte += hkuerz + ",";
            werte[hkuerz]=1;
            hkuerz = (hkuerz*hkuerz) % 1499;
            // if(werte.find(hkuerz) != -1){
            if(akuerz[hkuerz].kuerz == eingabe)
                return hkuerz*10+1;
            if(werte[hkuerz])
            {
                break;
            }
        }

    }
    return 0;
}

void deletefunc(string eingabe,aktie aname[],aktie akuerz[])
{
    int x;
    x = search(eingabe, aname, akuerz);
    cout<<x<<endl;
    int y;
    string s;
    if(!(x%10))
    {

        x/=10;
        s = aname[x].kuerz;
        cout<<s<<endl;
        y = hashd(s.c_str())%1499;

        if(akuerz[y].name == eingabe)
        {
             cout<<"name"<<endl;
            aname[x].name = "";
            aname[x].kuerz = "";
            akuerz[y].name = "";
            akuerz[y].kuerz = "";
        }


    }else
    {
        x/=10;
        cout<<x<<endl;
        s = akuerz[x].name;
        cout<<s<<endl;
        y = hashd(s.c_str())%1499;
        //cout<<y<<endl;
        if(aname[y].kuerz == eingabe)
        {
            cout<<"kurz"<<endl;
            akuerz[x].name = "";
            akuerz[x].kuerz = "";
            aname[y].name = "";
            aname[y].kuerz = "";
        }

    }
}
void showData(string eingabe,aktie aname[],aktie akuerz[])
{
    int hasw=search(eingabe,aname,akuerz);
    if((hasw/10))
    {
        if(!((hasw)%10))
        {
            hasw/=10;
            //Name

            ifstream f;  // Datei-Handle
            string s;
            f.open(aname[hasw].kuerz+".csv", ios::in); // Öffne Datei aus Parameter
            if(f)
            {
                getline(f, s);    // Lese eine Zeile
                cout << s << endl;    // Zeige sie auf dem Bildschirm
                getline(f, s);    // Lese eine Zeile
                cout << s << endl;    // Zeige sie auf dem Bildschirm
            }
            else
                cout<<"Es existieren keine Kursdaten für diese Eingabe!"<<endl;
            f.close();
        }
        else
        {
            //Kürzel
            hasw/=10;
            ifstream f;  // Datei-Handle
            string s;
            f.open(akuerz[hasw].kuerz+".csv", ios::in); // Öffne Datei aus Parameter
            if(f)
            {
                getline(f, s);    // Lese eine Zeile
                cout << s << endl;    // Zeige sie auf dem Bildschirm
                getline(f, s);    // Lese eine Zeile
                cout << s << endl;    // Zeige sie auf dem Bildschirm

            }
            else
                cout<<"Es existieren keine Kursdaten für diese Eingabe!"<<endl;
            f.close();
        }
    }

}

void ls(aktie aname[],aktie akuerz[])
{
    int i=0;
    while(i<1499)
    {
        if(aname[i].name!=""||akuerz[i].kuerz!="")
        {
            cout<<i<<","<< aname[i].name <<","<< akuerz[i].kuerz<<endl;
        }
        i++;
    }

}

int main()
{
//    string aname[1499]="NULL";
//    string akuerz[1499]="NULL";

    aktie aname[1499];
    aktie akuerz[1499];

//    loadHash(aname,akuerz);
    string eingabe="";
    string name, kurz;

    do
    {
        if(eingabe=="ls")
        {
            ls(aname,akuerz);
        }
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
            showData(eingabe,aname,akuerz);
            //search(eingabe)
        }
        if(eingabe =="delete")
        {
            cout<<"Was möchten Sie löschen?"<<endl;
            cin>>eingabe;
            deletefunc(eingabe,aname,akuerz);
        }
        if(eingabe =="save")
        {
            cout<<"Speichern der Hashtable \"FILENAME\": ";
            cin>>eingabe;
            saveHash(eingabe,aname,akuerz);
        }
        if(eingabe=="load")
        {
            cout<<"Laden der Hashtable \"FILENAME\": ";
            cin>>eingabe;
            loadHash(eingabe,aname,akuerz);
           // add("micro","msft",aname,akuerz);
        }

        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }
    while(eingabe != "quit");


    return 0;
}


