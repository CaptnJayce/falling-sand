#include <raylib.h>

enum CellType {
    Empty,
    Sand,
};

struct Cell {
    int cell_w = 4;
    int cell_h = 4;

    static Color GetColour(CellType type) {
        switch (type) {
        case Empty:
            return BLACK;
        case Sand:
            return YELLOW;
        default:
            return RED; // error
        }
    }
};

class Grid {
  public:
    int rows = 200;
    int col = 400;
    CellType *cells;

    Grid() {
        cells = new CellType[rows * col];

        for (int i = 0; i < rows * col; i++) {
            int rand_type = GetRandomValue(0, 5);

            if (rand_type == 0) {
                cells[i] = Sand;
            } else {
                cells[i] = Empty;
            }
        }
    }

    Color GetCellColour(int x, int y) { return Cell::GetColour(cells[y * col + x]); }

    void Update() {
        for (int y = Grid::rows - 2; y >= 0; y--) {
            for (int x = 0; x < Grid::col; x++) {
                if (cells[y * col + x] == Sand) {
                    if (cells[(y + 1) * col + x] == Empty) {
                        cells[(y + 1) * col + x] = Sand;
                        cells[y * col + x] = Empty;
                    } else {
                        bool moved = false;

                        // not necessary to randomise direction but sand piles won't look "natural" otherwise
                        int d = GetRandomValue(0, 1) ? 1 : -1;

                        // first, if not second
                        if (x + d >= 0 && x + d < col && cells[(y + 1) * col + (x + d)] == Empty) {
                            cells[(y + 1) * col + (x + d)] = Sand;
                            cells[y * col + x] = Empty;
                            moved = true;
                        } else if (x - d >= 0 && x - d < col && cells[(y + 1) * col + (x - d)] == Empty) {
                            cells[(y + 1) * col + (x - d)] = Sand;
                            cells[y * col + x] = Empty;
                            moved = true;
                        }
                    }
                }
            }
        }
    }
};

int main() {
    int screen_width = 1600;
    int screen_height = 800;

    SetTargetFPS(60);
    InitWindow(screen_width, screen_height, "Falling Sand");

    // objects
    Grid g;
    Cell c;

    while (!WindowShouldClose()) {
        // update
        g.Update();

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < g.rows; y++) {
            for (int x = 0; x < g.col; x++) {
                DrawRectangle(x * c.cell_w, y * c.cell_h, c.cell_w, c.cell_h, g.GetCellColour(x, y));
            }
        }

        DrawFPS(10, 10);
        EndDrawing();
    }
}
