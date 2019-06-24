// -----------------------------------------------------------------------------
// SetGetHandler.cpp                                           SetGetHandler.cpp
// -----------------------------------------------------------------------------
/**
 * @file
 * @brief      This file holds the implementation of the @ref SetGetHandler class.
 * @author     Col. Walter E. Kurtz
 * @version    2019-06-18
 * @copyright  GNU General Public License - Version 3.0
 */

// -----------------------------------------------------------------------------
// Includes                                                             Includes
// -----------------------------------------------------------------------------
#include <iostream>
#include "SetGetHandler.h"


// -----------------------------------------------------------------------------
// Used namespaces                                               Used namespaces
// -----------------------------------------------------------------------------
using namespace std;


// -----------------------------------------------------------------------------
// Construction                                                     Construction
// -----------------------------------------------------------------------------

// -------------
// SetGetHandler
// -------------
/*
 *
 */
SetGetHandler::SetGetHandler()
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
void SetGetHandler::OnBeginParsing()
{
  // reset list of attributes
  m_attributes.clear();
}

// ------------
// OnEndParsing
// ------------
/*
 *
 */
void SetGetHandler::OnEndParsing(const string& buffer)
{
  string indent("");

  // find initial indent
  for(unsigned i = 0; i < buffer.size(); i++)
  {
    if ((buffer[i] == ' ') || (buffer[i] == '\t'))
    {
      indent += buffer[i];
    }

    else
    {
      break;
    }
  }

  // restore parsed lines
  cout << buffer << endl;

  // show framed comment
  if (m_attributes.size() > 1)
  {
    if ( showBigComment("Setter methods", indent) )
    {
      cout << endl;
    }
  }

  // show all setter methods
  for(unsigned i = 0; i < m_attributes.size(); i++)
  {
    showSetter(m_attributes[i], indent);
    cout << endl;
  }

  // show framed comment
  if (m_attributes.size() > 1)
  {
    if ( showBigComment("Getter methods", indent) )
    {
      cout << endl;
    }
  }

  // show all getter methods
  for(unsigned i = 0; i < m_attributes.size(); i++)
  {
    showGetter(m_attributes[i], indent);
    cout << endl;
  }
}

// -----------
// OnAttribute
// -----------
/*
 *
 */
void SetGetHandler::OnAttribute( const string&  type,
                                 const string&  name,
                                 int            visibility,
                                 bool           isStatic,
                                 bool           isFinal
                               )
{
  // create new attribute
  Attribute a;
  a.type       = type;
  a.name       = name;
  a.visibility = visibility;
  a.isStatic   = isStatic;
  a.isFinal    = isFinal;

  // add to list of attributes
  m_attributes.push_back(a);
}


// -----------------------------------------------------------------------------
// Internal methods                                             Internal methods
// -----------------------------------------------------------------------------

// -----
// upper
// -----
/*
 *
 */
char SetGetHandler::upper(char c) const
{
  switch (c)
  {
    case 'a': return 'A';
    case 'b': return 'B';
    case 'c': return 'C';
    case 'd': return 'D';
    case 'e': return 'E';
    case 'f': return 'F';
    case 'g': return 'G';
    case 'h': return 'H';
    case 'i': return 'I';
    case 'j': return 'J';
    case 'k': return 'K';
    case 'l': return 'L';
    case 'm': return 'M';
    case 'n': return 'N';
    case 'o': return 'O';
    case 'p': return 'P';
    case 'q': return 'Q';
    case 'r': return 'R';
    case 's': return 'S';
    case 't': return 'T';
    case 'u': return 'U';
    case 'v': return 'V';
    case 'w': return 'W';
    case 'x': return 'X';
    case 'y': return 'Y';
    case 'z': return 'Z';
  }

  return c;
}

// ---------------
// getFunctionName
// ---------------
/*
 *
 */
string SetGetHandler::getFunctionName(const string& prefix, const string& attribute) const
{
  unsigned start = 0;

  // skip initial 'm_'
  if (attribute.size() > 3)
  {
    if ( (attribute[0] == 'm')
    &&   (attribute[1] == '_') )
    {
      start = 2;
    }
  }

  // start with given prefix
  string fname(prefix);

  // copy attribute name
  for(unsigned i = start; i < attribute.size(); i++)
  {
    // start with capital letter
    if ((i == start) && (!prefix.empty()))
    {
      fname += upper(attribute[i]);
    }

    else
    {
      fname += attribute[i];
    }
  }

  return fname;
}

// ----------------
// getParameterName
// ----------------
/**
 * @brief  This method returns the name of the related parameter.
 */
string SetGetHandler::getParameterName(const string& attribute) const
{
  // same as function but without prefix
  return getFunctionName("", attribute);
}

// --------------
// showBigComment
// --------------
/*
 *
 */
bool SetGetHandler::showBigComment(const string& comment, const string& indent) const
{
  // indent too large
  if (indent.size() > 76) return false;

  // maximum width of 80 characters
  unsigned max = 77 - indent.size();

  // comment is too long to be shown
  if (comment.size() > max) return false;

  string dashes(max, '-');

  // upper frame
  cout << indent << "// " << dashes << endl;

  // show comment two times
  if (comment.size() < (max / 2))
  {
    string space(max - 2 * comment.size(), ' ');

    cout << indent << "// " << comment << space << comment << endl;
  }

  // show comment once
  else
  {
    string space(max - comment.size(), ' ');

    cout << indent << "// " << space << comment << endl;
  }

  // lower frame
  cout << indent << "// " << dashes << endl;

  return true;
}

// ----------
// showSetter
// ----------
/*
 *
 */
void SetGetHandler::showSetter(const Attribute& a, const string& indent) const
{
  // function and parameter names
  string fname = getFunctionName("set", a.name);
  string pname = getParameterName(a.name);

  // a sequence of dashes
  string dashes(fname.size(), '-');

  cout << indent << "// " << dashes << endl;
  cout << indent << "// " << fname  << endl;
  cout << indent << "// " << dashes << endl;
  cout << indent << "/**" << endl;
  cout << indent << " * @brief  This method sets " << a.name << "." << endl;
  cout << indent << " */" << endl;
  cout << indent << "public void " << fname << "(" << a.type << " " << pname << ")" << endl;
  cout << indent << "{" << endl;

  if (a.name == pname)
  {
    cout << indent << "  this." << a.name << " = " << pname << ";" << endl;
  }

  else
  {
    cout << indent << "  " << a.name << " = " << pname << ";" << endl;
  }

  cout << indent << "}" << endl;
}

// ----------
// showGetter
// ----------
/*
 *
 */
void SetGetHandler::showGetter(const Attribute& a, const string& indent) const
{
  // function name
  string fname = getFunctionName("get", a.name);

  // a sequence of dashes
  string dashes(fname.size(), '-');

  cout << indent << "// " << dashes << endl;
  cout << indent << "// " << fname  << endl;
  cout << indent << "// " << dashes << endl;
  cout << indent << "/**" << endl;
  cout << indent << " * @brief  This method returns " << a.name << "." << endl;
  cout << indent << " */" << endl;
  cout << indent << "public " << a.type << " " << fname << "()" << endl;
  cout << indent << "{" << endl;
  cout << indent << "  return " << a.name << ";" << endl;
  cout << indent << "}" << endl;
}

