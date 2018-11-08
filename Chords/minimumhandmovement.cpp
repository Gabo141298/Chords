#include <cmath>
#include <limits>

#include "minimumhandmovement.h"

void MinimumHandMovement::calculateCentroid(ChordShape shape)
{
    int count = 0, acum = 0;

    // Go string by string
    for (int finger = 0; finger < 6; ++finger)
    {
        // If the string is player
        if (shape.fingers[finger] >= 0)
        {
            acum += shape.fingers[finger];
            ++count;
        }
    }

    // The centroid is the average of the frets in the string played
    if (count)
        shape.centroid = acum / count;
}

void MinimumHandMovement::printChord(Chord chord)
{
    std::cout << chord.name << std::endl;

    for (int shape = 0; shape < 3; ++shape)
    {
        std::cout << "shape" << shape << ": ";
        for (int finger = 0; finger < 6; ++finger)
            std::cout << chord.chordShapes[shape].fingers[finger] << ", ";

        std::cout << "centroide: " << chord.chordShapes[shape].centroid << std::endl;
    }
}

int MinimumHandMovement::parseFile(std::string chordsFilename)
{
    std::ifstream buf ("/Users/luisalvarezc/Desktop/positions.csv");

    if (!buf)
        return std::cerr << "Could not open file" << std::endl, 1;

    while (buf)
    {
        // Get the data of one chord
        std::string line;
        std::getline(buf, line);

        Chord chord;

        // Variables to parse the line
        size_t pos = line.find(",");
        std::string token;

        // Get the name of the chord
        token = line.substr(0, pos);
        chord.name = token;
        line.erase(0, pos + 1); pos = line.find(",");

        // Get the data of the three shapes of the chord
        for (int curr_shape = 0; curr_shape < 3; ++curr_shape)
        {
            ChordShape shape;

            // Get the offset
            token = line.substr(0, pos);

            // If there's offset insert it. Else, insert 0
            shape.offset = (token.length()) ? std::stoi(token) : 0;
            line.erase(0, pos + 1); pos = line.find(",");

            // Get each of the fingers in the chord
            for (int finger = 0; finger < 6; ++finger)
            {
                token = line.substr(0, pos);

                // If the string is played, insert in which fret. Else, insert -1
                shape.fingers[finger] = (token.length()) ? std::stoi(token) : -1;
                line.erase(0, pos + 1); pos = line.find(",");

                std::cout << line << std::endl;
            }

            // Add the shape to the shapes vector
            chord.chordShapes.push_back(shape);
        }

        // Add the chord to the chords vector
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

double MinimumHandMovement::calculateMinimumHandMovement(std::string songFilename, std::string chordsFilename)
{
    parseFile(chordsFilename);

    printChord(this->chords[0]);

    return 0.0;
}
