#include <raylib.h>

class Grid {
  public:
    int rows = 100;
    int columns = 100;
    Color *cells;

    Grid() {
        cells = new Color[rows * columns];

        for (int i = 0; i < rows * columns; i++) {
            cells[i] = BLACK;
        }

        // random sand for testing
        for (int i = 0; i < 2000; i++) {
            int randomCell = GetRandomValue(0, rows * columns - 1);
            cells[randomCell] = YELLOW;
        }
    }

    ~Grid() { delete[] cells; }
};

struct Cell {
    int cell_width = 16;
    int cell_height = 16;
};

int main() {
    int screen_width = 1600;
    int screen_height = 800;

    InitWindow(screen_width, screen_height, "Falling Sand");

    // objects
    Grid grid;
    Cell cell;

    while (!WindowShouldClose()) {
        // update

        // draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < grid.rows; y++) {
            for (int x = 0; x < grid.columns; x++) {
                Color cellColor = grid.cells[y * grid.columns + x];

                DrawRectangle(x * cell.cell_width, y * cell.cell_height, cell.cell_width, cell.cell_height, cellColor);
            }
        }

        DrawFPS(10, 10);
        EndDrawing();
    }
}
