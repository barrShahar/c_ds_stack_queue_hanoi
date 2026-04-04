#include "hanoi.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define NUMBER_OF_destinationWERS 3
#define BlockSizeZero 0
struct Towers
{
    Stack *m_destinationwers[NUMBER_OF_destinationWERS];
    size_t m_numberOfDisks;
};

static int TowerPrintIntegerAction(void* _element, size_t _index, void* _context);
static void TowersMoveDisk(Towers *_destinationwers, size_t _source, size_t _destination);
static void RecTowersMoveDisks(Towers *_destinationwers, size_t _source, size_t _destination, size_t _helper, size_t _numberOfDisks);
static void DestroyIntElement(void *_element);

#define IN_RANGE(num) ((num) >= 1 && (num) <= NUMBER_OF_destinationWERS)
#define GET_destinationWER(towers, num) towers->m_destinationwers[num - 1]

TowersResult TowersMoveDisks(Towers *_destinationwers, size_t _source, size_t _destination)
{
    if (_destinationwers == NULL) { return TOWERS_UNINITIALIZED_ERROR; }
    if (!IN_RANGE(_source) || !IN_RANGE(_destination)) { return TOWERS_OUT_OF_BOUND_ERROR; }

    // Find the tower that is neither the source nor the destination
    size_t helper; 
    for (helper = 1 ; helper <= NUMBER_OF_destinationWERS; ++helper)
    {
        if (helper != _source && helper != _destination)
        {
            break;
        }
    }

    RecTowersMoveDisks(_destinationwers, _source, _destination, helper, _destinationwers->m_numberOfDisks);
    return TOWERS_SUCCESS;
}


void TowersPrint(Towers *_destinationwers)
{
    if (_destinationwers == NULL) { return; }

    for (size_t i = 0 ; i < NUMBER_OF_destinationWERS ; ++i)
    {
        printf("===");
        StackPrint(_destinationwers->m_destinationwers[i], TowerPrintIntegerAction, NULL);
        printf("\n");
    }
}


Towers *TowersCreate(size_t _numberOfDisks)
{
    Towers *towers = malloc(1 * sizeof(Towers));
    if (towers == NULL)
    {
        return NULL;
    }

    for (size_t i = 0 ; i < NUMBER_OF_destinationWERS ; ++i)
    {
        towers->m_destinationwers[i] = StackCreate(_numberOfDisks, BlockSizeZero);
        if (towers->m_destinationwers[i] == NULL)
        {
            for (size_t j = 0; j < i ; ++j)
            {
                StackDestroy(&towers->m_destinationwers[j], DestroyIntElement);
            }

            free(towers);
            return NULL;
        }
    }

    // Push the disks to the first tower
    for (size_t i = 0 ; i < _numberOfDisks; ++i)
    {
        int *number = malloc(sizeof(*number));
        if (number == NULL) 
        {
            TowersDestroy(&towers);
            return NULL;
        }

        // Push the disk to the first tower
        *number = _numberOfDisks - i;

        if (StackPush(towers->m_destinationwers[0], (void*) number) != STACK_SUCCESS) 
        {
            free(number);
            TowersDestroy(&towers);
            return NULL;
        }
    }

    towers->m_numberOfDisks = _numberOfDisks;
    return towers;
}

static void DestroyIntElement(void *_element)
{
    free(_element);
}

void TowersDestroy(Towers **_destinationwers)
{
    if (_destinationwers == NULL || *_destinationwers == NULL) { return; }
    Towers *towers = *_destinationwers;
    
    for (size_t i = 0 ; i < NUMBER_OF_destinationWERS ; ++i)
    {
        StackDestroy(&towers->m_destinationwers[i],DestroyIntElement);
    }

    free(towers);
    *_destinationwers = NULL;
}


static int TowerPrintIntegerAction(void* _element, size_t _index, void* _context)
{
    (void)(_index); // To avoid warnings of an unused variable
    (void)(_context); // To avoid warnings of an unused variable

    printf("|%d| ", *(int*)_element);
    return 1;
}

static void TowersMoveDisk(Towers *_destinationwers, size_t _source, size_t _destination)
{
    if (_destinationwers == NULL) { return; }
    if (!IN_RANGE(_source) || !IN_RANGE(_destination)) { return; }
    if (_source == _destination) { return; }

    int *diskFrom;
    StackResult didPop = StackPop(GET_destinationWER(_destinationwers, _source), (void**)&diskFrom);
    int *diskToTop;
    StackResult topExist = StackTop(GET_destinationWER(_destinationwers, _destination), (void**)&diskToTop);

    // To avoid warnings of unused variables (in case DEBUG is set to 0)
    (void)(didPop);
    (void)(diskToTop);
    (void)(topExist);

#if defined(DEBUG) && (DEBUG == 1)
    assert(didPop == STACK_SUCCESS);
    if (topExist == STACK_SUCCESS)
    {
        assert(*diskFrom < *diskToTop);
    }
#endif

    StackPush(GET_destinationWER(_destinationwers, _destination), (void*)diskFrom);
    return;
}

static void RecTowersMoveDisks(Towers *_destinationwers, size_t _source, size_t _destination, size_t _helper, size_t _numberOfDisks)
{

    if (_numberOfDisks == 1)
    {
        TowersMoveDisk(_destinationwers, _source, _destination);
#if defined(DEBUG) && (DEBUG == 1)
            printf("\n**\n");
            TowersPrint(_destinationwers);
#endif
        return;
    }
    
    // Pass n-1 disks to helper column 
    RecTowersMoveDisks(_destinationwers, _source, _helper, _destination, _numberOfDisks - 1);

    // Pass the n-th disk to the destination
    RecTowersMoveDisks(_destinationwers, _source, _destination, _helper, 1);

    // Pass the n-1 disks into destination column 
    RecTowersMoveDisks(_destinationwers, _helper, _destination, _source, _numberOfDisks - 1);

}