
#pragma once

class StringParserException
{
};

class StringParser
{
public:

  static CString Next(CString& string, const CString& token)
  {
    int tokenPosition = string.Find(token);

    if (tokenPosition < 0)
      throw StringParserException();

    int endPosition = tokenPosition + token.GetLength();

    CString next = string.Left(tokenPosition);

    string = string.Mid(endPosition);

    return next;
  }
  static CString TrimString(const CString& string, const CString& startTag, const CString& endTag)
  {
    CString item;

    int startPosition = string.Find(startTag);

    if (startPosition < 0)
      throw StringParserException();

    int endPosition = string.Find(endTag, startPosition + 1);

    if (endPosition < startPosition)
      throw StringParserException();

    item = string.Mid(
      startPosition + startTag.GetLength(),
      endPosition - (startPosition + startTag.GetLength()));

    return item;
  }

};