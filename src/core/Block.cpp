#include "Block.h"

#include <functional>

Block::Block() {
  cSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rOffset = 0;
  cOffset = 0;
}

void Block::Draw(int xOffset, int yOffset) const {
  std::vector<Position> cellPositions = GetCellPositions();
  for (const Position cellPosition : cellPositions) {
    DrawRectangle(cellPosition.c * cSize + xOffset, cellPosition.r * cSize + yOffset, cSize - 1, cSize - 1, colors[id]);
  }
}

void Block::DrawGhost(int xOffset, int yOffset, const std::function<bool(const std::vector<Position>&)>& isValid) const {
  int dropOffset = 0;
  while (true) {
    std::vector<Position> testPositions = GetCellPositions();
    for (auto& pos : testPositions) {
      pos.r += dropOffset;
    }
    if (!isValid(testPositions)) {
      break;
    }
    dropOffset++;
  }
  std::vector<Position> ghostPositions = GetCellPositions();
  for (auto& pos : ghostPositions) {
    pos.r += dropOffset;
    DrawRectangle(pos.c * cSize + xOffset, pos.r * cSize + yOffset, cSize - 1, cSize - 1, Fade(WHITE, 0.5f)); // Semi-transparent
    DrawRectangle(pos.c * cSize + xOffset+1, pos.r * cSize + yOffset+1, cSize - 3, cSize - 3, darkGrey); // Semi-transparent
  }
}

void Block::Move(int r, int c) {
  rOffset += r;
  cOffset += c;
}

void Block::Rotate() {
  rotationState = (rotationState + 1) % 4;
}

void Block::UndoRotate() {
  rotationState = (rotationState - 1) % 4;
  if (rotationState < 0) {
    rotationState = 3;
  }
}

std::vector<Position> Block::GetCellPositions() const {
  std::vector<Position> cellPositions = cells.at(rotationState);
  std::vector<Position> translatedCellPositions;
  translatedCellPositions.reserve(cellPositions.size());
  for (const Position cellPosition : cellPositions) {
    translatedCellPositions.push_back({cellPosition.r + rOffset, cellPosition.c + cOffset});
  }
  return translatedCellPositions;
}
