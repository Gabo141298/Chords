#ifndef MINIMUMHANDMOVEMENT_H
#define MINIMUMHANDMOVEMENT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class MinimumHandMovement
{
  private:
    double FASE(int i, float dacum, float sigmaMin);
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
            float centroid;
        };

      public:
        std::string name;
        std::vector<ChordShape> chordShapes;
    };

    std::vector<Chord> chords;
};

#endif // MINIMUMHANDMOVEMENT_H
