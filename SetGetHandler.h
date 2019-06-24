// -----------------------------------------------------------------------------
// SetGetHandler.h                                               SetGetHandler.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref SetGetHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef SETGETHANDLER_H_INCLUDE_NO1
#define SETGETHANDLER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "AttributeHandler.h"


// -------------
// SetGetHandler
// -------------
/**
 * @brief  This class generates java getter- and setter-methods.
 */
class SetGetHandler : public AttributeHandler
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // -------------
  // SetGetHandler
  // -------------
  /**
   * @brief  The standard-constructor.
   */
  SetGetHandler();


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

protected:

  // ---------------------------------------------------------------------------
  // Internal types                                               Internal types
  // ---------------------------------------------------------------------------

  // ---------
  // Attribute
  // ---------
  /**
   * @brief  All information about an attribute.
   */
  struct Attribute
  {
    std::string  name;
    std::string  type;
    int          visibility;
    bool         isStatic;
    bool         isFinal;
  };


  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // -----
  // upper
  // -----
  /**
   * @brief  This method returns the related uppercase character.
   */
  char upper(char c) const;

  // ---------------
  // getFunctionName
  // ---------------
  /**
   * @brief  This method returns the name of the related function.
   */
  std::string getFunctionName(const std::string& prefix, const std::string& attribute) const;

  // ----------------
  // getParameterName
  // ----------------
  /**
   * @brief  This method returns the name of the related parameter.
   */
  std::string getParameterName(const std::string& attribute) const;

  // --------------
  // showBigComment
  // --------------
  /**
   * @brief  This method pushes a framed comment to stdout.
   */
  bool showBigComment(const std::string& comment, const std::string& indent) const;

  // ----------
  // showSetter
  // ----------
  /**
   * @brief  This method pushes the code of s setter-method to stdout.
   */
  void showSetter(const Attribute& a, const std::string& indent = "") const;

  // ----------
  // showGetter
  // ----------
  /**
   * @brief  This method pushes the code of s getter-method to stdout.
   */
  void showGetter(const Attribute& a, const std::string& indent = "") const;


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the list of parsed attributes
  std::vector<Attribute> m_attributes;

};


#endif  /* #ifndef SETGETHANDLER_H_INCLUDE_NO1 */

