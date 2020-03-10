#include "Image.h"
#include <cmath>
#include <iostream>

void Image::lighten() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double lum = pixel.l + 0.1;
      if (lum > 1.0) {
        lum = 1.0;
      }
      pixel.l = lum;
    }
  }
}
void Image::lighten(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double lum = pixel.l + amount;
      if (lum > 1.0) {
        lum = 1.0;
      }
      pixel.l = lum;
    }
  }
}
void Image::darken() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double lum = pixel.l - 0.1;
      if (lum < 0.0) {
        lum = 0;
      }
      pixel.l = lum;
    }
  }
}
void Image::darken(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double lum = pixel.l - amount;
      if (lum < 0.0) {
        lum = 0;
      }
      pixel.l = lum;
    }
  }
}
void Image::saturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double sat = pixel.s + 0.1;
      if (sat > 1.0) {
        sat = 1.0;
      }
      pixel.s = sat;
    }
  }
}
void Image::saturate(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double sat = pixel.s + amount;
      if (sat > 1.0) {
        sat = 1.0;
      }
      pixel.s = sat;
    }
  }
}
void Image::desaturate() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double sat = pixel.s - 0.1;
      if (sat < 0.0) {
        sat = 0.0;
      }
      pixel.s = sat;
    }
  }
}
void Image::desaturate(double amount) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double sat = pixel.s - amount;
      if (sat < 0.0) {
        sat = 0.0;
      }
      pixel.s = sat;
    }
  }
}
void Image::grayscale() {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::rotateColor(double degree) {
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double newh = pixel.h + degree;
      if (newh > 360) {
        newh -= 360;
      }
      if (newh < 0) {
        newh +=360;
      }
      pixel.h = newh;
    }
  }
}
void Image::illinify() {
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      double minB = fmin(abs(pixel.h - 216), abs(360 + pixel.h - 216));
      double minO = fmin(abs(pixel.h - 11), abs(360 - pixel.h + 11));
      if (minO > minB) {
        pixel.h = 216;
      } else {
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor) {
  cs225::PNG* image = new cs225::PNG(this->width() * factor, this->height() * factor);
  for (unsigned int i = 0; i < image->width(); i++) {
    for (unsigned int j = 0; j < image->height(); j++) {
      cs225::HSLAPixel & pixel = image->getPixel(i, j);
      pixel.h = this->getPixel(floor(i / factor), floor(j / factor)).h;
      pixel.l = this->getPixel(floor(i / factor), floor(j / factor)).l;
      pixel.s = this->getPixel(floor(i / factor), floor(j / factor)).s;
      pixel.a = this->getPixel(floor(i / factor), floor(j / factor)).a;
    }
  }
  this->resize(this->width() * factor, this->height() * factor);
  for (unsigned int i = 0; i < this->width(); i++) {
    for (unsigned int j = 0; j < this->height(); j++) {
      cs225::HSLAPixel & pixel = this->getPixel(i, j);
      pixel.h = image->getPixel(i, j).h;
      pixel.s = image->getPixel(i, j).s;
      pixel.l = image->getPixel(i, j).l;
      pixel.a = image->getPixel(i, j).a;
    }
  }
  delete image;
}
void Image::scale(unsigned w, unsigned h) {
  double factor = std::min((double) w/this->width(), (double) h/this->height());
  this->scale(factor);
}
