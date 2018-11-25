#ifndef MINIMUMHANDMOVEMENT_H
#define MINIMUMHANDMOVEMENT_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define EXHAUSTIVE_SEARCH 0
#define DYNAMIC_PROGRAMMING 1

class MinimumHandMovement
{
  private:
    struct ChordShape
    {
        double centroid = 0.0;
        int fingers[6];
        int offset = 1;
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

  private:
    /**
     * @brief Recursive method that works as the exhaustive search algorithm
     * @param i The index of the current chord
     * @param dacum The accumulated amount of hand movement bewteen chords
     * @details
     */
    double fase(size_t i, double dacum);

    /**
     * @brief Algorithm to solve the hand movement problem using Dynamic Programming
     * @details
     */
    double dynamicMinimumHandMovement();

    /**
     * @brief Parses a .csv file to get the shapes of all the chords.
     * @param chordsFilename The name of the csv file to parse.
     */
    int parseChordsFile(std::string chordsFilename);

    /**
     * @brief Parses a .txt containing all the chords of a song
     * @param chordsFilename The name of the file with the chords of the song
     */
    int parseSongFile(std::string songFilename);

    /**
     * @brief Auxiliary method to print a chord
     * @param chords The chord to print
     * @details Prints the name of the chord, the shapes and centroids
     */
    void printChord(const Chord& chord);

    /**
     * @brief Calculates the centroid of a chordShape
     * @param shape The shape whose centroid needs to be calculated
     */
    void calculateCentroid(ChordShape& shape);

  public:

    /**
     * @brief calculateMinimumHandMovement
     * @param chordsFilename
     * @param songFilename
     * @return the minimum amount of hand movement needed to play the songs
     */
    double calculateMinimumHandMovement(std::string chordsFilename, std::string songFilename);
};

#endif // MINIMUMHANDMOVEMENT_H
