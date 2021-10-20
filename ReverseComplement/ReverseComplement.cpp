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
        bigBeans.pop_back();
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

string ReverseComplement(string pattern) {
    string reverse;
    int textLength = pattern.length();
    for (int i = textLength-1; i >= 0; i--) {
        if (pattern[i] == 'A') reverse.push_back('T');
        else if (pattern[i] == 'T') reverse.push_back('A');
        else if (pattern[i] == 'C') reverse.push_back('G');
        else if (pattern[i] == 'G') reverse.push_back('C');
    }
    return reverse;
}

int HammingDistance(string pattern1, string pattern2) {
    int dist = 0;
    for (int i = 0; i < pattern1.length(); i++) {
        if (pattern1[i] != pattern2[i]) {
            dist++;
        }
    }
    return dist;
}

set<string> ImmediateNeighbors(string pattern) {
    set<string> immedNeighbors;
    immedNeighbors.insert(pattern);

    for (int i = 0; i < pattern.length(); i++) {
        char symbol = pattern[i];
        if (symbol == 'A') {
            string neighbor = pattern;
            neighbor[i] = 'C';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'G';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'T';
            immedNeighbors.insert(neighbor);
        }

        if (symbol == 'C') {
            string neighbor = pattern;
            neighbor[i] = 'T';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'G';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'A';
            immedNeighbors.insert(neighbor);
        }

        if (symbol == 'G') {
            string neighbor = pattern;
            neighbor[i] = 'C';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'T';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'A';
            immedNeighbors.insert(neighbor);
        }

        if (symbol == 'T') {
            string neighbor = pattern;
            neighbor[i] = 'C';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'G';
            immedNeighbors.insert(neighbor);
            neighbor[i] = 'A';
            immedNeighbors.insert(neighbor);
        }
    }
    return immedNeighbors;
}

set<string> Neighbors(string pattern, int d) {
    set<string> neighborhood;
    set<string> workingNeighborHood;
    neighborhood.insert(pattern);
    for (int i = 1; i <= d; i++) {
        for (string x : neighborhood) {
            //cout << x << " -- ";
            set<string> temp = ImmediateNeighbors(x);
            for (string y : temp) {
                //cout << y << " ";
                workingNeighborHood.insert(y);
            }
            //cout << endl;
        }
        for (string x : workingNeighborHood) {
            neighborhood.insert(x);
        }
    }
    return neighborhood;
}

void ComputeFrequencyArrayWithMismatchesAndReverses(string text, int k, int d) {
    int* freqArray;
    set<string> frequentPatterns;
    int arrSize = pow(4, k);
    freqArray = new int[arrSize] { 0 };

    if (freqArray == NULL) {
        cout << "Failure to allcoate memeory";
        exit(1);
    }

    for (int i = 0; i < text.length() - k; i++) {
        string pattern = text.substr(i, k);
        set<string> neighborhood = Neighbors(pattern, d);
        for (string approxPattern : neighborhood) {
            int idx = PatternToNumber(approxPattern);

            freqArray[idx] = freqArray[idx] + 1;
            idx = PatternToNumber(ReverseComplement(approxPattern));
            freqArray[idx] = freqArray[idx] + 1;
        }
    }

    int maxCount = getMax(freqArray, pow(4, k));
    for (int i = 0; i <= arrSize - 1; i++) {
        string pattern = NumberToPattern(i, k);
        //cout << pattern << " " << freqArray[i] << endl;
        if (freqArray[i] == maxCount) {
            frequentPatterns.insert(pattern);
        }
    }

    for (string x : frequentPatterns) {
        cout << x << endl;
    }

    if (freqArray != NULL) {
        delete[] freqArray;
    }
    
}

int main()
{
    string inputStr = "AACTAGGGGGTAACAGGTAACAAACTAGGGGGTAACAATTGAAGGGTAACAAACTAGGGGGATACGGATCCGATAATTGAAGGATCCGATAGATCCGATAGGTAACAGGTAACAATTGAAGGGTAACAAACTAGGGAACTAGGGATTGAAGATTGAAGGATCCGATAGATCCGATAAACTAGGGGATCCGATAAACTAGGGAACTAGGGGGATACGGATCCGATAGATCCGATAGGATACGGGTAACAGATCCGATAGGATACGGGTAACAGGATACGGGATACGAACTAGGGGATCCGATAATTGAAGATTGAAGAACTAGGGGGATACGGGATACGGGTAACAGATCCGATAGGTAACAATTGAAGAACTAGGGATTGAAGGGTAACAGGTAACAGGATACGGATCCGATAGATCCGATAGGTAACAATTGAAGGGATACGGGATACGGGTAACAATTGAAGATTGAAGAACTAGGGATTGAAGGATCCGATAGGATACGGATCCGATAGATCCGATAGGATACGGATCCGATAAACTAGGGGATCCGATAGATCCGATAAACTAGGGGATCCGATAGGTAACAGGATACGGATCCGATAGGTAACAAACTAGGGATTGAAGGGATACGGGTAACAGGTAACAGGTAACAAACTAGGGAACTAGGGATTGAAGAACTAGGGATTGAAGGATCCGATAGGTAACAAACTAGGGATTGAAGGATCCGATAGATCCGATAGGTAACAGGTAACAGGTAACAATTGAAGAACTAGGGGATCCGATAATTGAAGAACTAGGGGATCCGATAAACTAGGGAACTAGGGGGATACG";
    
    int inputK = 5;
    int mismatches = 2;

    ComputeFrequencyArrayWithMismatchesAndReverses(inputStr, inputK, mismatches);

}
