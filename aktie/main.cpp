#include <iostream>
#include <fstream>
#include <string>
#include "aktie.h"

using namespace std;

unsigned int hashd(const char* s, unsigned int seed = 0)
{
    unsigned int hashs = seed;
    while (*s)
    {
        hashs = hashs * 101  +  *s++;
    }
    return hashs;
}

void add()
{

}

void import(string s, string kurz){

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


    cout<<hashd("Google",0)%1499<<endl;
}

int main()
{
    string eingabe="";
    string name, kurz;


    do{



        if(eingabe == "add"){
            cout<<"Name: ";
            cin>>name;
            cout<<"Kürzel: ";
            cin>>kurz;

        }
        if(eingabe =="import")
        {
            import("");
        }
        cout<<"What do you want to do?"<<endl;
        cin>>eingabe;
    }while(eingabe != "QUIT");
    return 0;
}


