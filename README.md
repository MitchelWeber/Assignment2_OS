# Banker’s Algorithm (C++)

## Summary
This repository implements the Banker's Algorithm for deadlock avoidance. The program reads a snapshot of the system (total resources, allocation matrix, and maximum demand matrix) from an input file, computes the Need matrix and Available vector, and determines whether the system is in a safe state. If safe, it prints a safe sequence.

## Files
- `banker.cpp` - C++ implementation.
- `input.txt` - Example input file (the program reads this by default if no argument is given).

## Compile
From project root:
```bash
g++ -std=c++17 banker.cpp -o banker
./banker input.txt
