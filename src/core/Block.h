#pragma once
#include <functional>
#include <map>
#include <array>

#include "colors.h"
#include "position.h"

class Block {
 public:
  Block();
  int id;
  [[nodiscard]] std::vector<Position> GetCellPositions() const;
  std::map<int, std::vector<Position>> cells;
  void Draw(int xOffset, int yOffset) const;
  void DrawGhost(int xOffset, int yOffset, const std::function<bool(const std::vector<Position>&)>& isValid) const;

  void Move(int r, int c);
  void Rotate();
  void UndoRotate();

 private:
  int cSize;
  int rotationState;
  int rOffset;
  int cOffset;
  std::array<Color, 8> colors{};
};
