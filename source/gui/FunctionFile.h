
#pragma once

#include <fstream>
#include <map>
#include <string>

typedef std::map<CString, CString> CString2CStringMap;

class FunctionFile
{
  class ParserException
  {
  };

  static int FindAndCheck(const CString& data, char find, int illegalPosition = -1)
  {
    int position =
      data.Find(find);

    if (position == illegalPosition)
      throw FunctionFile::ParserException();

    return position;
  }

  static void ExtractFromLine(const CString& line, 
    CString2CStringMap& definitions)
  {
    CString data(line);
    data.TrimLeft();
    data.TrimRight();
    
    try
    {
      FunctionFile::FindAndCheck(data, '/', 0);

      int parameterStartPos = FunctionFile::FindAndCheck(data, '(');
      int parameterEndPos = FunctionFile::FindAndCheck(data, ')');

      CString functionName =
        data.Left(parameterStartPos);

      CString parameters =
        data.Mid(parameterStartPos + 1, (parameterEndPos - parameterStartPos - 1));

      if (!functionName.IsEmpty() && !parameters.IsEmpty())
        definitions.insert(CString2CStringMap::value_type(functionName, parameters));       
    }
    catch(const FunctionFile::ParserException&)
    {
      // we should ignore this line (comment or incomplete)
    }

  }

public:

  static void ReadFunctions(LPCTSTR pszFilename, CString2CStringMap& definitions)
  {
    ATLASSERT(definitions.size() == 0); // don't read into non-empty buffer

    std::string line;
    std::ifstream definitionsFile(pszFilename);

    if (definitionsFile.is_open())
    {
      while (!definitionsFile.eof())
      {
        std::getline(definitionsFile, line);

        FunctionFile::ExtractFromLine(CString(line.c_str()), definitions);
      }

      definitionsFile.close();
    }
   
  }

};