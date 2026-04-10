#include "class_recursia.h"
#include <stdio.h>
#include <string.h>

static void PrintMultiplicationBoard(size_t _row, size_t _col, size_t _n);
static void ReverseRecursion(int *_head, int *_tail);
static float FindAverage(int const *_array, int const *_end, size_t _length, long _sum);

void RecPrintMultiplicationBoard(size_t _n)
{
    PrintMultiplicationBoard(1, 1, _n);
    return;
}

static void PrintMultiplicationBoard(size_t _row, size_t _col, size_t _n)
{
    // Stopping condition
    if (_row > _n)
    {
        return;
    }

    // Prints element i,j of the multiplication board (nxn matrix)
    printf("%zu\t", _col * _row);

    // Condition of moving the next row of nXx matrix
    if (_col + 1 > _n)
    {
        printf("\n");   // New line for a new row
        PrintMultiplicationBoard(_row + 1, 1, _n);
        return;
    }

    PrintMultiplicationBoard(_row, _col + 1, _n);

}

static float FindAverage(int const *_array, int const *_end, size_t _length, long _sum)
{
    if (_array == _end)
    {
        return (float) _sum / _length;
    }

    return FindAverage(_array + 1, _end, _length, _sum + *_array);
}

float RecFindAverage(int const *_array, size_t const _length)
{
    if (_length == 0) { return 0.0f; }
    return FindAverage(_array, _array + _length, _length, 0);
}

#define SWAP(a, b, type) do { \
    type tmp = *(a);          \
    *(a) = *(b);              \
    *(b) = tmp;               \
} while(0)

static void ReverseRecursion(int *_head, int *_tail)
{
    if (_head >= _tail)
    {
        return;
    }
    SWAP(_head, _tail, int);

    ReverseRecursion(_head + 1, _tail - 1);
}


void RecReverseArray(int *_head, int *_tail)
{
    if (!_head || !_tail)
    {
        return;
    }

    ReverseRecursion(_head, _tail);
    return;
}


static bool IsPalindrome(char *_head, char *_tail)
{
    if (_head >= _tail)
    {
        return true;
    }
    if (*_head != *_tail)
    {
        return false;
    }
    return IsPalindrome(_head + 1, _tail - 1);
}

bool RecIsPalindrome(char *_arr)
{
    if (!_arr) { return false; }
    size_t length;
    if ((length = strlen(_arr)) == 0) { return true; }
    return IsPalindrome(_arr, _arr + length - 1);
}

static void ReverseStringRecursion(char *_head, char *_tail)
{
    if (_head >= _tail)
    {
        return;
    }
    SWAP(_head, _tail, char);
    ReverseStringRecursion(_head + 1, _tail - 1);
}

void RecReverseString(char *_arr)
{
    if (!_arr)
    {
        return;
    }
    size_t length;
    if ((length = strlen(_arr)) == 0) { return; }
    ReverseStringRecursion(_arr, _arr + length - 1);
    return;
}
