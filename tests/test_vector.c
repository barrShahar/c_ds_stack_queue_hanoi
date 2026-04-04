#include "../vector.h"
#include "stdio.h"
#include <assert.h>
#include <stdlib.h>
#define TYPE int
#define UNUSED(x) (void)(x)


void PrintVector(const Vector* _vector);

int PrintIntAction(void* _integer, size_t i, void* context)
{
    UNUSED(context); // To silent a warning

    if (_integer == NULL)
    {
        return 0;
    }

    int* intPtr = (int*)_integer;
    printf("%ld: %d  \n", i, *intPtr);
    return 1; // Keep going, dont break the foreach loop
}

void PrintVector(const Vector* _vector)
{
    VectorForEach(_vector, PrintIntAction, NULL);
}

void TestAppend(Vector* _vector, size_t _initialCapacity, size_t _blockSize)
{
    printf("==\nTest Append\n==\n");

    size_t n = (_initialCapacity + _blockSize) * 3;

    size_t size = 0;
    size_t capacity = _initialCapacity;
    for (size_t i = 0; i < n ; ++i)
    {
        int* toAppend = malloc(sizeof(int));
        *toAppend = i % 4;
        assert(VectorAppend(_vector, (void*) toAppend) == 0);
        assert(++size == VectorSize(_vector));
        if (size > capacity)
        {
            capacity += _blockSize;
            assert(capacity == VectorCapacity(_vector));
        }
    }
}

void IntElementDestroy(void* _int)
{
    free((int*) _int);
}

void TestDestroy(Vector** _vector)
{
    VectorDestroy(_vector, IntElementDestroy);

    assert(*_vector == NULL);
}

void TestRemove(Vector* _vector)
{
    printf("==\nTest Remove\n==\n");
    size_t size = VectorSize(_vector);

    for (size_t i = size; i > 0; --i)
    {
        int* elementPtr;
        VectorResult result = VectorRemove(_vector, (void**) &elementPtr);
        assert(result == 0);
        printf("element: %d ", *elementPtr);
        free(elementPtr);
        printf("size: %ld, capacity: %ld\n", VectorSize(_vector), VectorCapacity(_vector));
        // assert(size-- == VectorSize(_vector));
    }
    printf("\n");

    // Remove empty vector
    int* elementPtr;
    VectorResult result = VectorRemove(_vector, (void**) &elementPtr);
    assert(result == VECTOR_SIZE_ZERO_ERROR);
}


void TestSet(Vector *_vector)
{
    printf("==\nTest Set\n==\n");

    size_t size = VectorSize(_vector);
    int value = 3000;
    for (size_t i = 0 ; i < size ; ++i)
    {
        VectorSet(_vector, i, &value);
    }

    int *getValue;
    for (size_t i = 0 ; i < size ; ++i)
    {
        VectorGet(_vector, i, (void**) &getValue);
        assert(*getValue == value);
    }

    PrintVector(_vector);
}

int main()
{
    size_t initialCapacity = 3;
    size_t blockSize = 6;
    Vector* vector = VectorCreate(initialCapacity, blockSize);
    TestAppend(vector, initialCapacity, blockSize);

    printf("After append test: \n"); PrintVector(vector); 
    printf("\n");

    TestRemove(vector);

    TestDestroy(&vector);

    Vector* vector2 = VectorCreate(initialCapacity, blockSize);
    TestAppend(vector2, initialCapacity, blockSize);
    TestSet(vector2);
    
    return 0;
}