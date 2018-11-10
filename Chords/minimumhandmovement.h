#ifndef MINIMUMHANDMOVEMENT_H
#define MINIMUMHANDMOVEMENT_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class MinimumHandMovement
{
  private:
    struct ChordShape
    {
        double centroid = 0.0;
        int fingers[6];
        int offset;
    };

    class Chord
    {
      public:
        std::string name;
        std::vector<ChordShape> chordShapes;
    };

    std::map<std::string, Chord> allChords;
    std::vector<Chord> songChords;
    std::vector<int> sigma;
    size_t n;

  private:
    double fase(size_t i, double dacum);
    int parseChordsFile(std::string chordsFilename);
    int parseSongFile(std::string songFilename);
    void printChord(const Chord& chord);
    void calculateCentroid(ChordShape& shape);

  public:
    double calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename);
};

#endif // MINIMUMHANDMOVEMENT_H
