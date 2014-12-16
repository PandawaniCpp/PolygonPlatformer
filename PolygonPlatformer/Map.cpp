#include "Map.h"


Map::Map (std::pair<int, int> size = {20, 20},               //no idea how to use Dimensions typedef in constructor lol
          std::pair<int, int> biggestPlatform = {10, 2},
          std::pair<int, int> smallestPlatform = {10, 2},
          unsigned int numberOfPlatforms = 1) :                  //if the biggest size id equal to the smallest, number of platforms can be equal to 1
          mSize (size),
          mBiggestPlatform (biggestPlatform),
          mSmallestPlatform (smallestPlatform),
          mNumberOfPlatforms (numberOfPlatforms) {
    generate (mSize, mBiggestPlatform, mSmallestPlatform, mNumberOfPlatforms);
}

Map::~Map () {}


void Map::generate (std::pair<int, int> size, std::pair<int, int> biggestPlatform, std::pair<int, int> smallestPlatform, unsigned int numberOfPlatforms) {
    //some freakin voodoo
}