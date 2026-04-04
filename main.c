#include "class_recursia.h"
#include "hanoi.h"

#include <stdio.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static void PrintArray(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// For testing memory leaks run:
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./run
int main(void)
{
    /* --- Multiplication board, array, and palindrome (class_recursia) --- */
    int size = 5;
    printf("--------------------------------\n");
    printf("Multiplication board of size of %d:\n", size);
    RecPrintMultiplicationBoard(size);
    printf("\n");
    printf("--------------------------------\n");
    int arr[] = {0, 5, 10, 14};
    printf("Print original array: ");
    PrintArray(arr, SIZE(arr));
    printf("Array's average: %f\n", (float) RecFindAverage(arr, SIZE(arr)));
    printf("Print reversed array: ");

    RecReverseArray(arr, arr + SIZE(arr) - 1);
    PrintArray(arr, SIZE(arr));
    char *str = "madam";
    printf("%s Is palindrome: %d\n", str, RecIsPalindrome(str));
    char *str2 = "hello";
    printf("%s Is palindrome: %d\n", str2, RecIsPalindrome(str2));
    printf("\n");


    /* --- Hanoi towers --- */
    Towers *towers = TowersCreate(3);

    if (towers == NULL)
    {
        printf("Error creating towers\n");
        return 1;
    }
    
    printf("--------------------------------\n");
    printf("Print towers:\n");
    TowersPrint(towers);
    TowersMoveDisks(towers, 1, 3);
    printf("Print towers after move:\n");
    TowersPrint(towers);
    TowersDestroy(&towers);
    return 0;
}