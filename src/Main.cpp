#include "../include/Cell.hpp"
#include "../include/Grid.hpp"
#include <raylib.h>

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
