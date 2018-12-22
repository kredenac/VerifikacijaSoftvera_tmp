
#include <iostream>
#include <exception>


#include "nizbajtova.h"
#include "transformacije.h"
#include "progkodek.h"

int main(int argc, char** argv)
{
    try
    {
        ProgKoDek program;
        program.izvrsi(argc, argv);
    }
    catch (invalid_argument& e) {
        cerr << "Neispravna upotreba programa" << endl;
        cerr << e.what() << endl;
        cerr << "Kodiranje (k|d) <ulazna dat.> <izlazna dat> <transformacije>" << endl;
        return 1;
    }
    catch (exception& e) {
        cerr << "Greska: " << e.what() << endl;
        return 1;
    }
    return 0;

}

