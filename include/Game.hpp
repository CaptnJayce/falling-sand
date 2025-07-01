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

    int width;
    int height;
    const char *title;
    Grid grid;
    int cursor_size;
    int current_type;
    Vector2 mouse_pos;
};
