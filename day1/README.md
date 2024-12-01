# Advent of Code 2024 - Day 1

This is the directory for the **first** day's puzzles.

## About the puzzles
Given a text file input consisting of two rows of numbers in the following format-

```txt
3   4
4   3
2   5
1   3
3   9
3   3
```

- Parse this file into two lists that contain one of the rows of input each. 
- Sort both the lists.
- Pair up the numbers and measure how far apart they are. Pair the
  **smallest left number** with the **smallest right number**,
  then the **second-smallest left number** with the 
  **second-smallest right number**, and so on.
- Within each pair, figure out **how far apart** the two 
  numbers are; you'll need to **add up all of those distances**.
- To find the **total distance** between the left list and 
  the right list, add up the distances between all of the pairs
  you found.
- Your actual left and right lists contain many location IDs.
  **What is the total distance between your lists?**

## How to Run
To compile and run the solutions, use a C++ compiler (e.g., `g++`):

```bash
g++ part1.cpp -o part1
./part1

g++ part2.cpp -o part2
./part2
```
