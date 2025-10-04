#include "Level.h"
#include "AssetManager.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

Level::Level(int levelNumber) : levelNumber(levelNumber), exitReached(false), width(20), height(15) {
    LoadLevel(levelNumber);
}

void Level::LoadLevel(int levelNumber) {
    this->levelNumber = levelNumber;
    
    // Clear existing level data
    tiles.clear();
    diamonds.clear();
    
    // Try to load level data from file
    std::string levelFile = "level_" + std::to_string(levelNumber) + ".txt";
    
    // For now, create a test level
    CreateTestLevel();
}

void Level::CreateTestLevel() {
    // Set dimensions for test level
    width = 20;
    height = 15;
    
    // Initialize tiles with empty spaces
    tiles.resize(width * height, TileType::EMPTY);
    
    // Create walls around the perimeter
    for (int x = 0; x < width; x++) {
        SetTileAt(x, 0, TileType::WALL);
        SetTileAt(x, height-1, TileType::WALL);
    }
    
    for (int y = 0; y < height; y++) {
        SetTileAt(0, y, TileType::WALL);
        SetTileAt(width-1, y, TileType::WALL);
    }
    
    // Add some dirt and platforms
    for (int x = 2; x < width-2; x++) {
        SetTileAt(x, height-3, TileType::DIRT);
    }
    
    // Add some diamonds
    diamonds.push_back(std::make_unique<Diamond>(5 * TILE_SIZE, 10 * TILE_SIZE));
    diamonds.push_back(std::make_unique<Diamond>(10 * TILE_SIZE, 10 * TILE_SIZE));
    diamonds.push_back(std::make_unique<Diamond>(15 * TILE_SIZE, 10 * TILE_SIZE));
    
    // Set player start position
    playerStartPosition = {TILE_SIZE * 2, TILE_SIZE * 10};
    
    // Set exit position
    exitPosition = {TILE_SIZE * (width-3), TILE_SIZE * (height-4)};
    SetTileAt(width-3, height-4, TileType::EXIT);
                    }

TileType Level::GetTileAt(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return TileType::WALL; // Out of bounds is treated as wall
    }
    return tiles[y * width + x];
}

void Level::SetTileAt(int x, int y, TileType type) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return; // Out of bounds
    }
    tiles[y * width + x] = type;
}

void Level::BreakTile(int x, int y) {
    if (GetTileAt(x, y) == TileType::BREAKABLE || GetTileAt(x, y) == TileType::DIRT) {
        SetTileAt(x, y, TileType::EMPTY);
    }
}

void Level::Update() {
    // Update all diamonds
    for (auto& diamond : diamonds) {
        diamond->Update();
    }
}

void Level::Draw() {
    // Draw tiles
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            TileType tile = GetTileAt(x, y);
            float posX = x * TILE_SIZE;
            float posY = y * TILE_SIZE;
            
            Color color;
            switch (tile) {
                case TileType::WALL:
                    color = DARKGRAY;
                    break;
                case TileType::DIRT:
                    color = BROWN;
                    break;
                case TileType::LADDER:
                    color = ORANGE;
                    break;
                case TileType::SPIKES:
                    color = RED;
                    break;
                case TileType::EXIT:
                    color = GREEN;
                    break;
                case TileType::ROCK:
                    color = GRAY;
                    break;
                case TileType::BREAKABLE:
                    color = BEIGE;
                    break;
                default:
                    continue; // Skip empty tiles
            }
            
            DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, color);
        }
    }
    
    // Draw diamonds
    for (auto& diamond : diamonds) {
        diamond->Draw();
    }
}

void Level::CheckCollisions(Player& player) {
    // Check diamond collisions
    for (auto& diamond : diamonds) {
        if (!diamond->IsCollected() && CheckCollisionRecs(player.GetBounds(), diamond->GetBounds())) {
            diamond->Collect();
            player.CollectDiamond();
        }
    }
    
    // Check exit collision
    Rectangle exitRect = {exitPosition.x, exitPosition.y, TILE_SIZE, TILE_SIZE};
    if (CheckCollisionRecs(player.GetBounds(), exitRect) && GetRemainingDiamonds() == 0) {
        exitReached = true;
    }
}

int Level::GetRemainingDiamonds() const {
    int count = 0;
    for (const auto& diamond : diamonds) {
        if (!diamond->IsCollected()) {
            count++;
        }
    }
    return count;
}
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