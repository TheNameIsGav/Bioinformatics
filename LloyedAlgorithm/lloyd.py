def findInitialCenter(k,points):
    return points[:k]

def eucDist(point1, point2, dimensions):
    sumTotal = 0
    for i in range(dimensions):
        sumTotal = sumTotal + (point1[i] - point2[i])**2
    return sumTotal

def kmeans(numCenters, dimensions , points):
    centers = findInitialCenter(numCenters, points)
    difference = float("inf")
    while difference > 0:
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
    numCenters = 0
    dimensions = 0
    points = []
 
    with open ('in3.txt') as f:   
        for line in f:
            if dimensions == 0:
                values = line.strip().split()
                dimensions = int(values[0])
                numCenters = int(values[1])
            else:
                points.append([float(v) for v in line.strip().split()])

                
        for pt in kmeans(dimensions , numCenters , points):
            print (pt)
