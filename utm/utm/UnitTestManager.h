//
// UnitTestManager.h
//
// Copyright: Mark Claypool and WPI, 2014
//

#ifndef __UNIT_TEST_MANAGER_H__
#define __UNIT_TEST_MANAGER_H__

using std::string;

#define UTM_VERSION 1.0		     // Version number.
#define UTM_MAX_TEST_CASES 256	     // Maximum number of unit tests.
#define UTM_TEST_LOGFILE "utm.log"   // Name of summary logfile.
#define UTM_ALL_TESTS -1             // Index if running all tests.

// Named test case.
struct testCase {
  string name;
  bool (* function)(void);
};

// Manage set of test cases.
class UnitTestManager {

 private:
  struct testCase test_case[UTM_MAX_TEST_CASES]; // Test cases to run.
  int case_count;			         // Count of cases to run.

  UnitTestManager(void);		     // Private since Singleton.
  UnitTestManager(UnitTestManager const&);   // Hide copy.
  void operator=(UnitTestManager const&);    // Hide assignment.

  // Function before start of all test cases.
  void (* p_func_setup)(void);

  // Function after end of all test cases.
  void (* p_func_cleanup)(void);

  // Function before start of each test case.
  void (* p_func_before)(string test_name);

  // Function after end of each test case.
  void (* p_func_after)(string test_name);

  // Run test with indicated index.
  // Return results of test (true means "passed").
  bool runTest(int test_index);
  
 public:

  // Get the one and only one Singleton instance of the manager.
  static UnitTestManager& getInstance(void);
  
  // Set setup function.
  void setSetupFunc(void (*function)(void));
  
  // Set cleanup function.
  void setCleanupFunc(void (*function)(void));
  
  // Set before function.
  void setBeforeFunc(void (*function)(string test_name));

  // Set after function.  
  void setAfterFunc(void (*function)(string test_name));

  // Register new test.
  void registerTestFunction(string name, bool (*function)(void));

  // Run test(s).  
  // If index is ALL_TESTS then run all tests.
  int run(int test_index = UTM_ALL_TESTS);
};

#endif
