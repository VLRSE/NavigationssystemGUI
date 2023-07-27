#ifndef ADRESSE_H
#define ADRESSE_H
#include <iostream>
#include "ort.h"

using namespace std;
class Adresse : public Ort
{
private:
    string strasse;
    string hausnummer;
    int plz;
    string stadt;


public:
    Adresse( double Lg, double Bg,
             string strasse,
             string hausnummer,
             int plz,
             string stadt,
             string name);

    Adresse( int id, double Lg, double Bg,
             string strasse,
             string hausnummer,
             int plz,
             string stadt,
             string name);

    string getStrasse()const ;
    string getHausnummer()const ;
    int getPlz() const ;
    string getStadt() const;
    virtual std::string getTypeAsString() const override{
        return "Adr";
    }


    void anzeigen() const override{
        Ort::anzeigen();
        cout.width(10);
        cout <<std::left <<"Adr"<<" |";
        cout.width(20);
        cout <<std::left <<this->getName()<<" |";
        cout.width(20);
        cout <<std::left <<this->getLg()<<" |";
        cout.width(20);
        cout <<std::left <<this->getBg()<<" |";
        cout.width(30);
        cout <<std::left <<this->getParameters() <<endl;



        //   cout << "Strasse: "<< strasse << endl;
        //  cout << "Hausnummer: "<< hausnummer << endl;
        //  cout << "Postleitzahl: "<< plz << endl;
        //  cout << "Stadt: "<< stadt<< endl;
        // cout << "Laengengrad: "<< this->getLg() << endl;
        // cout << "Breitengrad: "<< this->getBg() << endl<<endl;

    }
    virtual string attributeAlsString(char delimiter)const override{
        return "" + to_string(this->getID()) + delimiter + to_string(this->getType())+ delimiter
               + this->getName()+ delimiter + this->getStrasse() + delimiter + this->getHausnummer() + delimiter
               + to_string(this->getPlz())  + delimiter + this->getStadt()
               + delimiter + to_string(this->getLg())+ delimiter + to_string(this->getBg())+ "\n" ;
    }
    virtual string getParameters() const override{
        return this->getStrasse() + this->getHausnummer() + ", "
               +"," + to_string(this->getPlz()) +","+this->getStadt();
    }
};

#endif // ADRESSE_H
