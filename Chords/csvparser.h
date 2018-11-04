#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>

class CsvParser
{
  public:
    CsvParser();
    int parseFile(std::string songFilename, std::string chordsFilename);
};

#endif // CSVPARSER_H
