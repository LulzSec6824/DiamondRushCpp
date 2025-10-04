#pragma once

#include "../raylib/src/raylib.h"

class GameObject {
public:
    GameObject(float x, float y) : position({x, y}) {}
    virtual ~GameObject() = default;
    
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    
    Vector2 GetPosition() const { return position; }
    void SetPosition(Vector2 newPosition) { position = newPosition; }
    
    virtual Rectangle GetBounds() const = 0;
    
protected:
    Vector2 position;
};