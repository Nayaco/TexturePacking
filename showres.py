#!/usr/bin/env python3
from visualize import visualize, async_call
from collections import namedtuple
import os
Rectangle = namedtuple('Rectangle', ['x', 'y', 'w', 'h'])

def main(filename: str, idx = 1):
    with open(filename) as f:
        n, m = [int(x) for x in next(f).split()]
        array = [[int(x) for x in line.split()] for line in f]
    result = [None] * len(array)
    for i in range(0, len(array)):
        result[i] = Rectangle(array[i][0], array[i][1], array[i][2], array[i][3])        
    visualize(m, n, result, idx)

if __name__ == "__main__":
    os.system("make")
    os.system("./a.out")
    main("ph.out", 1)
    main("ffog.out", 2)
    main("ffrg.out", 3)
    main("nfog.out", 4)
    main("nfrg.out", 5)
    main("bfog.out", 6)
    main("bfrg.out", 7)
