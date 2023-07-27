
#include "adresse.h"
#include "ort.h"

Adresse::Adresse(double lg, double bg, string strasse, string hausnummer, int plz, string stadt, string pName):
    Ort( lg, bg,1, pName), strasse(strasse), hausnummer(hausnummer), plz(plz), stadt(stadt){}

Adresse::Adresse(int id, double Lg, double Bg, string strasse, string hausnummer, int plz, string stadt, string name)
    :   Ort(id, Lg, Bg,1, name), strasse(strasse), hausnummer(hausnummer), plz(plz), stadt(stadt){}

string Adresse::getStrasse() const
{
    return strasse;
}

string Adresse::getHausnummer() const
{
    return hausnummer;
}

int Adresse::getPlz() const
{
    return plz;
}

string Adresse::getStadt() const
{
    return stadt;
}




