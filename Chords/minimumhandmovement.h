#ifndef MINIMUMHANDMOVEMENT_H
#define MINIMUMHANDMOVEMENT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class MinimumHandMovement
{
  private:
    double FASE(int i, double dacum);
    int parseFile(std::string chordsFilename, std::string songFilename);

  public:
    double calculateMinimumHandMovement(std::string songFilename, std::string chordsFilename);

  private:
    class Chord
    {
      public:
        struct ChordShape
        {
            int offset;
            double centroid;
        };

      public:
        std::string name;
        std::vector<ChordShape> chordShapes;
    };

    std::vector<Chord> chords;
    std::vector<int> sigma;
    int n;
};

#endif // MINIMUMHANDMOVEMENT_H
