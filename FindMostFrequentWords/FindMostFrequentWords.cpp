// FindMostFrequentWords.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int BaseToOffset(char base) {
    if (base == 'A') return 0;
    if (base == 'C') return 1;
    if (base == 'G') return 2;
    if (base == 'T') return 3;
    else return -1;
}

char OffsetToBase(int offset) {
    if (offset == 0) return 'A';
    if (offset == 1) return 'C';
    if (offset == 2) return 'G';
    if (offset == 3) return 'T';
    else return '0';
}

string NumberToPattern(int idx, int k) {
    if (k == 1) {
        string retVal = "";
        retVal.push_back(OffsetToBase(idx));
        return retVal;
    } else {
        int prefixIndex = idx / 4;
        double remainder = idx % 4;
        char symbol = OffsetToBase(remainder);
        string prefixPattern = NumberToPattern(prefixIndex, k - 1);
        prefixPattern.push_back(symbol);
        return prefixPattern;
    }
}

int PatternToNumber(string pattern) {
    string bigBeans = pattern;
    if (pattern.length() == 0) {
        return 0;
    } else {
        char symbol = pattern[pattern.length() - 1];
        bigBeans.pop_back(); //Digusting function that totally shags the string its called upon
        string prefix = bigBeans;
        int offset = BaseToOffset(symbol);
        return (4 * PatternToNumber(prefix)) + offset;
    }
}

int getMax(int input[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (input[i] >= max) {
            max = input[i];
        }
    }
    return max;
}

void FasterFrequentWords(string text, int k) {
    set<string> frequentPatterns;
    int sizeOfFreqArray = pow(4, k);
    
    int* freqArray;
    freqArray = new int [sizeOfFreqArray] { 0 } ;
    if (freqArray == NULL) {
        cout << "Failure to allcoate memeory";
        exit(1);
    }

    for (int i = 0; i <= (text.length() - k); i++) {
        string pattern = text.substr(i, k);
        int idx = PatternToNumber(pattern);
        freqArray[idx] = freqArray[idx] + 1;
    }

    int maxCount = getMax(freqArray, pow(4, k));
    for (int i = 0; i <= pow(4, k) - 1; i++) {
        if (freqArray[i] == maxCount) {
            string pattern = NumberToPattern(i, k);
            frequentPatterns.insert(pattern);
        }
    }

    for (string x : frequentPatterns) {
        cout << x << endl;
    }

    if (freqArray != NULL){
        cout << "Deleting FreqArray";
        delete[] freqArray;
    }
}

int main()
{
    string inputStr = "CATCCGATTACAATAAGATACAATAAGATTGTCCCCGCGGCTCGGCGACTATTCCGTACAATAAGACGGCTCGGCTACAATAAGATTGTCCCCGTTGTCCCCGCATCCGATTACAATAAGATTGTCCCCGGACTATTCCGTTGTCCCCGCGGCTCGGCCATCCGATTTGTCCCCGTTGTCCCCGTACAATAAGAGACTATTCCGCGGCTCGGCTTGTCCCCGCATCCGATCATCCGATGACTATTCCGCGGCTCGGCCGGCTCGGCTTGTCCCCGGACTATTCCGCGGCTCGGCTACAATAAGACGGCTCGGCTACAATAAGATTGTCCCCGCATCCGATTACAATAAGATTGTCCCCGTACAATAAGATACAATAAGACGGCTCGGCTACAATAAGACATCCGATCGGCTCGGCTTGTCCCCGTTGTCCCCGTTGTCCCCGCGGCTCGGCCATCCGATCGGCTCGGCGACTATTCCGGACTATTCCGCATCCGATTACAATAAGATACAATAAGACGGCTCGGCCGGCTCGGCTTGTCCCCGCGGCTCGGCCGGCTCGGCCGGCTCGGCCATCCGATGACTATTCCGCATCCGATCATCCGATCATCCGATCGGCTCGGCTACAATAAGAGACTATTCCGGACTATTCCGTACAATAAGATACAATAAGACGGCTCGGCTTGTCCCCGTACAATAAGACGGCTCGGCTTGTCCCCGCGGCTCGGCCATCCGATTTGTCCCCGCATCCGATCGGCTCGGCCATCCGATCGGCTCGGCTACAATAAGACATCCGATCATCCGATCGGCTCGGCCATCCGATGACTATTCCGCATCCGATGACTATTCCGGACTATTCCGGACTATTCCGCATCCGATCATCCGATCATCCGATTTGTCCCCGCGGCTCGGC";
    int inputK = 14;
    FasterFrequentWords(inputStr, inputK);
}
