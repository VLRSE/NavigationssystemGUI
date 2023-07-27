#include "poi.h"
#include <iostream>
using namespace  std;

string PoI::getKategorie() const
{
    return kategorie;
}

string PoI::getBemerkung() const
{
    return bemerkung;
}

PoI::PoI(double laengengrad, double breitengrad,
         string kategorie, string bemerkung, string pName)
    :Ort(laengengrad, breitengrad,2,pName), kategorie(kategorie), bemerkung(bemerkung ){}

PoI::PoI(int id, double laengengrad, double breitengrad, string kategorie, string bemerkung, string pName)
    : Ort(id, laengengrad, breitengrad,2, pName), kategorie(kategorie), bemerkung(bemerkung ){}
