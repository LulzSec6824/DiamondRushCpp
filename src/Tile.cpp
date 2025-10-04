#include "Tile.h"

Tile::Tile(float x, float y, TileType type) 
    : GameObject(x, y), type(type) {
    
    // Set up collider
    collider = { x, y, 32, 32 };
    
    // Set color based on tile type
    switch (type) {
        case TileType::WALL:
            color = DARKGRAY;
            break;
        case TileType::FLOOR:
            color = LIGHTGRAY;
            break;
        case TileType::SPIKES:
            color = RED;
            break;
        case TileType::DOOR:
            color = BROWN;
            break;
        default:
            color = BLANK;
            break;
    }
}

void Tile::Update(float deltaTime) {
    // Tiles typically don't have update logic, but we keep it for GameObject interface
}

void Tile::Draw() {
    if (type != TileType::EMPTY) {
        DrawRectangleRec(collider, color);
        DrawRectangleLinesEx(collider, 1, BLACK);
    }
}