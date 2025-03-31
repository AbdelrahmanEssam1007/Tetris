#include "Grid.h"

#include <algorithm>
#include <iostream>

#include "colors.h"
#include "position.h"

Grid::Grid() {
  rNum = 20;
  cNum = 10;
  cSize = 30;
  colors = COLOUR::CellColors;
  Init();
}

void Grid::Init() {
  for (int r = 0; r < rNum; r++) {
    for (int c = 0; c < cNum; c++) {
      cells[r][c] = 0;
    }
  }
}

void Grid::Print() const {
  for (int r = 0; r < rNum; r++) {
    for (int c = 0; c < cNum; c++) {
      std::cout << cells[r][c] << " ";
    }
    std::cout << std::endl;
  }
}


void Grid::Draw() const {
  for (int r = 0; r < rNum; r++) {
    for (int c = 0; c < cNum; c++) {
      const int cell = cells[r][c];
      DrawRectangle(c * cSize + 11, r * cSize + 11, cSize - 1, cSize - 1, colors[cell]);
    }
  }
}

bool Grid::isCellOutside(int r, int c) const {
  if (r >= 0 && r < rNum && c >= 0 && c < cNum) {
    return false;
  }
  return true;
}

bool Grid::isCellEmpty(int r, int c) const {
  if (isCellOutside(r, c)) return false;
  return cells[r][c] == 0;
}

int Grid::ClearFullRows() {
  int numRowsCleared = 0;

  for (int r = rNum - 1; r >= 0; r--) {
    if (IsRowFull(r)) {
      numRowsCleared++;
    }
    else if (numRowsCleared > 0) {
      std::copy_n(cells[r], cNum, cells[r + numRowsCleared]);
    }
  }

  for (int r = 0; r < numRowsCleared; r++) {
    std::fill_n(cells[r], cNum, 0);
  }

  return numRowsCleared;
}
int Grid::getRNum() const {
  return rNum;
}
int Grid::getCNum() const {
  return cNum;
}

bool Grid::IsRowFull(int r) const {
  if (std::all_of(cells[r], cells[r] + cNum, [](const int cell) { return cell != 0; })) {
    return true;
  }
  return false;
}

void Grid::ClearRow(int r) {
  for (int i = r; i > 0; i--) {
    std::copy_n(cells[i - 1], cNum, cells[i]);
  }
  std::fill_n(cells[0], cNum, 0);  // Ensures row 0 is reset properly
}

void Grid::ShiftRowsDown(const int r, const int numRows) {
  for (int i = r; i >= numRows; i--) {  // Start at r, stop at numRows
    std::copy_n(cells[i - numRows], cNum, cells[i]);  // Shift correctly
  }
  for (int i = 0; i < numRows; i++) {
    std::fill_n(cells[i], cNum, 0);  // Only clear the necessary rows
  }
}
