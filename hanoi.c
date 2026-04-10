#include "hanoi.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define NUMBER_OF_TOWERS 3
#define STATIC_CAPACITY 0
struct Towers
{
    Stack *m_towers[NUMBER_OF_TOWERS];
    size_t m_numberOfDisks;
};

static int TowerPrintIntegerAction(void* _element, size_t _index, void* _context);
static void TowersMoveDisk(Towers *_towers, size_t _source, size_t _destination);
static void RecTowersMoveDisks(Towers *_towers, size_t _source, size_t _destination, size_t _helper, size_t _numberOfDisks);
static void DestroyIntElement(void *_element);

#define IN_RANGE(num) ((num) >= 1 && (num) <= NUMBER_OF_TOWERS)
#define GET_TOWER(towers, num) towers->m_towers[num - 1]

TowersResult TowersMoveDisks(Towers *_towers, size_t _source, size_t _destination)
{
    if (_towers == NULL) { return TOWERS_UNINITIALIZED_ERROR; }
    if (!IN_RANGE(_source) || !IN_RANGE(_destination)) { return TOWERS_OUT_OF_BOUND_ERROR; }

    // Find the tower that is neither the source nor the destination
    size_t helper; 
    for (helper = 1 ; helper <= NUMBER_OF_TOWERS; ++helper)
    {
        if (helper != _source && helper != _destination)
        {
            break;
        }
    }

    RecTowersMoveDisks(_towers, _source, _destination, helper, _towers->m_numberOfDisks);
    return TOWERS_SUCCESS;
}


void TowersPrint(Towers *_towers)
{
    if (_towers == NULL) { return; }

    for (size_t i = 0 ; i < NUMBER_OF_TOWERS ; ++i)
    {
        printf("===");
        StackPrint(_towers->m_towers[i], TowerPrintIntegerAction, NULL);
        printf("\n");
    }
}


Towers *TowersCreate(size_t _numberOfDisks)
{
    if (_numberOfDisks == 0) { return NULL; }

    Towers *towers = malloc(sizeof(Towers));
    if (towers == NULL) { return NULL; }

    for (size_t i = 0 ; i < NUMBER_OF_TOWERS ; ++i)
    {
        towers->m_towers[i] = StackCreate(_numberOfDisks, STATIC_CAPACITY);
        if (towers->m_towers[i] == NULL)
        {
            for (size_t j = 0; j < i ; ++j)
            {
                StackDestroy(&towers->m_towers[j], DestroyIntElement);
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

        if (StackPush(towers->m_towers[0], (void*) number) != STACK_SUCCESS) 
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

void TowersDestroy(Towers **_towers)
{
    if (_towers == NULL || *_towers == NULL) { return; }
    Towers *towers = *_towers;
    
    for (size_t i = 0 ; i < NUMBER_OF_TOWERS ; ++i)
    {
        StackDestroy(&towers->m_towers[i],DestroyIntElement);
    }

    free(towers);
    *_towers = NULL;
}


static int TowerPrintIntegerAction(void* _element, size_t _index, void* _context)
{
    (void)(_index); // To avoid warnings of an unused variable
    (void)(_context); // To avoid warnings of an unused variable

    printf("|%d| ", *(int*)_element);
    return 1;
}

static void TowersMoveDisk(Towers *_towers, size_t _source, size_t _destination)
{
    if (_towers == NULL) { return; }
    if (!IN_RANGE(_source) || !IN_RANGE(_destination)) { return; }
    if (_source == _destination) { return; }

    int *diskFrom;
    StackResult didPop = StackPop(GET_TOWER(_towers, _source), (void**)&diskFrom);
    int *diskToTop;
    StackResult topExist = StackTop(GET_TOWER(_towers, _destination), (void**)&diskToTop);

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

    StackResult didPush = StackPush(GET_TOWER(_towers, _destination), (void*)diskFrom);
    #if defined(DEBUG) && (DEBUG == 1)
    assert(didPush == STACK_SUCCESS);
    #endif
    (void)(didPush); // To avoid warning

    return;
}

static void RecTowersMoveDisks(Towers *_towers, size_t _source, size_t _destination, size_t _helper, size_t _numberOfDisks)
{

    if (_numberOfDisks == 1)
    {
        TowersMoveDisk(_towers, _source, _destination);
#if defined(DEBUG) && (DEBUG == 1)
            printf("\n**\n");
            TowersPrint(_towers);
#endif
        return;
    }
    
    // Pass n-1 disks to helper column 
    RecTowersMoveDisks(_towers, _source, _helper, _destination, _numberOfDisks - 1);

    // Pass the n-th disk to the destination
    TowersMoveDisk(_towers, _source, _destination);

    // Pass the n-1 disks into destination column 
    RecTowersMoveDisks(_towers, _helper, _destination, _source, _numberOfDisks - 1);

}