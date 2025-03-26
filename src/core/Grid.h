#pragma once
#include <vector>
#include "raylib.h"

class Grid {
public:
  int cells[20][10]{};
  Grid();
  void Init();
  void Print() const;
  void Draw() const;
  bool isCellOutside(int r, int c) const;
  bool isCellEmpty(int r, int c) const;
  int ClearFullRows();

private:
  int rNum;
  int cNum;
  int cSize;
  [[nodiscard]] bool IsRowFull(int r) const;
  std::vector<Color> colors;
  void ClearRow(int r);
  void ShiftRowsDown(int r, int numRows);
};
