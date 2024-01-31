//
// UnitTestManager.cpp
//
// Copyright: Mark Claypool and WPI, 2014
//
// (Based on early version by Ben Sautermeister - bsautermeister.de)
//

#include <stdio.h>		// for file operations
#include <sstream>		// for stream operations
#include <unistd.h>

#include "UnitTestManager.h"
#include "unit-test-utility.h"

// Create new unit test manager instance.
UnitTestManager::UnitTestManager(void) {
  case_count = 0;
  p_func_before = NULL;
  p_func_after = NULL;
  p_func_setup = NULL;
  p_func_cleanup = NULL;
}

// Get the one and only one Singleton instance.
UnitTestManager& UnitTestManager::getInstance(void) {
  static UnitTestManager unit_test_manager;
  return unit_test_manager;
}

// Run test with indicated index.
// Return results of test (true means "passed").
bool UnitTestManager::runTest(int test_index) {

  /////////////////////
  // Setup.

  // Open logfile.
  FILE *p_f = fopen(UTM_TEST_LOGFILE, "a");
  if (!p_f)
    p_f = stderr;

  /////////////////////
  // Run. 

  // Run before function.
  if (p_func_before != NULL)
    p_func_before(test_case[test_index].name);
  
  // Run current test.
  bool result = test_case[test_index].function();
  
  // Run after function.
  if (p_func_after != NULL)
    p_func_after(test_case[test_index].name);
  
  /////////////////////
  // Make result string.
  string result_string_screen, result_string_file, temp_string;

  // String for pass/fail.
  if (result == true)  {
    result_string_screen += passColor();
    result_string_screen += "PASS";
    result_string_file += "PASS";
    result_string_screen += resetColor();
  } else {
    result_string_screen += failColor();
    result_string_screen += "FAIL";
    result_string_file += "FAIL";
    result_string_screen += resetColor();
  }

  // String for test number and name.
  temp_string += "  test [";
  std::stringstream temp_out;
  temp_out << test_index;
  temp_string += temp_out.str();
  temp_string += "]: ";
  temp_string += test_case[test_index].name;
  temp_string += "\n";
  result_string_screen += temp_string;
  result_string_file += temp_string;
  
  // Write result string to screen and file.
  printf("%s", result_string_screen.c_str());
  fprintf(p_f, "%s", result_string_file.c_str());

  /////////////////////
  // Clean up.

  // Close logfile.
  if (p_f != stderr)
    fclose(p_f);

  return result;
}

// Set setup function.
void UnitTestManager::setSetupFunc(void (*function)(void)) {
  p_func_setup = function;
}

// Set cleanup function.
void UnitTestManager::setCleanupFunc(void (*function)(void)) {
  p_func_cleanup = function;
}

// Set before function.
void UnitTestManager::setBeforeFunc(void (*function)(string test_name)) {
  p_func_before = function;
}

// Set after function.
void UnitTestManager::setAfterFunc(void (*function)(string test_name)) {
  p_func_after = function;
}

// Register new test.
void UnitTestManager::registerTestFunction(string name, bool(*function)(void)){
  if (case_count < UTM_MAX_TEST_CASES) {
    test_case[case_count].name = name;
    test_case[case_count].function = function;
    case_count++;
  }
}

// Run test(s).  
int UnitTestManager::run(int test_index) {
  int start_index;
  int end_index;

  // Check test_index in valid range.
  if (test_index != UTM_ALL_TESTS &&
      ((test_index < 0) || (test_index >= case_count))) {
    fprintf(stderr, "Test index %d out of range. Valid range is [%d - %d].\n",
	    test_index, 0, case_count - 1);
    return -1;
  }

  // Call setup function (if appropriate).
  if (p_func_setup != NULL)
    p_func_setup();
  
  // If single test, start_index and end_index will be the same.
  // Otherwise, will go from 0 to case_count-1.
  if (test_index == UTM_ALL_TESTS) {
    start_index = 0;
    end_index = case_count-1;
  } else {
    start_index = test_index;
    end_index = test_index;
  }

  // Erase logfile.
  unlink(UTM_TEST_LOGFILE);

  // Run all tests from start_index to end_index (inclusive).
  int success_count = 0;
  for (int i = start_index; i <= end_index; i++) {
    if (runTest(i))
      success_count++;
  }

  // Write summary results to logfile.
  FILE *p_f = fopen(UTM_TEST_LOGFILE, "a");
  if (!p_f)
    p_f = stderr;
  int num_tests = end_index - start_index + 1;
  printf("Summary: %d of %d tests passed\n", success_count, num_tests);
  fprintf(p_f, "Summary: %d of %d tests passed\n", success_count, num_tests);
  if (p_f != stderr)
    fclose(p_f);

  // Call cleanup function (if appropriate).
  if (p_func_cleanup != NULL)
    p_func_cleanup();
  
  return success_count;
}
