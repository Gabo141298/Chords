#include <cctype>
#include <cmath>
#include <cfloat>
#include <limits>
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
            acum += shape.fingers[finger] + (shape.fingers[finger] > 0 ? shape.offset : 0);
            ++count;
        }
    }

    // The centroid is the average of the frets in the string played
    if (count)
        shape.centroid = (double)acum / count;
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

        // To parse the file
        std::istringstream ss(line);
        std::string token;

        Chord chord;

        // Get the name of the chord
        getline(ss,token,',');
#if TESTING_CSV_PARSER
        std::cout << token << std::endl;
#endif
        chord.name = token;

        // Get the data of the three shapes of the chord
        for (int curr_shape = 0; curr_shape < 3; ++curr_shape)
        {
            ChordShape shape;

            // Get the offset
            getline(ss,token,',');
#if TESTING_CSV_PARSER
            std::cout << token;
#endif
            // If there's offset insert it. Else, insert 0
            shape.offset = (token.length()) ? std::stoi(token) : 0;

            // Get each of the fingers in the chord
            for (int finger = 0; finger < 6; ++finger)
            {
                // Get the fret pressed in the string
                getline(ss,token,',');
#if TESTING_CSV_PARSER
                std::cout << ' ' << token;
#endif
                // If the string is played, insert in which fret. Else, insert -1
                shape.fingers[finger] = (token.length()) && !isspace(token[0]) ? std::stoi(token) : -1;
            }

            // Calls the method to calculate the centroid of each chordshape
            calculateCentroid(shape);

            // Add the shape to the shapes vector
            if(shape.centroid != DBL_MAX)
                chord.chordShapes.push_back(shape);
#if TESTING_CSV_PARSER
            std::cout << std::endl;
#endif
        }

        // Add the chord to the chords vector
        this->allChords.insert(std::pair<std::string, Chord>(chord.name,chord));
#if TESTING_CSV_PARSER
        std::cout << std::endl;
#endif
    }

    // Close the file
    buf.close();
#if TESTING_CSV_PARSER
    std::cout << "Terminé de leer el csv\n";
#endif

    return 0;
}

int MinimumHandMovement::parseSongFile(std::string songFilename)
{
    std::ifstream buf (songFilename);

    if (!buf)
        return std::cerr << "Could not open file" << std::endl, 1;

    while (buf)
    {
        std::string line;
        std::getline(buf, line);
        if (line.length())
        {
            std::map<std::string, Chord>::iterator itr = allChords.find(line);
            if(itr != allChords.end())
                songChords.push_back(itr->second);
        }
    }

#if TESTING_SONG
    std::cout << this->songChords.size() << std::endl;
#endif
    sigma.resize(songChords.size());

    // Close the file
    buf.close();

    return 0;
}

double MinimumHandMovement::fase(size_t i, double dacum)
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
            d = fase(i+1, dacum + fabs((double)(songChords[i - 1].chordShapes[sigma[i - 1]].centroid - songChords[i].chordShapes[j].centroid)));
        else
            d = fase(i+1, 0.0);

        if (d < dmin)
        {
            dmin = d;
            sigmaMin = sigma;
        }
#if TESTING_FASE
        std::cout << i << ": " << d << std::endl;
#endif
    }

    sigma = sigmaMin;
    return dmin;
}

double MinimumHandMovement::calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename)
{
    parseChordsFile(chordsFilename);
    parseSongFile(songFilename);
#if TESTING_CHORDS
    for(size_t index = 0; index < songChords.size(); ++index)
        printChord(songChords[index]);
#endif

    std::cout << fase(0, 0.0) << ": ";

    for(size_t index = 0; index < sigma.size(); ++index)
        std::cout << ' ' << sigma[index] + 1;
    std::cout << std::endl;

    return 0.0;
}
