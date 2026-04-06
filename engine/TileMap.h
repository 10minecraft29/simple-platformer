#pragma once
#include <vector>

class TileMap {
public:
    int width = 25;
    int height = 18;

    std::vector<int> tiles;

    TileMap() {
        tiles.resize(width * height, 0);

        // Make ground
        for (int x = 0; x < width; x++) {
            tiles[(height - 1) * width + x] = 1;
        }

        // Add a platform
        tiles[(height - 5) * width + 10] = 1;
        tiles[(height - 5) * width + 11] = 1;
        tiles[(height - 5) * width + 12] = 1;
    }

    bool isSolid(int x, int y) {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return false;
        return tiles[y * width + x] == 1;
    }
};
