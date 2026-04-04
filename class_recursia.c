#include "class_recursia.h"
#include <stdio.h>
#include <string.h>

static void PrintMultiplicationBoard(size_t row, size_t col, size_t n);
static void ReverseRecursion(int *head, int *tail);
static float FindAverage(int const *array, int const *end, size_t length, long sum);

void RecPrintMultiplicationBoard(size_t n)
{
    PrintMultiplicationBoard(1, 1, n);
    return;
}

static void PrintMultiplicationBoard(size_t row, size_t col, size_t n)
{
    // Stopping condition
    if (row > n)
    {
        return;
    }

    // Prints element i,j of the multiplication board (nxn matrix)
    printf("%ld\t", col * row);

    // Condition of moving the next row of nXx matrix
    if (col + 1 > n)
    {
        printf("\n");   // New line for a new row
        PrintMultiplicationBoard(row + 1, 1, n);
        return;
    }
    
    PrintMultiplicationBoard(row, col + 1, n);

}

static float FindAverage(int const *array, int const *end, size_t length, long sum)
{
    if (array == end)
    {
        return (float) sum / length;
    }

    return FindAverage(array + 1, end, length, sum + *array);
}

float RecFindAverage(int const *array, size_t const length)
{
    return FindAverage(array, array + length, length, 0);
}

#define SWAP(a, b, type) do { \
    type tmp = *(a);          \
    *(a) = *(b);              \
    *(b) = tmp;               \
} while(0)

static void ReverseRecursion(int *head, int *tail)
{
    if (head >= tail)
    {
        return;
    }
    SWAP(head, tail, int);

    ReverseRecursion(head + 1, tail - 1);
}


void RecReverseArray(int *head, int *tail)
{
    if (!head || !tail)
    {
        return;
    }

    ReverseRecursion(head, tail);
    return;
}


static bool IsPalindrome(char *head, char *tail)
{
    if (head >= tail)
    {
        return true;
    }
    if (*head != *tail)
    {
        return false;
    }
    return IsPalindrome(head + 1, tail - 1);
}

bool RecIsPalindrome(char *arr)
{
    if (!arr)
    {
        return false;
    }
    return IsPalindrome(arr, arr + strlen(arr) - 1);
}

static void ReverseStringRecursion(char *head, char *tail)
{
    if (head >= tail)
    {
        return;
    }
    SWAP(head, tail, char);
    ReverseStringRecursion(head + 1, tail - 1);
}

void RecReverseString(char *_arr)
{
    if (!_arr)
    {
        return;
    }
    ReverseStringRecursion(_arr, _arr + strlen(_arr) - 1);
    return;
}
