//
// Created by Tobias Wollowski on 02.01.17.
//

#include <stdlib.h>     /* rand */
#include "dice.h"

/**
 * simple random between 1 and 6
 * @return
 */
uint16_t Dice::roll() {
    return (uint16_t) rand() % 6 + 1;
}