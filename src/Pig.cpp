////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2015, Paul Beckingham, Federico Hernandez.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <cmake.h>
#include <Pig.h>
#include <Lexer.h>
#include <utf8.h>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
Pig::Pig (const std::string& text)
: _text (text)
, _mark (0)
, _cursor (0)
, _debug (false)
{
}

////////////////////////////////////////////////////////////////////////////////
bool Pig::skipWS ()
{
  int c;
  auto prev = _cursor;
  while ((c = utf8_next_char (_text, _cursor)))
  {
    if (! Lexer::isWhitespace (c))
    {
      _cursor = prev;
      break;
    }
    prev = _cursor;
  }

  if (_cursor > _mark)
  {
    _mark = _cursor;
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////
void Pig::debug (bool value)
{
  _debug = value;
}

////////////////////////////////////////////////////////////////////////////////
std::string Pig::dump () const
{
  std::stringstream out;
  out << "≪" << _text << "≫"
      << " l" << _text.length ()
      << " m" << _mark
      << " c" << _cursor;

  return out.str ();
}

////////////////////////////////////////////////////////////////////////////////
