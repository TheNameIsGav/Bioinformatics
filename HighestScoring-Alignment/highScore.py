global indelPen
indelPen = 5

def readMatrixFromFile(file_name):
    with open(file_name, 'r') as file:
        alphabet = file.readline().rstrip().split()
        matrix = []
        for _ in range(len(alphabet)):
            line = file.readline().rstrip().split()
            matrix.append([int(line[i]) for i in range(1, len(line))])

    return matrix, alphabet


def getHighScore(set1, set2, matrix, alphabet):
    length1 = len(set1)
    length2 = len(set2)

    distances = [[0 for i in range(length1+1)] for j in range(length2+1)]
    
    #initialize top row and left column

    #top row
    for i in range(length1):
        distances[0][i+1] = distances[0][i] - indelPen

    #left column
    for i in range(length2):
        distances[i+1][0] = distances[i][0] - indelPen

#run through and calculate score for each node
    for i in range(length2):
        for j in range(length1):
            upperNode = distances[i][j+1] - indelPen
            leftNode = distances[i+1][j] - indelPen

            acidPenalty = matrix [alphabet.index(set2[i])] [alphabet.index(set1[j])]
            diagNode = distances[i][j] + acidPenalty
            
            distances[i+1][j+1] = max(upperNode, leftNode, diagNode)
            
#Realize somewhere that string1 and string 2 are backwards in my head, but like it works sooo might fix it later?
#Set to max score
    score = distances[-1][-1]
    ans1 = ""
    ans2 = ""
    i = length2 - 1
    j = length1 - 1
    #decrement until we reach the end of the line
    while i != -1 or j != -1:
        maxElem = distances[i+1][j+1] - matrix[alphabet.index(set2[i])][alphabet.index(set1[j])]
        #check if im diagonal
        if maxElem == distances[i][j]:
            ans1 = set1[j] + ans1
            ans2 = set2[i] + ans2
            i = i - 1
            j = j - 1
            
        else:
            maxElem = max(distances[i+1][j], distances[i][j+1])
            #check which string I came from if I am not diagonal
            #check left
            if maxElem == distances[i+1][j]:
                ans1 = set1[j] + ans1
                ans2 = "-" + ans2
                j = j - 1
            else:
                #check other
                ans1 = "-" + ans1
                ans2 = set2[i] + ans2
                i = i - 1
                
    print(score)
    print("".join(ans1))
    print("".join(ans2))

def main(filename):
    file = open(filename, "r")
    lines = file.readlines()
    file.close()
    stuff = []
    for x in lines:
        stuff.append(x.rstrip())
    set1 = stuff[0]
    set2 = stuff[1]

    matrix, alphabet = readMatrixFromFile("BLOSUM62.txt")

    getHighScore(set1, set2, matrix, alphabet)


