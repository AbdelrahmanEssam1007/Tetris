#include "Game.h"

#include <algorithm>
#include <random>

#include "Blocks.cpp"

Game::Game() {
  grid = Grid();
  blocks = GetBlocks();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
}

Block Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetBlocks();
  }
  const int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetBlocks() {
  return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() const {
  grid.Draw();
  currBlock.Draw();
}

void Game::HandleInput() {
  const int keyPress = GetKeyPressed();
  if (gameOver && keyPress != 0) {
    gameOver = false;
    Reset();
  }
  switch (keyPress) {
    case KEY_LEFT:
      MoveBlockLeft();
      break;

    case KEY_RIGHT:
      MoveBlockRight();
      break;

    case KEY_DOWN:
      MoveBlockDown();
      break;

    case KEY_UP:
      RotateBlock();
      break;
    case KEY_SPACE:
      DropBlock();
      break;
    default:
      break;
  }
}

void Game::MoveBlockLeft() {
  if (gameOver) {
    return;
  }
  currBlock.Move(0, -1);
  if (isBlockOutside() || isBlockColliding()) {
    currBlock.Move(0, 1);
  }
}

void Game::MoveBlockRight() {
  if (gameOver) {
    return;
  }
  currBlock.Move(0, 1);
  if (isBlockOutside() || isBlockColliding()) {
    currBlock.Move(0, -1);
  }
}

void Game::MoveBlockDown() {
  if (gameOver) {
    return;
  }
  currBlock.Move(1, 0);
  if (isBlockOutside() || isBlockColliding()) {
    currBlock.Move(-1, 0);
    LockBlock();
  }
}

void Game::DropBlock() {
  if (gameOver) {
    return;
  }
  while (!isBlockOutside() && !isBlockColliding()) {
    currBlock.Move(1, 0);
  }
  currBlock.Move(-1, 0);
  LockBlock();
}

void Game::Reset() {
  grid.Init();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
}

bool Game::isBlockOutside() const {
  const auto& cellPositions = currBlock.GetCellPositions();
  return std::any_of(cellPositions.begin(), cellPositions.end(),
                     [&](const Position& cellPosition) { return grid.isCellOutside(cellPosition.r, cellPosition.c); });
}

void Game::RotateBlock() {
  if (gameOver) {
    return;
  }
  currBlock.Rotate();
  if (isBlockOutside()) {
    currBlock.UndoRotate();
  }
}

void Game::LockBlock() {
  std::vector<Position> cellPositions = currBlock.GetCellPositions();
  for (const Position& cellPosition : cellPositions) {
    grid.cells[cellPosition.r][cellPosition.c] = currBlock.id;
  }
  currBlock = nextBlock;
  if (isBlockColliding()) {
    gameOver = true;
    return;
  }
  nextBlock = GetRandomBlock();
  grid.ClearFullRows();
}

bool Game::isBlockColliding() const {
  std::vector<Position> cellPositions = currBlock.GetCellPositions();
  return std::any_of(cellPositions.begin(), cellPositions.end(),
                     [&](const Position& cellPosition) { return grid.cells[cellPosition.r][cellPosition.c] != 0; });
}
