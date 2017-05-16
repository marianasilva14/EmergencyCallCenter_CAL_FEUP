/*
 * matcher.h
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

void pre_kmp(string pattern, vector<int> & prefix);

int kmp(string text, string pattern);


int numStringMatching(string filename,string toSearch);

int editDistance(string pattern, string text);

float numApproximateStringMatching(string filename,string toSearch);


