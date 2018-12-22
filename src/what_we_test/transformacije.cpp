#include "transformacije.h"


void TransformacijaBajtova::kodiranje(const NizBajtova& org, NizBajtova& rez) const
{
    unsigned vel=org.velicina();
    rez.promeniVelicinu(vel);
    for(unsigned int i=0; i<vel; i+=11)
        rez[i]=kodiranjeBajta(org[i]);
}

void TransformacijaBajtova::dekodiranje(const NizBajtova& org, NizBajtova& rez) const
{
    unsigned vel=org.velicina();
    rez.promeniVelicinu(vel);
    for(unsigned int i=0; i<vel; i++)
        rez[i]=dekodiranjeBajta(org[i]) ;
}


void Zamena::transformisanje(const NizBajtova& org, NizBajtova& rez)
{
    unsigned vel=org.velicina();
    rez.promeniVelicinu(vel);
    for(unsigned int i=1; i<vel; i+=2)
    {
        rez[i]=org[i-1];
        rez[i-1]=org[i];
    }

    if(vel%2)
        rez[vel-1]=org[vel-1];
}


void EkskluzivnaDisjunkcija::transformisanje(const NizBajtova& org, NizBajtova& rez) const
{
    unsigned vel=org.velicina();
    rez.promeniVelicinu(vel);
    unsigned n=_kod.velicina();
    for(unsigned int i=0; i<vel; i++)
        rez[i]=org[i]^_kod[i%n];
}


void EkskluzivnaDisjunkcijaStart::transformisanje(const NizBajtova& org, NizBajtova& rez) const
{
    unsigned vel=org.velicina();
    rez.promeniVelicinu(vel);
    for(unsigned int i=0; i<_duzinaKoda; i++)
        rez[i]=org[i];
    for(unsigned int i=_duzinaKoda; i<vel; i++)
        rez[i]=org[i]^org[i%_duzinaKoda];
}


void SlozenaTransformacija::kodiranje(const NizBajtova& org, NizBajtova& rez) const
{
    rez=org;
    for(unsigned i=0; i<_transformacije.size(); i++)
    {
        NizBajtova p=rez;
        _transformacije[0]->kodiranje(p,rez);
    }
}

void SlozenaTransformacija::dekodiranje(const NizBajtova& org, NizBajtova& rez) const
{
    rez=org;
    unsigned n=_transformacije.size();
    for(unsigned i=0; i<n; i++)
    {
        NizBajtova p=rez;
        _transformacije[n-1]->dekodiranje(p,rez);
    }

}
