#include "StickerSheet.h"
#include <algorithm>
#include <iostream>
#include "Image.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
  length = max;
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
  x_value = new int[length];
  y_value = new int[length];
}
StickerSheet::~StickerSheet() {
  for (unsigned int i = 0; i < length; i++) {
    if (sheetCollection[i] != NULL) {
      delete sheetCollection[i];
    }
  }
  delete[] sheetCollection;
  delete[] x_value;
  delete[] y_value;
  delete base;
  delete output;
}
StickerSheet::StickerSheet(StickerSheet & other) {
  track = other.track;
  length = other.length;
  base = new Image();
  base->resize(other.base->width(), other.base->height());
  x_value = new int[length];
  y_value = new int[length];
  *base = *(other.base);
  sheetCollection = new Image*[length];
  for (unsigned int i = 0; i < length; i++) {
    if (other.getSticker(i) == NULL) {
      sheetCollection[i] = NULL;
      continue;
    }
    sheetCollection[i] = new Image();
    sheetCollection[i]->resize(other.getSticker(i)->width(), other.getSticker(i)->height());
    *(sheetCollection[i]) = *(other.getSticker(i));
    x_value[i] = other.x_value[i];
    y_value[i] = other.y_value[i];
  }
}
const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {
  this->track = other.track;
  length = other.length;
  delete base;
  delete[] x_value;
  delete[] y_value;
  for (unsigned int i = 0; i < length; i++) {
    delete sheetCollection[i];
    sheetCollection[i] = NULL;
  }
  delete[] sheetCollection;
  base = new Image();
  base->resize(other.base->width(), other.base->height());
  sheetCollection = new Image*[length];
  *base = *(other.base);
  x_value = new int[length];
  y_value = new int[length];
  for (unsigned int i = 0; i < length; i++) {
    if (other.sheetCollection[i] == NULL) {
      sheetCollection[i] = NULL;
      continue;
    }
    sheetCollection[i] = new Image();
    sheetCollection[i]->resize(other.sheetCollection[i]->width(), other.sheetCollection[i]->height());
    *(sheetCollection[i]) = *(other.sheetCollection[i]);
    x_value[i] = other.x_value[i];
    y_value[i] = other.y_value[i];
  }
  return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
  if (max < length) {
    for (unsigned int i = max; i < length; i++) {
      if (sheetCollection[i] != NULL) {
        delete sheetCollection[i];
        sheetCollection[i] = NULL;
      }
    }
  }
  Image** newCollection = new Image*[max];
  for (unsigned int i = 0; i < max; i++) {
    newCollection[i] = NULL;
  }
  for (unsigned int i = 0; i < std::min(length, max); i++) {
    if (sheetCollection[i] != NULL) {
      newCollection[i] = new Image();
      newCollection[i]->resize(sheetCollection[i]->width(), sheetCollection[i]->height());
      *(newCollection[i]) = *(sheetCollection[i]);
    }
  }
  for (unsigned int i = 0; i < length; i++) {
    if (sheetCollection[i] != NULL) {
      delete sheetCollection[i];
    }
  }
  delete[] sheetCollection;
  if (max < length) {
    track = max;
  }
  sheetCollection = newCollection;
  int* newX = new int[max];
  int* newY = new int[max];
  for (unsigned int i = 0; i < std::min(length, max); i++) {
    newX[i] = x_value[i];
    newY[i] = y_value[i];
  }
  length = max;
  delete[] x_value;
  delete[] y_value;
  x_value = newX;
  y_value = newY;
}
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  if (getSticker(length - 1) != NULL) {
    return -1;
  }
  int index = 0;
  for (unsigned int i = 0; i < length; i++) {
    if (getSticker(i) == NULL) {
      index = i;
      break;
    }
  }
  sheetCollection[index] = new Image();
  sheetCollection[index]->resize(sticker.width(), sticker.height());
  *(sheetCollection[index]) = sticker;
  x_value[index] = x;
  y_value[index] = y;
  track += 1;
  return index;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index >= length) {
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
  if (index >= length) {
    return;
  }
  if (getSticker(index) == NULL) {
    return;
  }
  delete sheetCollection[index];
  for (unsigned int i = index; i < length - 1; i++) {
    sheetCollection[i] = sheetCollection[i + 1];
  }
  sheetCollection[length - 1] = NULL;
  track -= 1;
  if (index != length - 1) {
    for (unsigned int i = index; i < length - 1; i++) {
      x_value[i] = x_value[i + 1];
      y_value[i] = y_value[i + 1];
    }
  }
}
Image* StickerSheet::getSticker(unsigned index) {
  return sheetCollection[index];
}
Image StickerSheet::render() const {
  output->resize(base->width(), base->height());
  for (unsigned int i = 0; i < base->width(); i++) {
    for (unsigned int j = 0; j < base->height(); j++) {
      output->getPixel(i, j) = base->getPixel(i, j);
    }
  }
  for (unsigned int index = 0; index < length; index++) {
    if (sheetCollection[index] == NULL) {
      break;
    }
    if (x_value[index] + sheetCollection[index]->width() >= output->width()) {
      output->resize(x_value[index] + sheetCollection[index]->width(), output->height());
    }
    if (y_value[index] + sheetCollection[index]->height() >= output->height()) {
      output->resize(output->width(), y_value[index] + sheetCollection[index]->height());
    }
    for (unsigned int i = x_value[index]; i < sheetCollection[index]->width() + x_value[index]; i++) {
      for (unsigned int j = y_value[index]; j < sheetCollection[index]->height() + y_value[index]; j++) {
        if (sheetCollection[index]->getPixel(i-x_value[index], j-y_value[index]).h == 0) {
          continue;
        }
        output->getPixel(i, j) = sheetCollection[index]->getPixel(i-x_value[index], j-y_value[index]);
      }
    }
  }
  return *output;
}
