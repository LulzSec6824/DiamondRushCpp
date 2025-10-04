#pragma once

#include "GameObject.h"

enum class TileType {
    EMPTY,
    WALL,
    FLOOR,
    SPIKES,
    DOOR
};

class Tile : public GameObject {
public:
    Tile(float x, float y, TileType type);
    ~Tile() = default;
    
    void Update(float deltaTime) override;
    void Draw() override;
    
    TileType GetType() const { return type; }
    Rectangle GetBounds() const override { return collider; }
    
private:
    TileType type;
    Rectangle collider;
    Color color;
};