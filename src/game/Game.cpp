#include "Game.h"

#include <algorithm>
#include <random>
#include <thread>

#include "Blocks.cpp"

std::mt19937 rng(std::random_device{}());

Game::Game() {
  gameSpeed = 0.5;
  grid = Grid();
  blocks = GetBlocks();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  startLockTime = 0;
  lockDelay = 0.5;
  atBottom = false;
  InitAudioDevice();
  music = LoadMusicStream("../src/assets/sounds/music.mp3");
  rotate = LoadSound("../src/assets/sounds/rotate.mp3");
  clear = LoadSound("../src/assets/sounds/clear.mp3");
  PlayMusicStream(music);
}

Game::~Game() {
  CloseAudioDevice();
  UnloadMusicStream(music);
  UnloadSound(rotate);
  UnloadSound(clear);
}

Block Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetBlocks();
  }
  std::uniform_int_distribution<int> dist(0, static_cast<int>((blocks.size())) - 1);
  const int randomIndex = dist(rng);
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetBlocks() {
  return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() const {
  grid.Draw();
  currBlock.DrawGhost(11, 11, [&](const std::vector<Position>& cellPositions) {
    // at first god and I understood this code, but now only god knows
    // do not touch, do not try to fix, do not try to understand. LEAVE IT ALONE!!!!
    return std::none_of(cellPositions.begin(), cellPositions.end(), [&](const Position& cellPosition) {
      return (cellPosition.r < 0 || cellPosition.r >= grid.getRNum() ||  // Row out of bounds
              cellPosition.c < 0 || cellPosition.c >= grid.getCNum() ||  // Column out of bounds
              grid.cells[cellPosition.r][cellPosition.c] != 0);  // Cell occupied
    });
  });
  currBlock.Draw(11, 11);
  switch (nextBlock.id) {
    case 3:
      nextBlock.Draw(255, 290);
      break;
    case 4:
      nextBlock.Draw(255, 280);
      break;
    default:
      nextBlock.Draw(270, 270);
  }
}

void Game::HandleInput() {
  if (gameOver) {
    if (GetKeyPressed() != 0) {
      Reset();
    }
    return;
  }


  static auto lastMoveTime = std::chrono::steady_clock::now();
  static std::unordered_map<int, bool> keyWasDown;
  constexpr int moveDelay = 100;  // Delay for movement keys

  const auto now = std::chrono::steady_clock::now();
  bool canMove = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastMoveTime).count() >= moveDelay;

  // Movement keys (delayed)
  if (canMove) {
    if (IsKeyDown(KEY_LEFT))
      MoveBlockLeft();
    else if (IsKeyDown(KEY_RIGHT))
      MoveBlockRight();
    else if (IsKeyDown(KEY_DOWN)) {
      MoveBlockDown();
      UpdateScore(0, 1);
    }
    lastMoveTime = std::chrono::steady_clock::now();
  }

  // Rotation and drop keys (trigger once per press)
  if (IsKeyDown(KEY_UP) && !keyWasDown[KEY_UP]) RotateBlock();
  if (IsKeyDown(KEY_SPACE) && !keyWasDown[KEY_SPACE]) {
    DropBlock();
    UpdateScore(0, 10);
  }

  // Update key states
  keyWasDown[KEY_UP] = IsKeyDown(KEY_UP);
  keyWasDown[KEY_SPACE] = IsKeyDown(KEY_SPACE);
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

    if (!atBottom) {
      atBottom = true;
      startLockTime = GetTime();
    }
    else {
      atBottom = false;
    }
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

void Game::UpdateGameSpeed() {
  if (score < 1000) {
    gameSpeed = 0.5;
    SetMusicPitch(music, 1.0);
  }
  else if (score < 2000) {
    gameSpeed = 0.4;
    SetMusicPitch(music, 1.02);
  }
  else if (score < 3000) {
    gameSpeed = 0.3;
    SetMusicPitch(music, 1.05);
  }
  else if (score < 4000) {
    gameSpeed = 0.2;
    SetMusicPitch(music, 1.07);
  }
  else {
    gameSpeed = 0.1;
    SetMusicPitch(music, 1.1);
  }
}

void Game::DropBlock() {
  if (gameOver) {
    return;
  }
  while (true) {
    currBlock.Move(1, 0);
    if (isBlockOutside() || isBlockColliding()) {
      currBlock.Move(-1, 0);
      break;
    }
  }
  LockBlock();
}

void Game::Reset() {
  grid.Init();
  currBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  SeekMusicStream(music, 0.0);  // Reset music to the beginning
  PlayMusicStream(music);  // Start playing again
  SetMusicPitch(music, 1.0);  // Reset pitch and speed
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

  if (currBlock.id == 4) {
    return;
  }

  currBlock.Rotate();
  if (isBlockOutside() || isBlockColliding()) {
    currBlock.UndoRotate();
  }
  else {
    PlaySound(rotate);
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
  if (const int rowsCleared = grid.ClearFullRows(); rowsCleared > 0) {
    UpdateScore(rowsCleared, 0);
    PlaySound(clear);
  }
}
void Game::UpdateScore(const int linesCleared, const int moveDown) {
  switch (linesCleared) {
    case 0:
      break;
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    default:
      score += 800;
      break;
  }
  score += moveDown;
}
void Game::ResetBlockTimer() {
  if (atBottom) {
    startLockTime = GetTime();
  }
}

bool Game::isBlockColliding() const {
  std::vector<Position> cellPositions = currBlock.GetCellPositions();
  return std::any_of(cellPositions.begin(), cellPositions.end(),
                     [&](const Position& cellPosition) { return grid.cells[cellPosition.r][cellPosition.c] != 0; });
}
