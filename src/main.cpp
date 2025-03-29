#include <iostream>

#include "Game.h"
#include "raylib.h"
#include "utils/colors.h"

double lastUpdate = 0;

bool EventTriggered(const double interval) {
  if (const double currTime = GetTime(); currTime - lastUpdate >= interval) {
    lastUpdate = currTime;
    return true;
  }
  return false;
}

int main() {
  const Image icon = LoadImage("../src/assets/icon/tetris.bmp");
  const Font arcadeClassic = LoadFontEx("../src/assets/font/ARCADECLASSIC.ttf", 64, nullptr, 0);

  InitWindow(500, 620, "Tetris");
  SetWindowIcon(icon);
  SetTargetFPS(60);

  auto game = Game();

  while (WindowShouldClose() == false) {
    UpdateMusicStream(game.music);
    game.HandleInput();
    if (EventTriggered(0.2)) {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(darkBlue);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    auto [x, y] = MeasureTextEx(arcadeClassic, scoreText, 38, 2);
    DrawTextEx(arcadeClassic, "Score", {355, 15}, 38, 2, WHITE);
    DrawTextEx(arcadeClassic, scoreText, {320 + (170 - x) / 2, 65}, 38, 2, WHITE);
    DrawTextEx(arcadeClassic, "Next", {360, 175}, 38, 2, WHITE);
    if (game.gameOver) DrawTextEx(arcadeClassic, "GAME OVER", {315, 450}, 38, 2, WHITE);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
