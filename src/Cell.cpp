#include "../include/Cell.hpp"
#include <algorithm>

Color Cell::GenerateColour(Color c) {
    int variation = GetRandomValue(-15, 15);

    c.r = std::clamp(c.r + variation, c.r - 15, c.r + 15);
    c.g = std::clamp(c.g + variation, c.g - 15, c.g + 15);
    c.b = std::clamp(c.b + variation / 2, c.b - 10, c.b + 10);

    return c;
}

Color Cell::GetColour(CellType type) {
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
