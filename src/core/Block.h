#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block {
public:
  Block();
  int id;
  std::vector<Position> GetCellPositions() const;
  std::map<int, std::vector<Position>> cells;
  void Draw() const;
  void Move(int r, int c);
  void Rotate();
  void UndoRotate();

private:
  int cSize;
  int rotationState;
  std::vector<Color> colors;
  int rOffset;
  int cOffset;
};
