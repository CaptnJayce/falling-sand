#include "../include/Grid.hpp"
#include <raylib.h>

class Game {
  public:
    Game(int width, int height, const char *title);
    ~Game();

    void Run();

  private:
    void ProcessInput();
    void Update();
    void Render();

    int m_width;
    int m_height;
    const char *m_title;
    Grid m_grid;
    int m_cursor_size;
    int m_current_type;
    Vector2 m_mouse_pos;
};
