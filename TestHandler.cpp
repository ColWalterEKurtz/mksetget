// -----------------------------------------------------------------------------
// TestHandler.cpp                                               TestHandler.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref TestHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
// #include <cstdlib>
// #include <climits>
// #include <cfloat>
// #include <cmath>
// #include <ctime>
// #include <list>
// #include <stack>
// #include <vector>
// #include <queue>
// #include <deque>
// #include <set>
// #include <map>
// #include <algorithm>
// #include <string>
// #include <sstream>
// #include <fstream>
#include <iostream>
// #include <iomanip>
#include "TestHandler.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// -----------
// TestHandler
// -----------
/*
 *
 */
TestHandler::TestHandler()
{
  // initialization
}


// -----------------------------------------------------------------------------
// Callback handler                                             Callback handler
// -----------------------------------------------------------------------------

// --------------
// OnBeginParsing
// --------------
/*
 *
 */
void TestHandler::OnBeginParsing()
{
  cout << "OnBeginParsing()" << endl;
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void TestHandler::OnEndParsing(const string& buffer)
{
  cout << "OnEndParsing()" << endl;
  cout << endl;
  cout << buffer << endl;
}

// -----------
// OnAttribute
// -----------
/*
 *
 */
void TestHandler::OnAttribute( const string&  type,
                               const string&  name,
                               int            visibility,
                               bool           isStatic,
                               bool           isFinal
                             )
{
  string vid[4];
  vid[AttributeHandler::PRIVATE]   = "PRIVATE";
  vid[AttributeHandler::DEFAULT]   = "DEFAULT";
  vid[AttributeHandler::PROTECTED] = "PROTECTED";
  vid[AttributeHandler::PUBLIC]    = "PUBLIC";

  cout << "OnAttribute("
       << type
       << ", "
       << name
       << ", "
       << vid[visibility]
       << ", "
       << (isStatic ? "true" : "false")
       << ", "
       << (isFinal ? "true" : "false")
       << ")" << endl;
}

