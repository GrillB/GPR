#include <iostream>
#include <fstream>
using namespace std;



int main()
{
    ifstream f;  // Datei-Handle
    string s;int lenge=1;
    f.open("msft.csv", ios::in); // Öffne Datei aus Parameter
    while (!f.eof())          // Solange noch Daten vorliegen
    {
        getline(f, s);        // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        lenge++;if(lenge>30)break;

    }
    f.close();
    //Hallo
    return 0;
}
