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

    std::vector<Chord> chords;
    std::vector<int> sigma;
    int n;

  private:
    double FASE(int i, double dacum);
    int parseFile(std::string chordsFilename);
    void printChord(Chord chord);
    void calculateCentroid(ChordShape shape);

  public:
    double calculateMinimumHandMovement(std::string songFilename, std::string chordsFilename);
};

#endif // MINIMUMHANDMOVEMENT_H
