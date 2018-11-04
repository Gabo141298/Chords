#include "minimumhandmovement.h"

int MinimumHandMovement::parseFile(std::string chordsFilename, std::string songFilename)
{
    // Creation of fstream class object
    std::fstream buf;

    std::string line;

    buf.open(chordsFilename, std::ios::trunc | std::ios::out | std::ios::in);

    if (!buf)
    {
        std::cerr << "Could not open file" << std::endl;
        return 1;
    }

    buf.seekg(0, std::ios::beg);

    while (buf)
    {
        Chord chord;

        std::getline(buf, line);

        //----parsear linea---//

        this->chords.push_back(chord);
    }

    // Close the file
    buf.close();

    return 0;
}

double MinimumHandMovement::FASE(int i, float dacum, float sigmaMin)
{
    /* if (i >= n)
        return dacum;
    cosa = ;
    double dmin = DOUBLE.MAX;

    for (int j = 0; j < 2; ++j)
    {
        sigme[i] = j;
        float = FASE(i+1, dacum + chords[i-1][sigma[i-1]] - chords[i][j], sigmaMin);

        if (d < min)
        {
            dmin = d;
            cosa = j;
        }
    }

    sigma[i] = cosa;
    return dmin;

    */

    return 0;
}

double MinimumHandMovement::calculateMinimumHandMovement(std::string songFilename, std::string chordsfilename)
{
    parseFile(songFilename, chordsfilename);
    return 0.0;
}
