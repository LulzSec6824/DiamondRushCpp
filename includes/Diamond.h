#pragma once

#include "raylib.h"

class Diamond {
public:
    Diamond(float x, float y);
    ~Diamond() = default;
    
    void Update();
    void Draw();
    
    bool IsCollected() const { return collected; }
    void Collect() { collected = true; }
    Rectangle GetBounds() const { return collider; }
    Vector2 GetPosition() const { return position; }
    
private:
    Vector2 position;
    bool collected;
    Rectangle collider;
    float animTime;
    int currentFrame;
    float sparkleTime;
};