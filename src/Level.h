#pragma once

#include "../raylib/src/raylib.h"
#include "Player.h"
#include "Tile.h"
#include "Diamond.h"
#include "Enemy.h"
#include <vector>
#include <memory>
#include <string>

// Define tile size constant
constexpr int TILE_SIZE = 32;

class Level {
public:
    Level(int levelNumber);
    ~Level() = default;
    
    void Update(float deltaTime);
    void Draw();
    void CheckCollisions(Player& player);
    
    // Getters
    int GetDiamondCount() const { return diamonds.size(); }
    int GetRemainingDiamonds() const;
    Vector2 GetPlayerStartPosition() const;
    bool IsExitReached() const;
    
private:
    void LoadLevel(int levelNumber);
    void LoadFromString(const std::string& levelData);
    void CreateTestLevel(int levelNumber);
    
    int levelNumber;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Diamond>> diamonds;
    std::vector<std::unique_ptr<Enemy>> enemies;
    
    Vector2 playerStartPosition;
    Vector2 exitPosition;
    bool exitReached;
};