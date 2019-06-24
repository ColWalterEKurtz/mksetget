// -----------------------------------------------------------------------------
// Squeezer.h                                                         Squeezer.h
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the definition of the @ref Squeezer class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// One-Definition-Rule                                       One-Definition-Rule
// -----------------------------------------------------------------------------
#ifndef SQUEEZER_H_INCLUDE_NO1
#define SQUEEZER_H_INCLUDE_NO1


// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>


// --------
// Squeezer
// --------
/**
 * @brief  This class reads java code from stdin and pushes only the
 *         minimum number of needed characters to stdout.
 */
class Squeezer
{

public:

  // ---------------------------------------------------------------------------
  // Construction                                                   Construction
  // ---------------------------------------------------------------------------

  // --------
  // Squeezer
  // --------
  /**
   * @brief  The standard-constructor.
   */
  Squeezer(bool enableBuffer = false);


  // ---------------------------------------------------------------------------
  // Handling                                                           Handling
  // ---------------------------------------------------------------------------

  // ----
  // next
  // ----
  /**
   * @brief  This method returns the next character from stdin.
   */
  bool next(char& c);

  // ------
  // isCode
  // ------
  /**
   * @brief  This method returns true if the character from the
   *         most recent call of next() comes from a code context.
   */
  bool isCode() const;

  // ------
  // isText
  // ------
  /**
   * @brief  This method returns true if the character from the
   *         most recent call of next() comes from a string context.
   */
  bool isText() const;

  // ---------
  // getBuffer
  // ---------
  /**
   * @brief  This method returns the global buffer.
   */
  std::string getBuffer() const;

  // -----------
  // resetBuffer
  // -----------
  /**
   * @brief  This method clears the global buffer.
   */
  void resetBuffer();


protected:

  // ---------------------------------------------------------------------------
  // Internal types                                               Internal types
  // ---------------------------------------------------------------------------

  // ------
  // States
  // ------
  /**
   * @brief  The parser is always in one of these states.
   */
  enum States
  {
    CODE,
    DQ_STRING,
    DQ_ESCAPE,
    SQ_STRING,
    SQ_ESCAPE
  };


  // ---------------------------------------------------------------------------
  // Internal methods                                           Internal methods
  // ---------------------------------------------------------------------------

  // -------
  // isspace
  // -------
  /**
   * @brief  This method returns true if the passed character
   *         is a whitespace character.
   */
  bool isspace(char c) const;

  // -------
  // isalnum
  // -------
  /**
   * @brief  This method returns true if the passed character
   *         is from ['A', 'Z'], ['a', 'z'] or ['0', '9'].
   */
  bool isalnum(char c) const;

  // -----
  // delay
  // -----
  /**
   * @brief  This method buffers the passed character.
   */
  void delay(char c);

  // --------
  // nextChar
  // --------
  /**
   * @brief  This method returns the next character to analyze.
   */
  bool nextChar(char& c);

  // -----------
  // nextVisible
  // -----------
  /**
   * @brief  This method returns the next visible character to analyze.
   */
  bool nextVisible(char& c, bool& separated);

  // -----------
  // skipComment
  // -----------
  /**
   * @brief  This method drops comments. It must be called after the
   *         first (initial) slash has been extracted from stdin.
   *
   * @return
   * Value | Meaning
   * ----: | :------
   *  true | The initial slash was followed by either / or *
   * false | The initial slash was not part of a comment
   */
  bool skipComment();


private:

  // ---------------------------------------------------------------------------
  // Attributes                                                       Attributes
  // ---------------------------------------------------------------------------

  /// the parser's state
  States m_state;

  /// the entire input
  std::string m_buffer;

  /// true if the enrire input should be buffered
  bool m_useBuffer;

  /// one buffered character
  char m_delayed;

  /// true if m_next should be used
  bool m_useDelayed;

  /// true if two alphanumeric characters should be separated
  bool m_separate;

  /// the context of the character from the most recent call of next()
  int m_context;

};


#endif  /* #ifndef SQUEEZER_H_INCLUDE_NO1 */

