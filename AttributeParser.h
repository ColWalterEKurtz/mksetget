// -----------------------------------------------------------------------------
// AttributeParser.h                                           AttributeParser.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref AttributeParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef ATTRIBUTEPARSER_H_INCLUDE_NO1
#define ATTRIBUTEPARSER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>
#include "Squeezer.h"


// ----------------
// AttributeHandler
// ----------------
/*
 * Forward definition.
 */
class AttributeHandler;


// ---------------
// AttributeParser
// ---------------
/**
 * @brief  This class reads the definition of variables from java code.
 */
class AttributeParser
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // ---------------
  // AttributeParser
  // ---------------
  /**
   * @brief  The constructor sets the related handler.
   */
  AttributeParser(AttributeHandler* = 0);


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // -----
  // parse
  // -----
  /**
   * @brief  This method parses data from stdin.
   */
  bool parse();


  // ---------------------------------------------------------------------------
  // Setter methods                                               Setter methods
  // ---------------------------------------------------------------------------

  // ----------
  // setHandler
  // ----------
  /**
   * @brief  This method sets the related handler.
   */
  void setHandler(AttributeHandler* handler);


  // ---------------------------------------------------------------------------
  // Getter methods                                               Getter methods
  // ---------------------------------------------------------------------------

  // ----------
  // getHandler
  // ----------
  /**
   * @brief  This method returns the related handler.
   */
  AttributeHandler* getHandler() const;


protected:

  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // --------
  // isIDhead
  // --------
  /**
   * @brief  This method checks if an identifier can start with the passed character.
   */
  bool isIDhead(char c) const;

  // --------
  // isIDtail
  // --------
  /**
   * @brief  This method checks if an identifier can contain the passed character.
   */
  bool isIDtail(char c) const;

  // ------------
  // readBalanced
  // ------------
  /**
   * @brief  This method reads a well-balanced sequence <up> ... <down> from stdin.
   */
  std::string readBalanced(char up, char dn);


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the handler that will receive all messages
  AttributeHandler* m_handler;

  /// this Squeezer reads the relevant java code from stdin
  Squeezer m_sqz;

};


#endif  /* #ifndef ATTRIBUTEPARSER_H_INCLUDE_NO1 */

