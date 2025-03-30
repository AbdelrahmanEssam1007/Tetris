#pragma once

#include "Block.h"
#include "Grid.h"

class Game {
 public:
  Game();
  ~Game();
  Block GetRandomBlock();
  Grid grid;
  [[nodiscard]] static std::vector<Block> GetBlocks();
  bool gameOver;
  int score;
  float gameSpeed;
  void Draw() const;
  void HandleInput();
  void MoveBlockDown();
  void UpdateGameSpeed();
  Music music{};

 private:
  [[nodiscard]] bool isBlockOutside() const;
  [[nodiscard]] bool isBlockColliding() const;
  void MoveBlockLeft();
  void MoveBlockRight();
  void DropBlock();
  void Reset();
  void RotateBlock();
  void LockBlock();
  void UpdateScore(int linesCleared, int moveDown);
  void ResetBlockTimer();
  std::vector<Block> blocks;
  Block currBlock;
  Block nextBlock;
  Sound rotate{};
  Sound clear{};
  double startLockTime;
  double lockDelay;
  bool atBottom;
};
