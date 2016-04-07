#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main()
{
    ifstream f;  // Datei-Handle
    string s;int laenge=1;
    f.open("msft.csv", ios::in); // Öffne Datei aus Parameter
    while (!f.eof()&&laenge<31)          // Solange noch Daten vorliegen
    {
        getline(f, s);     // Lese eine Zeile
        cout << s << endl;    // Zeige sie auf dem Bildschirm
        laenge++;

    }
    f.close();
    //Hallo
    return 0;
}
