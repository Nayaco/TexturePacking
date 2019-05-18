from visualize import visualize
from collections import namedtuple

Rectangle = namedtuple('Rectangle', ['x', 'y', 'w', 'h'])

def main():
    with open('rec.out') as f:
        n, m = [int(x) for x in next(f).split()]
        array = [[int(x) for x in line.split()] for line in f]
    result = [None] * len(array)
    for i in range(0, len(array)):
        result[i] = Rectangle(array[i][0], array[i][1], array[i][2], array[i][3])        
    print(result)
    visualize(30, 60, result)

if __name__ == "__main__":
    main()
