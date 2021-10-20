def readFile(fileName):
    lines = []
    with open(fileName, 'r') as file:
        for line in file:
            lines.append(line.strip())

    return lines

def bwTransform(text):
    cyclics = [text]
    newString = text[-1] + text[:-1]
    while not newString in cyclics:
        cyclics.append(newString)
        newString = newString[-1] + newString[:-1]

    cyclics.sort()
    return cyclics

def rip(listOfTransforms):
    ret = ""
    for text in listOfTransforms:
        ret = ret + text[-1]
    print(ret)

def main():
    text = readFile("rosalind_ba9i.txt")[0]
    transform = bwTransform(text)
    rip(transform)
