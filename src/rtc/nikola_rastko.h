#ifndef NIKOLA_RASTKO_H
#define NIKOLA_RASTKO_H
#include <iostream>
#include "nadezda_spadijer.h"

// TODO by Nikola and Rastko
// take in test cases and generate
// gcov stats to decide if some
// test should be removed
class nikola_rastko
{
public:
    nikola_rastko(vector<TestCase> & tests);

    bool hasRedundant()
    {
        return false;
    }

    vector<TestCase> getRedundant(){
        return vector<TestCase>();
    }
private:
    vector<TestCase> tests;
};

#endif // NIKOLA_RASTKO_H
