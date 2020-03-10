/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas* finalCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     std::map<Point<3>, int> map;
     std::vector<Point<3>> points;

     for (unsigned i = 0; i < theTiles.size(); i++) {
       LUVAPixel averageColor = theTiles[i].getAverageColor();
       Point<3> point = convertToXYZ(averageColor);
       points.push_back(point);
       map[point] = i;
     }
     KDTree<3> kdtree(points);
     for (int i = 0; i < theSource.getRows(); i++) {
       for (int j = 0; j < theSource.getColumns(); j++) {
         LUVAPixel regionColor = theSource.getRegionColor(i, j);
         Point<3> regionPoint = convertToXYZ(regionColor);
         Point<3> findPoint = kdtree.findNearestNeighbor(regionPoint);
         finalCanvas->setTile(i, j, &theTiles[map[findPoint]]);
       }
     }
     return finalCanvas;
}
