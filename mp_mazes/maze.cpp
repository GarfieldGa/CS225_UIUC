/* Your code here! */
#include "maze.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

SquareMaze::SquareMaze() {}

void SquareMaze::makeMaze(int width, int height) {
  maze.clear();
  w = width;
  h = height;
  for (int i = 0; i < w*h; i++) {
    maze.push_back(Grid());
  }
  int root = findRoot(maze);
  while (root != -1) {
    if ((root-1)%w != w-1 && (root-1)%w != -1) {
      if (maze[root-1].right) {
        maze[root-1].right = 0;
        maze[root].up = root-1;
        root = findRoot(maze);
        continue;
      }
    }
    if (root-w >= 0) {
      if (maze[root-w].down) {
        maze[root-w].down = 0;
        maze[root].up = root-w;
        root = findRoot(maze);
        continue;
      }
    }
    if ((root+1)%w != 0) {
      if (maze[root].right) {
        maze[root].right = 0;
        maze[root].up = root+1;
        root = findRoot(maze);
        continue;
      }
    } else {
      maze[root].down = 0;
      maze[root].up = root+w;
      root = findRoot(maze);
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) {
  int idx = (y*w) + x;
  if (dir == 0) {
    return !maze[idx].right;
  }
  if (dir == 1) {
    return !maze[idx].down;
  }
  if (dir == 2) {
    if ((idx-1)%w == w-1 && (idx-1)%w != -1) {
      return !maze[idx-1].right;
    } else {
      return false;
    }
  } else {
    if ((idx-w) >= 0) {
      return !maze[idx-w].down;
    } else {
      return false;
    }
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  int idx = (y*w) + x;
  if (dir == 0) {
    maze[idx].right = exists;
    return;
  }
  if (dir == 1) {
    maze[idx].down = exists;
    return;
  }
  if (dir == 2) {
    if ((idx-1)%w == w-1 && (idx-1)%w != -1) {
      maze[idx-1].right = exists;
      return;
    } else {
      return;
    }
  } else {
    if ((idx-w) >= 0) {
      maze[idx-w].down = exists;
      return;
    } else {
      return;
    }
  }
}

std::vector<int> SquareMaze::solveMaze() {
  std::vector<std::vector<int>> paths;
  std::vector<int> path;
  getPath(paths, path, 0);
  return std::vector<int>();
}

void SquareMaze::getPath(std::vector<std::vector<int>>& paths, std::vector<int>& path, int curr) {
  int y = curr/w;
  int x = curr%w;
  path.push_back(curr);

  if (canTravel(x, y, 0) && path.back() != curr+1) {
    getPath(paths, path, curr+1);

  }
  if (canTravel(x, y, 1) && path.back() != curr+w) {
    getPath(paths, path, curr+w);
  }

}

cs225::PNG* SquareMaze::drawMaze() const {
  return new cs225::PNG();
}
cs225::PNG* SquareMaze::drawMazeWithSolution() const {
  return new cs225::PNG();
}

int SquareMaze::findRoot(std::vector<Grid> v) {
  std::vector<int> roots;
  for (unsigned int i = 1; i < v.size(); i++) {
    if (v[i].up < 0) {
      roots.push_back(i);
    }
  }
  if (roots.empty()) {
    return -1;
  } else {
    return rand() % roots.size();
  }
}
