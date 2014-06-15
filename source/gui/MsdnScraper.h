#pragma once
#define _IMAGEHLP_
#include <atlhttp.h>

class MsdnScraper
{
  static bool GetPage(const CString& url, CString& body, bool extraHeaders = true)
  {
    CAtlHttpClient client;
    CAtlNavigateData navData;

    char szExtraHeaders [] =
      "Accept: text/html, */*\n"
      "User-Agent: Mozilla/4.0\n";

    if (extraHeaders)
      navData.SetExtraHeaders(szExtraHeaders);

    if (client.Navigate((LPCTSTR)url, &navData))
    {
      body = (char*)client.GetBody();
      
      return true;
    }

    return false;
  }

public:


  static bool FindParameters(const CString& function, 
    const CString& msndUrl, CString& parameters)
  {
    CString body;
    parameters.Empty();

    if (MsdnScraper::GetPage(msndUrl, body, false))
    {
      try
      {
        CString chunk = StringParser::TrimString(body, "<code>", "</code>");

        while (true)
        {
          CString nextParam = StringParser::Next(chunk, "<em>");
          nextParam.TrimRight();
          nextParam.Replace(" *", "*");

          int spacePosition = nextParam.ReverseFind(' ');

          if (spacePosition > 0)
            nextParam = nextParam.Mid(spacePosition + 1);

          // we have the parameter
          if (parameters.GetLength() > 0)
            parameters += ", ";

          parameters += nextParam;
        }
      }
      catch(const StringParserException&)
      {
        // this is expected when there are nothing more to parse
        if (parameters.GetLength() > 0)
          return true;
      }

    }

    return false;
  }

  static bool FindMsdnURL(const CString& function, CString& msdnUrl)
  {
    CString googleUrl;
    googleUrl.Format("http://www.google.com/search?q=%s+site:msdn.microsoft.com", (LPCTSTR)function);

    CString body;
    if (MsdnScraper::GetPage(googleUrl, body))
    {
      CString findPattern;

      findPattern.Format(">%s<", function);
      int offset = body.Find(findPattern);

      if (offset > 0)
      {
        CString tmp(body.Left(offset));

        int urlEnd = tmp.ReverseFind('\"');

        if (urlEnd > 0)
        {
          tmp.Truncate(urlEnd);

          int urlStart = tmp.ReverseFind('\"');

          if (urlStart > 0)
          {
            msdnUrl = tmp.Mid(urlStart + 1);

            if (msdnUrl.Right(5) == ".aspx" && (-1 != msdnUrl.Find("msdn.microsoft.com")))
              return true;
          }
        }
      }
    }

    return false;
  }
};
