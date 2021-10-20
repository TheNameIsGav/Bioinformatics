import math

def findInitialCenter(k,points):
    return points[:k]

def eucDist(point1, point2, dimensions):
    sumTotal = 0
    for i in range(dimensions):
        sumTotal = sumTotal + (point1[i] - point2[i])**2
    return math.sqrt(sumTotal)

def kmeans(numCenters, dimensions , points):
    centers = findInitialCenter(numCenters, points)
    difference = float("inf")
    i = 0
    while difference > 0:
        print("processing " + str(i))
        i = i + 1
        newCenters = step( numCenters, dimensions, points, centers)
        difference = sum([eucDist(newCenters[i], centers[i], dimensions) for i in range(numCenters)] )
        centers = newCenters[:]
    return centers

def step( numCenters, dimensions, points, centers):
    
    def findMin(minCenter):
        index = -1
        minimum = float('inf')
        for i in range(numCenters):
            newDist = eucDist( minCenter, centers[i], dimensions)
            if newDist < minimum:
                index = i
                minimum = newDist
        return index
    
    def newCenterMaker(currCenter,indices):
        count = 0
        point = [0 for i in range(dimensions)]
        for i in range(len(points)):
            if indices[i] == currCenter:
                count += 1
                for j in range(dimensions):
                    point[j] += points[i][j]
        return [dim / max(count,1) for dim in point]
    
    indices = [findMin(point) for point in points]
    
    return [newCenterMaker(currCenter,indices) for currCenter in range(numCenters)]

def main():
    numCenters = 3
    dimensions = 31
    points = []
 
    with open ('reveresed.txt') as f:   
        for line in f:
            points.append([float(v) for v in line.strip().split()])

    
    newStuff = []
    centers = kmeans(numCenters , dimensions , points)
    targetCluster = centers[1]
    
    for point in points:
        minCenter = centers[0]
        minDist = eucDist(point, centers[0], dimensions)
        
        for center in centers:
            newDist = eucDist(point, center, dimensions)
            if newDist < minDist:
                minCenter = center
                minDist = newDist
                
        if minCenter == targetCluster:
            newStuff.append(point)
         
    with open('pointsInCluster.csv', 'w') as file:
        for x in newStuff:
            for val in x:
                file.write(str(val) + ",")
            file.write('\n')
    #print(*centers, sep='\n')









                
