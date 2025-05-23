#include <iostream>

#include "Game.h"
#include "colors.h"
#include "raylib.h"

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
  InitWindow(500, 620, "Tetris");
  const Font arcadeClassic = LoadFontEx("../src/assets/font/ARCADECLASSIC.TTF", 64, nullptr, 0);
  SetWindowIcon(icon);
  SetTargetFPS(60);
  auto game = Game();

  while (WindowShouldClose() == false) {
    UpdateMusicStream(game.music);
    game.UpdateGameSpeed();
    game.HandleInput();
    if (EventTriggered(game.gameSpeed)) {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(COLOUR::darkBlue);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, COLOUR::lightBlue);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, COLOUR::lightBlue);
    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    auto [x, y] = MeasureTextEx(arcadeClassic, scoreText, 38, 2);
    DrawTextEx(arcadeClassic, "Score", {355, 15}, 38, 2, WHITE);
    DrawTextEx(arcadeClassic, scoreText, {320 + (170 - x) / 2, 65}, 38, 2, WHITE);
    DrawTextEx(arcadeClassic, "Next", {360, 175}, 38, 2, WHITE);
    game.Draw();
    if (game.gameOver) {
      StopMusicStream(game.music);
      DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(COLOUR::darkGrey, 0.8f));
      DrawTextEx(arcadeClassic, "GAME OVER",
                 {static_cast<float>(GetScreenWidth() / 8.0), static_cast<float>(GetScreenHeight() / 3.0)}, 80, 2,
                 WHITE);
      DrawTextEx(arcadeClassic, "Press the ENTER key to restart",
                 {static_cast<float>(GetScreenWidth() / 8.0) + 5, static_cast<float>(GetScreenHeight() / 2.0) - 20}, 22,
                 2, COLOUR::menuGrey);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
