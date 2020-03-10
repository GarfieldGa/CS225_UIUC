/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"

class SquareMaze {
public:
  class Grid {
  public:
    int up;
    bool right;
    bool down;
    Grid() {
      up = -1;
      right = 1;
      down = 1;
    }
  };
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir);
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze();
  cs225::PNG* drawMaze() const;
  cs225::PNG* drawMazeWithSolution() const;
  void getPath(std::vector<std::vector<int>>& paths, std::vector<int>& path, int curr);
  int findRoot(std::vector<Grid> v);
private:
  int h;
  int w;
  std::vector<Grid> maze;
};
