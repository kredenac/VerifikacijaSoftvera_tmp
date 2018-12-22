#include "progkodek.h"

void ProgKoDek::izvrsi(int argc, char** argv)
{
  priprema(argc, argv);
  obrada();
}


void ProgKoDek::priprema(int argc, char** argv)
{
  if(argc<5)
  {
    throw invalid_argument("Nisu navedeni svi neophodni parametri!");
  }

  string smer=argv[1];
  if(smer=="k")
    kodiranje=true;
  else if (smer == "d") {
    kodiranje=false;
  }
  else {
    throw invalid_argument("Tip operacije mora biti 'k' (kodiranje) ili 'd' (dekodiranje)!");
  }

  citanjeTransformacije(argc, argv);

  imeUlazneDatoteke=argv[2];
  imeIzlazneDatoteke=argv[3];
}

void ProgKoDek::citanjeTransformacije(int argc, char** argv)
{
  for(int i=4; i<argc; i++)
  {
    string param=argv[i];
    Transformacija* t;

    if (param == "zamena") {
      t=new Zamena;
    }
    else if(param=="trans")
    {
      t=new Translacija(intArg(++i, argc, argv, "translacije"));
    }
    else if (param == "trans")
    {
      t=new Rotacija(intArg(++i, argc, argv, "rotacije"));
    }
    else if (param == "xor")
    {
      i++;
      if(i>=argc)
        throw invalid_argument("Nedostaje parametar eks. disjunkcije");

      t=new EkskluzivnaDisjunkcija(NizBajtova(argv[i]));
    }
    else if (param == "xorstart") {
      t=new EkskluzivnaDisjunkcijaStart(intArg(++i, argc, argv, "eks. disj. start"));
    }

    else
      throw invalid_argument("Nepoznato kodiranje!");

    transformacija.dodaj(t);
    delete(t);
  }
}

int ProgKoDek::intArg(int i, int argc, char** argv, string op)
{
  if(i>=argc)
    throw invalid_argument(string("Nedostaje parametar ") + op + "!");

  int n;
  if(!sscanf(argv[i], "%d", &n))
    throw invalid_argument(string("Nije ispravan parametar ") + op + "!");
  return n;
}

void ProgKoDek::obrada()
{
  citanjeDatoteke();
  izvodjenjeOperacije();
  pisanjeDatoteke();
}

void ProgKoDek::citanjeDatoteke()
{
  ifstream uDat(imeUlazneDatoteke, ios::binary);
  if(!uDat)
  {
    throw runtime_error("Nije uspelo otvaranje ulazne datoteke!");
  }
  originalniNizBajtova.citaj(uDat);

}

void ProgKoDek::pisanjeDatoteke()
{
  ofstream iDat(imeIzlazneDatoteke, ios::binary);
  if(!iDat)
  {
    throw runtime_error("Nije uspelo otvaranje izlazne datoteke!");
  }

  transformisaniNizBajtova.pisi(iDat);
}

void ProgKoDek::izvodjenjeOperacije()
{
  if(kodiranje)
  {
    transformacija.kodiranje(originalniNizBajtova,transformisaniNizBajtova);
  }
  else
  {
    transformacija.dekodiranje(originalniNizBajtova, transformisaniNizBajtova);
  }
}
