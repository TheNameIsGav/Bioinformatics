def readFile(fileName):
    with open(fileName, 'r') as file:
        with open("newFile.csv", 'w') as newFile:
            for line in file:
                line = line.replace('\t', ',')
                newFile.write(line)
            

def reverse(fileName):
    with open(fileName, 'r') as file:
        with open("reveresed.txt", 'w') as newFile:
            for line in file:
                line = line.replace(',', ' ')
                newFile.write(line)
