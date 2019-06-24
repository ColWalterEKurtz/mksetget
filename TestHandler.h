// -----------------------------------------------------------------------------
// TestHandler.h                                                   TestHandler.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref TestHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef TESTHANDLER_H_INCLUDE_NO1
#define TESTHANDLER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include "AttributeHandler.h"


// -----------
// TestHandler
// -----------
/**
 * @brief  This class generates simple output for each callback-handler.
 */
class TestHandler : public AttributeHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // -----------
  // TestHandler
  // -----------
  /**
   * @brief  The standard-constructor.
   */
  TestHandler();


  // ---------------------------------------------------------------------------
  // Callback handler                                           Callback handler
  // ---------------------------------------------------------------------------

  // --------------
  // OnBeginParsing
  // --------------
  /**
   * @brief  This method is called when the parser starts parsing.
   */
  virtual void OnBeginParsing();

  // ------------
  // OnEndParsing
  // ------------
  /**
   * @brief  This method is called when the parser has finished parsing.
   */
  virtual void OnEndParsing(const std::string& buffer);

  // -----------
  // OnAttribute
  // -----------
  /**
   * @brief  This method is called when the parser has found an attribute.
   */
  virtual void OnAttribute( const std::string&  type,
                            const std::string&  name,
                            int                 visibility,
                            bool                isStatic,
                            bool                isFinal
                          );

};


#endif  /* #ifndef TESTHANDLER_H_INCLUDE_NO1 */

