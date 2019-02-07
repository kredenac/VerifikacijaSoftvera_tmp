#ifndef STRING_DISTANCE_H
#define STRING_DISTANCE_H

#include <iostream>
/** the Hamming distance between two strings of equal length
 * is the number of positions at which the corresponding symbols are
 * different. In other words, it measures the minimum number of
 * substitutions required to change one string into the other, or the
 * minimum number of errors that could have transformed one string into
 *  the other. **/

int hamming_distance(std::string s1, std::string s2);

int min(int x, int y, int z);

/** The Levenshtein distance between two words is the minimum number
 * of single-character edits (i.e. insertions, deletions or substitutions)
 * required to change one word into the other. **/
int levenshtein_distance(std::string str1 , std::string str2 , int m ,int n);

#endif // STRING_DISTANCE_H
