#pragma once

#include "Block.h"
#include "Grid.h"

class Game {
 public:
  Game();
  Block GetRandomBlock();
  Grid grid;
  [[nodiscard]] static std::vector<Block> GetBlocks();
  bool gameOver;
  void Draw() const;
  void HandleInput();
  void MoveBlockLeft();
  void MoveBlockRight();
  void MoveBlockDown();
  void DropBlock();
  void Reset();

 private:
  [[nodiscard]] bool isBlockOutside() const;
  void RotateBlock();
  void LockBlock();
  [[nodiscard]] bool isBlockColliding() const;
  std::vector<Block> blocks;
  Block currBlock;
  Block nextBlock;
};
