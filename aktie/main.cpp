#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "aktie.h"

using namespace std;

string aname[1499]="NULL";
string akuerz[1499]="NULL";
int gr=0;
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
void add(string name, string kuerz)
{

    aname[hashd(name.c_str())%1499]=name;
    akuerz[hashd(kuerz.c_str())%1499]=kuerz;
    cout<< aname[hashd(name.c_str())%1499]<<endl;
    cout<<akuerz[hashd(kuerz.c_str())%1499]<<endl;

}

void loadHash()
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

        pos=s.find(",");
        //string to integger
        istringstream(s.substr(0,pos))>>i;
        cout<<i;
        pos1=s.find(",",pos+1);
        aname[i]=s.substr(pos+1,(pos1-pos-1));
        cout<<aname[i];
        akuerz[i]=s.substr(pos1+1);
        cout<<akuerz[i]<<endl;

    }
    f.close();
}

void saveHash()
{
    fstream f("hash.txt", ios::out);
    int i=0;
<<<<<<< HEAD
    string s;
    while(i<1499)
    {
        if(aname[i]!="NULL"||akuerz[i]!="NULL")
        f<<i<<","<< aname[i] <<","<< akuerz[i]<<endl;
        i++;
    }
=======

        while(i<1499
              )
        {
            f<<i<<","<< aname[i] <<","<< akuerz[i]<<endl;
            i++;
        }
>>>>>>> origin/master

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

void search(string eingabe){
    size_t found, found2;
    for(int i = 0; i<1499; i++){
        found = aname[i].find(eingabe);
        found2 = akuerz[i].find(eingabe);
        if(found != -1){
            cout<< "Name gefunden"<<endl;
            cout<< i <<endl;
        }
        if(found2 != -1){
            cout<< "Kuerzel gefunden"<<endl;
            cout<< i <<endl;
        }
    }
}
void deletefunc(string eingabe){
    size_t found, found2;
    for(int i = 0; i<1499; i++){
        found = aname[i].find(eingabe);
        found2 = akuerz[i].find(eingabe);
        if(found != -1){
            cout<< "Name gefunden"<<endl;
            cout<< i <<endl;
            cout<< aname[i] << "wird gelöscht" <<endl;
            aname[i] = "NULL";
        }
        if(found2 != -1){
            cout<< "Kuerzel gefunden"<<endl;
            cout<< i <<endl;
            cout<< akuerz[i] << "wird gelöscht" <<endl;
            akuerz[i] = "NULL";
        }
    }
}
int main()
{
    loadHash();
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
            add(name,kurz);
        }
        if(eingabe =="search")
        {
            cout<<"Was suchen Sie?"<<endl;
            cin>>eingabe;
            search(eingabe);
        }
        if(eingabe =="delete")
        {
            cout<<"Was möchten Sie löschen?"<<endl;
            cin>>eingabe;
            deletefunc(eingabe);
        }
        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }
    while(eingabe != "quit");
    saveHash();

    return 0;
}


