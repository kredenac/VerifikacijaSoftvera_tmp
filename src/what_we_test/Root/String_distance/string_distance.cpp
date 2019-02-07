#include "string_distance.h"
using namespace std;

int hamming_distance(string s1, string s2)
{
    int hamdist = 0;

    if (s1.length() == s2.length())
    {
        for (unsigned i=0; i<s1.length(); i++)
        {
            if (s1[i] != s2[i])
            {
                hamdist += 1;
            }
        }
    } else
    {
        hamdist = -1;
    }
        //throw invalid_argument("Undefined for sequences of unequal length.");    }

    return hamdist;
}


// Utility function to find minimum of three numbers
int min(int x, int y, int z)
{
    int min =x ;
    if(y < min)
        min =y;
    if(z < min)
        min =z;

    return min;
}

int levenshtein_distance(string str1 , string str2 , int m ,int n)
{
    // If first string is empty, the only option is to
    // insert all characters of second string into first
    if (m == 0) return n;

    // If second string is empty, the only option is to
    // remove all characters of first string
    if (n == 0) return m;

    // If last characters of two strings are same, nothing
    // much to do. Ignore last characters and get count for
    // remaining strings.
    if (str1[m-1] == str2[n-1])
        return levenshtein_distance(str1, str2, m-1, n-1);

    // If last characters are not same, consider all three
    // operations on last character of first string, recursively
    // compute minimum cost for all three operations and take
    // minimum of three values.
    return 1 + min ( levenshtein_distance(str1,  str2, m, n-1),    // Insert
                     levenshtein_distance(str1,  str2, m-1, n),   // Remove
                     levenshtein_distance(str1,  str2, m-1, n-1) // Replace
                   );
}

