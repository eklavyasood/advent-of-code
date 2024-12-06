# Advent of Code 2024 - Day 6

This is the directory for the **sixth** day's puzzles.

## About the puzzles
Given a text file input consisting of input in the following format-
```txt
....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
```

### Part 1
- **Parse** this file into a map where ^ is our **target**, the guard, and # 
  are obstacles.
- **Simulate** the guard's movement trajectory.
- **Track** the changes in the guard's direction, as she **turns 90°** whenever
  she reaches an obstacle.
- **Store** the entire path the guard takes until she leaves the map entirely.
- **Discard** positions previously covered by storing the trajectory in a **set**.
- **Find the total number** of unique positions covered by the guard.

### Part 2
- **Considering same input as Part 1**, consider all positions to figure out
  all the positions where **placing an extra obstacle would put the guard into
  an infinite loop**.

## How to Run
To compile and run the solutions, use a C++ compiler (e.g., `g++`):

```bash
g++ part1.cpp -o part1
./part1

g++ part2.cpp -o part2
./part2
```
