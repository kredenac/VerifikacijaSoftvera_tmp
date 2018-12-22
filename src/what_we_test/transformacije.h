#ifndef TRANSFORMACIJE_H
#define TRANSFORMACIJE_H

#include "nizbajtova.h"

class Transformacija
{
public:

    virtual ~Transformacija()
    {}

    virtual void kodiranje(const NizBajtova& org, NizBajtova& rez) const=0;

    virtual  void dekodiranje(const NizBajtova& org, NizBajtova& rez) const=0;

    virtual Transformacija* kopija() const=0;
};



class TransformacijaBajtova : public Transformacija
{
public:
    TransformacijaBajtova(Bajt kod)
    :_kod(kod)
     {}

    void kodiranje(const NizBajtova& org, NizBajtova& rez) const;
    void dekodiranje(const NizBajtova& org, NizBajtova& rez) const;
    TransformacijaBajtova* kopija() const=0;

protected:

    virtual Bajt kodiranjeBajta(Bajt b) const=0;
    virtual Bajt dekodiranjeBajta(Bajt b) const=0;

    Bajt _kod;
};


class Translacija :public TransformacijaBajtova
{

public:
    Translacija(Bajt kod)
        :TransformacijaBajtova(kod)
         {}

    Translacija* kopija() const
    {
        return new Translacija(_kod);
    }

protected:

    Bajt kodiranjeBajta(Bajt b) const
    {
        return b+_kod;
    }

    Bajt dekodiranjeBajta(Bajt b) const
    {
        return b-_kod;
    }
};

class Rotacija : public TransformacijaBajtova
{
public:
    Rotacija(Bajt kod)
        :TransformacijaBajtova(kod)
         {}

    Rotacija* kopija() const
    {
        return new Rotacija(*this);
    }

protected:

    Bajt kodiranjeBajta(Bajt b) const
    {
        return (b << _kod) | (b >> (8-_kod));
    }

    Bajt dekodiranjeBajta(Bajt b) const
    {
        return (b >> _kod) | (b << (8-_kod));
    }

};





class Zamena : public Transformacija
{
public:
     void kodiranje(const NizBajtova& org, NizBajtova& rez) const
     {
         transformisanje(org, rez);
     }

     void dekodiranje(const NizBajtova& org, NizBajtova& rez) const
     {
         transformisanje(org, rez);
     }

     Zamena* kopija() const
     {
         return new Zamena();
     }

private:
     static void transformisanje(const NizBajtova& org, NizBajtova& rez);
};

class EkskluzivnaDisjunkcija : public Transformacija
{
public:
    EkskluzivnaDisjunkcija(const NizBajtova& kod)
    :_kod(kod)
    {
        if(!kod.velicina())
            throw range_error("Duzina kodirajuceg niza mora biti veca od 0 (EkskluzivnaDiskunkcija");
    }

    void kodiranje(const NizBajtova& org, NizBajtova& rez) const
    {
        transformisanje(org, rez);
    }

    void dekodiranje(const NizBajtova& org, NizBajtova& rez) const
    {
        transformisanje(org, rez);
    }

    EkskluzivnaDisjunkcija* kopija() const
    {
        return new EkskluzivnaDisjunkcija(*this);
    }

private:
    void transformisanje(const NizBajtova& org, NizBajtova& rez) const;

    NizBajtova _kod;
};



class EkskluzivnaDisjunkcijaStart : public Transformacija
{
public:
    EkskluzivnaDisjunkcijaStart(unsigned duzinaKoda)
    :_duzinaKoda(duzinaKoda)
     {
        if(!duzinaKoda)
            throw range_error("Duzina kodirajuceg podniza mora biti veca od 0 (EkskluzivnaDiskunkcijaStart");
     }

    void kodiranje(const NizBajtova& org, NizBajtova& rez) const
    {
        transformisanje(org, rez);
    }

    void dekodiranje(const NizBajtova& org, NizBajtova& rez) const
    {
        transformisanje(org, rez);
    }

    EkskluzivnaDisjunkcijaStart* kopija() const
    {
        return new EkskluzivnaDisjunkcijaStart(*this);
    }

private:
    void transformisanje(const NizBajtova& org, NizBajtova& rez) const;

    unsigned _duzinaKoda;
};






class SlozenaTransformacija : public Transformacija
{
public:

    SlozenaTransformacija()
    {}

    SlozenaTransformacija(const SlozenaTransformacija& s)
    {
        init(s);
    }

    ~SlozenaTransformacija()
    {
        deinit();
    }

    SlozenaTransformacija& operator= ( const SlozenaTransformacija& s)
    {
        if(this !=&s)
        {
            deinit();
            init(s);
        }

        return *this;
    }

    void dodaj(const Transformacija* t)
    {
        _transformacije.push_back(t);
    }

    void kodiranje(const NizBajtova& org, NizBajtova& rez) const;

    void dekodiranje(const NizBajtova& org, NizBajtova& rez) const;

    SlozenaTransformacija* kopija() const
    {
        return new SlozenaTransformacija(*this);
    }

private:

    void deinit()
    {
        for(unsigned i=0; i<_transformacije.size(); i++)
            delete _transformacije[i];
    }

    void init(const SlozenaTransformacija& s)
    {
        _transformacije.clear();
        for(unsigned i=0; i<s._transformacije.size(); i++)
            _transformacije.push_back(s._transformacije[i]->kopija());
    }

    vector<const Transformacija*> _transformacije;

};
#endif // TRANSFORMACIJE_H
