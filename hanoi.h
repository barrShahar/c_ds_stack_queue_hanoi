#pragma once
#include <stdlib.h>
#include "genstack.h"

typedef struct Towers Towers;

#ifndef DEBUG
    #define DEBUG 0  // Default to OFF
#endif
typedef enum Towers_Result
{
    TOWERS_SUCCESS,
    TOWERS_UNINITIALIZED_ERROR,
    TOWERS_ALLOCATION_ERROR,
    TOWERS_NULL_PTR,
    TOWERS_OUT_OF_BOUND_ERROR,
    TOWERS_UNKNOWN_ERROR
} TowersResult;

/**
 * @brief Create a new Towers object
 * @param[in] _numberOfDisks - The number of disks to create
 * @return Towers pointer on success, NULL on failure
 */
Towers *TowersCreate(size_t _numberOfDisks);

/**
 * @brief Destroy a Towers object
 * @param[in] _towers - The Towers object to destroy
 * @return void
 */
void TowersDestroy(Towers **_towers);

/**
 * @brief Move the disks from one tower to another
 * @param[in] _towers - The Towers object to move the disks from
 * @param[in] _from - The tower to move the disks from
 * @param[in] _to - The tower to move the disks to
 * @return TowersResult - 
 */
TowersResult TowersMoveDisks(Towers *_towers, size_t _source, size_t _destination);

/**
 * @brief Print the Towers object
 * @param[in] _towers - The Towers object to print
 * @return void
 */
void TowersPrint(Towers *_towers);