#pragma once

#include "raylib.h"
#include "Player.h"
#include "Diamond.h"
#include <vector>
#include <memory>
#include <string>

// Define tile size constant
constexpr int TILE_SIZE = 16;

// Tile types for Diamond Rush
enum class TileType {
    EMPTY,
    WALL,
    DIRT,
    LADDER,
    SPIKES,
    EXIT,
    ROCK,
    BREAKABLE
};

class Level {
public:
    Level(int levelNumber);
    ~Level() = default;
    
    void Update();
    void Draw();
    void CheckCollisions(Player& player);
    
    // Getters
    int GetDiamondCount() const { return diamonds.size(); }
    int GetRemainingDiamonds() const;
    Vector2 GetPlayerStartPosition() const { return playerStartPosition; }
    bool IsExitReached() const { return exitReached; }
    bool IsLevelComplete() const { return GetRemainingDiamonds() == 0 && exitReached; }
    
    // Level manipulation
    TileType GetTileAt(int x, int y) const;
    void SetTileAt(int x, int y, TileType type);
    void BreakTile(int x, int y);
    
private:
    void LoadLevel(int levelNumber);
    void LoadFromFile(const std::string& filename);
    void CreateTestLevel();
    
    int levelNumber;
    int width;
    int height;
    std::vector<TileType> tiles;
    std::vector<std::unique_ptr<Diamond>> diamonds;
    
    Vector2 playerStartPosition;
    Vector2 exitPosition;
    bool exitReached;
};