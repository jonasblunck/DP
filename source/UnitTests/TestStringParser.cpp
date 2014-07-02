#include "stdafx.h"
#include "StringParser.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestStringParser)
{
  TEST_METHOD(StringParser_Trim_Tag)
  {
    Assert::AreEqual("include this", StringParser::TrimString("about <p>include this</p> but", "<p>", "</p>"));    
  }

  TEST_METHOD(StringParser_Trim_NoTag)
  {
	  Assert::AreEqual("find_this", StringParser::TrimString("nottag2find_thistag3", "tag2", "tag3"));
  }

  TEST_METHOD(StringParser_NextItem_Before_Stop1)
  {
    CString item = "text <stop> text2 <stop> text3 <stop>";

    Assert::AreEqual("text ", StringParser::Next(item, "<stop>"));
  }

  TEST_METHOD(StringParser_NextItem_After_Stop1)
  {
	  CString item = "text <stop> text2 <stop> text3 <stop>";

	  StringParser::Next(item, "<stop>");
	  Assert::AreEqual(" text2 <stop> text3 <stop>", item);	 
  }

  TEST_METHOD(StringParser_NextItem_After_Stop2)
  {
	  CString item = "text <stop> text2 <stop> text3 <stop>";

	  StringParser::Next(item, "<stop>");

	  Assert::AreEqual(" text2 ", StringParser::Next(item, "<stop>"));
  }

  TEST_METHOD(StringParser_NextItem_After_Stop3)
  {
	  CString item = "text <stop> text2 <stop> text3 <stop>";

	  StringParser::Next(item, "<stop>");
	  StringParser::Next(item, "<stop>");
	  
	  Assert::AreEqual(" text3 ", StringParser::Next(item, "<stop>"));	  
  }


  TEST_METHOD(StringParser_TrimThrowsOnNotFound)
  {
    try
    {
      CString item("tag2andtag1notcorrect");

      StringParser::TrimString(item, "tag1", "tag2");

      Assert::IsTrue(FALSE);
    }
    catch(const StringParserException&)
    {
      Assert::IsTrue(TRUE);
    }
  }
};
