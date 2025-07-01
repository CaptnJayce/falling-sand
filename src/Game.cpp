#include "../include/Game.hpp"
#include <raylib.h>

Game::Game(int width, int height, const char *title)
    : m_width(width), m_height(height), m_title(title), m_cursor_size(4), m_current_type(0) {
    InitWindow(m_width, m_height, m_title);
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
    m_mouse_pos = GetMousePosition();

    if (IsKeyPressed(KEY_ONE)) {
        m_current_type = 0;
    }
    if (IsKeyPressed(KEY_TWO)) {
        m_current_type = 1;
    }

    // place thing down
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        int grid_x = m_mouse_pos.x / Cell::cell_w;
        int grid_y = m_mouse_pos.y / Cell::cell_h;

        for (int y = grid_y - m_cursor_size / 2; y <= grid_y + m_cursor_size / 2; y++) {
            for (int x = grid_x - m_cursor_size / 2; x <= grid_x + m_cursor_size / 2; x++) {
                if (m_current_type == 0) {
                    if (x >= 0 && x < m_grid.col && y >= 0 && y < m_grid.row &&
                        m_grid.cells[y * m_grid.col + x] != Wood) {
                        int d = GetRandomValue(0, 10);
                        if (d == 0) {
                            m_grid.cells[y * m_grid.col + x] = Sand;
                            m_grid.cell_colours[y * m_grid.col + x] = Cell::GetColour(Sand);
                        }
                    }
                } else if (m_current_type == 1) {
                    if (x >= 0 && x < m_grid.col && y >= 0 && y < m_grid.row) {
                        m_grid.cells[y * m_grid.col + x] = Wood;
                        m_grid.cell_colours[y * m_grid.col + x] = Cell::GetColour(Wood);
                    }
                }
            }
        }
    }

    // remove thing that was placed down
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        int grid_x = m_mouse_pos.x / Cell::cell_w;
        int grid_y = m_mouse_pos.y / Cell::cell_h;

        for (int y = grid_y - m_cursor_size / 2; y <= grid_y + m_cursor_size / 2; y++) {
            for (int x = grid_x - m_cursor_size / 2; x <= grid_x + m_cursor_size / 2; x++) {
                if (x >= 0 && x < m_grid.col && y >= 0 && y < m_grid.row) {
                    m_grid.cells[y * m_grid.col + x] = Empty;
                }
            }
        }
    }
}

void Game::Update() { m_grid.Update(); }

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    // update things placed down
    for (int y = 0; y < m_grid.row; y++) {
        for (int x = 0; x < m_grid.col; x++) {
            DrawRectangle(x * Cell::cell_w, y * Cell::cell_h, Cell::cell_w, Cell::cell_h, m_grid.GetCellColour(x, y));
        }
    }

    DrawText("1 for Sand, 2 for Wood", 10, 40, 20, RAYWHITE);
    DrawText("Left click to place", 10, 60, 20, RAYWHITE);
    DrawText("Right click to erase", 10, 80, 20, RAYWHITE);
    DrawFPS(10, 10);
    EndDrawing();
}
