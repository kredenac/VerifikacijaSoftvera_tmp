#include "nizbajtova.h"

NizBajtova::NizBajtova(const string& s)
{
    unsigned v=s.length();
    _niz.resize(v);
    for(unsigned i=0; i<v; i++)
        _niz[i]=s[i];
}

Bajt NizBajtova::operator[](unsigned i) const
{
    return _niz[i];
}

Bajt& NizBajtova::operator[](unsigned i)
        {
    return _niz[i];
        }

void NizBajtova::promeniVelicinu(unsigned v)
{
    _niz.resize(v);
}

unsigned NizBajtova::velicina() const
{
    return _niz.size();
}



void NizBajtova::pisi(ostream& ostr) const
{
    ostr.write((char*)&_niz[0], velicina());
    if(!ostr)
        throw runtime_error("Nije uspelo pisanje u datoteku!");
}

void NizBajtova::citaj(istream& istr)
{
    istr.seekg(0, ios::end);
    unsigned v=istr.tellg();
    istr.seekg(0, ios::beg);
    _niz.resize(v);
    istr.read((char*)&_niz[0], v);
    if(!istr)
        throw runtime_error("Nije uspelo citanje datoteke!");
}
