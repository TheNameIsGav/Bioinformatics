def readFile(fileName):
    lines = []
    with open(fileName, 'r') as file:
        for line in file:
            lines.append(line.strip())

    return lines

def trieMatching(text, trie):
    matchingOccurs = []
    for root in range(0, len(trie)):
        for pattern in text:
            if trie[root] == pattern[0]:
                doesPatternMatch = True
                for char in range(0, len(pattern)):
                    if root + char >= len(trie):
                        doesPatternMatch = False
                    else:
                        if pattern[char] != trie[root+char]:
                            doesPatternMatch = False
                if doesPatternMatch:
                    matchingOccurs.append(root)
                    
    return matchingOccurs
    

def main():
    returnFromFile = readFile("rosalind_ba9b.txt")
    trie = returnFromFile[:1][0]
    patterns = returnFromFile[1:]
    matched = trieMatching(patterns, trie)
    print(*matched)
