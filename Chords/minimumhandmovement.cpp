#include <cctype>
#include <cmath>
#include <cfloat>
#include <limits>
#include <iomanip>
#include <sstream>


#include "minimumhandmovement.h"

void MinimumHandMovement::calculateCentroid(ChordShape& shape)
{
    size_t count = 0, acum = 0;

    // Go string by string
    for (int finger = 0; finger < 6; ++finger)
    {
        // If the string is played
        if (shape.fingers[finger] >= 0)
        {
            acum += shape.fingers[finger] + shape.offset - 1.0;
            ++count;
        }
    }

    // The centroid is the average of the frets in the string played
    if (count)
        shape.centroid = static_cast<double>(acum) / count;
    else
        shape.centroid = DBL_MAX;
}

void MinimumHandMovement::printChord(const Chord& chord)
{
    std::cout << chord.name << std::endl;

    for (size_t shape = 0; shape < chord.chordShapes.size(); ++shape)
    {
        std::cout << "shape" << shape << ": ";
        for (int finger = 0; finger < 6; ++finger)
            std::cout << chord.chordShapes[shape].fingers[finger] << ", ";

        std::cout << "centroide: " << chord.chordShapes[shape].centroid << std::endl;
    }
}

int MinimumHandMovement::parseChordsFile(std::string chordsFilename)
{
    std::ifstream buf (chordsFilename);

    if (!buf)
        return std::cerr << "Could not open file" << std::endl, 1;

    while (buf)
    {
        // Get the data of one chord
        std::string line;
        std::getline(buf, line);

        // Variables to read from the file
        std::istringstream ss(line);
        std::string token;

        Chord chord;

        // Get the name of the chord
        getline(ss,token,',');

        chord.name = token;

        // Get the data of the three shapes of the chord
        for (int curr_shape = 0; curr_shape < 3; ++curr_shape)
        {
            ChordShape shape;

            // Get the offset
            getline(ss,token,',');

            // If there's offset insert it. Else, insert 0
            shape.offset = (token.length()) ? std::stoi(token) : 1;

            // Get each of the fingers in the chord
            for (int finger = 0; finger < 6; ++finger)
            {
                // Get the fret pressed in the string
                getline(ss,token,',');

                // If the string is played, insert in which fret. Else, insert -1
                shape.fingers[finger] = (token.length()) && !isspace(token[0]) ? std::stoi(token) : -1;
            }

            // Calls the method to calculate the centroid of each chordshape
            calculateCentroid(shape);

            // Add the shape to the shapes vector
            if(shape.centroid != DBL_MAX)
                chord.chordShapes.push_back(shape);
        }

        // Add the chord to the chords vector
        this->allChords.insert(std::pair<std::string, Chord>(chord.name,chord));
    }

    // Close the file
    buf.close();

    return 0;
}


int MinimumHandMovement::parseSongFile(std::string songFilename)
{
    std::ifstream buf (songFilename);

    if (!buf)
        return std::cerr << "Could not open file" << std::endl, 1;

    while (!buf.eof())
    {
        std::string line;
        std::getline(buf, line);
        if (line.length() && !isspace(line[0]))
        {
            std::map<std::string, Chord>::iterator itr = allChords.find(line);
            if(itr != allChords.end())
                songChords.push_back(itr->second);
        }
    }

    sigma.resize(songChords.size());

    // Close the file
    buf.close();

    return 0;
}

double MinimumHandMovement::phase(size_t i, double dacum)
{
    if (i >= songChords.size())
        return dacum;

    double dmin = std::numeric_limits<double>::max();
    std::vector<int> sigmaMin;

    for (size_t j = 0; j < songChords[i].chordShapes.size(); ++j)
    {
        sigma[i] = j;
        double d = 0.0;
        if(i > 0)
            d = phase(i+1, dacum + fabs(static_cast<double>(songChords[i - 1].chordShapes[sigma[i - 1]].centroid - songChords[i].chordShapes[j].centroid)));
        else
            d = phase(i+1, 0.0);

        if (d < dmin)
        {
            dmin = d;
            sigmaMin = sigma;
        }
    }

    sigma = sigmaMin;
    return dmin;
}

double MinimumHandMovement::dynamicMinimumHandMovement()
{
    std::vector<std::vector<double>> f;
    std::vector<std::vector<int>> sigmaM;
    f.resize(sigma.size());
    sigmaM.resize(sigma.size());
    for(size_t index = 0; index < f.size(); ++index)
    {
        f[index].resize(songChords[index].chordShapes.size());
        sigmaM[index].resize(songChords[index].chordShapes.size());
    }

    for(size_t index = 0; index < sigmaM[sigmaM.size() - 1].size(); ++index)
        sigmaM[sigmaM.size() - 1][index] = 0;

    for(long row = f.size() - 2; row >= 0; --row)
    {
        for(size_t col = 0; col < f[row].size(); ++col)
        {
            f[row][col] = std::numeric_limits<double>::max();
            size_t prevRow = row + 1;
            for(size_t prevCol = 0; prevCol < f[prevRow].size(); ++prevCol)
            {
                double temp = f[prevRow][prevCol] +
                        fabs(songChords[row].chordShapes[col].centroid - songChords[prevRow].chordShapes[prevCol].centroid);
                if(temp < f[row][col])
                {
                    f[row][col] = temp;
                    sigmaM[row][col] = prevCol;
                }
            }
        }
    }
    double min = f[0][0];
    sigma[0] = 0;
    for(size_t index = 1; index < f[0].size(); ++index)
    {
        if(f[0][index] < min)
        {
            min = f[0][index];
            sigma[0] = index;
        }
    }

    for(size_t index = 1; index < sigma.size(); ++index)
    {
        sigma[index] = sigmaM[index - 1][sigma[index - 1]];
    }

    return min;
}

double MinimumHandMovement::calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename)
{
    parseChordsFile(chordsFilename);
    parseSongFile(songFilename);

    double minimumHandMovement = 0;

#if EXHAUSTIVE_SEARCH
    minimumHandMovement = fase(0, 0.0);
#endif

#if DYNAMIC_PROGRAMMING
    minimumHandMovement = dynamicMinimumHandMovement();
#endif

    for(size_t index = 0; index < sigma.size(); ++index)
        std::cout << this->songChords[index].name << ":\t" << this->sigma[index] + 1 << '\n' << std::endl;

    std::cout << "Total desplazamiento mínimo de la mano: " << minimumHandMovement << std::endl;
    std::cout << "Desplazamiento promedio por acorde: " << minimumHandMovement / this->songChords.size() << std::endl;

    return 0.0;
}
