#include <stdlib.h>
#include <math.h>

#include "util.h"

double getdelay (char const* nptr)
{
    char* endptr = NULL;
    double result = strtod (nptr, &endptr);
    if (result == 0.0) // Bad format
        return NAN;
    if (result < 0.001)
        return NAN;
    return result;
}
