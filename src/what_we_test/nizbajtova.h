#ifndef NIZBAJTOVA_H
#define NIZBAJTOVA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef unsigned char Bajt;
using namespace std;


class NizBajtova
{
public:

    NizBajtova()
    {}

    NizBajtova(const string& s);
    Bajt operator[](unsigned i) const;
    Bajt& operator[](unsigned i);

    void promeniVelicinu(unsigned v);
    unsigned velicina() const;
    void pisi(ostream& ostr) const;
    void citaj(istream& istr);

private:
    vector<Bajt> _niz;
};

#endif // NIZBAJTOVA_H
