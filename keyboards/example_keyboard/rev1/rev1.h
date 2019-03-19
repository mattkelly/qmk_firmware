#ifndef REV1_H
#define REV1_H

#include "example_keyboard.h"

#include "quantum.h"

#define LAYOUT( \
    K00, K01, \
    K10, K11  \
    ) \
    { \
        { K00, K01 }, \
        { K10, K11 }  \
    }
#endif
