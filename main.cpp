#include <algorithm>
#include <raylib.h>

enum CellType {
    Empty,
    Sand,
    Wood,
};

struct Cell {
    int cell_w = 4;
    int cell_h = 4;

    static Color GenerateColour(Color c) {
        int variation = GetRandomValue(-15, 15);

        c.r = std::clamp(c.r + variation, c.r - 15, c.r + 15);
        c.g = std::clamp(c.g + variation, c.g - 15, c.g + 15);
        c.b = std::clamp(c.b + variation / 2, c.b - 10, c.b + 10);

        return c;
    }

    static Color GetColour(CellType type) {
        switch (type) {
        case Empty:
            return BLACK;
        case Sand:
            return GenerateColour({194, 178, 128, 255});
        case Wood:
            return GenerateColour({63, 29, 11, 255});
        default:
            return RED;
        }
    }
};

class Grid {
  public:
    int row = 200;
    int col = 400;
    CellType *cells;
    Color *cell_colours;

    Grid() {
        cells = new CellType[row * col];
        cell_colours = new Color[row * col];
        for (int i = 0; i < row * col; i++) {
            cells[i] = Empty;
            cell_colours[i] = BLACK;
        }
    }

    ~Grid() {
        delete[] cells;
        delete[] cell_colours;
    }

    Color GetCellColour(int x, int y) {
        if (cells[y * col + x] == Empty) {
            return BLACK;
        }
        return cell_colours[y * col + x];
    }

    void Update() {
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
};

int main() {
    int screen_width = 1600;
    int screen_height = 800;

    SetTargetFPS(60);
    InitWindow(screen_width, screen_height, "Falling Sand");

    Grid g;
    Cell c;
    int cursor_size = 4;
    int current_type = 0;

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();

        if (IsKeyPressed(KEY_ONE)) {
            current_type = 0;
        }
        if (IsKeyPressed(KEY_TWO)) {
            current_type = 1;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int grid_x = mouse_pos.x / c.cell_h;
            int grid_y = mouse_pos.y / c.cell_w;

            for (int y = grid_y - cursor_size / 2; y <= grid_y + cursor_size / 2; y++) {
                for (int x = grid_x - cursor_size / 2; x <= grid_x + cursor_size / 2; x++) {
                    if (current_type == 0) {
                        if (x >= 0 && x < g.col && y >= 0 && y < g.row && g.cells[y * g.col + x] != Wood) {
                            int d = GetRandomValue(0, 10);
                            if (d == 0) {
                                g.cells[y * g.col + x] = Sand;
                                g.cell_colours[y * g.col + x] = Cell::GetColour(Sand);
                            }
                        }
                    }

                    if (current_type == 1) {
                        if (x >= 0 && x < g.col && y >= 0 && y < g.row) {
                            g.cells[y * g.col + x] = Wood;
                            g.cell_colours[y * g.col + x] = Cell::GetColour(Wood);
                        }
                    }
                }
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            int grid_x = mouse_pos.x / c.cell_h;
            int grid_y = mouse_pos.y / c.cell_w;

            for (int y = grid_y - cursor_size / 2; y <= grid_y + cursor_size / 2; y++) {
                for (int x = grid_x - cursor_size / 2; x <= grid_x + cursor_size / 2; x++) {
                    if (x >= 0 && x < g.col && y >= 0 && y < g.row) {
                        g.cells[y * g.col + x] = Empty;
                    }
                }
            }
        }

        g.Update();

        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < g.row; y++) {
            for (int x = 0; x < g.col; x++) {
                DrawRectangle(x * c.cell_w, y * c.cell_h, c.cell_w, c.cell_h, g.GetCellColour(x, y));
            }
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    return 0;
}
