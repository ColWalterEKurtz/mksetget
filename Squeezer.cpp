// -----------------------------------------------------------------------------
// Squeezer.cpp                                                     Squeezer.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref Squeezer class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "Squeezer.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// --------
// Squeezer
// --------
/*
 *
 */
Squeezer::Squeezer(bool enableBuffer)
{
  m_state      = CODE;
  m_buffer     = "";
  m_useBuffer  = enableBuffer;
  m_delayed    = 0;
  m_useDelayed = false;
  m_separate   = false;
  m_context    = 0;
}


// -----------------------------------------------------------------------------
// Handling                                                             Handling
// -----------------------------------------------------------------------------

// ----
// next
// ----
/*
 *
 */
bool Squeezer::next(char& c)
{
  // this character will be returned
  char tmp = 0;

  // true if the next visible character was
  // seperated by at least one whitespace
  bool sep = false;

  // CODE
  if (m_state == CODE)
  {
    // set 'code' context
    m_context = 1;

    // skip all whitespace characters first
    if ( !nextVisible(tmp, sep) )
    {
      // set 'null' context
      m_context = 0;

      // no more visible characters
      return false;
    }

    // skip all comments next
    while (tmp == '/')
    {
      // try to skip comment
      if ( skipComment() )
      {
        // get first visible character after comment
        if ( !nextVisible(tmp, sep) )
        {
          // set 'null' context
          m_context = 0;

          // no more visible characters
          return false;
        }
      }

      // slash not consumed by comment
      else
      {
        // set return value
        c = '/';

        // update alphanumeric flag
        m_separate = isalnum(c);

        // signalize success
        return true;
      }
    }

    // double-quoted string started
    if (tmp == '"')
    {
      m_state = DQ_STRING;
    }

    // single-quoted string started
    else if (tmp == '\'')
    {
      m_state = SQ_STRING;
    }

    // check if whitespace is needed
    if ( m_separate && sep && isalnum(tmp) )
    {
      // use this character next time
      delay(tmp);

      // return syntactical whitespace (ASCII 32 only)
      tmp = ' ';
    }
  }

  // DQ_STRING
  else if (m_state == DQ_STRING)
  {
    // set 'string' context
    m_context = 2;

    // try to get next character from stdin
    if ( !nextChar(tmp) )
    {
      // set 'null' context
      m_context = 0;

      // no more visible characters
      return false;
    }

    // string finished
    if (tmp == '"')
    {
      // set 'code' context
      m_context = 1;

      // next state
      m_state = CODE;
    }

    // escape sequence found
    else if (tmp == '\\')
    {
      m_state = DQ_ESCAPE;
    }
  }

  // DQ_ESCAPE
  else if (m_state == DQ_ESCAPE)
  {
    // set 'string' context
    m_context = 2;

    // try to get next character from stdin
    if ( !nextChar(tmp) )
    {
      // set 'null' context
      m_context = 0;

      // no more visible characters
      return false;
    }

    // back to last state
    m_state = DQ_STRING;
  }

  // SQ_STRING
  else if (m_state == SQ_STRING)
  {
    // set 'string' context
    m_context = 2;

    // try to get next character from stdin
    if ( !nextChar(tmp) )
    {
      // set 'null' context
      m_context = 0;

      // no more visible characters
      return false;
    }

    // string finished
    if (tmp == '\'')
    {
      // set 'code' context
      m_context = 1;

      // next state
      m_state = CODE;
    }

    // escape sequence found
    else if (tmp == '\\')
    {
      m_state = SQ_ESCAPE;
    }
  }

  // SQ_ESCAPE
  else if (m_state == SQ_ESCAPE)
  {
    // set 'string' context
    m_context = 2;

    // try to get next character from stdin
    if ( !nextChar(tmp) )
    {
      // set 'null' context
      m_context = 0;

      // no more visible characters
      return false;
    }

    // back to last state
    m_state = SQ_STRING;
  }

  // set return value
  c = tmp;

  // update alphanumeric flag
  m_separate = isalnum(c);

  // signalize success
  return true;
}

// ------
// isCode
// ------
/*
 *
 */
bool Squeezer::isCode() const
{
  return (m_context == 1);
}

// ------
// isText
// ------
/*
 *
 */
bool Squeezer::isText() const
{
  return (m_context == 2);
}

// ---------
// getBuffer
// ---------
/*
 *
 */
string Squeezer::getBuffer() const
{
  return m_buffer;
}

// -----------
// resetBuffer
// -----------
/*
 *
 */
void Squeezer::resetBuffer()
{
  m_buffer.clear();
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// -------
// isspace
// -------
/**
 *
 */
bool Squeezer::isspace(char c) const
{
  if (c == 32) return true;
  if (c == 10) return true;
  if (c ==  9) return true;
  if (c == 13) return true;

  return false;
}

// -------
// isalnum
// -------
/**
 *
 */
bool Squeezer::isalnum(char c) const
{
  if ((c >= 'a') && (c <= 'z')) return true;
  if ((c >= 'A') && (c <= 'Z')) return true;
  if ((c >= '0') && (c <= '9')) return true;

  return false;
}

// -----
// delay
// -----
/*
 *
 */
void Squeezer::delay(char c)
{
  m_delayed = c;
  m_useDelayed = true;
}

// --------
// nextChar
// --------
/*
 *
 */
bool Squeezer::nextChar(char& c)
{
  // use delayed character
  if (m_useDelayed)
  {
    c = m_delayed;
    m_useDelayed = false;
  }

  // no delayed character
  else
  {
    // try to get next byte from stdin
    if ( !cin.get(c) )
    {
      // no more characters
      return false;
    }

    // check flag
    if (m_useBuffer)
    {
      // append next byte from stdin
      m_buffer += c;
    }
  }

  // signalize success
  return true;
}

// -----------
// nextVisible
// -----------
/*
 *
 */
bool Squeezer::nextVisible(char& c, bool& separated)
{
  // start with whitespace
  c = ' ';

  // skip all subsequent whitespaces
  while ( isspace(c) )
  {
    // try to get next character
    if ( !nextChar(c) )
    {
      // no more characters
      return false;
    }

    // update whitespace flag
    if ( isspace(c) )
    {
      separated = true;
    }
  }

  // signalize success
  return true;
}

// -----------
// skipComment
// -----------
/*
 *
 */
bool Squeezer::skipComment()
{
  char tmp = 0;

  // no more characters from stdin
  if ( !nextChar(tmp) ) return false;

  // short comment found
  if (tmp == '/')
  {
    // skip rest of line
    while ( nextChar(tmp) )
    {
      // stop at LF or CR
      if ((tmp == 10) || (tmp == 13)) break;
    }

    // slash consumed
    return true;
  }

  // multi-line comment found
  if (tmp == '*')
  {
    // two characters must be matched
    int match = 0;

    // skip rest of comment
    while ( nextChar(tmp) )
    {
           if ((match == 0) && (tmp == '*')) match = 1;
      else if ((match == 1) && (tmp == '/')) break;
      else match = 0;
    }

    // slash consumed
    return true;
  }

  // handle wrong character next time
  delay(tmp);

  // slash not consumed
  return false;
}

