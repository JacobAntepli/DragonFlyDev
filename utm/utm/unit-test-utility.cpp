//
// unit-test-utility.cpp
//
// Copyright: Mark Claypool and WPI, 2014
//

#include <stdio.h>		// for fileno()
#include <unistd.h>		// for isatty()

#include "unit-test-utility.h"

// Return true if terminal supports color, else false.
bool termColor() {

  // If a tty terminal, should support color.
  if (isatty(STDOUT_FILENO) == 1)
    return true;
  else
    return false;
}

// Return test FAIL color.
const char *failColor() {
  if (termColor()) 
    return FAIL_COLOR;
  else
    return "";
}

// Return test PASS color.
const char *passColor() {
  if (termColor())
    return PASS_COLOR;
  else
    return "";
}

// Return reset color string.
const char *resetColor() {
  if (termColor())
    return RESET_COLOR;
  else 
    return "";
}
