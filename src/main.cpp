#include <iostream>

#include "Game.h"
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
  constexpr Color darkBlue = {44, 44, 127, 255};
  InitWindow(300, 600, "Tetris");
  SetTargetFPS(60);

  auto game = Game();

  while (WindowShouldClose() == false) {
    game.HandleInput();
    if (EventTriggered(0.2)) {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(darkBlue);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
