///\file

/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2020 John Wellbelove, John Lagerquist

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef ETL_STRING_UTILITIES_INCLUDED
#define ETL_STRING_UTILITIES_INCLUDED

#include "platform.h"
#include "cstring.h"
#include "string_view.h"
#include "algorithm.h"
#include "private/string_utilities_helper.h"

#include <ctype.h>

namespace etl
{
  //***************************************************************************
  /// trim_whitespace_left
  /// Trim left of whitespace
  //***************************************************************************
  inline void trim_whitespace_left(etl::istring& s)
  {
    etl::private_string_utilities::trim_from_left<etl::istring>(s, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_whitespace_left
  /// View trim left of whitespace
  //***************************************************************************
  inline etl::string_view trim_whitespace_left(const etl::string_view& view)
  {
    return etl::private_string_utilities::view_trim_from_left<etl::string_view>(view, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_from_left
  /// Trim left of specified characters
  //***************************************************************************
  inline void trim_from_left(etl::istring& s, etl::istring::const_pointer trim_characters)
  {
    etl::private_string_utilities::trim_from_left<etl::istring>(s, trim_characters);
  }

  //***************************************************************************
  /// trim_from_left
  /// View trim left of specified characters
  //***************************************************************************
  inline etl::string_view trim_from_left(const etl::string_view& view, etl::istring::const_pointer trim_characters)
  {
    return etl::private_string_utilities::view_trim_from_left<etl::string_view>(view, trim_characters);
  }

  //***************************************************************************
  /// trim_left
  /// Trim left, up to, but not including, delimiters.
  //***************************************************************************
  inline void trim_left(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    etl::private_string_utilities::trim_left_delimiters<etl::istring>(s, delimiters);
  }

  //***************************************************************************
  /// trim_left
  /// Trim left, up to, but not including, delimiters.
  //***************************************************************************
  inline etl::string_view trim_left(etl::string_view& s, etl::string_view::const_pointer delimiters)
  {
    return etl::private_string_utilities::view_trim_left_delimiters<etl::string_view>(s, delimiters);
  }

  //***************************************************************************
  /// trim_whitespace_right
  /// Trim right of whitespace
  //***************************************************************************
  inline void trim_whitespace_right(etl::istring& s)
  {
    etl::private_string_utilities::trim_from_right<etl::istring>(s, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_whitespace_right
  /// Trim right of whitespace
  //***************************************************************************
  inline etl::string_view trim_whitespace_right(const etl::string_view& view)
  {
    return etl::private_string_utilities::view_trim_from_right<etl::string_view>(view, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_from_right
  /// Trim right of specified characters
  //***************************************************************************
  inline void trim_from_right(etl::istring& s, etl::istring::const_pointer trim_characters)
  {
    etl::private_string_utilities::trim_from_right<etl::istring>(s, trim_characters);
  }

  //***************************************************************************
  /// trim_from_right
  /// Trim right of specified characters
  //***************************************************************************
  inline etl::string_view trim_from_right(const etl::string_view& view, etl::istring::const_pointer trim_characters)
  {
    return etl::private_string_utilities::view_trim_from_right<etl::string_view>(view, trim_characters);
  }

  //***************************************************************************
  /// trim_right
  //***************************************************************************
  inline void trim_right(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    etl::private_string_utilities::trim_right_delimiters<etl::istring>(s, delimiters);
  }

  //***************************************************************************
  /// trim_right
  //***************************************************************************
  inline etl::string_view trim_right(const etl::string_view& view, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::view_trim_right_delimiters<etl::string_view>(view, delimiters);
  }

  //***************************************************************************
  /// trim_whitespace
  /// Trim both ends of whitespace
  //***************************************************************************
  inline void trim_whitespace(etl::istring& s)
  {
    etl::private_string_utilities::trim_from<etl::istring>(s, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_whitespace
  /// Trim both ends of whitespace
  //***************************************************************************
  inline etl::string_view trim_whitespace(const etl::string_view& view)
  {
    return etl::private_string_utilities::view_trim_from<etl::string_view>(view, " \t\n\r\f\v");
  }

  //***************************************************************************
  /// trim_from
  /// Trim right of specified characters
  //***************************************************************************
  inline void trim_from(etl::istring& s, etl::istring::const_pointer trim_characters)
  {
    etl::private_string_utilities::trim_from<etl::istring>(s, trim_characters);
  }

  //***************************************************************************
  /// trim_from
  /// Trim right of specified characters
  //***************************************************************************
  inline etl::string_view trim_from(const etl::string_view& view, etl::istring::const_pointer trim_characters)
  {
    return etl::private_string_utilities::view_trim_from<etl::string_view>(view, trim_characters);
  }

  //***************************************************************************
  /// trim
  //***************************************************************************
  inline void trim(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    etl::private_string_utilities::trim_delimiters<etl::istring>(s, delimiters);
  }

  //***************************************************************************
  /// trim
  //***************************************************************************
  inline etl::string_view trim(const etl::string_view& view, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::view_trim_delimiters<etl::string_view>(view, delimiters);
  }

  //***************************************************************************
  /// reverse
  /// Reverse the string
  //***************************************************************************
  inline void reverse(etl::istring& s)
  {
    etl::private_string_utilities::reverse<etl::istring>(s);
  }

  //***************************************************************************
  /// Get up to the first n characters.
  //***************************************************************************
  inline void left_n(etl::istring& s, size_t n)
  {
    n = (n > s.size()) ? s.size() : n;

    s.erase(s.begin() + n, s.end());
  }

  //***************************************************************************
  /// Get a view of up to the first n characters.
  //***************************************************************************
  inline etl::string_view left_n(etl::string_view view, size_t n)
  {
    n = (n > view.size()) ? view.size() : n;

    return etl::string_view(view.begin(), view.begin() + n);
  }

  //***************************************************************************
  /// Get up to the last n characters.
  //***************************************************************************
  inline void right_n(etl::istring& s, size_t n)
  {
    n = (n > s.size()) ? s.size() : n;

    s.erase(s.begin(), s.end() - n);
  }

  //***************************************************************************
  /// Get a view of up to the last n characters.
  //***************************************************************************
  inline etl::string_view right_n(etl::string_view view, size_t n)
  {
    n = (n > view.size()) ? view.size() : n;

    return etl::string_view(view.end() - n, view.end());
  }

  //***************************************************************************
  /// pad_left
  //***************************************************************************
  inline void pad_left(etl::istring& s, size_t required_size, etl::istring::value_type pad_char)
  {
    etl::private_string_utilities::pad_left(s, required_size, pad_char);
  }

  //***************************************************************************
  /// pad_right
  //***************************************************************************
  inline void pad_right(etl::istring& s, size_t required_size, etl::istring::value_type pad_char)
  {
    etl::private_string_utilities::pad_right(s, required_size, pad_char);
  }

  //***************************************************************************
  /// pad
  //***************************************************************************
  void pad(etl::istring& s, size_t required_size, string_pad_direction pad_direction, etl::istring::value_type pad_char)
  {
    etl::private_string_utilities::pad(s, required_size, pad_direction, pad_char);
  }

  //***************************************************************************
  /// to_upper_case
  //***************************************************************************
  inline void to_upper_case(etl::istring& s)
  {
    etl::istring::iterator itr = s.begin();

    while (itr != s.end())
    {
      *itr = etl::istring::value_type(::toupper(*itr));
      ++itr;
    }
  }

  //***************************************************************************
  /// to_lower_case
  //***************************************************************************
  inline void to_lower_case(etl::istring& s)
  {
    etl::istring::iterator itr = s.begin();

    while (itr != s.end())
    {
      *itr = etl::istring::value_type(::tolower(*itr));
      ++itr;
    }
  }

  //***************************************************************************
  /// to_sentence_case
  //***************************************************************************
  inline void to_sentence_case(etl::istring& s)
  {
    etl::istring::iterator itr = s.begin();

    *itr = etl::istring::value_type(::toupper(*itr));
    ++itr;

    while (itr != s.end())
    {
      *itr = etl::istring::value_type(::tolower(*itr));
    }
  }

  //***************************************************************************
  /// transform
  //***************************************************************************
  inline void transform(etl::istring& s,
                        const etl::pair<etl::istring::value_type, etl::istring::value_type>* pairsbegin, 
                        const etl::pair<etl::istring::value_type, etl::istring::value_type>* pairsend)
  {
    etl::private_string_utilities::transform_characters<etl::istring>(s, pairsbegin, pairsend);
  }

  //***************************************************************************
  /// transform
  //***************************************************************************
  inline void transform(etl::istring& s,
                        const etl::pair<const etl::istring::value_type*, const etl::istring::value_type*>* pairsbegin,
                        const etl::pair<const etl::istring::value_type*, const etl::istring::value_type*>* pairsend)
  {
    etl::private_string_utilities::transform_strings<etl::istring>(s, pairsbegin, pairsend);
  }

  //***************************************************************************
  /// get_token
  //***************************************************************************
  inline etl::string_view get_token(const etl::istring& s, etl::istring::const_pointer delimiters, const string_view& last_view)
  {
    return etl::private_string_utilities::get_token(s, delimiters, last_view);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_first_of(etl::istring::iterator first, etl::istring::iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_of(etl::istring::const_iterator first, etl::istring::const_iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_first_of(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_of(const etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_of(s.cbegin(), s.cend(), delimiters);
  }

  //*********************************************************************
  /// Find first of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_of(const etl::string_view& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_of(s.cbegin(), s.cend(), delimiters);
  }

  //*********************************************************************
  /// Find first not of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_first_not_of(etl::istring::iterator first, etl::istring::iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_not_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find first not of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_not_of(etl::istring::const_iterator first, etl::istring::const_iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_not_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find first not of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_first_not_of(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_not_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find first not of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_not_of(const etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_not_of(s.cbegin(), s.cend(), delimiters);
  }

  //*********************************************************************
  /// Find first not of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_first_not_of(const etl::string_view& view, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_first_not_of(view.cbegin(), view.cend(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_last_of(etl::istring::iterator first, etl::istring::iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_of(etl::istring::const_iterator first, etl::istring::const_iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_last_of(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_of(const etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_of(s.cbegin(), s.cend(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_of(const etl::string_view& view, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_of(view.cbegin(), view.cend(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_last_not_of(etl::istring::iterator first, etl::istring::iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_not_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_not_of(etl::istring::const_iterator first, etl::istring::const_iterator last, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_not_of(first, last, delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::iterator find_last_not_of(etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_not_of(s.begin(), s.end(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_not_of(const etl::istring& s, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_not_of(s.cbegin(), s.cend(), delimiters);
  }

  //*********************************************************************
  /// Find last of any of delimiters within the string
  //*********************************************************************
  inline etl::istring::const_iterator find_last_not_of(const etl::string_view& view, etl::istring::const_pointer delimiters)
  {
    return etl::private_string_utilities::find_last_not_of(view.cbegin(), view.cend(), delimiters);
  }
}

#endif