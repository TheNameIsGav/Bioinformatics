def readFile(file_name):
    with open(file_name, 'r') as file:
        line = file.readline().strip().split()

    
    length = len(line)

    #removes the silly parenthesis that rosalind includes
    line[0] = line[0].replace("(", "")
    line[-1] = line[-1].replace(")", "")
    print(line)
    #convert all texts to integers
    for i in range(len(line)):
        line[i] = int(line[i])
    print(line)
    line = [0] + line + [length+1] #add endpoints
    print(line)
    return line

def breakpointsCalculator(ints):
    bps = 0
    for i in range(len(ints)-1):
        if ints[i] != ints[i+1] - 1:
            bps += 1
    print(bps)

def main():
    dataFromFile = readFile("rosalind_ba6b.txt")
    breakpointsCalculator(dataFromFile)
