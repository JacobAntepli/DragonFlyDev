//
// unit-test-utility.h
//
// Copyright: Mark Claypool and WPI, 2014
//

#ifndef _UTILITY_H_
#define _UTILITY_H_

// For colors, see: http://en.wikipedia.org/wiki/ANSI_escape_code
#define FAIL_COLOR  "\x1b[1;31m" // bold red
#define PASS_COLOR  "\x1b[32m"	 // non-bold green
#define RESET_COLOR "\x1b[0m"	 // reset to default

// Return true if terminal supports color, else false.
bool termColor();

// Return test FAIL color string.
const char *failColor();

// Return test PASS color string.
const char *passColor();

// Return reset color string.
const char *resetColor();

#endif // _UTILITY_H_
