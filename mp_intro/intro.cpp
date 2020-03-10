#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png, result;
  png.readFromFile(inputFile);
  result.readFromFile(inputFile);
  for (int i = 0; i < png.width(); i++) {
    for (int j = 0; j < png.height(); j++) {
      result.getPixel(png.width() - 1 - i, png.height() - 1 - j) = png.getPixel(i, j);
    }
  }
  result.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      png.getPixel(i, j).l = 0.5 - 0.003 * (((i << 2) + (j << 2)) >> 14);
      png.getPixel(i, j).a = 1.0;
      png.getPixel(i, j).h = 180 + (i - j) * 0.225;
      png.getPixel(i, j).s = 0.5 + (i - j) * 0.000625;
    }
  }
  return png;
}
