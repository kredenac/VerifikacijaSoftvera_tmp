#include <QtTest>

#include "../Kodiranje/nizbajtova.h"
#include "../Kodiranje/transformacije.h"
#include "../Kodiranje/progkodek.h"

class kodiranjeTest : public QObject
{
    Q_OBJECT

public:
    kodiranjeTest();
    ~kodiranjeTest();

private slots:
    void pripremaTest();
    void rotacijaKodiranjeTest();
    void slozenaKodiranjeTest();
    void zamenaKodiranjeTest();
    void translacijaKodiranjeTest();
    void slozenaDekodiranjeTest();
};

kodiranjeTest::kodiranjeTest()
{}

kodiranjeTest::~kodiranjeTest()
{}

void kodiranjeTest::pripremaTest()
{
    int argc = 5;
    char *argv[5];
    argv[0] = strdup("tst_kodiranjetest");
    argv[1] = strdup("k");
    argv[2] = strdup("test/test1");
    argv[3] = strdup("test/test1_zamena.kodiran");
    argv[4] = strdup("zamena");

    ProgKoDek p;
    p.priprema(argc,argv);

    QCOMPARE(p.kodiranje,1);

    for(int i=0;i<5;i++)
        free(argv[i]);
}


void kodiranjeTest::zamenaKodiranjeTest(){
    Zamena z;
    string niska("Nesto novo");
    NizBajtova nb_izlaz;
    z.kodiranje(NizBajtova(niska),nb_izlaz);

    QCOMPARE(nb_izlaz._niz, NizBajtova("eNts oonov")._niz);
}

void kodiranjeTest::translacijaKodiranjeTest(){
    Translacija t(2);
    string niska("abcdef");
    NizBajtova nb_izlaz;
    t.kodiranje(NizBajtova(niska),nb_izlaz);

    QCOMPARE(nb_izlaz._niz, NizBajtova("cdefgh")._niz);
}

void kodiranjeTest::rotacijaKodiranjeTest(){
    Rotacija r(8) ;
    string niska("abcdef");

    NizBajtova nb_izlaz;
    r.kodiranje(NizBajtova(niska),nb_izlaz);

    QCOMPARE(nb_izlaz._niz, NizBajtova("abcdef")._niz);
}

void kodiranjeTest::slozenaKodiranjeTest(){
    SlozenaTransformacija st;

    string niska("abcdef");
    NizBajtova nb_izlaz;

    st.dodaj(new Zamena);
    st.dodaj(new Translacija(2));
    st.kodiranje(NizBajtova(niska),nb_izlaz);

    QCOMPARE(nb_izlaz._niz, NizBajtova("dcfehg")._niz);
}

void  kodiranjeTest::slozenaDekodiranjeTest(){
    SlozenaTransformacija st;

    string niska("dcfehg");
    NizBajtova nb_izlaz;

    st.dodaj(new Zamena);
    st.dodaj(new Translacija(2));
    st.dekodiranje(NizBajtova(niska),nb_izlaz);

    QCOMPARE(nb_izlaz._niz, NizBajtova("abcdef")._niz);
}

QTEST_APPLESS_MAIN(kodiranjeTest)

#include "tst_kodiranjetest.moc"
