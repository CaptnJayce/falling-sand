#include "../include/Grid.hpp"

Grid::Grid() {
    cells = new CellType[row * col];
    cell_colours = new Color[row * col];
    for (int i = 0; i < row * col; i++) {
        cells[i] = Empty;
        cell_colours[i] = BLACK;
    }
}

Grid::~Grid() {
    delete[] cells;
    delete[] cell_colours;
}

Color Grid::GetCellColour(int x, int y) {
    if (cells[y * col + x] == Empty) {
        return BLACK;
    }
    return cell_colours[y * col + x];
}

void Grid::Update() {
    for (int y = row - 2; y >= 0; y--) {
        for (int x = 0; x < col; x++) {
            if (cells[y * col + x] == Sand) {
                if (cells[(y + 1) * col + x] == Empty) {
                    cells[(y + 1) * col + x] = Sand;
                    cell_colours[(y + 1) * col + x] = cell_colours[y * col + x];
                    cells[y * col + x] = Empty;
                } else {
                    int d = GetRandomValue(0, 1) ? 1 : -1;

                    if (x + d >= 0 && x + d < col && cells[(y + 1) * col + (x + d)] == Empty) {
                        cells[(y + 1) * col + (x + d)] = Sand;
                        cell_colours[(y + 1) * col + (x + d)] = cell_colours[y * col + x];
                        cells[y * col + x] = Empty;
                    } else if (x - d >= 0 && x - d < col && cells[(y + 1) * col + (x - d)] == Empty) {
                        cells[(y + 1) * col + (x - d)] = Sand;
                        cell_colours[(y + 1) * col + (x - d)] = cell_colours[y * col + x];
                        cells[y * col + x] = Empty;
                    }
                }
            }

            if (cells[y * col + x] == Wood) {
                // wood behaviour
            }
        }
    }
}
