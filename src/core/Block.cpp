#include "Block.h"

#include <functional>

Block::Block() : id(0), cSize(30), rotationState(0), rOffset(0), cOffset(0) {
  colors = COLOUR::CellColors;
}

void Block::Draw(const int xOffset, const int yOffset) const {
  std::vector<Position> cellPositions = GetCellPositions();
  for (const Position cellPosition : cellPositions) {
    DrawRectangle(cellPosition.c * cSize + xOffset, cellPosition.r * cSize + yOffset, cSize - 1, cSize - 1, colors[id]);
  }
}

void Block::DrawGhost(const int xOffset, const int yOffset,
                      const std::function<bool(const std::vector<Position>&)>& isValid) const {
  int dropOffset = 0;
  while (true) {
    std::vector<Position> testPositions = GetCellPositions();
    for (auto& pos : testPositions) {
      pos.r += dropOffset;
    }
    if (!isValid(testPositions)) {
      dropOffset--;  // Move back to the last valid position
      break;
    }
    dropOffset++;
  }

  std::vector<Position> ghostPositions = GetCellPositions();
  for (auto& pos : ghostPositions) {
    pos.r += dropOffset;
    DrawRectangle(pos.c * cSize + xOffset, pos.r * cSize + yOffset, cSize - 1, cSize - 1,
                  Fade(WHITE, 0.5f));  // Semi-transparent
    DrawRectangle(pos.c * cSize + xOffset + 1, pos.r * cSize + yOffset + 1, cSize - 3, cSize - 3,
                  COLOUR::darkGrey);  // Semi-transparent
  }
}

void Block::Move(const int r, const int c) {
  rOffset += r;
  cOffset += c;
}
void Block::Rotate() {
  rotationState = (rotationState + 1) % static_cast<int>(cells.size());
}

void Block::UndoRotate() {
  rotationState = (rotationState + static_cast<int>(cells.size()) - 1) % static_cast<int>(cells.size());
}


std::vector<Position> Block::GetCellPositions() const {
  const std::vector<Position>& cellPositions = cells.at(rotationState);
  std::vector<Position> translatedCellPositions;
  translatedCellPositions.reserve(cellPositions.size());
  for (const Position cellPosition : cellPositions) {
    translatedCellPositions.emplace_back(cellPosition.r + rOffset, cellPosition.c + cOffset);
  }
  return translatedCellPositions;
}
