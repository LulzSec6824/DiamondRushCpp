#include "Level.h"
#include "AssetManager.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

Level::Level(int levelNumber) : levelNumber(levelNumber), exitReached(false) {
    LoadLevel(levelNumber);
}

void Level::LoadLevel(int levelNumber) {
    this->levelNumber = levelNumber;
    
    // Clear existing level data
    tiles.clear();
    diamonds.clear();
    enemies.clear();
    
    // Try to load level data from file
    std::string levelFile = "level_" + std::to_string(levelNumber) + ".txt";
    
    // Check if AssetManager has the level data
    if (AssetManager::GetInstance().HasLevelData(levelFile)) {
        std::string levelData = AssetManager::GetInstance().GetLevelData(levelFile);
        LoadFromString(levelData);
        return;
    }
    
    // If no level file exists, create a test level based on the level number
    CreateTestLevel(levelNumber);
}

void Level::LoadFromString(const std::string& levelData) {
    std::istringstream stream(levelData);
    std::string line;
    int y = 0;
    
    while (std::getline(stream, line)) {
        for (size_t x = 0; x < line.length(); x++) {
            char tile = line[x];
            float posX = x * TILE_SIZE;
            float posY = y * TILE_SIZE;
            
            switch (tile) {
                case '#': // Wall
                    tiles.push_back(std::make_unique<Tile>(posX, posY, TileType::WALL));
                    break;
                case '=': // Floor
                    tiles.push_back(std::make_unique<Tile>(posX, posY, TileType::FLOOR));
                    break;
                case 'D': // Diamond
                    diamonds.push_back(std::make_unique<Diamond>(posX, posY));
                    break;
                case 'E': // Enemy
                    enemies.push_back(std::make_unique<Enemy>(posX, posY));
                    break;
                case 'X': // Exit
                    exitPosition = {posX, posY};
                    break;
                case 'P': // Player start position
                    playerStartPosition = {posX, posY};
                    break;
            }
        }
        y++;
    }
}

void Level::CreateTestLevel(int levelNumber) {
    // Default player start position
    playerStartPosition = {100, 450};
    
    // Create floor
    for (int x = 0; x < 25; x++) {
        tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 532, TileType::FLOOR));
    }
    
    // Create platforms and obstacles based on level number
    switch (levelNumber) {
        case 1: // Easy level
            // Create some platforms
            for (int x = 5; x < 10; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 400, TileType::FLOOR));
            }
            
            for (int x = 15; x < 20; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 300, TileType::FLOOR));
            }
            
            // Create some walls
            for (int y = 13; y < 17; y++) {
                tiles.push_back(std::make_unique<Tile>(3 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            // Add some diamonds
            diamonds.push_back(std::make_unique<Diamond>(200, 350));
            diamonds.push_back(std::make_unique<Diamond>(500, 480));
            diamonds.push_back(std::make_unique<Diamond>(600, 480));
            diamonds.push_back(std::make_unique<Diamond>(550, 250));
            
            // Set exit position
            exitPosition = {750, 480};
            break;
            
        case 2: // Medium level
            // More complex platforms
            for (int x = 3; x < 8; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 450, TileType::FLOOR));
            }
            
            for (int x = 10; x < 15; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 350, TileType::FLOOR));
            }
            
            for (int x = 17; x < 22; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 250, TileType::FLOOR));
            }
            
            // Walls
            for (int y = 10; y < 14; y++) {
                tiles.push_back(std::make_unique<Tile>(9 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            for (int y = 6; y < 10; y++) {
                tiles.push_back(std::make_unique<Tile>(16 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            // Diamonds
            diamonds.push_back(std::make_unique<Diamond>(6 * TILE_SIZE, 400));
            diamonds.push_back(std::make_unique<Diamond>(12 * TILE_SIZE, 300));
            diamonds.push_back(std::make_unique<Diamond>(19 * TILE_SIZE, 200));
            diamonds.push_back(std::make_unique<Diamond>(22 * TILE_SIZE, 480));
            diamonds.push_back(std::make_unique<Diamond>(3 * TILE_SIZE, 480));
            
            // Add an enemy
            enemies.push_back(std::make_unique<Enemy>(400, 500));
            
            // Set exit position
            exitPosition = {23 * TILE_SIZE, 480};
            break;
            
        case 3: // Hard level
            // Complex layout
            // Platforms
            for (int x = 2; x < 6; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 450, TileType::FLOOR));
            }
            
            for (int x = 8; x < 12; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 380, TileType::FLOOR));
            }
            
            for (int x = 14; x < 18; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 300, TileType::FLOOR));
            }
            
            for (int x = 20; x < 24; x++) {
                tiles.push_back(std::make_unique<Tile>(x * TILE_SIZE, 220, TileType::FLOOR));
            }
            
            // Walls
            for (int y = 10; y < 14; y++) {
                tiles.push_back(std::make_unique<Tile>(7 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            for (int y = 8; y < 12; y++) {
                tiles.push_back(std::make_unique<Tile>(13 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            for (int y = 5; y < 9; y++) {
                tiles.push_back(std::make_unique<Tile>(19 * TILE_SIZE, y * TILE_SIZE, TileType::WALL));
            }
            
            // Diamonds
            diamonds.push_back(std::make_unique<Diamond>(4 * TILE_SIZE, 400));
            diamonds.push_back(std::make_unique<Diamond>(10 * TILE_SIZE, 330));
            diamonds.push_back(std::make_unique<Diamond>(16 * TILE_SIZE, 250));
            diamonds.push_back(std::make_unique<Diamond>(22 * TILE_SIZE, 170));
            diamonds.push_back(std::make_unique<Diamond>(2 * TILE_SIZE, 480));
            diamonds.push_back(std::make_unique<Diamond>(12 * TILE_SIZE, 480));
            diamonds.push_back(std::make_unique<Diamond>(22 * TILE_SIZE, 480));
            
            // Add enemies
            enemies.push_back(std::make_unique<Enemy>(300, 500));
            enemies.push_back(std::make_unique<Enemy>(600, 500));
            
            // Set exit position
            exitPosition = {23 * TILE_SIZE, 170};
            break;
    }
}

void Level::Update(float deltaTime) {
    // Update all tiles
    for (auto& tile : tiles) {
        tile->Update(deltaTime);
    }
    
    // Update all diamonds
    for (auto it = diamonds.begin(); it != diamonds.end();) {
        (*it)->Update(deltaTime);
        if ((*it)->IsCollected()) {
            it = diamonds.erase(it);
        } else {
            ++it;
        }
    }
    
    // Update all enemies
    for (auto& enemy : enemies) {
        enemy->Update(deltaTime);
    }
}

void Level::Draw() {
    // Draw all tiles
    for (auto& tile : tiles) {
        tile->Draw();
    }
    
    // Draw all diamonds
    for (auto& diamond : diamonds) {
        diamond->Draw();
    }
    
    // Draw all enemies
    for (auto& enemy : enemies) {
        enemy->Draw();
    }
    
    // Draw exit
    Color exitColor = diamonds.empty() ? GREEN : RED;
    DrawRectangle(exitPosition.x, exitPosition.y, TILE_SIZE, TILE_SIZE, exitColor);
    
    // Draw debug info
    #ifdef _DEBUG
    DrawText(TextFormat("Level: %d", levelNumber), 10, 10, 20, WHITE);
    DrawText(TextFormat("Diamonds: %d", diamonds.size()), 10, 40, 20, WHITE);
    #endif
}

void Level::CheckCollisions(Player& player) {
    Rectangle playerBounds = player.GetBounds();

    // Check tile collisions
    for (auto& tile : tiles) {
        Rectangle tileBounds = tile->GetBounds();
        
        if (CheckCollisionRecs(playerBounds, tileBounds)) {
            // Determine collision side
            if (tile->GetType() == TileType::FLOOR) {
                // Check if player is above the tile (falling onto it)
                if (player.GetVelocity().y > 0 && 
                    playerBounds.y + playerBounds.height - player.GetVelocity().y <= tileBounds.y) {
                    player.OnCollideWithGround();
                    player.SetPosition({player.GetPosition().x, tileBounds.y - playerBounds.height});
                }
                // Check if player is below the tile (jumping into it)
                else if (player.GetVelocity().y < 0 && 
                         playerBounds.y - player.GetVelocity().y >= tileBounds.y + tileBounds.height) {
                    player.OnCollideWithCeiling();
                    player.SetPosition({player.GetPosition().x, tileBounds.y + tileBounds.height});
                }
            }
            else if (tile->GetType() == TileType::WALL) {
                // Check if player is to the left of the wall
                if (player.GetVelocity().x > 0 && 
                    playerBounds.x + playerBounds.width - player.GetVelocity().x <= tileBounds.x) {
                    player.OnCollideWithWall();
                    player.SetPosition({tileBounds.x - playerBounds.width, player.GetPosition().y});
                }
                // Check if player is to the right of the wall
                else if (player.GetVelocity().x < 0 && 
                         playerBounds.x - player.GetVelocity().x >= tileBounds.x + tileBounds.width) {
                    player.OnCollideWithWall();
                    player.SetPosition({tileBounds.x + tileBounds.width, player.GetPosition().y});
                }
            }
        }
    }
    
    // Check diamond collisions
    for (auto& diamond : diamonds) {
        if (!diamond->IsCollected() && CheckCollisionRecs(playerBounds, diamond->GetBounds())) {
            diamond->Collect();
            player.OnCollideWithDiamond();
        }
    }
    
    // Check enemy collisions
    for (auto& enemy : enemies) {
        if (CheckCollisionRecs(playerBounds, enemy->GetBounds())) {
            player.OnCollideWithEnemy();
        }
    }
    
    // Check exit collision
    Rectangle exitBounds = {exitPosition.x, exitPosition.y, TILE_SIZE, TILE_SIZE};
    if (CheckCollisionRecs(playerBounds, exitBounds)) {
        // Only allow exit if all diamonds are collected
        if (diamonds.empty()) {
            exitReached = true;
            player.OnCollideWithExit();
        }
    }
}

Vector2 Level::GetPlayerStartPosition() const {
    return playerStartPosition;
}

bool Level::IsExitReached() const {
    return exitReached;
}

int Level::GetRemainingDiamonds() const {
    return diamonds.size();
}