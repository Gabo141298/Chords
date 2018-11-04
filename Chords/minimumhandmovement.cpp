#include <cmath>
#include <limits>

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

double MinimumHandMovement::FASE(int i, double dacum)
{
     if (i >= n)
        return dacum;

    double dmin = std::numeric_limits<double>::max();
    std::vector<int> sigmaMin;

    for (int j = 0; j < 3; ++j)
    {
        sigma[i] = j;
        double d = FASE(i+1, dacum + abs(chords[i - 1].chordShapes[sigma[i - 1]].centroid - chords[i].chordShapes[j].centroid));

        if (d < dmin)
        {
            dmin = d;
            sigmaMin = sigma;
        }
    }

    sigma = sigmaMin;
    return dmin;
}

double MinimumHandMovement::calculateMinimumHandMovement(std::string songFilename, std::string chordsfilename)
{
    parseFile(songFilename, chordsfilename);
    return 0.0;
}
