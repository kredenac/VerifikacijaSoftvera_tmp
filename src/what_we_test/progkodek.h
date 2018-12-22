#ifndef PROGKODEK_H
#define PROGKODEK_H
#include "transformacije.h"

class ProgKoDek
{
public:
    void izvrsi(int argc, char** argv);

private:
    void priprema(int argc, char** argv);
    void citanjeTransformacije(int argc, char** argv);

    static int intArg(int i, int argc, char** argv, string op);

    void obrada();
    void citanjeDatoteke();
    void pisanjeDatoteke();
    void izvodjenjeOperacije();

    bool kodiranje;
    string imeUlazneDatoteke;
    string imeIzlazneDatoteke;
    NizBajtova originalniNizBajtova;
    NizBajtova transformisaniNizBajtova;
    SlozenaTransformacija transformacija;
};
#endif // PROGKODEK_H
