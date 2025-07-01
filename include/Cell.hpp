#pragma once
#include <raylib.h>

enum CellType {
    Empty,
    Sand,
    Wood,
};

struct Cell {
    static const int cell_w = 4;
    static const int cell_h = 4;

    static Color GenerateColour(Color c);
    static Color GetColour(CellType type);
};
