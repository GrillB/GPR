#include <iostream>
#include <stdlib.h>

#define SIZE 8
using namespace std;

void printField(char myField[],bool newField)
{
    for(int i=1; i<6; i++)
    {


        for(int j=1; j<9; j++)
        {
            if(newField)
                myField[i*SIZE+j]='.';
            cout<<""<<myField[i*SIZE+j];
        }
        cout<<i<<endl;



    }
    cout<<"12345678"<<endl;
}

int fillField(char myField[],int j,bool spieler)
{
    for(int i=5; i>0; i--)
    {

        if(myField[i*SIZE+j]=='.')
        {
            if(spieler)
            {
                myField[i*SIZE+j]='A';
            }
            else
            {
                myField[i*SIZE+j]='B';

            }
            return i;
        }
    }
    return 0;

}
int checkMatch(int posx,int posy,int direction,char myField[])
{

    int zaehler=0;
    bool reversedirect=false;
    int pos=posx*8+posy;
    int sze=SIZE;
    int newPos=pos+sze+direction;
    int gPos=newPos-posx*8;
    int gPosequal=SIZE+1;
    for(int i=0 ; i<4; i++)
    {
        if(myField[pos]==myField[newPos]&&!reversedirect&&gPos<gPosequal)
        {
            gPos++;
            zaehler++;
            newPos=newPos+sze+direction;
            if(zaehler==3)
            {

                return 1;
            }
        }
        else if(!reversedirect)
        {
            i=0;
            reversedirect=true;
            newPos=(newPos-sze)-direction;
            pos=newPos;
            newPos=(pos-sze)-direction;
            zaehler=0;
            gPos--;
        }
        if(myField[pos]==myField[newPos]&&reversedirect&&gPos>1)
        {
            zaehler++;
            gPos--;
            newPos=(newPos-sze)-direction;
            if(zaehler==3)
            {

                return 1;
            }
        }

    }

    return 0;

}

bool checkWin(int posx,int posy,char myField[])
{
    int pos=posx*SIZE+posy;
    int zaehler=0;
    int win=0;
    //  int newPos=pos+1;
    bool direction=true;
    int i=0;
    if(myField[pos]==myField[pos+SIZE]&&myField[pos]==myField[pos+SIZE*2]&&myField[pos]==myField[pos+SIZE*3]&&myField[pos]!='.')
    {

        i=4;
        return true;
    }
    else if(checkMatch(posx,posy,-SIZE+1,myField))
        return true;
    else    if(checkMatch(posx,posy,-1,myField))
        return true;
    else    if(checkMatch(posx,posy,1,myField))
        return true;

}


int main()
{
    string eingabe;
    cout << "Player or Computer!"<<"\n"<<"Player(p)/Computer(c): " << endl;
    cin>>eingabe;
    char myField[50];
    printField(myField,true);
    bool spieler=false;
    int pos;
    if(eingabe=="p")
    {

        while(true)
        {

            int zahl;
            if(!spieler)
            {
                do
                {
                    cout<<"Player A: ";
                    cin>>zahl;
                }
                while(zahl>8&&zahl<=0);
                pos=fillField(myField,zahl,true);
                if(pos)
                {
                    spieler= true;
                }

                else
                    cout<<"Nochmal !!!"<<endl;

            }
            else
            {
                do
                {
                    cout<<"Player B: ";
                    cin>>zahl;
                }
                while(zahl>8&&zahl<=0);
                pos=fillField(myField,zahl,false);
                if(pos)
                {

                    spieler=false;
                }
                else
                    cout<<"Nochmal !!!"<<endl;
            }
            system("cls");
            if(checkWin(pos,zahl,myField))
                break;
            printField(myField,false);
            cout<<endl;
        }
    }
    else if(eingabe=="c")
    {

    }
    else
    {

    }
    printField(myField,false);
    if(spieler)
        cout<<"Congratulations Player A Wins"<<endl;
    else
        cout<<"Congratulations Player B Wins"<<endl;
    return 0;
}
