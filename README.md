# Queues, Recursion & Data Structures

C implementations of generic data structures and recursion exercises.

## Data Structures

- **Vector** — dynamic array with automatic grow/shrink
- **Generic Stack** — LIFO stack built on top of Vector
- **Generic Queue** — FIFO queue with iterator support

## Recursion Exercises

- Multiplication board
- Array average & reverse
- Palindrome check
- Towers of Hanoi

## Build

```bash
make        # build app + all test runners
make clean  # remove binaries
```

## Run

```bash
./run       # main demo
./test_v    # vector tests
./test_s    # stack tests
./test_q    # queue tests
```

## Memory Check

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./run
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_v
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_q
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_s

```
