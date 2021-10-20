import sys

def PatternCount(text, kmer):
    count = 0
    for i in range(0, len(text)-len(kmer)+1):
        if text[i:i+len(kmer)] == kmer:
            count = count + 1
    return count

#Running this script expects an input file to be specified as the 1st argument
def main(filename):
    fin = open(filename, "r")
    inputText = fin.readline().rstrip()
    inputKmer = fin.readline().rstrip()

    outputCount = PatternCount(inputText, inputKmer)
    print( outputCount)
