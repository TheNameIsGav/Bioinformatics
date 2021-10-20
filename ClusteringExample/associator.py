
pointMatch = []
geneMatch = []
with open("pointsInCluster.csv", 'r') as file:
    for line in file:
        pointMatch.append(line.split(',')[0])

with open("noHeaders.csv", 'r') as file:
    for line in file:
        line = line.split(',')
        geneMatch.append((line[0], line[1]))

with open("outputGenes.txt", 'w') as file:
    
    for (gene, val) in geneMatch:
        for value in pointMatch:
            if float(value) == float(val):
                file.write(gene + '\n')

