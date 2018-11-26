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
     * @brief Recursive method that works as the exhaustive search algorithm.
     * @param i The index of the current chord
     * @param dacum The accumulated amount of hand movement bewteen chords
     * @details The algorithm seeks all possible solutions from i=0,1,...,n-1.
     * To do this, the function calls itself using each of the i-th chord shapes and adding to the accumulation the difference between the centroid of that chord shape and the previous chord given the shape selected in sigma[i-1].
     * It also uses a vector to save the state of sigma that got the minimum hand movement required between all the shapes of the i-th chord.
     */
    double phase(size_t i, double dacum);

    /**
     * @brief Algorithm to solve the hand movement problem using Dynamic Programming.
     * @details The algorithm fills a matrix F used to know the minimum hand movement required from chords i to n given a shape j of that i-th chord.
     * Along that matrix, the algorithm also fills a matrix Sigma used to mark the way to get the minimum required hand movement.
     * Sigma[i][j] says which shape of chord i+1 helps to achieve the minimum hand movement required.
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
