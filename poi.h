#ifndef POI_H
#define POI_H

#include "ort.h"
#include <iostream>
using namespace std;

class PoI : public Ort
{
private:
    string kategorie;
    string bemerkung;

public:
    PoI( double laengengrad, double breitengrad,
        string kategorie, string bemerkung, string pName);
    PoI(int id, double laengengrad, double breitengrad,
        string kategorie, string bemerkung, string pName);
    ~PoI();
    string getKategorie() const;
    string getBemerkung() const;

    virtual string attributeAlsString(char delimiter)const override{
        return "" + to_string(this->getID()) + delimiter + to_string(this->getType())+ delimiter
               + this->getName() + delimiter + this->getKategorie()
               + delimiter + this->getBemerkung()+ delimiter + to_string(this->getLg())
               + delimiter + to_string(this->getBg())+ "\n";
    }
    virtual string getParameters() const override{
        return  this->getKategorie() +"," + this->getBemerkung();
    }
    void anzeigen() const override{
        Ort::anzeigen();
        cout.width(10);
        cout <<std::left <<"PoI"<<" |";
        cout.width(20);
        cout <<std::left <<this->getName()<<" |";
        cout.width(20);
        cout <<std::left <<this->getLg()<<" |";
        cout.width(20);
        cout <<std::left <<this->getBg()<<" |";
        cout.width(30);
        cout  <<std::left<<this->getParameters() <<endl;

        //cout << "Kategorie: "<< kategorie << endl;
        //cout << "Bemerkung: "<< bemerkung << endl;
        //cout << "Laengengrad: "<< this->getLg() << endl;
        //cout << "Breitengrad: "<< this->getBg() << endl<<endl;
    }
    virtual std::string getTypeAsString() const override{
        return "PoI";
    }
};

#endif // POI_H
