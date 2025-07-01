#include "../include/Game.hpp"

Game::Game(int width, int height, const char *title)
    : width(width), height(height), title(title), cursor_size(4), current_type(0) {
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

Game::~Game() { CloseWindow(); }

void Game::Run() {
    while (!WindowShouldClose()) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    mouse_pos = GetMousePosition();

    if (IsKeyPressed(KEY_ONE)) {
        current_type = 0;
    }
    if (IsKeyPressed(KEY_TWO)) {
        current_type = 1;
    }

    // place thing down
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int grid_x = mouse_pos.x / Cell::cell_w;
        int grid_y = mouse_pos.y / Cell::cell_h;

        for (int y = grid_y - cursor_size / 2; y <= grid_y + cursor_size / 2; y++) {
            for (int x = grid_x - cursor_size / 2; x <= grid_x + cursor_size / 2; x++) {
                if (current_type == 0) {
                    if (x >= 0 && x < grid.col && y >= 0 && y < grid.row && grid.cells[y * grid.col + x] != Wood) {
                        int d = GetRandomValue(0, 10);
                        if (d == 0) {
                            grid.cells[y * grid.col + x] = Sand;
                            grid.cell_colours[y * grid.col + x] = Cell::GetColour(Sand);
                        }
                    }
                } else if (current_type == 1) {
                    if (x >= 0 && x < grid.col && y >= 0 && y < grid.row) {
                        grid.cells[y * grid.col + x] = Wood;
                        grid.cell_colours[y * grid.col + x] = Cell::GetColour(Wood);
                    }
                }
            }
        }
    }

    // remove thing that was placed down
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        int grid_x = mouse_pos.x / Cell::cell_w;
        int grid_y = mouse_pos.y / Cell::cell_h;

        for (int y = grid_y - cursor_size / 2; y <= grid_y + cursor_size / 2; y++) {
            for (int x = grid_x - cursor_size / 2; x <= grid_x + cursor_size / 2; x++) {
                if (x >= 0 && x < grid.col && y >= 0 && y < grid.row) {
                    grid.cells[y * grid.col + x] = Empty;
                }
            }
        }
    }
}

void Game::Update() { grid.Update(); }

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    // update things placed down
    for (int y = 0; y < grid.row; y++) {
        for (int x = 0; x < grid.col; x++) {
            DrawRectangle(x * Cell::cell_w, y * Cell::cell_h, Cell::cell_w, Cell::cell_h, grid.GetCellColour(x, y));
        }
    }

    DrawFPS(10, 10);
    EndDrawing();
}
