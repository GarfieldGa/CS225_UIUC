#include "StickerSheet.h"
#include <algorithm>

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
  length = max + 1;
  track = 0;
  base = new Image();
  sheetCollection = new Image*[length];
  base->resize(picture.width(), picture.height());
  for (unsigned int i = 0; i < picture.width(); i++) {
    for (unsigned int j = 0; j < picture.height(); j++) {
      base->getPixel(i, j) = picture.getPixel(i, j);
    }
  }
  for (unsigned int i = 0; i < length; i++) {
    sheetCollection[i] = NULL;
  }
  x_value = new int[length - 1];
  y_value = new int[length - 1];
  sheetCollection[0] = base;
}
StickerSheet::~StickerSheet() {
  for (unsigned int i = 0; i < length; i++) {
    if (sheetCollection[i] != NULL) {
      delete *(sheetCollection+i);
      sheetCollection[i] = NULL;
    }
  }
  delete[] sheetCollection;
  delete[] x_value;
  delete[] y_value;
}
StickerSheet::StickerSheet(StickerSheet & other) {
  this->track = other.track;
  length = other.length;
  x_value = new int[other.length - 1];
  y_value = new int[other.length - 1];
  this->sheetCollection = new Image*[length];
  for (unsigned int i = 0; i < other.length; i++) {
    *(sheetCollection[i]) = *(other.getSticker(i - 1));
  }
  for (unsigned int i = 0; i < other.length - 1; i++) {
    x_value[i] = other.x_value[i];
    y_value[i] = other.y_value[i];
  }
  *base = *(sheetCollection[0]);
}
const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {
  this->track = other.track;
  for (unsigned int i = 0; i < length; i++) {
    if (sheetCollection != NULL) {
      delete sheetCollection[i];
      sheetCollection[i] = NULL;
    }
  }
  delete[] x_value;
  delete[] y_value;
  length = other.length;
  x_value = new int[other.length - 1];
  y_value = new int[other.length - 1];
  for (unsigned int i = 0; i < other.length; i++) {
    *(sheetCollection[i]) = *(other.sheetCollection[i]);
  }
  for (unsigned int i = 0; i < other.length - 1; i++) {
    x_value[i] = other.x_value[i];
    y_value[i] = other.y_value[i];
  }
  base = sheetCollection[0];
  return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
  if (max + 1 < length) {
    for (unsigned int i = max; i < length; i++) {
      delete sheetCollection[i];
      sheetCollection[i] = NULL;
    }
  }
  Image** newCollection = new Image*[max + 1];
  for (unsigned int i = 0; i < max + 1; i++) {
    newCollection[i] = NULL;
  }
  for (unsigned int i = 0; i < max + 1; i++) {
    if (sheetCollection[i] != NULL) {
      *(newCollection[i]) = *(sheetCollection[i]);
    }
  }
  for (unsigned int i = 0; i < length; i++) {
    if (sheetCollection[i] != NULL) {
      delete sheetCollection[i];
    }
  }
  if (max+1 < length) {
    this->track = max+1;
  }
  length = max + 1;
  sheetCollection = newCollection;
  int* newX = new int[max];
  int* newY = new int[max];
  for (unsigned int i = 0; i < max; i++) {
    newX[i] = x_value[i];
    newY[i] = y_value[i];
  }
  delete[] x_value;
  delete[] y_value;
  x_value = newX;
  y_value = newY;
}
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  if (getSticker(length - 2) != NULL) {
    return -1;
  }
  int index = length - 2;
  for (int i = index; i > 0; i--) {
    if (getSticker(i) != NULL) {
      index = i + 1;
    }
  }
  sheetCollection[index] = & sticker;
  x_value[index - 1] = x;
  y_value[index - 1] = y;
  this->track += 1;
  return index - 1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index + 1 >= length) {
    return false;
  }
  if (getSticker(index) == NULL) {
    return false;
  }
  x_value[index] = x;
  y_value[index] = y;
  return true;
}
void StickerSheet::removeSticker(unsigned index) {
  if (index + 1 >= length) {
    return;
  }
  if (getSticker(index) == NULL) {
    return;
  }
  delete sheetCollection[index + 1];
  for (unsigned int i = index + 2; i < length; i++) {
    sheetCollection[i - 1] = sheetCollection[i];
  }
  sheetCollection[track] = NULL;
  this->track -= 1;
  for (unsigned int i = index + 1; i < length - 1; i++) {
    x_value[i - 1] = x_value[i];
    y_value[i - 1] = y_value[i];
  }
}
Image* StickerSheet::getSticker(unsigned index) {
  return sheetCollection[index + 1];
}
Image StickerSheet::render() const {
  Image* render = new Image();
  render->resize(base->width(), base->height());
  for (unsigned int i = 0; i < base->width(); i++) {
    for (unsigned int j = 0; j < base->height(); j++) {
      render->getPixel(i, j) = base->getPixel(i, j);
    }
  }
  for (unsigned int index = 1; index < length; index++) {
    if (sheetCollection[index] == NULL) {
      break;
    }
    for (unsigned int i = x_value[index-1]; i < std::min(sheetCollection[index]->width(), base->width()); i++) {
      for (unsigned int j = y_value[index-1]; j < std::min(sheetCollection[index]->height(), base->height()); j++) {
        render->getPixel(i, j) = (sheetCollection[index]->getPixel(i-x_value[index-1], j-y_value[index-1]));
      }
    }
  }
  return *render;
}
