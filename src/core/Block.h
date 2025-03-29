#pragma once
#include <map>
#include <vector>

#include "colors.h"
#include "position.h"

class Block {
 public:
  Block();
  int id;
  [[nodiscard]] std::vector<Position> GetCellPositions() const;
  std::map<int, std::vector<Position>> cells;
  void Draw(int xOffset, int yOffset) const;
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
