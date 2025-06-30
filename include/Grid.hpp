#pragma once
#include "Cell.hpp"

class Grid {
  public:
    Grid();
    ~Grid();

    void Update();
    Color GetCellColour(int x, int y);

    int row = 200;
    int col = 400;
    CellType *cells;
    Color *cell_colours;
};
