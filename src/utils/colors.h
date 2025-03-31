#pragma once
#include <array>

#include "raylib.h"

namespace COLOUR {
  inline constexpr Color darkGrey = {26, 31, 40, 255};
  inline constexpr Color green = {47, 230, 23, 255};
  inline constexpr Color red = {232, 18, 18, 255};
  inline constexpr Color orange = {226, 116, 17, 255};
  inline constexpr Color yellow = {237, 234, 4, 255};
  inline constexpr Color purple = {166, 0, 247, 255};
  inline constexpr Color cyan = {21, 204, 209, 255};
  inline constexpr Color blue = {13, 64, 216, 255};
  inline constexpr Color darkBlue = {44, 44, 127, 255};
  inline constexpr Color lightBlue = {59, 85, 162, 255};
  inline constexpr Color menuGrey = {200, 200, 200, 150};

  inline std::array<Color, 8> GetCellColors() {
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
  }
}  // namespace COLOUR
