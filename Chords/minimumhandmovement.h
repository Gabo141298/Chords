#ifndef MINIMUMHANDMOVEMENT_H
#define MINIMUMHANDMOVEMENT_H

#include <fstream>
#include <iostream>
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

    std::vector<Chord> allChords;
    std::vector<Chord> songChords;
    std::vector<int> sigma;
    int n;

  private:
    double FASE(int i, double dacum);
    int parseChordsFile(std::string chordsFilename);
    int parseSongFile(std::string songFilename);
    void printChord(Chord chord);
    void calculateCentroid(ChordShape shape);

  public:
    double calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename);
};

#endif // MINIMUMHANDMOVEMENT_H
