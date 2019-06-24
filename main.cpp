// -----------------------------------------------------------------------------
// main.cpp                                                             main.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the program's showHelp(), showVersion()
 *             and main() function and doxygen's main page.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-13
 * @copyright  GNU General Public License - Version 3.0
 *
 * @mainpage
 *
 * @section issue What is the issue here?
 *   Lorem ipsum dolor sit amet, consectetur adipisici elit, sed eiusmod
 *   tempor incidunt ut labore et dolore magna aliqua. Ut enim ad minim
 *   veniam, quis nostrud exercitation ullamco laboris nisi ut aliquid
 *   ex ea commodi consequat. Quis aute iure reprehenderit in voluptate
 *   velit esse cillum dolore eu fugiat nulla pariatur.
 *   Excepteur sint obcaecat cupiditat non proident, sunt in culpa qui
 *   officia deserunt mollit anim id est laborum.
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "message.h"
#include "cli.h"
#include "AttributeParser.h"
#include "SetGetHandler.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Functions                                                           Functions
// -----------------------------------------------------------------------------

// --------
// showHelp
// --------
/**
 * @brief  This function shows the program's help.
 */
void showHelp()
{
  cout << endl;
  cout << "NAME" << endl;
  cout << "  mksetget - make setter and getter methods" << endl;
  cout << endl;
  cout << "SYNOPSIS" << endl;
  cout << "  mksetget {-h|-v}  show help resp. version and exit" << endl;
  cout << endl;
  cout << "DESCRIPTION" << endl;
  cout << "  mksetget reads the declaration of java attributes from stdin" << endl;
  cout << "  and pushes the related setter and getter methods to stdout." << endl;
  cout << endl;
  cout << "OPTIONS" << endl;
  cout << "  -h  show help and exit" << endl;
  cout << "  -v  show version and exit" << endl;
  cout << endl;
}

// -----------
// showVersion
// -----------
/**
 * @brief  This function shows the program's version.
 */
void showVersion()
{
  cout << "2019-06-18" << endl;
}

// ----
// main
// ----
/**
 * @brief  The program starts in this function.
 *
 * @param argc  holds the number of passed command-line arguments.
 * @param argv  holds the list of passed command-line arguments.
 *
 * @return
 * Value | Meaning
 * ----: | :------
 *     0 | The requested operation finished successfully.
 *     1 | The requested operation failed.
 */
int main(int argc, char** argv)
{
  // create command-line parser
  cli cmdl;

  // parse command-line
  if ( cmdl.parse(argc, argv) )
  {
    // SHOW_HELP
    if (cmdl.operation == cli::SHOW_HELP)
    {
      showHelp();

      // signalize success
      return 0;
    }

    // SHOW_VERSION
    else if (cmdl.operation == cli::SHOW_VERSION)
    {
      showVersion();

      // signalize success
      return 0;
    }

    // DEFAULT
    else if (cmdl.operation == cli::DEFAULT)
    {
      // this handler creates the output
      SetGetHandler handler;

      // this parser reads the java code
      AttributeParser parser(&handler);

      // parse data from stdin
      return parser.parse() ? 0 : 1;
    }
  }

  // invalid command-line
  return 1;
}

