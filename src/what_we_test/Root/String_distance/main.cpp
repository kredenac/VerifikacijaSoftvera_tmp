// Testing Hamming and Levenshtein distance

#include "string_distance.h"

using namespace std;
int main(){

    // prompt user for two values
    cout << "Enter two strings: ";

    // recieve values
    string val1;
    string val2;
    cin >> val1 >> val2;

    int distance;
    // output
    try {
        distance = hamming_distance(val1,val2);

        cout << "Hamming distance between " << val1 << " and " << val2
            << " is " << distance << "." << endl;

    } catch (invalid_argument e) {
       cerr  << e.what() << endl;
    }

    distance = levenshtein_distance( val1 , val2 , val1.length(), val2.length());
    cout << endl << "Levenshtein distance between " << val1 << " and " << val2
         << " is " << distance  << "." << endl;

    return 0;
}
