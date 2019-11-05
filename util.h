#pragma once


// Parse double from string with restrictions
// Number must be > 0.001
// Return NaN if failed to parse or restrictions unmet

double getdelay (char const* nptr);
