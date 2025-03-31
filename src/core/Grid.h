#pragma once
#include <array>
#include <vector>

#include "raylib.h"

class Grid {
 public:
  int cells[20][10];
  Grid();
  void Init();
  void Print() const;
  void Draw() const;
  [[nodiscard]] bool isCellOutside(int r, int c) const;
  [[nodiscard]] bool isCellEmpty(int r, int c) const;
  int ClearFullRows();
  [[nodiscard]] int getRNum() const;
  [[nodiscard]] int getCNum() const;

  
 private:
  int rNum;
  int cNum;
  int cSize;
  [[nodiscard]] bool IsRowFull(int r) const;
  std::array<Color,8> colors;
  void ClearRow(int r);
  void ShiftRowsDown(int r, int numRows);
};
