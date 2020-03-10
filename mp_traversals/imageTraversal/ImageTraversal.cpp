#include <cmath>
#include <iterator>
#include <iostream>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include "ImageTraversal.h"
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;
  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;
  return sqrt( (h*h) + (s*s) + (l*l) );
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
  visited = new bool*[1];
}
ImageTraversal::Iterator::Iterator(ImageTraversal * travel, PNG png, Point & start, double tolerance)
  :traversal (travel), curr(start), tol(tolerance),  image(png) {
    if (curr.x < image.width()&& curr.y < image.height()) {
      st = image.getPixel(curr.x, curr.y);
      curr = traversal -> peek();
      visited = new bool*[image.width()];
      for (unsigned i = 0; i < image.width(); i++){
        visited[i] = new bool[image.height()];
      }
      for (unsigned i = 0; i < image.width(); i++){
        for (unsigned j = 0; j < image.height(); j++){
          visited[i][j] = false;
        }
      }
    } else {
      Iterator();
    }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
 ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
   /** @todo [Part 1] */
   curr = traversal->pop();
   unsigned cx = curr.x;
   unsigned cy = curr.y;
   if (cx + 1 < image.width()) {
     if (calculateDelta(st, image.getPixel(cx+1, cy)) < tol) {
       traversal->add(Point(cx+1, cy));
     }
   }
   if (cy + 1 < image.height()) {
     if (calculateDelta(st, image.getPixel(cx, cy+1)) < tol) {
       traversal->add(Point(cx, cy+1));
     }
   }
   if (cx > 0) {
     if (calculateDelta(st, image.getPixel(cx-1, cy)) < tol) {
       traversal->add(Point(cx-1, cy));
     }
   }
   if (cy > 0) {
     if (calculateDelta(st, image.getPixel(cx, cy - 1)) < tol) {
       traversal->add(Point(cx, cy - 1));
     }
   }
   visited[curr.x][curr.y] = true;
   while(!traversal->empty()) {
     curr = traversal->peek();
     if (visited[curr.x][curr.y]) {
       traversal->pop();
     } else {
       break;
     }
   }
   if (traversal->empty()) {
     traversal = NULL;
   }
   return *this;
 }
/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  curr = traversal -> peek();
  return curr;
}
/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //point_ = traversal_ -> peek();
  if (traversal == NULL && other.traversal == NULL) {
    return false;
  } else if (traversal == NULL || other.traversal == NULL){
    return true;
  }
  if (curr.x == other.curr.x && curr.y == other.curr.y) {
    return false;
  }
  return true;
}
ImageTraversal::Iterator::~Iterator() {
  //TODO: correct delete
  for (unsigned i = 0; i < image.width(); i++) {
    delete[] visited[i];
  }
  delete[] visited;
}
