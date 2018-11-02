#include <fstream>
#include <iostream>

#include "csvparser.h"

CsvParser::CsvParser()
{

}

int CsvParser::parseFile(std::string file_name)
{
    // Creation of fstream class object
    std::fstream buf;

    std::string line;

    buf.open(file_name, std::ios::trunc | std::ios::out | std::ios::in);

    if (!buf)
    {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    while (buf)
    {
        // Read a Line from standard input
        std::getline(std::cin, line);

        // Press -1 to exit
        if (line == "-1")
            break;

        // Write line in file
        std::cout << line << std::endl;
    }

    buf.seekg(0, std::ios::beg);

    while (buf)
    {
        std::getline(buf, line);

        // Print line in Console
        std::cout << line << std::endl;
    }

    // Close the file
    buf.close();

    return 0;
}
