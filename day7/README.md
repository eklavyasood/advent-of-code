# Advent of Code 2024 - Day 7

This is the directory for the **seventh** day's puzzles.

## About the puzzles
Given a text file input consisting of input in the following format-
```txt
190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
```

### Part 1
- **Interpret** this file such that every line consists of a *rule*, a colon, and
  a set of operands.
- **Consider** the set of operands, and figure out what *combination of given 
  operators* (+ and \*) would resolve into the rule.
- **Discard** all lines in which the rule isn't possible to get with the 
  given operands and any set of operations.
- **Calculate** the total of all the successful operations.

### Part 2
- **Introduce** the || operator, which *concatenates* the operands around it,
  such that `1 || 23` would become `123`.
- **Recalculate** the new total with this new operator in the mix.

## How to Run
To compile and run the solutions, use a C++ compiler (e.g., `g++`):

```bash
g++ part1.cpp -o part1
./part1

g++ part2.cpp -o part2
./part2
```
