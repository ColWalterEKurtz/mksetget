// -----------------------------------------------------------------------------
// AttributeHandler.h                                         AttributeHandler.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref AttributeHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-13
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef ATTRIBUTEHANDLER_H_INCLUDE_NO1
#define ATTRIBUTEHANDLER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>


// ----------------
// AttributeHandler
// ----------------
/**
 * @brief  This class defines all messages an AttributeParser can send.
 */
class AttributeHandler
{

public:

  // ---------------------------------------------------------------------------
  // Flags                                                                 Flags
  // ---------------------------------------------------------------------------

  // ----------
  // Visibility
  // ----------
  /**
   * @brief  named visibility flags
   */
  typedef enum { PRIVATE, DEFAULT, PROTECTED, PUBLIC } Visibility;


  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ----------------
  // AttributeHandler
  // ----------------
  /**
   * @brief  The standard-constructor.
   */
  AttributeHandler();


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


#endif  /* #ifndef ATTRIBUTEHANDLER_H_INCLUDE_NO1 */

