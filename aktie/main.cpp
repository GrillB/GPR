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
                stringstream ss(zeile);
                string cc;
                getline(ss,cc,',');
                istringstream(cc)>>i;
                getline(ss,cc,',');
                aname[i].name=cc;
                getline(ss,cc,',');
                akuerz[i].kuerz=cc;
                aname[i].kuerz=akuerz[i].kuerz;
                akuerz[i].name=aname[i].name;


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
            f<<i<<","<< aname[i].name <<","<< akuerz[i].kuerz<<endl;
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
void showData(string eingabe,aktie aname[],aktie akuerz[])
{
    int hasw=search(eingabe,aname,akuerz);
    if(!((hasw)%10))
    {
        hasw/=10;
        //Name

        ifstream f;  // Datei-Handle
        string s;
        f.open(aname[hasw].kuerz+".csv", ios::in); // Öffne Datei aus Parameter
        if(f){
        getline(f, s);    // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        getline(f, s);    // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        }else
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
        if(f){
        getline(f, s);    // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        getline(f, s);    // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm

        }else
        cout<<"Es existieren keine Kursdaten für diese Eingabe!"<<endl;
        f.close();
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
            //deletefunc(eingabe,aname,akuerz);
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
        }

        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }
    while(eingabe != "quit");


    return 0;
}


