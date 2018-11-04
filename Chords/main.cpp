#include <iostream>
#include <string>

#include "csvparser.h"
#include "minimumhandmovement.h"

int main(int argc, char* argv[])
{
    if (argc <= 2)
        return std::cout << "Error, por favor digite el nombre del csv y de los acordes de la canción", 1;

    MinimumHandMovement handMovement;
    return handMovement.calculateMinimumHandMovement(std::string(argv[1]), std::string(argv[2]));
}
