// -----------------------------------------------------------------------------
// AttributeParser.cpp                                       AttributeParser.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref AttributeParser class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "AttributeHandler.h"
#include "AttributeParser.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// ---------------
// AttributeParser
// ---------------
/*
 *
 */
AttributeParser::AttributeParser(AttributeHandler* handler)
: m_sqz(true)
{
  setHandler(handler);
}


// -----------------------------------------------------------------------------
// Handling                                                             Handling
// -----------------------------------------------------------------------------

// -----
// parse
// -----
/*
 * @brief  This method parses data from stdin.
 */
bool AttributeParser::parse()
{
  // check if handler is missing
  if (m_handler == 0)
  {
    // signalize trouble
    return false;
  }

  // reset global buffer
  m_sqz.resetBuffer();

  // the parser's state
  enum
  {
    FIND_TYPE,
    READ_TYPE,
    READ_TYPE_ARRAY,
    FIND_NAME,
    READ_NAME,
    READ_NAME_ARRAY,
    DROP_INITIALIZATION,
    DROP_COMMAND
  }
  state = FIND_TYPE;

  // some local buffers
  string  type       = "";
  string  name       = "";
  string  tarray     = "";
  string  narray     = "";
  int     visibility = AttributeHandler::DEFAULT;
  bool    isStatic   = false;
  bool    isFinal    = false;

  // one byte from stdin
  char c;

  // notify handler
  m_handler->OnBeginParsing();

  // parse entire stream
  while ( m_sqz.next(c) )
  {
    // don't look inside strings
    if ( m_sqz.isText() ) continue;

    // FIND_TYPE
    if (state == FIND_TYPE)
    {
      if ( isIDhead(c) )
      {
        // start type with current character
        type = c;

        // reset other buffers
        name       = "";
        tarray     = "";
        narray     = "";
        visibility = AttributeHandler::DEFAULT;
        isStatic   = false;
        isFinal    = false;

        // next state
        state = READ_TYPE;
      }

      // unexpected character
      else
      {
        // next state
        state = DROP_COMMAND;
      }
    }

    // READ_TYPE
    else if (state == READ_TYPE)
    {
      // separator found
      if (c == ' ')
      {
        if (type == "public")
        {
          type = "";
          visibility = AttributeHandler::PUBLIC;
        }

        else if (type == "protected")
        {
          type = "";
          visibility = AttributeHandler::PROTECTED;
        }

        else if (type == "private")
        {
          type = "";
          visibility = AttributeHandler::PRIVATE;
        }

        else if (type == "static")
        {
          type = "";
          isStatic = true;
        }

        else if (type == "final")
        {
          type = "";
          isFinal = true;
        }

        else
        {
          // next state
          state = FIND_NAME;
        }
      }

      // template found
      else if (c == '<')
      {
        if ( !type.empty() )
        {
          // update type
          type += readBalanced('<', '>');

          // next state
          state = FIND_NAME;
        }

        else
        {
          // next state
          state = DROP_COMMAND;
        }
      }

      // array found
      else if (c == '[')
      {
        // start type array
        tarray = readBalanced('[', ']');

        // next state
        state = READ_TYPE_ARRAY;
      }

      // inner character found
      else if ( isIDtail(c) )
      {
        // append character
        type += c;
      }

      // unexpected character
      else
      {
        // next state
        state = DROP_COMMAND;
      }
    }

    // READ_TYPE_ARRAY
    else if (state == READ_TYPE_ARRAY)
    {
      // next dimension
      if (c == '[')
      {
        // update type array
        tarray += readBalanced('[', ']');
      }

      // name found
      else if ( isIDhead(c) )
      {
        // start name with current character
        name = c;

        // next state
        state = READ_NAME;
      }

      // unexpected character
      else
      {
        // next state
        state = DROP_COMMAND;
      }
    }

    // FIND_NAME
    else if (state == FIND_NAME)
    {
      // skip all whitespace characters
      if (c != ' ')
      {
        if ( isIDhead(c) )
        {
          // start name with current character
          name = c;

          // next state
          state = READ_NAME;
        }

        // unexpected character
        else
        {
          // next state
          state = DROP_COMMAND;
        }
      }
    }

    // READ_NAME
    else if (state == READ_NAME)
    {
      // inner character found
      if ( isIDtail(c) )
      {
        // append character
        name += c;
      }

      // command finished
      else if (c == ';')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // back to initial state
        state = FIND_TYPE;
      }

      // more than one variable defined
      else if (c == ',')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // reset name related buffers
        name = "";
        narray = "";

        // next state
        state = FIND_NAME;
      }

      // array found
      else if (c == '[')
      {
        // start name array
        narray = readBalanced('[', ']');

        // next state
        state = READ_NAME_ARRAY;
      }

      // initialization found
      else if (c == '=')
      {
        state = DROP_INITIALIZATION;
      }

      // unexpected character
      else
      {
        // next state
        state = DROP_COMMAND;
      }
    }

    // READ_NAME_ARRAY
    else if (state == READ_NAME_ARRAY)
    {
      // next dimension
      if (c == '[')
      {
        // update name array
        narray += readBalanced('[', ']');
      }

      // command finished
      else if (c == ';')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // back to initial state
        state = FIND_TYPE;
      }

      else if (c == ',')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // reset name related buffers
        name = "";
        narray = "";

        // next state
        state = FIND_NAME;
      }

      // initialization found
      else if (c == '=')
      {
        // next state
        state = DROP_INITIALIZATION;
      }

      // unexpected character
      else
      {
        // next state
        state = DROP_COMMAND;
      }
    }

    // DROP_INITIALIZATION
    else if (state == DROP_INITIALIZATION)
    {
      // command finished
      if (c == ';')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // back to initial state
        state = FIND_TYPE;
      }

      // more than one variable defined
      else if (c == ',')
      {
        // at least type and name must be given
        if (!name.empty() && !type.empty())
        {
          // notify handler
          m_handler->OnAttribute( type + tarray + narray,
                                  name,
                                  visibility,
                                  isStatic,
                                  isFinal
                                );
        }

        // reset name related buffers
        name = "";
        narray = "";

        // next state
        state = FIND_NAME;
      }

      else if (c == '(')
      {
        // skip section
        readBalanced('(', ')');
      }

      else if (c == '[')
      {
        // skip section
        readBalanced('[', ']');
      }

      else if (c == '<')
      {
        // skip section
        readBalanced('<', '>');
      }

      else if (c == '{')
      {
        // skip section
        readBalanced('{', '}');
      }
    }

    // DROP_COMMAND
    else if (state == DROP_COMMAND)
    {
      // command finished
      if (c == ';')
      {
        // back to initial state
        state = FIND_TYPE;
      }
    }
  }

  // notify handler
  m_handler->OnEndParsing( m_sqz.getBuffer() );

  // signalize success
  return true;
}



// -----------------------------------------------------------------------------
// Setter methods                                                 Setter methods
// -----------------------------------------------------------------------------

// ----------
// setHandler
// ----------
/*
 *
 */
void AttributeParser::setHandler(AttributeHandler* handler)
{
  m_handler = handler;
}


// -----------------------------------------------------------------------------
// Getter methods                                                 Getter methods
// -----------------------------------------------------------------------------

// ----------
// getHandler
// ----------
/*
 *
 */
AttributeHandler* AttributeParser::getHandler() const
{
  return m_handler;
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// --------
// isIDhead
// --------
/*
 *
 */
bool AttributeParser::isIDhead(char c) const
{
  if ((c >= 'a') && (c <= 'z')) return true;
  if ((c >= 'A') && (c <= 'Z')) return true;
  if  (c == '_')                return true;

  return false;
}

// --------
// isIDtail
// --------
/*
 *
 */
bool AttributeParser::isIDtail(char c) const
{
  if ((c >= 'a') && (c <= 'z')) return true;
  if ((c >= 'A') && (c <= 'Z')) return true;
  if ((c >= '0') && (c <= '9')) return true;
  if  (c == '_')                return true;
  if  (c == '.')                return true;

  return false;
}

// ------------
// readBalanced
// ------------
/*
 *
 */
string AttributeParser::readBalanced(char up, char dn)
{
  // start with 'up' character
  string balanced(1, up);

  int poise = 1;

  char c;

  while ( m_sqz.next(c) )
  {
    // append character
    balanced += c;

    if (c == up) poise++;
    if (c == dn) poise--;

    if (poise == 0) break;
  }

  return balanced;
}

