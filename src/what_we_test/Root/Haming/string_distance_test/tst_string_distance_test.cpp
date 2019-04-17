#include <QString>
#include <QtTest>

#include "../String_distance/string_distance.h"

class String_distance_Test : public QObject
{
    Q_OBJECT

public:
    String_distance_Test();

private Q_SLOTS:
    void testHamming1();
    void testHamming2();
    void testHamming3();
    void testLevenshtein1();
    void testLevenshtein2();
    void testLevenshtein3();
    void testHamming4ShouldBeRedundant();
};

String_distance_Test::String_distance_Test()
{
}

void String_distance_Test::testHamming1()
{
    QCOMPARE(hamming_distance("prvo", "prvo"), 0);
}

void String_distance_Test::testHamming2()
{
    QCOMPARE(hamming_distance("prva", "prvo"), 1);
}

void String_distance_Test::testHamming3()
{
    QCOMPARE(hamming_distance("nazovi", "nesto"), -1);
}

void String_distance_Test::testHamming4ShouldBeRedundant()
{
    QCOMPARE(hamming_distance("prvo", "prvo"), 0);
}

void String_distance_Test::testLevenshtein1()
{
    QCOMPARE(levenshtein_distance("prvo", "prvo",4,4), 0);
}

void String_distance_Test::testLevenshtein2()
{
    QCOMPARE(levenshtein_distance("prva", "prvo",4,4), 1);
}

void String_distance_Test::testLevenshtein3()
{
    QCOMPARE(levenshtein_distance("prvo", "drugo",4,5), 3);
}

QTEST_APPLESS_MAIN(String_distance_Test)

#include "tst_string_distance_test.moc"
