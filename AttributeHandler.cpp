// -----------------------------------------------------------------------------
// AttributeHandler.cpp                                     AttributeHandler.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref AttributeHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-13
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "AttributeHandler.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ----------------
// AttributeHandler
// ----------------
/*
 *
 */
AttributeHandler::AttributeHandler()
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
void AttributeHandler::OnBeginParsing()
{
  // nothing
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void AttributeHandler::OnEndParsing(const string& buffer)
{
  // nothing
}

// -----------
// OnAttribute
// -----------
/*
 *
 */
void AttributeHandler::OnAttribute( const string&  type,
                                    const string&  name,
                                    int            visibility,
                                    bool           isStatic,
                                    bool           isFinal
                                  )
{
  // nothing
}

