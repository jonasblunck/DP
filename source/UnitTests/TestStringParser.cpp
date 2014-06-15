
#include "stdafx.h"
#include "StringParser.h"

class TestStringParser
{
  void TestTrim()
  {
    DPUNIT_STR_EQUAL("include this", StringParser::TrimString("about <p>include this</p> but", "<p>", "</p>"));
    DPUNIT_STR_EQUAL("find_this", StringParser::TrimString("nottag2find_thistag3", "tag2", "tag3"));
  }

  void TestNextItem()
  {
    CString item = "text <stop> text2 <stop> text3 <stop>";

    DPUNIT_STR_EQUAL("text ", StringParser::Next(item, "<stop>"));
    DPUNIT_STR_EQUAL(" text2 <stop> text3 <stop>", item);
    DPUNIT_STR_EQUAL(" text2 ", StringParser::Next(item, "<stop>"));
    DPUNIT_STR_EQUAL(" text3 ", StringParser::Next(item, "<stop>"));
    DPUNIT_STR_EQUAL("", item);
  }

  void TestTrimThrowsOnNotFound()
  {
    try
    {
      CString item("tag2andtag1notcorrect");

      StringParser::TrimString(item, "tag1", "tag2");

      DPUNIT_ISTRUE(FALSE);
    }
    catch(const StringParserException&)
    {
      DPUNIT_ISTRUE(TRUE);
    }
  }

public:
  void Test()
  {
    TestTrim();
    TestTrimThrowsOnNotFound();
    TestNextItem();
  }
};

void testStringParser()
{
  TestStringParser tester;
  tester.Test();


}