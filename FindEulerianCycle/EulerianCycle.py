import random

with open('rosalind_ba3f.txt', 'r') as file:
    inputTemplate = file.read()

def formatInput(string):
    string = string.split('\n')
    tups = []
    for item in string:
        items = item.split(' ')
        if len(items[2]) == 1:
           tups.append((items[0],items[2]))
        else: 
            ends = items[2].split(',')
            for end in ends:
                tups.append((items[0],end))
    temp = []
    for (head, tail) in tups:
        temp.append((int(head), int(tail)))

    final = dict()
    for (head, tail) in temp:
        if head in final:
            final[head].append(tail)
        else:
            final[head] = [tail]
        
    return final

graph = formatInput(inputTemplate)

def cycler(initialHead, graph):
    
    head = initialHead
    cycle = [head]
    while len(graph[head]) > 0:
        tail = random.choice(graph[head])
        graph[head].remove(tail)
        head = tail
        cycle.append(tail)
    return cycle

def stripGraph(graph):
    target = []
    for key in graph:
        if (graph[key] == []):
            target.append(key)
    for key in target:
        graph.pop(key)

def findValidHead(graph, cycle):
    heads = []
    for key in graph:
        if(len(graph[key]) >= 0 and key in cycle):
            heads.append(key)
    return random.choice(heads)

def eulerCycle(graph):
    start = random.choice(list(graph))
    cycle = cycler(start, graph)

    stripGraph(graph)
    
    while len(graph.values()) > 0:
        nextHead = findValidHead(graph, cycle)
        cyclePrime = cycler(nextHead, graph)
        mergePoint = cycle.index(nextHead)
        
        cycle1 = cycle[:mergePoint]
        cycle2 = cycle[mergePoint+1:]

        cycle1.extend(cyclePrime)
        cycle1.extend(cycle2)
        cycle = cycle1
        stripGraph(graph)

    return cycle

    
        
def main():
#Only run once per opening of the cmd window, file opening is scuffed
    total = eulerCycle(graph)
    string = ""

    #Have the output just be list
    for x in total:
        string = string + str(x) + "->"
    print(string[:-2])
        
