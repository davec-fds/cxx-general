/*****************************************************************************
 * SafeInt.c++
 *****************************************************************************
 * Unit tests the SafeInt class.
 *****************************************************************************/

// Standard includes.
#include <string>
#include <iostream>

// Testing include.
#include <SafeInt.h++>

// Bring in namespaces.
using namespace std;

/*
 * Test a given type.
 */
template <typename T> int test (string const& type) {
  
  // Output the test.
  cout << "Testing type " << type << "..." << endl;
  
  // Test SafeIntUtils first.
  cout << "  Testing SafeIntUtils::
  
  // All tests passed.
  return 0;
  
}

/*
 * Here we go.
 */
int main (int argc, char** argv) {
  
  // Ignore argc and argv.
  if (argc && argv) {}
  
  // Test every possible type.
  if (test<bool          >("bool"          )) { return 1; }
  if (test<char          >("char"          )) { return 1; }
  if (test<signed char   >("signed char"   )) { return 1; }
  if (test<unsigned char >("unsigned char" )) { return 1; }
  if (test<wchar_t       >("wchar_t"       )) { return 1; }
  if (test<short         >("short"         )) { return 1; }
  if (test<unsigned short>("unsigned short")) { return 1; }
  if (test<int           >("int"           )) { return 1; }
  if (test<unsigned int  >("unsigned int"  )) { return 1; }
  if (test<long          >("long"          )) { return 1; }
  if (test<unsigned long >("unsigned long" )) { return 1; }
  
  // All tests passed.
  return 0;
  
}

