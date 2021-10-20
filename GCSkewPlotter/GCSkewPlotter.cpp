// GCSkewPlotter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

void CalculateGCSkew(string genome) {
    int* skew;
    int arrSize = genome.length();
    skew = new int[arrSize]{ 0 };
    if (genome[0] == 'G') skew[0] == 1;
    if (genome[0] == 'C') skew[0] == -1;

    int modFactor = 10;

    for (int i = 1; i <= genome.length() - 1; i++) {
        if (i % modFactor == 0) {
            if (genome[i] == 'G') skew[i] = skew[i - modFactor] + 1;
            else if (genome[i] == 'C') skew[i] = skew[i - modFactor] - 1;
            else skew[i] = skew[i - 10];
        }
    }

    for (int i = 0; i < arrSize; i++) {
        if (i % modFactor == 0) {
            cout << skew[i] << endl;
        }
    }

}


int main()
{
    //Photorhabdus_luminescens.txt
    //Salmonella_enterica.txt
    ifstream file("Photorhabdus_luminescens.txt");
    string tmp;
    string genome; 
    while (getline(file, tmp)) {
        genome = genome + tmp;
    }
    CalculateGCSkew(genome);
}
