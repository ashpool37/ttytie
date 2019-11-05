#include <string.h>
#include <math.h>

#include "util.h"
#include "ttytie.h"

// This program shall concatenate a list of ttyrec files into one
// ttyrec file, shifting the timestamps in the second file onwards
// so that the result looks like a continuous session.

double const TTYTIE_DEFAULT_DELAY = 1.0;

int main (int argc, char const* argv[])
{
    // Want an interface similar to cat
    // Get list of input files as arguments, print result to stdout

    // We need to know the boundaries between files though,
    // as we want to know where to begin shifting the timestamps.
    // Therefore, reading from stdin makes little sense, and
    // we want at least one file as an argument.
    
    double delay = TTYTIE_DEFAULT_DELAY;

    if (argc < 2)
        return 1;

    int argno = 1;
    for (; argno < argc; ++argno)
    {

        if (!strcmp(argv[argno], "-d"))
        {
            // Delay (seconds) between files (optional)
            // Minimum 0.001 (1 usec)

            if (argno + 1 == argc)
                return 1;

            delay = getdelay (argv[argno + 1]);

            if (delay == NAN)
                return 1;

            ++argno;
        }
	else 
            break;
    }

    int args_left = argc - argno;
    if (args_left < 1)
        return 1;

    return ttytie (args_left, argv + argno, delay);
}
