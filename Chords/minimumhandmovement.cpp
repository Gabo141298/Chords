#include <cmath>
#include <cfloat>
#include <climits>
#include <sstream>


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
    else
        shape.centroid = DBL_MAX;
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

        // To parse the file
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
            shape.offset = (token.length()) ? std::stoi(token) : 0;

            // Get each of the fingers in the chord
            for (int finger = 0; finger < 6; ++finger)
            {
                // Get the fret pressed in the string
                getline(ss,token,',');

                // If the string is played, insert in which fret. Else, insert -1
                shape.fingers[finger] = (token.length()) ? std::stoi(token) : -1;
            }

            // Calls the method to calculate the centroid of each chordshape
            calculateCentroid(shape);

            // Add the shape to the shapes vector
            chord.chordShapes.push_back(shape);
        }

        // Add the chord to the chords vector
        this->allChords.push_back(chord);
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

    // Store just the name of each chord played in the song
    std::vector<std::string> chordNames;

    while (buf)
    {
        std::string line;
        std::getline(buf, line);
        if (line.length())
            chordNames.push_back(line);
    }

    for(unsigned long chordName = 0; chordName < chordNames.size(); ++chordName)
    {
        for (unsigned long chord = 0; chord < this->allChords.size(); ++chord)
        {
            if (chordNames[chordName] == this->allChords[chord].name)
            {
                this->songChords.push_back(this->allChords[chord]);
                chord = this->allChords.size();
            }
        }
    }

    std::cout << this->songChords.size() << std::endl;

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
        double d = FASE(i+1, dacum + abs(songChords[i - 1].chordShapes[sigma[i - 1]].centroid - songChords[i].chordShapes[j].centroid));

        if (d < dmin)
        {
            dmin = d;
            sigmaMin = sigma;
        }
    }

    sigma = sigmaMin;
    return dmin;
}

double MinimumHandMovement::calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename)
{
    parseChordsFile(chordsFilename);
    parseSongFile(songFilename);

    //printChord(this->chords[0]);

    return 0.0;
}
